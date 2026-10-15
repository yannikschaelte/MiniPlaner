#!/bin/bash
# Build MiniPlaner.dmg from a meson build directory. Needs dylibbundler.
# Usage: package.sh [BUILDDIR]
set -euo pipefail
cd "$(dirname "$0")/../.."
BUILD="${1:-.build/meson}"
DIST=.build/dist
APP="$DIST/MiniPlaner.app"
LIBS="${CONDA_PREFIX:+$CONDA_PREFIX/lib}"

rm -rf "$APP" && mkdir -p "$DIST"
mkdir -p "$APP/Contents/MacOS" "$APP/Contents/Resources"
sed "s/@VERSION@/$(cat version.dat)/" packaging/macos/Info.plist > "$APP/Contents/Info.plist"
cp "$BUILD/miniplaner" "$APP/Contents/MacOS/"

ICONSET=.build/miniplaner.iconset
mkdir -p "$ICONSET" && sips -z 256 256 src/img/minis256.png --out "$ICONSET/icon_256x256.png" >/dev/null
iconutil -c icns "$ICONSET" -o "$APP/Contents/Resources/miniplaner.icns"

dylibbundler -od -b -x "$APP/Contents/MacOS/miniplaner" \
    -d "$APP/Contents/Frameworks" -p @executable_path/../Frameworks ${LIBS:+-s "$LIBS"}
# dylibbundler invalidates signatures; sign ad hoc (no Developer ID), otherwise Apple Silicon reports a "damaged" app
codesign --force --deep -s - "$APP"
hdiutil create -volname MiniPlaner -srcfolder "$APP" -ov -format UDZO "$DIST/MiniPlaner.dmg"
