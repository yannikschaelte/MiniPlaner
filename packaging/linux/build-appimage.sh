#!/bin/bash
# Build MiniPlaner-x86_64.AppImage from an existing meson build directory.
# Usage: build-appimage.sh [BUILDDIR]   (run inside the build environment)
# Output: .build/dist/MiniPlaner-x86_64.AppImage
set -euo pipefail
cd "$(dirname "$0")/../.."
BUILD="${1:-.build/meson}"
TOOLS="$PWD/.build/tools"
APPDIR=".build/AppDir"

mkdir -p "$TOOLS"
fetch() { [ -x "$TOOLS/$1" ] || { curl -fsSL -o "$TOOLS/$1" "$2" && chmod +x "$TOOLS/$1"; }; }
GH=https://github.com/linuxdeploy
fetch linuxdeploy "$GH/linuxdeploy/releases/download/1-alpha-20251107-1/linuxdeploy-x86_64.AppImage"
fetch linuxdeploy-plugin-gtk.sh "https://raw.githubusercontent.com/linuxdeploy/linuxdeploy-plugin-gtk/7a3fbc31a9e5075073ff8790f26effbac5f84453/linuxdeploy-plugin-gtk.sh"

mkdir -p .build/dist
rm -rf "$APPDIR"
meson configure "$BUILD" --prefix /usr >/dev/null
meson install -C "$BUILD" --destdir "$PWD/$APPDIR"

# linuxdeploy never bundles fontconfig/freetype, but the bundled Pango needs the versions it was built
# against (older distributions lack newer symbols). Ship them and point fontconfig at the system's fonts.
if [ -n "${CONDA_PREFIX:-}" ]; then
    mkdir -p "$APPDIR/usr/lib" "$APPDIR/apprun-hooks"
    cp -a "$CONDA_PREFIX"/lib/libfontconfig.so.1* "$CONDA_PREFIX"/lib/libfreetype.so.6* "$APPDIR/usr/lib/"
    echo 'export FONTCONFIG_FILE="${FONTCONFIG_FILE:-/etc/fonts/fonts.conf}"' > "$APPDIR/apprun-hooks/fontconfig.sh"
fi

export PATH="$TOOLS:$PATH" APPIMAGE_EXTRACT_AND_RUN=1 DEPLOY_GTK_VERSION=3
LD_LIBRARY_PATH="${CONDA_PREFIX:+$CONDA_PREFIX/lib}" \
OUTPUT=.build/dist/MiniPlaner-x86_64.AppImage \
    "$TOOLS/linuxdeploy" --appdir "$APPDIR" --plugin gtk --output appimage \
    -d "$APPDIR/usr/share/applications/miniplaner.desktop" \
    -i src/img/minis256.png
