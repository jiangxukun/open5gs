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
    out = []
    out.append(comment_exact(anyof_line))
    out.append(comment_exact(first_head))

    reindented_enum_lines = reindent_block(enum_lines, anyof_indent)
    for line in reindented_enum_lines:
        out.append(line)

    out.append(comment_exact(second_head))
    for line in second_tail:
        out.append(comment_exact(line))

    for line in sibling_desc:
        out.append(comment_exact(line))

    return out, j


def transform_lines(lines):
    out = []
    i = 0
    changed_b_blocks = 0
    changed_allof_blocks = 0

    while i < len(lines):
        transformed = try_transform_allof_patterns(lines, i)
        if transformed is not None:
            new_lines, next_i = transformed
            out.extend(new_lines)
            i = next_i
            changed_allof_blocks += 1
            continue

        if lines[i].strip() == "anyOf:":
            transformed = try_transform_category_b(lines, i)
            if transformed is not None:
                new_lines, next_i = transformed
                out.extend(new_lines)
                i = next_i
                changed_b_blocks += 1
                continue

        out.append(lines[i])
        i += 1

    return out, changed_b_blocks, changed_allof_blocks


def process_yaml_file(in_file: Path, out_file: Path):
    with open(in_file, "r", encoding="utf-8", newline="") as f:
        original_text = f.read()

    lines = split_lines_preserve_exact(original_text)
    new_lines, changed_b_blocks, changed_allof_blocks = transform_lines(lines)
    new_text = "".join(new_lines)

    out_file.parent.mkdir(parents=True, exist_ok=True)
    with open(out_file, "w", encoding="utf-8", newline="") as f:
        f.write(new_text)

    return changed_b_blocks, changed_allof_blocks


def copy_other_file(in_file: Path, out_file: Path):
    out_file.parent.mkdir(parents=True, exist_ok=True)
    shutil.copy2(in_file, out_file)


def main():
    parser = argparse.ArgumentParser(
        description=(
            "Apply YAML transformations "
            "(allOf(pattern) comment-out + category B anyOf(enum,string) transform) "
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
    total_changed_b_blocks = 0
    total_changed_allof_blocks = 0

    for in_file in sorted(input_dir.rglob("*")):
        if in_file.is_dir():
            continue

        rel = in_file.relative_to(input_dir)
        out_file = output_dir / rel

        if is_yaml_file(in_file):
            total_yaml += 1
            changed_b_blocks, changed_allof_blocks = process_yaml_file(
                in_file, out_file
            )
            total_changed_b_blocks += changed_b_blocks
            total_changed_allof_blocks += changed_allof_blocks
            print(
                f"[YAML] {rel} "
                f"(changed_b_blocks={changed_b_blocks}, "
                f"changed_allof_blocks={changed_allof_blocks})"
            )
        else:
            copy_other_file(in_file, out_file)
            print(f"[COPY] {rel}")

    print()
    print(f"Processed YAML files   : {total_yaml}")
    print(f"Changed B blocks       : {total_changed_b_blocks}")
    print(f"Changed allOf blocks   : {total_changed_allof_blocks}")


if __name__ == "__main__":
    main()
