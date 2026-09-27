# bimg-texturec - Texture compiler for bimg/bgfx

This is a `build2` package for the [`texturec`](https://github.com/bkaradzic/bimg)
executable. It is a texture compiler that converts PNG, TGA, DDS, KTX, and PVR
textures into `bgfx`-supported texture formats. ETC1, PVRTC, BC6H, and BC7
output is not available because `libbimg-encode` compiles those encoders out.

Note that the `texturec` executable in this package provides `build2` metadata.


## Usage

To start using `bimg-texturec` in your project, add the following build-time
`depends` value to your `manifest`, adjusting the version constraint as
appropriate:

```
depends: * bimg-texturec ^1.153.0
```

Then import the executable in your `buildfile`:

```
import! [metadata] texturec = bimg-texturec%exe{texturec}
```


## Importable targets

This package provides the following importable targets:

```
exe{texturec}
```

The texture compiler command line tool. See `texturec --help` and the upstream
[tools documentation](https://bkaradzic.github.io/bgfx/tools.html) for usage.


## Configuration variables

This package provides no configuration variables.
