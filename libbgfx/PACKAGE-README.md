# libbgfx - Cross-platform rendering library

This is a `build2` package for the [bgfx](https://github.com/bkaradzic/bgfx) C++
library. It provides a cross-platform rendering API.


## Usage

To start using `libbgfx` in your project, add the following `depends`
value to your `manifest`, adjusting the version constraint as appropriate:

```
depends: libbgfx ^1.153.0
```

Then import the library in your `buildfile`:

```
import libs = libbgfx%lib{bgfx}
```

Public headers use the `<bgfx/...>` include style. `libbx` is an interface
dependency (for example `bx::AllocatorI` and `<bgfx/embedded_shader.h>`).


## Importable targets

This package provides the following importable targets:

```
lib{bgfx}
```

The rendering library. Depends on `libbx` and `libbimg`.

This build enables Vulkan and Noop on all platforms, Metal on macOS, and
Direct3D 11 and 12 on Windows. OpenGL and WebGPU are compiled out. The Vulkan
and D3D runtimes are not linked. bgfx loads them dynamically (`libMoltenVK.dylib`
on macOS, `libvulkan.so.1` on Linux, `vulkan-1.dll` on Windows, `d3d11.dll` and
`d3d12.dll` on Windows). Install a Vulkan loader or MoltenVK to use the Vulkan
backend at runtime.

On macOS the Metal backend depends on `libmetal-cpp` (header-only C++ Metal
bindings). Until published on cppget, resolve it from the git prerequisite
`https://github.com/helmesjo/build2-metal-cpp.git` declared in this project's
`repositories.manifest`.

On Windows the D3D11 and D3D12 backends depend on `libdirectx-headers`
(Microsoft DirectX-Headers, providing D3D12 and D3DX12 headers). D3D11 and
DXGI headers are supplied by the Windows SDK (MSVC) or MinGW-w64. Until
published on cppget, resolve `libdirectx-headers` from the git prerequisite
`https://github.com/helmesjo/build2-DirectX-Headers.git` declared in this
project's `repositories.manifest`.


## Configuration variables

This package provides no configuration variables. Debug behaviour follows
`config.libbx.debug` from the `libbx` dependency.
