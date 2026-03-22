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


def collect_indented_block(lines, start_idx):
    """
    Generic YAML block collector:
    include following blank lines and lines more indented than the first line.
    """
    base_indent = leading_spaces(lines[start_idx])
    block = [lines[start_idx]]
    i = start_idx + 1

    while i < len(lines):
        line = lines[i]

        if is_blank(line):
            block.append(line)
            i += 1
            continue

        if leading_spaces(line) <= base_indent:
            break

        block.append(line)
        i += 1

    return block, i


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
        # category B in these files doesn't place blank lines here
        # but if it does, it's not a supported match
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

        # must be sibling of anyOf block, not less-indented outer content
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

    for line in enum_lines:
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
    changed_blocks = 0

    while i < len(lines):
        if lines[i].strip() == "anyOf:":
            transformed = try_transform_category_b(lines, i)
            if transformed is not None:
                new_lines, next_i = transformed
                out.extend(new_lines)
                i = next_i
                changed_blocks += 1
                continue

        out.append(lines[i])
        i += 1

    return out, changed_blocks


def process_yaml_file(in_file: Path, out_file: Path):
    with open(in_file, "r", encoding="utf-8", newline="") as f:
        original_text = f.read()

    lines = split_lines_preserve_exact(original_text)
    new_lines, changed_blocks = transform_lines(lines)
    new_text = "".join(new_lines)

    out_file.parent.mkdir(parents=True, exist_ok=True)
    with open(out_file, "w", encoding="utf-8", newline="") as f:
        f.write(new_text)

    return changed_blocks


def copy_other_file(in_file: Path, out_file: Path):
    out_file.parent.mkdir(parents=True, exist_ok=True)
    shutil.copy2(in_file, out_file)


def main():
    parser = argparse.ArgumentParser(
        description=(
            "Apply category B transformation only "
            "(anyOf(enum,string) -> modified-style comments) "
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
    total_changed_blocks = 0

    for in_file in sorted(input_dir.rglob("*")):
        if in_file.is_dir():
            continue

        rel = in_file.relative_to(input_dir)
        out_file = output_dir / rel

        if is_yaml_file(in_file):
            total_yaml += 1
            changed_blocks = process_yaml_file(in_file, out_file)
            total_changed_blocks += changed_blocks
            print(f"[YAML] {rel} (changed_blocks={changed_blocks})")
        else:
            copy_other_file(in_file, out_file)
            print(f"[COPY] {rel}")

    print()
    print(f"Processed YAML files : {total_yaml}")
    print(f"Changed B blocks     : {total_changed_blocks}")


if __name__ == "__main__":
    main()
