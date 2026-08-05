# libbimg package

Image encoding and decoding used by bgfx (core library plus astc-encoder).

## Usage

```
import libs = libbimg%lib{bimg}
exe{hello}: cxx{**} $libs
```

Public headers use the `<bimg/bimg.h>` include style. This package
installs `bimg.h` into `include/bimg/`. The pkg-config file also adds
`include/bimg/` for the unprefixed `"bimg.h"` include used by
`decode.h` / `encode.h`. Those headers are installed by `libbimg-decode`
and `libbimg-encode`.
