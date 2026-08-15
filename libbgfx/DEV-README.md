# libbgfx packaging notes

## h264.h

`src/h264/` is the H.264 bitstream parser from Wicked Engine
(`WickedEngine/Utility/h264.h`), vendored by upstream bgfx. It is a one-off
MIT header. There is no standalone product to package. Keep it in-tree as
file-level symlinks, not a whole-directory `3rdparty/` mount:

```
src/h264/h264.h      -> upstream/bgfx/3rdparty/h264/h264.h
src/h264/LICENSE.txt    Wicked Engine MIT text (upstream snapshot has no
                        separate license file to symlink)
```

Sources include it as `#include <h264/h264.h>`. Video is compiled out
(`BGFX_CONFIG_VIDEO=0`). The same local-file pattern applies later to
`texturev` if video tools are packaged, and to `libbimg-encode` `src/edtaa3/`.
