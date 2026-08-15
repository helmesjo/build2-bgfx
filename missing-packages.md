# Missing third-party packages

Inventory of in-tree third-party dependencies that current packages still
require, but that are **not** yet available as separate `build2` packages
(import/`depends`). Already unbundled packages are listed only for context.

Focus is **modern hardware** support (BC6H/BC7, ETC2/EAC, ASTC already
packaged). Legacy GPU formats are listed at the bottom.

**Already external** (see `repositories.manifest` + cppget stable):

| Package | Source |
|---|---|
| `libastcenc` | `helmesjo/build2-astc-encoder` |
| `libmetal-cpp` | `helmesjo/build2-metal-cpp` |
| `libdirectx-headers` | `helmesjo/build2-DirectX-Headers` |
| `libsquish` | `helmesjo/build2-libsquish` |
| `libvulkan-headers` | `helmesjo/build2-Vulkan-Headers` |
| `stb_image_resize2`, `stb_truetype`, `stb_rect_pack`, `stb_image` | `build2-packaging/stb` |
| `catch2` | cppget stable |

---

## 1. Required for consumer library features (modern)

These are needed to build and use the primary libraries as shipped today
(encode path, runtime library). Unbundling them improves reuse and shrinks
what stays vendored in this repo.

### `libbimg-encode`

Texture compression / encode path. Still compiles and links these from
`src/3rdparty/` (upstream `bimg/3rdparty`):

| Missing package (candidate) | Upstream path | Role |
|---|---|---|
| **etcpak** | `bimg/3rdparty/etcpak` | ETC2 / EAC encode (mobile / GLES) |
| **nvtt** (NVIDIA Texture Tools subset) | `bimg/3rdparty/nvtt` | BC6H / BC7 encode (desktop) |
| **edtaa3** | `bimg/3rdparty/edtaa3` | Euclidean distance transform (SDF), small |
| **iqa** | `bimg/3rdparty/iqa` | Image quality assessment (SSIM), C |

Already packaged for encode: `libsquish` (BC1–5), `libastcenc` (ASTC),
`stb_image_resize2`.

Legacy encode vendors (**etc1**, **pvrtc**) are listed in [section 4](#4-legacy-hardware-formats).

Include layout today assumes a `3rdparty` root (`<etcpak/...>`,
`<nvtt/nvtt.h>`, `<edtaa3/...>`, `<iqa.h>`, plus legacy `<etc1/...>`,
`<pvrtc/...>`). External packages would need either matching include paths
or small include patches (as done for `libsquish` / `stb_image_resize2`).

### `libbgfx`

| Missing package (candidate) | Upstream path | Role | Notes |
|---|---|---|---|
| **renderdoc** (header-only) | `bgfx/3rdparty/renderdoc/renderdoc_app.h` | RenderDoc in-process API | Still required on Windows/Linux for `debug_renderdoc.cpp`. Single header. |
| **h264** (header-only) | `bgfx/3rdparty/h264/h264.h` | H.264 bitstream parser | Present and wired, but **inactive**: build sets `BGFX_CONFIG_VIDEO=0`. Required only if video decode is enabled later. |

Not missing as third-party product code: the `3rdparty/metal-cpp/` path is a
local **shim** to packaged `libmetal-cpp`, not a vendored copy.

### `libbx`

| Missing package (candidate) | Location | Role | Notes |
|---|---|---|---|
| **tinystl** | `include/tinystl/` (upstream bx) | Header-only mini-STL | Public part of bx's API. Usually left with `libbx` unless a shared package is wanted. |

### `libbimg`

No remaining required in-tree third-party. Depends on packaged `libastcenc`.

### `libbimg-decode`

Image parsers. Unbundled `liblodepng`, `stb_image`, and `libtinyexr` (pulls
`libminiz`). Still in-tree:

| Item | Upstream path | Role | Notes |
|---|---|---|---|
| **simplewebp** | `bimg/3rdparty/simplewebp` | WebP decode | Single header. File-level symlinks in `src/simplewebp/`. |

Compiled out until packaged:

| Item | Role |
|---|---|
| **dav1d** + **libavif** | AVIF (`BIMG_CONFIG_PARSE_AVIF=0`) |
| **libheif** | HEIF (upstream default off, LGPL) |

---

## 2. Required for examples (consumer demos, not core API)

Needed to build `bgfx-examples` / `libue{example-common}` as currently wired.

### `bgfx-examples`

| Missing package (candidate) | Upstream path | Role |
|---|---|---|
| **dear-imgui** | `bgfx/3rdparty/dear-imgui` | Dear ImGui sources compiled into example-common |
| **iconfontheaders** | `bgfx/3rdparty/iconfontheaders` | Icon codepoint headers (`icons_kenney.h`, `icons_font_awesome.h`) included from example imgui |

Already packaged and used here: `stb_truetype`, `stb_rect_pack`.

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
| Dead `3rdparty/stb` adhoc rule | `libbimg-encode/src/buildfile` | Symlink removed after unbundling `stb_image_resize2` |
| `stb_textedit.h` symlink | `bgfx-examples/common/include/stb/` | Unused by current examples (Dear ImGui ships `imstb_*`) |
| `catch_amalgamated.hpp` stub | `libbx-tests/tests/catch/` | Tests use packaged `catch2` |

---

## 4. Legacy hardware formats

Still compiled into upstream `bimg_encode`, but low priority for modern
targets (ASTC / ETC2 / BC6H–7 cover current desktop and mobile). Safe to
leave in-tree or compile out until something explicitly needs them.

| Missing package (candidate) | Upstream path | Role | Why legacy |
|---|---|---|---|
| **etc1** | `bimg/3rdparty/etc1` | ETC1 encoder only | Superseded by ETC2/EAC (`etcpak`) on modern GLES/Vulkan mobile |
| **pvrtc** | `bimg/3rdparty/pvrtc` | PVRTC (PTC14 / PTC14A) | Old PowerVR / iOS path. Apple platforms use ASTC now |

---

## Summary by local package

| Local package | Still needs (not packaged) | Priority |
|---|---|---|
| `libbimg-encode` | etcpak, nvtt, edtaa3, iqa (+ legacy etc1, pvrtc) | Highest (modern encode) |
| `libbgfx` | renderdoc header, h264 header (video off) | Medium / low |
| `libbx` | tinystl (optional unbundle) | Low (API-integrated) |
| `libbimg` | — | Done |
| `libbimg-decode` | simplewebp (in-tree), dav1d/libavif (compiled out) | Done for v1 |
| `bgfx-examples` | dear-imgui, iconfontheaders | Medium (demos only) |
| `libbx-tests` | — (`catch2` packaged) | Done |
| *(future)* shaderc / tools | see section 3 | Deferred |
| *(legacy)* etc1, pvrtc | section 4 | Lowest |

---

## Suggested unbundle order

1. **Modern encode vendors** (**etcpak**, then **nvtt**)
   Unlocks ETC2/EAC and BC6H/BC7 on top of already-packaged BC1–5 and ASTC.

2. **Decode leftovers** (**simplewebp**, then **dav1d** / **libavif**) if WebP
   should be an external package or AVIF should be compiled in.

3. **Encode utilities** (**edtaa3**, **iqa**) if SDF / quality tooling matters.

4. **dear-imgui** (+ **iconfontheaders** if kept separate)
   Only required for examples, but large and widely reusable.

5. **renderdoc** / **h264** headers only if video or stricter "no 3rdparty in
   tree" policy demands it. Otherwise fine as single-header adhoc includes.

6. **tinystl** only if there is a clear multi-package consumer beyond bx.

7. **Legacy encode** (**etc1**, **pvrtc**) last, or leave vendored / disabled.

8. **Tool stacks** (shaderc, …) when those packages are added.
