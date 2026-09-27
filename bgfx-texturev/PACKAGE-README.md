# bgfx-texturev - Texture viewer for the bgfx rendering library

This is a `build2` package for the [`texturev`](https://github.com/bkaradzic/bgfx)
executable. It is an interactive viewer for the texture and image formats
`bimg` decodes (DDS, KTX, PNG, EXR, and others). Video playback (MP4) is
compiled out.


## Usage

To start using `bgfx-texturev` in your project, add the following build-time
`depends` value to your `manifest`, adjusting the version constraint as
appropriate:

```
depends: * bgfx-texturev ^1.153.0
```

Then import the executable in your `buildfile`:

```
import texturev = bgfx-texturev%exe{texturev}
```


## Importable targets

This package provides the following importable targets:

```
exe{texturev}
```

The texture viewer. See the upstream
[tools documentation](https://bkaradzic.github.io/bgfx/tools.html) for usage.


## Configuration variables

This package provides no configuration variables.
