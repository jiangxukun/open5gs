#!/usr/bin/env python3
import argparse
import shutil
from pathlib import Path


def is_yaml_file(path: Path) -> bool:
    return path.suffix.lower() in {".yaml", ".yml"}


def leading_spaces(line: str) -> int:
    return len(line) - len(line.lstrip(" "))


def is_blank(line: str) -> bool:
    return line.strip("\r\n").strip() == ""


def comment_exact(line: str) -> str:
    return "#" + line


def split_lines_preserve_exact(text: str):
    # Keep original line endings exactly.
    return text.splitlines(keepends=True)


def reindent_block(block_lines, new_base_indent):
    """
    Reindent a block so that its first non-blank line starts at new_base_indent.
    Relative indentation inside the block is preserved.
    """
    first_nonblank = None
    for line in block_lines:
        if line.strip():
            first_nonblank = line
            break

    if first_nonblank is None:
        return block_lines[:]

    old_base_indent = leading_spaces(first_nonblank)
    delta = old_base_indent - new_base_indent

    out = []
    for line in block_lines:
        if not line.strip():
            out.append(line)
            continue

        indent = leading_spaces(line)
        new_indent = max(0, indent - delta)
        out.append(" " * new_indent + line.lstrip(" "))
    return out


def try_transform_allof_patterns(lines, start_idx):
    """
    Transform this form:

      type: string
      allOf:
        - pattern: ...
        - pattern: ...
      example: ...

    into:

      type: string
    #      allOf:
    #        - pattern: ...
    #        - pattern: ...
      example: ...

    Returns:
      (new_lines, next_idx) if matched
      None otherwise
    """
    if lines[start_idx].strip() != "type: string":
        return None

    type_line = lines[start_idx]
    type_indent = leading_spaces(type_line)
    j = start_idx + 1

    # optional blank lines are allowed but uncommon
    while j < len(lines) and is_blank(lines[j]):
        return None

    if j >= len(lines) or lines[j].strip() != "allOf:":
        return None

    allof_indent = leading_spaces(lines[j])
    if allof_indent != type_indent:
        return None

    block = [lines[j]]
    j += 1

    saw_pattern = False
    while j < len(lines):
        line = lines[j]

        if is_blank(line):
            block.append(line)
            j += 1
            continue

        indent = leading_spaces(line)
        stripped = line.lstrip(" ")

        if indent > allof_indent and stripped.startswith("- pattern:"):
            block.append(line)
            saw_pattern = True
            j += 1
            continue

        break

    if not saw_pattern:
        return None

    out = [type_line]
    for line in block:
        out.append(comment_exact(line))

    return out, j


def try_transform_category_b(lines, start_idx):
    """
    Match category B only.

    Supported forms:

      anyOf:
        - type: string
          enum:
            - ...
        - type: string
      description: ...

    and also:

      anyOf:
      - type: string
        enum:
          - ...
      - type: string
        description: >
          ...
      description: |
        ...

    Return:
      (new_lines, next_idx) if matched
      None otherwise
    """
    if lines[start_idx].strip() != "anyOf:":
        return None

    anyof_line = lines[start_idx]
    anyof_indent = leading_spaces(anyof_line)
    j = start_idx + 1

    # 1) first item head: allow indent >= anyOf indent
    if j >= len(lines) or lines[j].strip() != "- type: string":
        return None
    first_head = lines[j]
    first_indent = leading_spaces(first_head)
    if first_indent < anyof_indent:
        return None
    j += 1

    # 2) enum header
    while j < len(lines) and is_blank(lines[j]):
        return None

    if j >= len(lines) or lines[j].strip() != "enum:":
        return None

    enum_lines = [lines[j]]
    enum_indent = leading_spaces(lines[j])
    j += 1

    # 3) enum values
    saw_enum_value = False
    while j < len(lines):
        line = lines[j]

        if is_blank(line):
            enum_lines.append(line)
            j += 1
            continue

        indent = leading_spaces(line)
        stripped = line.lstrip(" ")

        if indent > enum_indent and stripped.startswith("- "):
            enum_lines.append(line)
            saw_enum_value = True
            j += 1
            continue

        break

    if not saw_enum_value:
        return None

    # 4) second item head
    if j >= len(lines) or lines[j].strip() != "- type: string":
        return None
    second_head = lines[j]
    second_indent = leading_spaces(second_head)
    if second_indent < anyof_indent:
        return None
    j += 1

    # 5) second item tail: nested description block etc.
    second_tail = []
    while j < len(lines):
        line = lines[j]

        if is_blank(line):
            second_tail.append(line)
            j += 1
            continue

        if leading_spaces(line) > second_indent:
            second_tail.append(line)
            j += 1
            continue

        break

    # 6) sibling description block after anyOf
    sibling_desc = []
    if j < len(lines) and lines[j].strip().startswith("description:"):
        desc_indent = leading_spaces(lines[j])

        if desc_indent == anyof_indent:
            sibling_desc.append(lines[j])
            j += 1

            while j < len(lines):
                line = lines[j]

                if is_blank(line):
                    sibling_desc.append(line)
                    j += 1
                    continue

                if leading_spaces(line) > desc_indent:
                    sibling_desc.append(line)
                    j += 1
                    continue

                break

    # 7) build transformed output
    eol = "\r\n" if anyof_line.endswith("\r\n") else "\n"
    out = []
    out.append(comment_exact(anyof_line))
    out.append(comment_exact(first_head))

    # type: string 삽입 — 제너레이터가 string enum으로 정확히 분류하고
    # collect_string_enums가 수집할 수 있도록
    out.append(" " * anyof_indent + "type: string" + eol)

    reindented_enum_lines = reindent_block(enum_lines, anyof_indent)
    for line in reindented_enum_lines:
        out.append(line)

    out.append(comment_exact(second_head))
    for line in second_tail:
        out.append(comment_exact(line))

    for line in sibling_desc:
        out.append(comment_exact(line))

    return out, j


def detect_eol(lines):
    """Detect line ending style. Returns '\r\n' or '\n'."""
    for line in lines:
        if line.endswith("\r\n"):
            return "\r\n"
        if line.endswith("\n"):
            return "\n"
    return "\n"


# ---------------------------------------------------------------------------
# Category D: allOf whose first item is $ref, rest are not/properties/required
# ---------------------------------------------------------------------------

def try_transform_category_d(lines, start_idx, eol="\n"):
    if lines[start_idx].strip() != "allOf:":
        return None

    allof_line = lines[start_idx]
    allof_indent = leading_spaces(allof_line)
    j = start_idx + 1

    while j < len(lines) and is_blank(lines[j]):
        j += 1
    if j >= len(lines) or leading_spaces(lines[j]) <= allof_indent:
        return None
    if not lines[j].lstrip().startswith("- $ref:"):
        return None

    first_line = lines[j]
    ref_value = first_line.lstrip().removeprefix("- $ref:").strip()
    j += 1

    rest_lines = []
    while j < len(lines):
        line = lines[j]
        if is_blank(line):
            rest_lines.append(line)
            j += 1
            continue
        indent = leading_spaces(line)
        if indent <= allof_indent:
            break
        stripped = line.lstrip()
        if indent == allof_indent + 2 and stripped.startswith("- "):
            allowed = ("- not:", "- properties:", "- required:")
            if not any(stripped.startswith(a) for a in allowed):
                return None
        rest_lines.append(line)
        j += 1

    while rest_lines and is_blank(rest_lines[-1]):
        rest_lines.pop()

    out = []
    out.append(" " * allof_indent + "$ref: " + ref_value + eol)
    out.append(comment_exact(allof_line))
    out.append(comment_exact(first_line))
    for line in rest_lines:
        out.append(comment_exact(line))
    return out, j


# ---------------------------------------------------------------------------
# Main transform pass (A/B/C/D)
# ---------------------------------------------------------------------------

def transform_lines(lines):
    eol = detect_eol(lines)
    out = []
    i = 0
    changed_b = changed_d = changed_allof = 0

    while i < len(lines):
        # A: type:string + allOf(pattern only)
        transformed = try_transform_allof_patterns(lines, i)
        if transformed is not None:
            new_lines, next_i = transformed
            out.extend(new_lines)
            i = next_i
            changed_allof += 1
            continue

        if lines[i].strip() == "allOf:":
            # D: allOf[$ref + not/properties]
            transformed = try_transform_category_d(lines, i, eol=eol)
            if transformed is not None:
                new_lines, next_i = transformed
                out.extend(new_lines)
                i = next_i
                changed_d += 1
                continue

        if lines[i].strip() == "anyOf:":
            # B: anyOf[enum + string]
            transformed = try_transform_category_b(lines, i)
            if transformed is not None:
                new_lines, next_i = transformed
                out.extend(new_lines)
                i = next_i
                changed_b += 1
                continue

        out.append(lines[i])
        i += 1

    return out, changed_b, changed_d, changed_allof


# ---------------------------------------------------------------------------
# File processing
# ---------------------------------------------------------------------------

def process_yaml_file(in_file: Path, out_file: Path):
    with open(in_file, "r", encoding="utf-8", newline="") as f:
        original_text = f.read()

    lines = split_lines_preserve_exact(original_text)
    new_lines, cb, cd, ca = transform_lines(lines)
    new_text = "".join(new_lines)

    out_file.parent.mkdir(parents=True, exist_ok=True)
    with open(out_file, "w", encoding="utf-8", newline="") as f:
        f.write(new_text)

    return cb, cd, ca


def copy_other_file(in_file: Path, out_file: Path):
    out_file.parent.mkdir(parents=True, exist_ok=True)
    shutil.copy2(in_file, out_file)


def main():
    parser = argparse.ArgumentParser(
        description=(
            "Apply YAML transformations (A/B/C/D) "
            "from input_dir to output_dir."
        )
    )
    parser.add_argument("input_dir", help="Input directory, e.g. standard")
    parser.add_argument("output_dir", help="Output directory, e.g. modified")
    parser.add_argument(
        "--clean-output",
        action="store_true",
        help="Delete output_dir first",
    )
    args = parser.parse_args()

    input_dir = Path(args.input_dir).resolve()
    output_dir = Path(args.output_dir).resolve()

    if not input_dir.is_dir():
        raise SystemExit(f"Input directory does not exist: {input_dir}")
    if input_dir == output_dir:
        raise SystemExit("input_dir and output_dir must be different")
    if args.clean_output and output_dir.exists():
        shutil.rmtree(output_dir)

    output_dir.mkdir(parents=True, exist_ok=True)

    total_yaml = 0
    total_b = total_d = total_allof = 0

    for in_file in sorted(input_dir.rglob("*")):
        if in_file.is_dir():
            continue
        rel = in_file.relative_to(input_dir)
        out_file = output_dir / rel

        if is_yaml_file(in_file):
            total_yaml += 1
            cb, cd, ca = process_yaml_file(in_file, out_file)
            total_b += cb
            total_d += cd
            total_allof += ca
            print(f"[YAML] {rel} (b={cb}, d={cd}, allof={ca})")
        else:
            copy_other_file(in_file, out_file)
            print(f"[COPY] {rel}")

    print()
    print(f"Processed YAML files   : {total_yaml}")
    print(f"Changed B blocks       : {total_b}")
    print(f"Changed D blocks       : {total_d}")
    print(f"Changed allOf blocks   : {total_allof}")



if __name__ == "__main__":
    main()

