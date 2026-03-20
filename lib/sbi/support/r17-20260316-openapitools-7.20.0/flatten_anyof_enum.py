#!/usr/bin/env python3
"""
Preprocessing script that flattens anyOf extensible enum patterns in Rel-17 YAML
into simple enums compatible with Rel-15/16 and openapi-generator 7.x C generator.

Input pattern:
  NfType:
    anyOf:
      - type: string
        enum: [NRF, UDM, AMF, ...]
      - type: string          <- catch-all for unknown/future values

Output pattern:
  NfType:
    type: string
    enum: [NRF, UDM, AMF, ...]

Effect:
  - openapi-generator treats NfType as enum instead of model
  - isEnumRef = true is set on referencing properties
  - Fields like nf_profile->nf_type remain OpenAPI_nf_type_e (no pointer indirection)
  - No changes to handwritten code required

Usage:
  # Process all YAML files in a directory (in-place)
  python3 flatten_anyof_enum.py modified/

  # Process a single file
  python3 flatten_anyof_enum.py input.yaml output.yaml

  # Dry-run: show what would be changed without modifying files
  python3 flatten_anyof_enum.py modified/ --dry-run
"""

import re
import sys
from pathlib import Path

try:
    import yaml
except ImportError:
    print("ERROR: pyyaml required → pip install pyyaml")
    sys.exit(1)


# ── YAML output configuration ───────────────────────────────────

class _Dumper(yaml.Dumper):
    pass

def _str_repr(dumper, data):
    if '\n' in data:
        return dumper.represent_scalar('tag:yaml.org,2002:str', data, style='|')
    return dumper.represent_scalar('tag:yaml.org,2002:str', data)

_Dumper.add_representer(str, _str_repr)


# ── Pre-fix: repair known YAML syntax issues in 3GPP spec files ─

def _prefix_text(text):
    """
    Fix syntax issues found in some 3GPP YAML files that cause pyyaml
    to fail before we can even parse the structure.

    Two known issues:
      1. Column-0 comments embedded inside indented block sequences.
         pyyaml strict parser treats these as terminating the block,
         causing 'expected <block end>' errors.
         Fix: replace column-0 comment lines with a blank line.

      2. Off-by-one indentation on a '- type: string' catch-all entry
         inside an anyOf block (e.g. 9 spaces instead of 8).
         Fix: normalise odd-indented '- type: string' lines by removing
         one leading space.
    """
    lines = text.splitlines(keepends=True)
    fixed = []
    for line in lines:
        # Fix 1: column-0 comment → blank line
        if line.startswith('#'):
            fixed.append('\n')
            continue
        # Fix 2: odd-indented anyOf catch-all "- type: string"
        m = re.match(r'^( +)- type: string\s*$', line)
        if m and len(m.group(1)) % 2 != 0:
            line = ' ' * (len(m.group(1)) - 1) + '- type: string\n'
        fixed.append(line)
    return ''.join(fixed)


# ── Core conversion logic ────────────────────────────────────────

def _is_extensible_enum(schema):
    """
    Detect the anyOf extensible enum pattern:
      anyOf: [{type: string, enum: [...]}, {type: string}]
    Conditions:
      1. schema must have an 'anyOf' key
      2. all items must be type: string
      3. at least one item must have an enum list
    """
    if not isinstance(schema, dict) or 'anyOf' not in schema:
        return False
    items = schema['anyOf']
    if not isinstance(items, list) or len(items) < 2:
        return False
    all_strings = all(
        isinstance(i, dict) and i.get('type') == 'string'
        for i in items
    )
    has_enum = any('enum' in i for i in items)
    return all_strings and has_enum


def _flatten(schema):
    """Recursively traverse the schema and flatten all extensible enums."""
    if isinstance(schema, dict):
        if _is_extensible_enum(schema):
            # Collect enum values (deduplicated, order preserved)
            enum_values = []
            for item in schema['anyOf']:
                for v in item.get('enum', []):
                    if v not in enum_values:
                        enum_values.append(v)
            # Replace anyOf with type/enum; preserve other keys
            # (e.g. description, nullable, x-* extensions)
            result = {k: v for k, v in schema.items() if k != 'anyOf'}
            result['type'] = 'string'
            result['enum'] = enum_values
            return result
        else:
            return {k: _flatten(v) for k, v in schema.items()}
    elif isinstance(schema, list):
        return [_flatten(item) for item in schema]
    else:
        return schema


def _count(schema, n=0):
    if isinstance(schema, dict):
        if _is_extensible_enum(schema):
            n += 1
        for v in schema.values():
            n = _count(v, n)
    elif isinstance(schema, list):
        for item in schema:
            n = _count(item, n)
    return n


# ── File processing ──────────────────────────────────────────────

def process_file(src, dst, dry_run=False):
    text = src.read_text(encoding='utf-8')

    # First attempt: parse as-is
    try:
        spec = yaml.safe_load(text)
    except yaml.YAMLError:
        # Second attempt: apply pre-fixes for known 3GPP YAML quirks
        text = _prefix_text(text)
        try:
            spec = yaml.safe_load(text)
        except yaml.YAMLError as e:
            print(f"  WARN: {src.name} parse error — {e}")
            return 0

    if not isinstance(spec, dict):
        return 0

    n = _count(spec)
    if n == 0:
        return 0

    if not dry_run:
        converted = _flatten(spec)
        with open(dst, 'w', encoding='utf-8') as f:
            yaml.dump(converted, f,
                      Dumper=_Dumper,
                      allow_unicode=True,
                      sort_keys=False,
                      default_flow_style=False)
    return n


# ── Entry point ──────────────────────────────────────────────────

def main():
    args = [a for a in sys.argv[1:] if not a.startswith('--')]
    dry_run = '--dry-run' in sys.argv

    if not args:
        print(__doc__)
        sys.exit(1)

    target = Path(args[0])

    if target.is_dir():
        yaml_files = sorted(target.glob('*.yaml'))
        if not yaml_files:
            print(f"No .yaml files in {target}")
            sys.exit(1)

        total_files = total_enums = 0
        for f in yaml_files:
            n = process_file(f, f, dry_run=dry_run)
            if n > 0:
                prefix = "[dry-run] " if dry_run else ""
                print(f"  {prefix}{f.name}: {n} anyOf enum(s) flattened")
                total_files += 1
                total_enums += n

        action = "would be modified" if dry_run else "modified"
        print(f"\nDone: {total_files} files {action}, "
              f"{total_enums} anyOf enums flattened total.")

    elif target.is_file():
        if len(args) < 2:
            print("Usage: flatten_anyof_enum.py input.yaml output.yaml")
            sys.exit(1)
        n = process_file(target, Path(args[1]), dry_run=dry_run)
        prefix = "[dry-run] " if dry_run else ""
        print(f"{prefix}Done: {n} anyOf enum(s) flattened → {args[1]}")

    else:
        print(f"Error: '{target}' not found")
        sys.exit(1)


if __name__ == '__main__':
    main()
