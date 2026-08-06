# bgfx-examples package

Interactive demos for [bgfx](https://github.com/bkaradzic/bgfx). This package
ships a **subset** of upstream examples and grows over time.

## Included (v1)

| Executable | Upstream | Notes |
|------------|----------|--------|
| `helloworld` | `examples/00-helloworld/helloworld.cpp` | Window, clear colour, debug-text logo |

Not automated tests. Run the executable by hand.

## Build and run

From the multi-package repository after `bdep init` / `bdep update`:

```
bdep update
# path depends on your configuration out tree, for example:
../bgfx-apple/bgfx-examples/00-helloworld/helloworld
```

Examples import `liba{}` (static) for `libbgfx` / `libbimg` / `libbx`. Shared
builds of those libraries use automatic symbol export (best-effort), but
Windows auto-import does not cover global data referenced from public inlines
(for example `bx::Ticks::s_kInvFreq` on MSVC).

Optional args (see upstream `Args`): `--vk`, `--mtl`, `--noop`, etc.

## Windowing

Native entry only (no SDL/GLFW in this cut):

- macOS: Cocoa (`entry_osx.mm`)
- Windows: Win32
- Linux: X11

## Rendering backends

Backends come from `libbgfx`. That package enables Vulkan (and Noop) on all
platforms and Metal on macOS. Vulkan is loaded at runtime (`libvulkan.so.1`,
`vulkan-1.dll`, or MoltenVK as `libMoltenVK.dylib` if you use Vulkan on
Apple). Install a loader / ICD for your OS when using Vulkan.
