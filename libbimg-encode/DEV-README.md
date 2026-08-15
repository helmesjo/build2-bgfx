# libbimg-encode packaging notes

## edtaa3

`src/edtaa3/` is Stefan Gustavson's Euclidean distance transform
(`edtaa3func`), vendored by upstream bimg. There is no standalone product
to package. Keep it in-tree as file-level symlinks, not a whole-directory
`3rdparty/` mount:

```
src/edtaa3/edtaa3func.cpp  -> upstream/bimg/3rdparty/edtaa3/edtaa3func.cpp
src/edtaa3/edtaa3func.h    -> upstream/bimg/3rdparty/edtaa3/edtaa3func.h
src/edtaa3/LICENSE.md      -> upstream/bimg/3rdparty/edtaa3/LICENSE.md
```

Sources include it as `#include <edtaa3/edtaa3func.h>`. It implements
`bimg::imageMakeDist` (SDF baking, `texturec --sdf`). Same local-file
pattern as `libbgfx` `src/h264/`.
