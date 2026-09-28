# bgfx-examples - Interactive examples for the bgfx rendering library

This is a `build2` package for a subset of the official
[bgfx](https://github.com/bkaradzic/bgfx) examples.

Examples are interactive demos and are not run as automated tests.

On macOS the examples depend on and link `libmoltenvk`, so the Vulkan backend
(`--vk`) uses that build, found through the executable's rpath, with no Vulkan
SDK or environment setup. In a static-only configuration MoltenVK is linked
statically, which bgfx cannot load, and `--vk` falls back to Metal.


## Importable targets

This package exports no targets.


## Configuration variables

This package provides no configuration variables. Demo debug behaviour follows
`config.libbx.debug` from the `libbx` dependency.
