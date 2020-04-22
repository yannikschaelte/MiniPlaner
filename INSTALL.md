# Install dependencies and build the MiniPlaner

## Dependencies

* [The Meson Build System](https://mesonbuild.com/Getting-meson.html)
* [wxWidgets](https://www.wxwidgets.org/downloads/) (via a config tool like `wx-config`)

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

### MSYS2

Package scripts are available in 
[MiniPlaner-MINGW](https://github.com/mwkroening/MiniPlaner-MINGW).

#### Static compilation

When compiling an executable to be independent of MSYS2, select 
`wx-config-static` as config tool for wxWidgets and append 
`-static` to your `LDFLAGS` before configuring the build directory.

