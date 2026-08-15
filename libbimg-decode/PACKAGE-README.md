# libbimg-decode

This is a `build2` package for the [bimg](https://github.com/bkaradzic/bimg)
image decoding library (`bimg_decode` upstream). It parses PNG, JPEG, EXR,
WebP, and related raster formats into `bimg` image containers.


## Usage

To start using `libbimg-decode` in your project, add the following `depends`
value to your `manifest`, adjusting the version constraint as appropriate:

```
depends: libbimg-decode ^1.153.0
```

Then import the library in your `buildfile`:

```
import libs = libbimg-decode%lib{bimg-decode}
```

Public headers use the `<bimg/decode.h>` include style. This package
installs `decode.h` into `include/bimg/`. The generated pkg-config file
also adds `include/bimg/` so the quoted `#include "bimg.h"` inside
`decode.h` (and a bare `<decode.h>`) still resolve. `bimg.h` itself is
installed by `libbimg`.


## Importable targets

This package provides the following importable targets:

```
lib{bimg-decode}
```

The decode library. Depends on `libbimg`, `liblodepng`, `stb_image`, and
`libtinyexr`. AVIF is compiled out until `dav1d` and `libavif` are packaged.


## Configuration variables

This package provides no configuration variables.
