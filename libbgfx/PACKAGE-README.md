# libbgfx package

Cross-platform rendering library (bgfx) packaged for build2.

## Backends

This package build enables **Vulkan** and **Noop** only. Other backends
(Metal, D3D, OpenGL, WebGPU) are compiled out.

## Usage

```
import libs = libbgfx%lib{bgfx}
exe{hello}: cxx{**} $libs
```

Public headers use the `<bgfx/...>` include style. `libbx` is an interface
dependency (for example `bx::AllocatorI` and `<bgfx/embedded_shader.h>`).

## Dependencies

- `libbx`, `libbimg` (co-located packages in this repository)

Vulkan API headers are taken from upstream `3rdparty/khronos/vulkan-local`
for this pin. A newer `Vulkan-Headers` package on cppget can replace that
once it is new enough for this bgfx revision.

The Vulkan runtime is **not** linked. bgfx loads it dynamically
(`libMoltenVK.dylib` on macOS, `libvulkan.so.1` on Linux, `vulkan-1.dll` on
Windows). Install a Vulkan loader / MoltenVK to use the Vulkan backend at
runtime.
