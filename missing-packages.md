# Missing third-party packages

Inventory of third-party dependencies that current packages still require
but that are **not** yet available as separate `build2` packages
(import/`depends`). Already unbundled packages are listed only for context.

After the unbundle stretch, no in-tree third-party **product** remains in the
local packages. Snippets (edtaa3, h264, vassvik dock, color wheel, sdf) stay
in-tree on purpose.
Compiled-out and future-tool vendors live in the upstream submodule only.

Focus is **modern hardware** support (ETC2/EAC and ASTC already packaged,
BC6H/BC7 encode compiled out). Legacy GPU formats are listed at the bottom.

**Already external** (git prereqs in `repositories.manifest`, or cppget
alpha, queue/testing, testing, or stable):

| Package | Source |
|---|---|
| `libastcenc` | cppget testing (`^5.7.0`) |
| `libmetal-cpp` | cppget testing (`^381.0.0`), macOS only |
| `libdirectx-headers` | cppget testing (`^1.619.5-`), Windows only |
| `libvulkan-headers` | cppget testing (`^1.4.359`) |
| `libmoltenvk` | cppget testing (`^1.4.2`), macOS only. Linked by `bgfx-examples`, `bgfx-geometryv`, and `bgfx-texturev`. `libbgfx` does not depend on it. |
| `libetcpak` | cppget testing (`^2.1.0`) |
| `libimguizmo` | git `helmesjo/build2-imguizmo#review` (`^1.10.0-`) |
| `librenderdoc-app` | git `helmesjo/build2-renderdoc#review` (`^1.45.0-`), in-application API header |
| `libmeshoptimizer` | cppget testing (`^1.2.0`), consumed by `bgfx_utils.cpp`'s `Mesh::load()`/`weldVertices()` and by `bgfx-geometryc` via path shims (`bgfx-examples/common/3rdparty/meshoptimizer/`, `bgfx-geometryc/3rdparty/meshoptimizer/`). v1.2 exports `<meshoptimizer.h>` unqualified. |
| `libsquish` | cppget testing (`^1.15.104-`) |
| `libiqa` | cppget testing (`^1.1.2-`) |
| `liblodepng` | cppget testing (`== 2026.1.19`) |
| `libsimplewebp` | cppget testing (`== 2026.7.18`) |
| `libtinyexr` | cppget testing (`^1.0.8`, pulls `libminiz`) |
| `libiconfontcppheaders` | cppget testing (`>= 2026.6.5-`), `build2-packaging/IconFontCppHeaders` |
| `libtinystl` | cppget alpha (`^0.0.1-`) |
| `libimgui` | cppget testing (`^1.92.3`, core only) |
| `stb_image_resize2`, `stb_image`, `stb_truetype` | cppget testing (`build2-packaging/stb`). `stb_rect_pack` is on cppget stable and is not a dependency. |
| `catch2` | cppget stable (`^3.5.0`) |
| `libcgltf` | git `helmesjo/build2-cgltf#review` (`^1.15.0-`), consumed by `bgfx-geometryc` via a path shim (`3rdparty/cgltf/cgltf.h`, implementation compiled into the library) |
| `libfcpp` | git `helmesjo/build2-fcpp#review` (`^0.0.1-`), `bagder/fcpp` plus patches, consumed by `bgfx-shaderc` with bgfx's buffer sizes |
| `libglslang` | cppget queue/testing (`^16.5.0+1`, `config.libglslang.opt`), consumed by `bgfx-shaderc` via path shims (`3rdparty/glslang/`) |
| `libspirv-tools` | cppget queue/testing (`^1.4.357+1`), consumed by `bgfx-shaderc` |
| `libspirv-cross` | cppget testing (`^1.4.357+1`, glsl, msl, and reflect), consumed by `bgfx-shaderc` via path shims (`3rdparty/spirv-cross/`) |

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
| **color wheel** | `bgfx-examples/common/imgui/widgets/color_wheel.{h,inl}` | Yes, in `libue{example-common}` (`28-wireframe` calls `ImGui::ColorWheel`) | **No.** Same `dear-imgui/widgets/` class as dock. Not packaged. |
| metal-cpp shim | `libbgfx/src/3rdparty/metal-cpp/metal.hpp` | macOS only | Not vendored product code. Path shim onto packaged `libmetal-cpp`. |
| renderdoc shim | `libbgfx/src/3rdparty/renderdoc/renderdoc_app.h` | Windows/Linux | Not vendored product code. Path shim onto packaged `librenderdoc-app`. |
| meshoptimizer shim | `bgfx-examples/common/3rdparty/meshoptimizer/src/meshoptimizer.h` | `bgfx_utils.cpp` | Not vendored product code. Path shim onto packaged `libmeshoptimizer` (v1.2 exports `<meshoptimizer.h>` unqualified; bgfx code expects `<meshoptimizer/src/meshoptimizer.h>`). |
| **sdf** | `bgfx-examples/common/3rdparty/sdf/` | Yes, `font_manager.cpp` defines `SDF_IMPLEMENTATION` | **No.** Mikko Mononen snippet, same class as edtaa3. |
| stb_truetype shim | `bgfx-examples/common/3rdparty/stb/stb_truetype.h` | font manager, NanoVG, `51-gpufont` | Not vendored product code. Path shim onto packaged `stb_truetype` (`<stb_truetype.h>`). One implementation translation unit. |
| iconfont shim | `bgfx-examples/common/3rdparty/iconfontheaders/` | `10-font` | Not vendored product code. Maps `<iconfontheaders/icons_font_awesome.h>` and `<iconfontheaders/icons_kenney.h>` onto `libiconfontcppheaders`. |
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
fonts, and `example-glue.cpp` stay in `bgfx-examples`. `meshoptimizer` is now
packaged and wired in: `bgfx_utils.cpp` (a patched local copy of upstream,
not a symlink, so it keeps the CWD-independent `BGFX_EXAMPLES_*_DIR` path
resolution `load_program.cpp` used to carry) replaced `load_program.cpp`,
and the 15 `meshLoad`-gated examples plus their `meshes/` runtime assets
were added as git-only extras. The numbered desktop examples are all
present. Only `00-helloworld` is distributed. NanoVG is bgfx's own example
backend under `common/nanovg/`, not a separate package. `sdf` stays in-tree.

### `bgfx-examples`

No remaining required in-tree third-party **product**. Depends on
`libimgui` (core only), `libimguizmo`, `libiconfontcppheaders`,
`libtinystl`, `libmeshoptimizer`, and `stb_truetype`. On macOS it also
depends on `libmoltenvk`.

Dock and color wheel stay as first-party overlay extras (file-level
symlinks under `common/imgui/widgets/`). Both are `dear-imgui/widgets/`
snippets (vassvik `imgui_docking_minimal`, upstream `color_wheel`), not
packaged libraries. Other 3rdparty widgets (markdown, ...) are unused by
these examples and are not compiled.

`stb_truetype` is a dependency of the font manager, NanoVG, and
`51-gpufont`. `stb_rect_pack` is not. Packaged imgui ships `imstb_*`.
Overlay is built with `USE_LOCAL_STB=0` so it does not compile a second stb.

Not compiled, and not vendored in the package trees:

| Missing package (candidate) | Would unlock | Notes |
|---|---|---|
| **native_app_glue** | Android entry | NDK helper, not a product to package |

`geometryc` (the offline mesh-authoring tool, as opposed to the runtime
decode path examples use) is packaged as `bgfx-geometryc` with `libcgltf`
and `libmeshoptimizer`.

The numbered desktop examples, including `10-font`, `11-fontsdf`,
`13-stencil`, `16-shadowmaps`, `18-ibl`, `20-nanovg`, `25-c99`,
`32-particles`, and `51-gpufont`, are in the git repository. They are not
in the distributed archive.

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

Would become missing-package work only when adding tools packages.

### Compiled out of the tool packages

| Item | Package | Effect |
|---|---|---|
| **glsl-optimizer** | `bgfx-shaderc` | No GLSL/ESSL output (`libbgfx` has OpenGL/ES compiled out) |
| **dawn/tint** | `bgfx-shaderc` | No WGSL output (`libbgfx` has WebGPU compiled out) |
| **d3d4linux**, DXC headers | `bgfx-shaderc` | HLSL/DXIL output on Windows only |
| **l-smash** | `bgfx-texturev` | No MP4 video playback (`libbgfx` has `BGFX_CONFIG_VIDEO=0`) |

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
| `bgfx-examples` | vassvik dock, color wheel, and sdf stay in-tree | Done: desktop examples added |
| `libbx-tests` | none (`catch2` packaged) | Done |
| `bgfx-shaderc` | glsl-optimizer, dawn/tint, d3d4linux (compiled out) | Done for v1 |
| `bgfx-geometryc` | none | Done |
| `bgfx-geometryv` | none | Done |
| `bgfx-texturev` | l-smash (compiled out) | Done for v1 |
| `bimg-texturec` | none (encoders as in `libbimg-encode`) | Done |
| *(legacy)* etc1, pvrtc | section 4 | Lowest |

---

## Suggested unbundle order

1. ~~**meshoptimizer**~~ Done: cppget testing, `meshLoad`/`weldVertices`
   restored in `bgfx_utils.cpp`, and the 15 unblocked mesh examples added.
   **cgltf** is packaged for `geometryc`.

2. **dav1d** / **libavif** if AVIF should be compiled in.

3. ~~**NanoVG**~~ Not a package. bgfx's example backend is compiled in
   `bgfx-examples`. **sdf** stays in-tree, same class of snippet as edtaa3.

4. **nvtt** only to restore BC6H/BC7 encode. Already compiled out.

5. ~~**Tool stacks**~~ Done: all upstream tools packaged. **l-smash**
   (texturev video), **glsl-optimizer**, and **dawn/tint** (shaderc GLSL/ESSL
   and WGSL output) only if the matching `libbgfx` features are enabled.

6. **Legacy encode** (**etc1**, **pvrtc**) and **libheif** last.
