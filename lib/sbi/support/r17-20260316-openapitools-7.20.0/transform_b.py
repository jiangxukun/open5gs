#!/usr/bin/env python3
import argparse
import shutil
from pathlib import Path

import yaml


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

    # 3) enum values (comments inside enum block are preserved)
    saw_enum_value = False
    while j < len(lines):
        line = lines[j]

        if is_blank(line):
            enum_lines.append(line)
            j += 1
            continue

        # YAML comment lines (possibly at column 0) inside enum block
        stripped_raw = line.strip()
        if stripped_raw.startswith("#"):
            enum_lines.append(line)
            j += 1
            continue

        indent = leading_spaces(line)
        stripped = line.lstrip(" ")

        if indent >= enum_indent and stripped.startswith("- "):
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
# Category E: anyOf whose ALL items resolve to type: string
# ---------------------------------------------------------------------------

def _is_extensible_enum(schema: dict) -> bool:
    """Check if a schema is an extensible enum (anyOf[string+enum, string])."""
    if not isinstance(schema, dict):
        return False
    variants = schema.get("anyOf")
    if not isinstance(variants, list) or len(variants) != 2:
        return False
    return (all(isinstance(v, dict) and v.get("type") == "string" for v in variants)
            and any("enum" in v for v in variants))


def collect_string_schemas(input_dir: Path) -> set:
    """
    First pass: collect (filename, schema_name) pairs where the schema is
    type: string at the top level, OR is an extensible enum
    (anyOf[string+enum, string]).
    """
    string_schemas = set()
    for yaml_file in sorted(input_dir.rglob("*")):
        if not is_yaml_file(yaml_file):
            continue
        with open(yaml_file, "r", encoding="utf-8") as f:
            try:
                doc = yaml.safe_load(f)
            except Exception:
                continue
        if not isinstance(doc, dict):
            continue
        components = doc.get("components")
        if not isinstance(components, dict):
            continue
        schemas = components.get("schemas")
        if not isinstance(schemas, dict):
            continue
        fname = yaml_file.name
        for name, schema in schemas.items():
            if not isinstance(schema, dict):
                continue
            if schema.get("type") == "string":
                string_schemas.add((fname, name))
            elif _is_extensible_enum(schema):
                string_schemas.add((fname, name))
    return string_schemas


def resolve_ref_is_string(ref_str: str, current_filename: str,
                          string_schemas: set) -> bool:
    """Check whether a $ref target is a type: string schema."""
    ref_str = ref_str.strip().strip("'\"")
    if "#" not in ref_str:
        return False
    file_part, path_part = ref_str.split("#", 1)
    parts = path_part.strip("/").split("/")
    if len(parts) >= 3 and parts[0] == "components" and parts[1] == "schemas":
        schema_name = parts[2]
        fname = file_part if file_part else current_filename
        return (fname, schema_name) in string_schemas
    return False


def resolve_ref_is_null_value(ref_str: str) -> bool:
    """Check whether a $ref target is NullValue."""
    ref_str = ref_str.strip().strip("'\"")
    if "#" not in ref_str:
        return False
    _, path_part = ref_str.split("#", 1)
    parts = path_part.strip("/").split("/")
    if len(parts) >= 3 and parts[0] == "components" and parts[1] == "schemas":
        return parts[2] == "NullValue"
    return False


def _is_inline_extensible_enum(item_lines):
    """
    Check if an anyOf item is an inline extensible enum:
        - anyOf:
            - type: string
              enum:
                - VALUE
            - type: string

    Returns the enum value lines (reindentable) if matched, None otherwise.
    """
    if not item_lines:
        return None
    first = item_lines[0].strip()
    if first != "- anyOf:":
        return None

    # Parse the inner sub-items
    rest = item_lines[1:]
    sub_items = []
    current_sub = None
    sub_base_indent = None

    for line in rest:
        if is_blank(line):
            if current_sub is not None:
                current_sub.append(line)
            continue
        indent = leading_spaces(line)
        stripped = line.lstrip()
        if stripped.startswith("- "):
            if sub_base_indent is None:
                sub_base_indent = indent
            if indent == sub_base_indent:
                if current_sub is not None:
                    sub_items.append(current_sub)
                current_sub = [line]
                continue
        if current_sub is not None:
            current_sub.append(line)

    if current_sub is not None:
        sub_items.append(current_sub)

    if len(sub_items) != 2:
        return None

    # One sub-item must be "- type: string" with enum, the other plain
    enum_sub = None
    plain_sub = None
    for sub in sub_items:
        first_sub = sub[0].strip()
        if first_sub == "- type: string" and len(sub) == 1:
            plain_sub = sub
        elif first_sub == "- type: string" and len(sub) > 1:
            has_enum = any(l.strip() == "enum:" or l.strip().startswith("enum:")
                          for l in sub[1:])
            if has_enum:
                enum_sub = sub
            else:
                return None
        else:
            return None

    if enum_sub is None or plain_sub is None:
        return None

    # Extract enum: header and values from enum_sub
    enum_lines = []
    in_enum = False
    enum_indent = None
    for line in enum_sub[1:]:  # skip "- type: string"
        stripped = line.strip()
        if not in_enum:
            if stripped == "enum:" or stripped.startswith("enum:"):
                in_enum = True
                enum_lines.append(line)
                enum_indent = leading_spaces(line)
                continue
        else:
            if is_blank(line):
                enum_lines.append(line)
                continue
            if stripped.startswith("#"):
                enum_lines.append(line)
                continue
            indent = leading_spaces(line)
            if indent >= enum_indent and stripped.startswith("- "):
                enum_lines.append(line)
                continue
            break

    return enum_lines if enum_lines else None


def try_transform_category_e(lines, start_idx, string_schemas,
                             current_file, eol="\n"):
    """
    Category E — anyOf where items are a mix of:
      - type: string schemas ($ref or inline)
      - NullValue ($ref — 3GPP's nullable pattern)
      - inline extensible enums (- anyOf: with enum+string sub-items)

    At least one non-NullValue item must exist.
    The first non-NullValue item is promoted; everything else is commented out.
    """
    if lines[start_idx].strip() != "anyOf:":
        return None

    anyof_line = lines[start_idx]
    anyof_indent = leading_spaces(anyof_line)
    j = start_idx + 1

    # Detect compact style: first non-blank line starts with "- " at anyof_indent
    peek = j
    while peek < len(lines) and is_blank(lines[peek]):
        peek += 1
    compact = (peek < len(lines)
               and leading_spaces(lines[peek]) == anyof_indent
               and lines[peek].lstrip().startswith("- "))

    # Collect entire anyOf body
    body_start = j
    while j < len(lines):
        if is_blank(lines[j]):
            j += 1
            continue
        indent = leading_spaces(lines[j])
        stripped = lines[j].lstrip()
        if compact:
            # In compact style, items start at anyof_indent with "- "
            # Body continues while: deeper than anyof_indent, OR at anyof_indent with "- "
            if indent > anyof_indent:
                j += 1
                continue
            if indent == anyof_indent and stripped.startswith("- "):
                j += 1
                continue
            break  # sibling key at same indent (e.g. description:)
        else:
            if indent <= anyof_indent:
                break
            j += 1
    body_end = j
    body_lines = lines[body_start:body_end]

    # Parse items — new item starts at the same indent as the first "- "
    items = []          # list of list-of-lines
    current_item = None
    item_base_indent = None

    for line in body_lines:
        if is_blank(line):
            if current_item is not None:
                current_item.append(line)
            continue

        indent = leading_spaces(line)
        stripped = line.lstrip()

        if stripped.startswith("- "):
            if item_base_indent is None:
                item_base_indent = indent
            if indent == item_base_indent:
                if current_item is not None:
                    items.append(current_item)
                current_item = [line]
                continue
        if current_item is not None:
            current_item.append(line)

    if current_item is not None:
        items.append(current_item)

    if len(items) < 2:
        return None

    # Classify each item
    ITEM_STRING = "string"
    ITEM_NULL = "null"
    ITEM_INLINE_ENUM = "inline_enum"
    ITEM_DIRECT_ENUM = "direct_enum"   # - type: string + enum: [...]

    item_types = []
    promote_idx = None

    for idx, item in enumerate(items):
        first = item[0].strip()

        if first.startswith("- $ref:"):
            ref_val = first.removeprefix("- $ref:").strip()
            if resolve_ref_is_null_value(ref_val):
                item_types.append(ITEM_NULL)
                continue
            if resolve_ref_is_string(ref_val, current_file, string_schemas):
                item_types.append(ITEM_STRING)
                if promote_idx is None:
                    promote_idx = idx
                continue
            return None

        elif first == "- type: string":
            # Check if this item has an enum: block
            has_enum = False
            if len(item) > 1:
                for sub_line in item[1:]:
                    s = sub_line.strip()
                    if s == "enum:" or s.startswith("enum:"):
                        has_enum = True
                        break
            if has_enum:
                item_types.append(ITEM_DIRECT_ENUM)
                if promote_idx is None:
                    promote_idx = idx
            else:
                item_types.append(ITEM_STRING)
                # Only set promote_idx if no better candidate yet
                if promote_idx is None:
                    promote_idx = idx
            continue

        elif first == "- anyOf:":
            enum_lines = _is_inline_extensible_enum(item)
            if enum_lines is not None:
                item_types.append(ITEM_INLINE_ENUM)
                if promote_idx is None:
                    promote_idx = idx
                continue
            return None

        else:
            return None

    # Must have at least one promotable item
    if promote_idx is None:
        return None

    # Prefer DIRECT_ENUM or INLINE_ENUM over plain STRING for promotion
    for idx, itype in enumerate(item_types):
        if itype in (ITEM_DIRECT_ENUM, ITEM_INLINE_ENUM):
            promote_idx = idx
            break

    # Build output
    out = []
    promote_type = item_types[promote_idx]
    promote_item = items[promote_idx]

    if promote_type == ITEM_STRING:
        promote_stripped = promote_item[0].strip()
        if promote_stripped.startswith("- $ref:"):
            ref_val = promote_stripped.removeprefix("- $ref:").strip()
            out.append(" " * anyof_indent + "$ref: " + ref_val + eol)
        else:
            out.append(" " * anyof_indent + "type: string" + eol)

    elif promote_type == ITEM_DIRECT_ENUM:
        # Extract enum: block from the item
        out.append(" " * anyof_indent + "type: string" + eol)
        enum_lines_extracted = []
        in_enum = False
        enum_indent_local = None
        for sub_line in promote_item[1:]:  # skip "- type: string"
            s = sub_line.strip()
            if not in_enum:
                if s == "enum:" or s.startswith("enum:"):
                    in_enum = True
                    enum_lines_extracted.append(sub_line)
                    enum_indent_local = leading_spaces(sub_line)
                continue
            # inside enum block
            if is_blank(sub_line):
                enum_lines_extracted.append(sub_line)
                continue
            if s.startswith("#"):
                enum_lines_extracted.append(sub_line)
                continue
            indent = leading_spaces(sub_line)
            if indent >= enum_indent_local and s.startswith("- "):
                enum_lines_extracted.append(sub_line)
                continue
            break  # end of enum block
        reindented = reindent_block(enum_lines_extracted, anyof_indent)
        out.extend(reindented)

    elif promote_type == ITEM_INLINE_ENUM:
        enum_lines = _is_inline_extensible_enum(promote_item)
        out.append(" " * anyof_indent + "type: string" + eol)
        reindented = reindent_block(enum_lines, anyof_indent)
        out.extend(reindented)

    # Comment out original anyOf block
    out.append(comment_exact(anyof_line))
    for line in lines[body_start:body_end]:
        out.append(comment_exact(line))

    return out, body_end


# ---------------------------------------------------------------------------
# Main transform pass (A/B/D/E)
# ---------------------------------------------------------------------------

def transform_lines(lines, string_schemas=None, current_file=""):
    eol = detect_eol(lines)
    out = []
    i = 0
    changed_b = changed_d = changed_allof = changed_e = 0

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
            # B: anyOf[enum + string]  (try first — more specific)
            transformed = try_transform_category_b(lines, i)
            if transformed is not None:
                new_lines, next_i = transformed
                out.extend(new_lines)
                i = next_i
                changed_b += 1
                continue

            # E: anyOf where all items are type: string
            if string_schemas is not None:
                transformed = try_transform_category_e(
                    lines, i, string_schemas, current_file, eol=eol)
                if transformed is not None:
                    new_lines, next_i = transformed
                    out.extend(new_lines)
                    i = next_i
                    changed_e += 1
                    continue

        out.append(lines[i])
        i += 1

    return out, changed_b, changed_d, changed_allof, changed_e


# ---------------------------------------------------------------------------
# File processing
# ---------------------------------------------------------------------------

def process_yaml_file(in_file: Path, out_file: Path,
                      string_schemas: set = None):
    with open(in_file, "r", encoding="utf-8", newline="") as f:
        original_text = f.read()

    lines = split_lines_preserve_exact(original_text)
    new_lines, cb, cd, ca, ce = transform_lines(
        lines, string_schemas=string_schemas, current_file=in_file.name)
    new_text = "".join(new_lines)

    out_file.parent.mkdir(parents=True, exist_ok=True)
    with open(out_file, "w", encoding="utf-8", newline="") as f:
        f.write(new_text)

    return cb, cd, ca, ce


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

    # ---- 1st pass: collect type: string schemas across all YAML files ----
    string_schemas = collect_string_schemas(input_dir)
    print(f"Collected {len(string_schemas)} string-type schemas")

    # ---- 2nd pass: transform ----
    total_yaml = 0
    total_b = total_d = total_allof = total_e = 0

    for in_file in sorted(input_dir.rglob("*")):
        if in_file.is_dir():
            continue
        rel = in_file.relative_to(input_dir)
        out_file = output_dir / rel

        if is_yaml_file(in_file):
            total_yaml += 1
            cb, cd, ca, ce = process_yaml_file(
                in_file, out_file, string_schemas=string_schemas)
            total_b += cb
            total_d += cd
            total_allof += ca
            total_e += ce
            print(f"[YAML] {rel} (b={cb}, d={cd}, allof={ca}, e={ce})")
        else:
            copy_other_file(in_file, out_file)
            print(f"[COPY] {rel}")

    print()
    print(f"Processed YAML files   : {total_yaml}")
    print(f"Changed B blocks       : {total_b}")
    print(f"Changed D blocks       : {total_d}")
    print(f"Changed allOf blocks   : {total_allof}")
    print(f"Changed E blocks       : {total_e}")



if __name__ == "__main__":
    main()

