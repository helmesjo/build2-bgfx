# bgfx - build2 packaging

This is a `build2` multi-package repository for the
[bkaradzic](https://github.com/bkaradzic) graphics stack:

| Package | Upstream | Role |
|---------|----------|------|
| `libbx` | [bx](https://github.com/bkaradzic/bx) | Base utilities |
| `libbimg` | [bimg](https://github.com/bkaradzic/bimg) | Image core (+ astc-encoder) |
| `libbgfx` | [bgfx](https://github.com/bkaradzic/bgfx) | Renderer (Vulkan + Noop) |

Upstream sources live as git submodules under `upstream/{bx,bimg,bgfx}/`.

## Development

```
git clone --recurse-submodules .../bgfx.git
cd bgfx
bdep init -C @apple cc config.cxx=c++
bdep update
bdep test
```

See each package's `PACKAGE-README.md` for consumption notes.

## Version

Packages share stack version `1.<BGFX_API_VERSION>.<BGFX_REV_NUMBER>` (currently
1.153.9149 pre-release).
