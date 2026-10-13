#!/bin/bash
# Build MiniPlaner-Setup.exe from a statically linked meson build (-Dstatic=true, MSYS2 shell).
# Usage: package.sh [BUILDDIR]
set -euo pipefail
cd "$(dirname "$0")"
BUILD="../../${1:-.build/meson}"
STAGE=../../.build/stage

rm -rf "$STAGE" && mkdir -p "$STAGE"
cp "$BUILD/miniplaner.exe" "$STAGE"/

export MINIPLANER_VERSION="$(cat ../../version.dat)"
"/c/Program Files (x86)/Inno Setup 6/ISCC.exe" installer.iss
# The statically linked executable also works on its own, without installation.
cp "$STAGE"/miniplaner.exe ../../.build/dist/MiniPlaner.exe
