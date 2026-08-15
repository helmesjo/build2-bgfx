# libbimg-decode packaging notes

## simplewebp

`src/simplewebp/` is the single-header WebP decoder vendored by upstream
bimg. There is no standalone build2 package. Keep it in-tree as file-level
symlinks, not a whole-directory `3rdparty/` mount:

```
src/simplewebp/simplewebp.h  -> upstream/bimg/3rdparty/simplewebp/simplewebp.h
src/simplewebp/LICENSE.md    -> upstream/bimg/3rdparty/simplewebp/LICENSE.md
```

Sources include it as `#include <simplewebp/simplewebp.h>` with
`SIMPLEWEBP_IMPLEMENTATION`. The `src/` include path makes that work. Same
local-file pattern as `libbimg-encode` `src/edtaa3/` and `libbgfx` `src/h264/`.

## AVIF

AVIF support needs `dav1d` and `libavif`, which are not packaged. This
package compiles with `BIMG_CONFIG_PARSE_AVIF=0` until those exist. HEIF
stays off (upstream default, LGPL).
