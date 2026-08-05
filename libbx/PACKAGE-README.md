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
