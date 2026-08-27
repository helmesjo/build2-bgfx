# Missing third-party packages

Inventory of third-party dependencies that current packages still require
but that are **not** yet available as separate `build2` packages
(import/`depends`). Already unbundled packages are listed only for context.

After the unbundle stretch, no in-tree third-party **product** remains in the
local packages. Snippets (edtaa3, h264, vassvik dock) stay in-tree on purpose.
Compiled-out and future-tool vendors live in the upstream submodule only.

Focus is **modern hardware** support (ETC2/EAC and ASTC already packaged,
BC6H/BC7 encode compiled out). Legacy GPU formats are listed at the bottom.

**Already external** (git prereqs in `repositories.manifest`, cppget
queue/testing/stable, or `build2-packaging` GitHub):

| Package | Source |
|---|---|
| `libastcenc` | git `helmesjo/build2-astc-encoder#review` |
| `libmetal-cpp` | git `helmesjo/build2-metal-cpp#review` |
| `libdirectx-headers` | git `helmesjo/build2-DirectX-Headers#review` |
| `libvulkan-headers` | git `helmesjo/build2-Vulkan-Headers#review` |
| `libetcpak` | git `helmesjo/build2-etcpak#review` |
| `libimguizmo` | git `helmesjo/build2-imguizmo#review` |
| `librenderdoc-app` | dir `../build2-renderdoc` (`^1.45.0-`), in-application API header |
| `libsquish` | cppget queue (`^1.15.104-`) |
| `libiqa` | cppget queue (`^1.1.2-`) |
| `liblodepng` | cppget queue (`== 2026.1.19`) |
| `libsimplewebp` | cppget queue (`== 2026.7.18`) |
| `libtinyexr` | cppget (`^1.0.8`, pulls `libminiz`) |
| `libiconfontcppheaders` | cppget testing (`>= 2026.6.5-`), `build2-packaging/IconFontCppHeaders` |
| `libtinystl` | `build2-packaging/tinystl` (`^0.0.1-`) |
| `libimgui` | cppget testing (`^1.92.3`, core only) |
| `stb_image_resize2`, `stb_image`, `stb_truetype`, `stb_rect_pack` | cppget (`build2-packaging/stb`) |
| `catch2` | cppget stable |

Official `libimgui-docking` is also on cppget. This repo does not use it.

---

## Currently vendored in this repo

These are the only third-party leftovers **inside the local packages**
(not merely under `upstream/`).

| Item | Path | Compiled today | Package it? |
|---|---|---|---|
| **h264** | `libbgfx/src/h264/` (file-level symlink plus local `LICENSE.txt`) | Wired as `h264/libul{WickedEngine-h264}`, inactive (`BGFX_CONFIG_VIDEO=0`) | **No.** Wicked Engine one-off MIT header. See `libbgfx/DEV-README.md`. |
| **edtaa3** | `libbimg-encode/src/edtaa3/` | Yes (`bimg::imageMakeDist` / SDF) | **No.** Educational Stefan Gustavson snippet. See `libbimg-encode/DEV-README.md`. |
| **vassvik dock** | `bgfx-examples/common/imgui/widgets/dock.{h,inl}` | Yes, in `libue{example-common}` | **No.** Public-domain `imgui_docking_minimal`. Not packaged `libimgui-docking`. |
| metal-cpp shim | `libbgfx/src/3rdparty/metal-cpp/metal.hpp` | macOS only | Not vendored product code. Path shim onto packaged `libmetal-cpp`. |
| renderdoc shim | `libbgfx/src/3rdparty/renderdoc/renderdoc_app.h` | Windows/Linux | Not vendored product code. Path shim onto packaged `librenderdoc-app`. |
| catch stub | `libbx-tests/tests/catch/catch_amalgamated.hpp` | Tests include it | Not vendored product code. Redirects to packaged `catch2`. |

No other in-tree third-party mounts remain under `libbx`, `libbimg`,
`libbimg-encode`, `libbimg-decode`, `libbgfx`, `bgfx-examples`, or
`libbx-tests`.

---

## 1. Required for consumer library features (modern)

These are needed to build and use the primary libraries as shipped today
(encode path, runtime library).

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

Already packaged for encode: `libsquish` (BC1-5), `libastcenc` (ASTC),
`libetcpak` (ETC2/EAC), `stb_image_resize2`, `libiqa`.

Compiled out with nvtt: **etc1** (ETC1) and **pvrtc** (PTC14 / PTC14A).
See [section 4](#4-legacy-hardware-formats).

### `libbgfx`

**h264** stays in-tree. It is a Wicked Engine one-off MIT header, not a
product to package. File-level symlink lives in `src/h264/` with a local
`LICENSE.txt` and `h264/libul{WickedEngine-h264}` target. Include is
`<h264/h264.h>`. Video is compiled out (`BGFX_CONFIG_VIDEO=0`).

No remaining required in-tree third-party product. `librenderdoc-app` supplies
`<renderdoc_app.h>` (shimmed as `<renderdoc/renderdoc_app.h>`). Runtime
`dlopen` of the capture library is unchanged.

Not missing as third-party product code: the `3rdparty/metal-cpp/` and
`3rdparty/renderdoc/` paths are local **shims** to packaged `libmetal-cpp`
and `librenderdoc-app`, not vendored copies.

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
fonts, and `example-glue.cpp` stay in `bgfx-examples`. Git-only extras
added in `9838c26` still avoid meshoptimizer and NanoVG.
`load_program.cpp` is a subset of upstream `bgfx_utils.cpp` without
`meshLoad`.

### `bgfx-examples`

No remaining required in-tree third-party **product**. Depends on
`libimgui` (core only), `libimguizmo`, `libiconfontcppheaders`, and
`libtinystl`.

Dock stays as a first-party overlay extra (file-level symlinks under
`common/imgui/widgets/`). It is vassvik `imgui_docking_minimal`, not
packaged `libimgui-docking`. Other 3rdparty widgets (markdown, color
wheel, ...) are unused by this example subset and are not compiled.

`stb_truetype` / `stb_rect_pack` are not example dependencies. Packaged
imgui ships `imstb_*`. Overlay is built with `USE_LOCAL_STB=0`.

Not compiled by the current example-common build (upstream uses them more
widely, none of them are vendored in the package trees today):

| Missing package (candidate) | Would unlock | Notes |
|---|---|---|
| **meshoptimizer** | Remaining `meshLoad` examples (`04-mesh`, `09-hdr`, `12-lod`, `14-shadowvolumes`, `15-shadowmaps-simple`, `18-ibl`, `28-wireframe`, `30-picking`, `31-rsm`, `36-sky`, `39-assao`, `42-bunnylod`, `43-denoise`, `44-sss`, `45-bokeh`, `46-fsr`) plus `geometryc` | Needed by full `bgfx_utils.cpp` `meshLoad` |
| **cgltf** | `geometryc` glTF path (with meshoptimizer) | Header-only. Not used by current extras |
| **NanoVG** | `10-font`, `11-fontsdf`, `18-ibl`, `20-nanovg` | Lives under upstream `examples/common/nanovg/` with a bgfx backend |
| **sdf** | Font SDF path (`font_manager.cpp`) | Mikko Mononen / Stefan Gustavson snippet, same class as edtaa3 |
| **native_app_glue** | Android entry | NDK helper, not a product to package |

Other skipped upstream examples (`13-stencil`, `16-shadowmaps`, `25-c99`,
`32-particles`, `51-gpufont`, ...) are not necessarily waiting on a missing
package.

---

## 3. Dev / debug / optional, or not part of current packages

Lower priority for packaging against **this** repository as it stands.
Either optional, compile-out, leftover, or only relevant when new packages
are added.

### Optional or compile-out in current builds

| Item | Package that would care | Why lower priority |
|---|---|---|
| **h264** | `libbgfx` | Video disabled (`BGFX_CONFIG_VIDEO=0`). Keep as snippet |
| **khronos** GL/EGL/GLES headers | `libbgfx` if OpenGL/ES enabled | OpenGL/ES compiled out today |

### Not packaged yet (upstream has them, no local package consumes them)

Would become missing-package work only when adding tools packages or the
remaining mesh/font examples.

| Future package surface | Upstream third-party (still missing) |
|---|---|
| **remaining mesh examples** / **geometryc** | meshoptimizer, cgltf |
| **font / nanovg examples** | NanoVG, sdf |
| **shaderc** / tools | fcpp, glsl-optimizer, glslang, spirv-cross, spirv-headers, spirv-tools, dawn/tint, d3d4linux |
| **texturev** | l-smash |

A local `build2-SPIRV-Cross` tree already exists under the packaging workspace
and may help if/when shaderc is packaged.

### Cleanup only (not new packages)

| Item | Where | Note |
|---|---|---|
| **edtaa3** | `libbimg-encode/src/edtaa3/` | Keep. File-level symlinks, own license and `libul` |
| **h264** | `libbgfx/src/h264/` | Keep. File-level symlink, local license, `libul` |
| **vassvik dock** | `bgfx-examples/common/imgui/widgets/` | Keep as overlay extra |
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
| `libbgfx` | h264 stays, video off | Done for v1 |
| `libbx` | none | Done |
| `libbimg` | none | Done |
| `libbimg-decode` | dav1d/libavif (compiled out) | Done for v1 |
| `bgfx-examples` | vassvik dock stays. meshoptimizer/NanoVG/cgltf/sdf not in the current extras | Done for current extras |
| `libbx-tests` | none (`catch2` packaged) | Done |
| *(future)* remaining mesh/font examples, geometryc | meshoptimizer, cgltf, NanoVG, sdf | Next if those ship |
| *(future)* shaderc / tools | see section 3 | Deferred |
| *(legacy)* etc1, pvrtc | section 4 | Lowest |

---

## Suggested unbundle order

1. **meshoptimizer** (then **cgltf**) if remaining mesh examples or
   `geometryc` should ship.

2. **dav1d** / **libavif** if AVIF should be compiled in.

3. **NanoVG** if font/nanovg examples should ship. **sdf** may stay in-tree
   the way edtaa3 does (same class of snippet).

4. **nvtt** only to restore BC6H/BC7 encode. Already compiled out.

5. **Tool stacks** (shaderc, texturev / l-smash) when those packages are
   added.

6. **Legacy encode** (**etc1**, **pvrtc**) and **libheif** last.
