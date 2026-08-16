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
| `stb_image_resize2`, `stb_truetype`, `stb_rect_pack`, `stb_image` | `build2-packaging/stb` |
| `catch2` | cppget stable |

---

## 1. Required for consumer library features (modern)

These are needed to build and use the primary libraries as shipped today
(encode path, runtime library). Unbundling them improves reuse and shrinks
what stays vendored in this repo.

### `libbimg-encode`

Texture compression / encode path. Still in-tree:

| Item | Upstream path | Role | Notes |
|---|---|---|---|
| **edtaa3** | `bimg/3rdparty/edtaa3` | Euclidean distance transform (SDF) | File-level symlinks in `src/edtaa3/`. Not a standalone product. |

Compiled out until packaged:

| Item | Role |
|---|---|
| **nvtt** (NVIDIA Texture Tools subset) | BC6H / BC7 encode (`imageEncodeFromRgba32f` errors, same as the RGBA8 path) |

Already packaged for encode: `libsquish` (BC1–5), `libastcenc` (ASTC),
`libetcpak` (ETC2/EAC), `stb_image_resize2`, `libiqa`.

Legacy encode vendors (**etc1**, **pvrtc**) are listed in [section 4](#4-legacy-hardware-formats).

Include layout for leftovers uses `<edtaa3/...>` via the `src/` include path,
plus `<etc1/...>` and `<pvrtc/...>` via the `3rdparty` root.

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

Image parsers. Unbundled `liblodepng`, `stb_image`, `libtinyexr` (pulls
`libminiz`), and `libsimplewebp`.

Compiled out until packaged:

| Item | Role |
|---|---|
| **dav1d** + **libavif** | AVIF (`BIMG_CONFIG_PARSE_AVIF=0`) |
| **libheif** | HEIF (upstream default off, LGPL) |

---

## 2. Required for examples (consumer demos, not core API)

Needed to restore the example overlay / settings UI. Compiled out today.

### `bgfx-examples`

| Missing package (candidate) | Upstream path | Role |
|---|---|---|
| **dear-imgui** | `bgfx/3rdparty/dear-imgui` | Overlay and settings widgets. Compiled out. |
| **iconfontheaders** | `bgfx/3rdparty/iconfontheaders` | Icon codepoints used by the overlay. Compiled out. |

`stb_truetype` / `stb_rect_pack` were only pulled in to compile Dear ImGui
fonts. They are not example dependencies while imgui is compiled out.

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
| Example imgui overlay | `bgfx-examples/common/imgui/` | No-op stub until dear-imgui is packaged |
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
| `libbimg-encode` | edtaa3 (in-tree), nvtt (compiled out), legacy etc1/pvrtc | Low / leftover encode |
| `libbgfx` | renderdoc header, h264 header (video off) | Medium / low |
| `libbx` | tinystl (optional unbundle) | Low (API-integrated) |
| `libbimg` | — | Done |
| `libbimg-decode` | dav1d/libavif (compiled out) | Done for v1 |
| `bgfx-examples` | dear-imgui, iconfontheaders (compiled out) | Medium (demos only) |
| `libbx-tests` | — (`catch2` packaged) | Done |
| *(future)* shaderc / tools | see section 3 | Deferred |
| *(legacy)* etc1, pvrtc | section 4 | Lowest |

---

## Suggested unbundle order

1. **Encode leftover** (**edtaa3**) if SDF tooling should be an external
   package. **nvtt** only if BC6H/BC7 encode should be compiled back in.

2. **Decode leftovers** (**dav1d** / **libavif**) if AVIF should be compiled
   in.

3. **dear-imgui** (+ **iconfontheaders** if kept separate)
   Only required for examples, but large and widely reusable.

4. **renderdoc** / **h264** headers only if video or stricter "no 3rdparty in
   tree" policy demands it. Otherwise fine as single-header adhoc includes.

5. **tinystl** only if there is a clear multi-package consumer beyond bx.

6. **Legacy encode** (**etc1**, **pvrtc**) last, or leave vendored / disabled.

7. **Tool stacks** (shaderc, …) when those packages are added.
