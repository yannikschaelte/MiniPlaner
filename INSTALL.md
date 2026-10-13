# Install dependencies and build the MiniPlaner


## Dependencies

* [The Meson Build System](https://mesonbuild.com/Getting-meson.html)
* [wxWidgets](https://www.wxwidgets.org/downloads/) (via a config tool like `wx-config`)


## Quick start (Linux, macOS)

[micromamba](https://mamba.readthedocs.io/en/latest/installation/micromamba-installation.html)
provides compilers, Meson and wxWidgets from `environment.yml` (also used by CI):

```sh
micromamba create -p .build/env -f environment.yml   # `.build/` is gitignored
micromamba run -p .build/env meson setup .build/meson
micromamba run -p .build/env meson compile -C .build/meson
```


## Compiling

See [Compiling a Meson project](https://mesonbuild.com/Quick-guide.html#compiling-a-meson-project).


### Selecting the config tool

For explicitly setting the config tool used for wxWidgets, 
describe the 
[native environment](https://mesonbuild.com/Native-environments.html) 
used by meson. 


#### Example

```ini
[binaries]
wx-config = 'wx-config-custom'
```

Either configure a _persistent_ native environment in one of the 
[native file locations](https://mesonbuild.com/Native-environments.html#native-file-locations) 
or supply the native file to meson when configuring the build directory with 
`--native-file NATIVE_FILE`.


### Static compilation

To build a single-file executable that is independent of MSYS2 (this is what the Windows
release uses), configure with `-Dstatic=true`.



## Packaging

Run after compiling; results land in `.build/dist`, and CI uploads them as artifacts.

| Platform | Command | Result |
|----------|---------|--------|
| Linux    | `packaging/linux/build-appimage.sh BUILDDIR` | `MiniPlaner-x86_64.AppImage` |
| macOS    | `packaging/macos/package.sh BUILDDIR` (needs `dylibbundler`) | `MiniPlaner.dmg` |
| Windows  | `packaging/windows/package.sh BUILDDIR` (MSYS2, Inno Setup) | `MiniPlaner-Setup.exe`, `MiniPlaner.exe` (standalone) |

**Releasing:** set the version in `meson.build` and `version.dat`, merge to `master`, then push a
tag `vX.Y.Z`. The Release workflow builds all platforms and publishes the four files on GitHub,
where the homepage links to them.

User data lives in the per-user data directory (`~/.local/share/MiniPlaner`,
`%APPDATA%\MiniPlaner`, `~/Library/Application Support/MiniPlaner`); data
found next to the executable by older versions is copied there on first start.
Exports default to `<Documents>/MiniPlaner/output`.

On first start a welcome wizard offers to start empty or with demo data. The
demo data is the content of `res/demo`, embedded into the executable at build
time by `tools/embed_demo.py` (re-run `meson setup --reconfigure` after adding
files there). The Settings tab can reload it or delete all data (a backup folder
is kept). The manual is opened from
<https://yannikschaelte.github.io/MiniPlaner/Handbuch.pdf>.
