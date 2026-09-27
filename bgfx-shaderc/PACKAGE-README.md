# bgfx-shaderc - Shader compiler for the bgfx rendering library

This is a `build2` package for the [`shaderc`](https://github.com/bkaradzic/bgfx)
executable. It is the shader compiler for `bgfx`'s cross-platform shader
language. This build outputs SPIR-V and Metal on all platforms, and HLSL
(DXBC via D3DCompiler, and DXIL via DXC with the Windows SDK) on Windows.
GLSL/ESSL output (glsl-optimizer) and WGSL output (Tint) are compiled out.

Note that the `shaderc` executable in this package provides `build2`
metadata.


## Usage

To start using `bgfx-shaderc` in your project, add the following build-time
`depends` value to your `manifest`, adjusting the version constraint as
appropriate:

```
depends: * bgfx-shaderc ^1.153.0
```

Then import the executable in your `buildfile`:

```
import! [metadata] shaderc = bgfx-shaderc%exe{shaderc}
```

Shaders include `<bgfx_shader.sh>` (and `bgfx_compute.sh`), which `libbgfx`
installs into `include/bgfx/`. Pass that directory to `shaderc` with `-i`.


## Importable targets

This package provides the following importable targets:

```
exe{shaderc}
```

The shader compiler command line tool. See `shaderc --help` and the upstream
[tools documentation](https://bkaradzic.github.io/bgfx/tools.html) for usage.


## Configuration variables

This package provides no configuration variables.
