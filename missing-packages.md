# Missing third-party packages

Inventory of in-tree third-party dependencies that current packages still
require, but that are **not** yet available as separate `build2` packages
(import/`depends`). Already unbundled packages are listed only for context.

Focus is **modern hardware** support (ETC2/EAC and ASTC already packaged,
BC6H/BC7 encode compiled out). Legacy GPU formats are listed at the bottom.

**Already external** (see `repositories.manifest` + cppget stable):

| Package | Source |
|---|---|
| `libastcenc` | `helmesjo/build2-astc-encoder` |
| `libmetal-cpp` | `helmesjo/build2-metal-cpp` |
| `libdirectx-headers` | `helmesjo/build2-DirectX-Headers` |
| `libsquish` | `helmesjo/build2-libsquish` |
| `libvulkan-headers` | `helmesjo/build2-Vulkan-Headers` |
| `libetcpak` | `helmesjo/build2-etcpak` |
| `libiqa` | `build2-packaging/iqa` |
| `liblodepng` | `build2-packaging/lodepng` |
| `libtinyexr` | decode `depends` (`^1.0.8`) |
| `libsimplewebp` | `build2-packaging/simplewebp` |
| `libiconfontcppheaders` | `helmesjo/build2-IconFontCppHeaders` |
| `libtinystl` | `helmesjo/build2-tinystl` |
| `libimgui` | cppget testing (`^1.92.3`) |
| `stb_image_resize2`, `stb_truetype`, `stb_rect_pack`, `stb_image` | `build2-packaging/stb` |
| `catch2` | cppget stable |

---

## 1. Required for consumer library features (modern)

These are needed to build and use the primary libraries as shipped today
(encode path, runtime library). Unbundling them improves reuse and shrinks
what stays vendored in this repo.

### `libbimg-encode`

Texture compression / encode path.

**edtaa3** stays in-tree. It is a small educational distance-transform
snippet (Stefan Gustavson), not a product to package. File-level
symlinks live in `src/edtaa3/` with their own `LICENSE.md` and
`edtaa3/libul{edtaa3}` target. Include is `<edtaa3/edtaa3func.h>`.

Compiled out until packaged:

| Item | Role |
|---|---|
| **nvtt** (NVIDIA Texture Tools subset) | BC6H / BC7 encode (`imageEncodeFromRgba32f` errors, same as the RGBA8 path) |
| **etc1** | ETC1 encode |
| **pvrtc** | PVRTC (PTC14 / PTC14A) encode |

Already packaged for encode: `libsquish` (BC1–5), `libastcenc` (ASTC),
`libetcpak` (ETC2/EAC), `stb_image_resize2`, `libiqa`.

Compiled out with nvtt: **etc1** (ETC1) and **pvrtc** (PTC14 / PTC14A).
See [section 4](#4-legacy-hardware-formats).

### `libbgfx`

| Missing package (candidate) | Upstream path | Role | Notes |
|---|---|---|---|
| **renderdoc** (header-only) | `bgfx/3rdparty/renderdoc/renderdoc_app.h` | RenderDoc in-process API | Still required on Windows/Linux for `debug_renderdoc.cpp`. Single header. |
| **h264** (header-only) | `bgfx/3rdparty/h264/h264.h` | H.264 bitstream parser | Present and wired, but **inactive**: build sets `BGFX_CONFIG_VIDEO=0`. Required only if video decode is enabled later. |

Not missing as third-party product code: the `3rdparty/metal-cpp/` path is a
local **shim** to packaged `libmetal-cpp`, not a vendored copy.

### `libbx`

No remaining required in-tree third-party. `libtinystl` is a package.
`libbgfx` (private `bgfx_p.h`), `bgfx-examples`, and `libbx-tests`
depend on it for `<tinystl/...>`. `libbx` itself does not include those
headers.

### `libbimg`

No remaining required in-tree third-party. Depends on packaged `libastcenc`.

### `libbimg-decode`

Image parsers. Unbundled `liblodepng`, `stb_image`, `libtinyexr` (pulls
`libminiz`), and `libsimplewebp`.

Compiled out until packaged:

| Item | Role |
|---|---|
| **dav1d** + **libavif** | AVIF (`BIMG_CONFIG_PARSE_AVIF=0`) |
| **libheif** | HEIF (upstream default off, LGPL) |

---

## 2. Required for examples (consumer demos, not core API)

Overlay restored via packaged `libimgui`. First-party draw path, shaders,
fonts, and `example-glue.cpp` stay in `bgfx-examples`.

### `bgfx-examples`

No remaining required in-tree third-party. Depends on `libimgui` (core
only), `libiconfontcppheaders`, and `libtinystl`.

Dock and gizmo stay as first-party overlay extras (file-level
symlinks under `common/imgui/widgets/`). They lived next to vendored
dear-imgui and are not part of packaged `libimgui`. Other 3rdparty
widgets (markdown, color wheel, ...) are unused by this example
subset and are not compiled.

`stb_truetype` / `stb_rect_pack` are not example dependencies. Packaged
imgui ships `imstb_*`. Overlay is built with `USE_LOCAL_STB=0`.

Not required by the reduced example-common build (upstream uses them more
widely): `meshoptimizer`, full nanovg/font stacks, `cgltf`, `sdf`,
`native_app_glue`.

---

## 3. Dev / debug / optional, or not part of current packages

Lower priority for packaging against **this** repository as it stands.
Either optional, compile-out, leftover, or only relevant when new packages
are added.

### Optional or compile-out in current builds

| Item | Package that would care | Why lower priority |
|---|---|---|
| **h264** | `libbgfx` | Video disabled (`BGFX_CONFIG_VIDEO=0`) |
| **khronos** GL/EGL/GLES headers | `libbgfx` if OpenGL/ES enabled | OpenGL/ES compiled out today |
| **renderdoc** | `libbgfx` | Dev tooling header only, tiny, dlopen at runtime |

### Not packaged yet (upstream has them, no local package consumes them)

Would become missing-package work only when adding tools packages.

| Future package surface | Upstream third-party (still missing) |
|---|---|
| **shaderc** / tools | fcpp, glsl-optimizer, glslang, spirv-cross, spirv-headers, spirv-tools, dawn/tint, d3d4linux |
| **geometryc** | meshoptimizer |
| **texturev** | l-smash |

A local `build2-SPIRV-Cross` tree already exists under the packaging workspace
and may help if/when shaderc is packaged.

### Cleanup only (not new packages)

| Item | Where | Note |
|---|---|---|
| **edtaa3** | `libbimg-encode/src/edtaa3/` | Keep. File-level symlinks, own license and `libul` |
| `catch_amalgamated.hpp` stub | `libbx-tests/tests/catch/` | Tests use packaged `catch2` |

---

## 4. Legacy hardware formats

Compiled out of `libbimg-encode`. Low priority for modern targets (ASTC /
ETC2 cover current desktop and mobile). Runtime sampling of already-compressed
ETC1/PVRTC is unchanged.

| Item | Upstream path | Role | Why legacy |
|---|---|---|---|
| **etc1** | `bimg/3rdparty/etc1` | ETC1 encoder only | Superseded by ETC2/EAC (`libetcpak`) |
| **pvrtc** | `bimg/3rdparty/pvrtc` | PVRTC (PTC14 / PTC14A) | Old PowerVR / iOS path. Apple platforms use ASTC |

---

## Summary by local package

| Local package | Still needs (not packaged) | Priority |
|---|---|---|
| `libbimg-encode` | edtaa3 stays in-tree. nvtt/etc1/pvrtc compiled out | Leftover encode compiled out |
| `libbgfx` | renderdoc header, h264 header (video off) | Medium / low |
| `libbx` | — | Done |
| `libbimg` | — | Done |
| `libbimg-decode` | dav1d/libavif (compiled out) | Done for v1 |
| `bgfx-examples` | — | Done |
| `libbx-tests` | — (`catch2` packaged) | Done |
| *(future)* shaderc / tools | see section 3 | Deferred |
| *(legacy)* etc1, pvrtc | section 4 | Lowest |

---

## Suggested unbundle order

1. **Decode leftovers** (**dav1d** / **libavif**) if AVIF should be compiled
   in.

2. **renderdoc** / **h264** headers only if video or stricter "no 3rdparty in
   tree" policy demands it. Otherwise fine as single-header adhoc includes.

3. **Legacy encode** (**etc1**, **pvrtc**, **nvtt**) already compiled out.
   Re-enable only if something explicitly needs them.

4. **Tool stacks** (shaderc, …) when those packages are added.
