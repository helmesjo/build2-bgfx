# libbx - Base C++ utilities used by bgfx and bimg

This is a `build2` package for the [bx](https://github.com/bkaradzic/bx) C++
library. It provides OS, runtime, and compiler independent core utilities used
by bgfx and bimg.


## Usage

To start using `libbx` in your project, add the following `depends`
value to your `manifest`, adjusting the version constraint as appropriate:

```
depends: libbx ^1.153.0
```

Then import the library in your `buildfile`:

```
import libs = libbx%lib{bx}
```

Public headers use the `<bx/...>` include style. With MSVC, enable
`/Zc:preprocessor` when compiling code that includes those headers (public
headers require the conforming preprocessor).

Upstream requires SSE4.2 on x86. Some SIMD functions in the public headers
(for example `bx::simd128_f32_dot()` and `bx::float4x4_inverse()`) use SSE4.1
instructions, so on x86 with compilers other than MSVC, compile code that
calls them with `-msse4.2`.


## Importable targets

This package provides the following importable targets:

```
lib{bx}
```

The base utilities library.


## Configuration variables

This package provides the following configuration variables:

```
[bool] config.libbx.debug ?= false
```

`config.libbx.debug` defines `BX_CONFIG_DEBUG`. When true, consumers of
`libbgfx` also treat `BGFX_CONFIG_DEBUG` as true and default
`bgfx::Init::debug` to true (for example Vulkan validation layers).
