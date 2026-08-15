# bgfx

This is a `build2` package repository for the
[bkaradzic](https://github.com/bkaradzic) graphics stack
([bx](https://github.com/bkaradzic/bx), [bimg](https://github.com/bkaradzic/bimg),
[bgfx](https://github.com/bkaradzic/bgfx)).

This file contains setup instructions and other details that are more
appropriate for development rather than consumption. If you want to use these
packages in your `build2`-based project, then instead see the accompanying
`PACKAGE-README.md` files:

- [`libbx`](libbx/PACKAGE-README.md)
- [`libbimg`](libbimg/PACKAGE-README.md)
- [`libbimg-encode`](libbimg-encode/PACKAGE-README.md)
- [`libbimg-decode`](libbimg-decode/PACKAGE-README.md)
- [`libbgfx`](libbgfx/PACKAGE-README.md)
- [`bgfx-examples`](bgfx-examples/PACKAGE-README.md)
- [`libbx-tests`](libbx-tests/PACKAGE-README.md)

## Development

The development setup uses the standard `bdep`-based workflow. For example:

```
git clone --recurse-submodules https://github.com/build2-packaging/bgfx.git
cd bgfx

bdep init -C @gcc cc config.cxx=g++
bdep update
bdep test
```

Upstream sources live as git submodules under `upstream/{bx,bimg,bgfx}/`.
Packages share stack version `1.<BGFX_API_VERSION>.<BGFX_REV_NUMBER>` (currently
1.153.9149 pre-release).
