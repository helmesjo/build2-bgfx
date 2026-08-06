# libbx package

Base C++ utilities used by bgfx and bimg.

## Usage

```
import libs = libbx%lib{bx}
exe{hello}: cxx{**} $libs
```

Public headers use the `<bx/...>` include style.

## Configuration

| Variable | Default | Meaning |
|----------|---------|---------|
| `config.libbx.debug` | `false` | Define `BX_CONFIG_DEBUG` (required by public headers) |

## MSVC

Public headers require the conforming preprocessor. When building against
`libbx` with MSVC, enable `/Zc:preprocessor` (this package does so for its
own translation units). For a whole configuration:

```
config.cxx.coptions+=/Zc:preprocessor
```

This package also uses `/EHs-c-` for its own sources (upstream
`NoExceptions`, needed for SEH `__try` in `thread.cpp`). Consumers are not
required to disable exceptions.

Shared libraries use automatic DLL symbol exporting on Windows (generated
`.def` on MSVC, `--export-all-symbols` on MinGW).
