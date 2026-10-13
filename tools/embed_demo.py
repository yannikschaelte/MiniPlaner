#!/usr/bin/env python3
"""Embed the demo data directory into a C++ source file.

Usage: embed_demo.py --list DIR          print the files below DIR
       embed_demo.py DIR OUTPUT.cpp      generate the source (see src/DemoData.h)
"""
import sys
from pathlib import Path


def files(root):
    return sorted(p for p in Path(root).rglob('*') if p.is_file())


def generate(root, out):
    root = Path(root)
    lines = ['#include "DemoData.h"', '']
    entries = []
    for i, path in enumerate(files(root)):
        data = path.read_bytes()
        body = ','.join(str(b) for b in data)
        lines.append(f'static const unsigned char file{i}[] = {{{body}}};')
        entries.append(f'\t{{"{path.relative_to(root).as_posix()}", file{i}, {len(data)}}}')
    lines += ['', 'const DemoFile DEMO_FILES[] = {', ',\n'.join(entries), '};',
              f'const unsigned DEMO_FILE_COUNT = {len(entries)};', '']
    Path(out).write_text('\n'.join(lines))


if __name__ == '__main__':
    if sys.argv[1] == '--list':
        print('\n'.join(p.as_posix() for p in files(sys.argv[2])))
    else:
        generate(sys.argv[1], sys.argv[2])
