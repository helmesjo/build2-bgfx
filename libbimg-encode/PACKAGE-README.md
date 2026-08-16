# libbimg-encode

This is a `build2` package for the [bimg](https://github.com/bkaradzic/bimg)
texture encoding library (`bimg_encode` upstream). It compresses images into
GPU formats (BC1–5, ETC2/EAC, ASTC, and related helpers). ETC1, PVRTC, and
BC6H/BC7 encode are compiled out.


## Usage

To start using `libbimg-encode` in your project, add the following `depends`
value to your `manifest`, adjusting the version constraint as appropriate:

```
depends: libbimg-encode ^1.153.0
```

Then import the library in your `buildfile`:

```
import libs = libbimg-encode%lib{bimg-encode}
```

Public headers use the `<bimg/encode.h>` include style. This package
installs `encode.h` into `include/bimg/`. The generated pkg-config file
also adds `include/bimg/` so the quoted `#include "bimg.h"` inside
`encode.h` (and a bare `<encode.h>`) still resolve. `bimg.h` itself is
installed by `libbimg`.


## Importable targets

This package provides the following importable targets:

```
lib{bimg-encode}
```

The encode library. Depends on `libbimg`, `libastcenc`, `libsquish`,
`libetcpak`, `stb_image_resize2`, and `libiqa`.


## Configuration variables

This package provides no configuration variables.
