# bgfx-geometryv - Geometry viewer for the bgfx rendering library

This is a `build2` package for the [`geometryv`](https://github.com/bkaradzic/bgfx)
executable. It is an interactive viewer for meshes in the `bgfx` mesh format
produced by `geometryc`.


## Usage

To start using `bgfx-geometryv` in your project, add the following build-time
`depends` value to your `manifest`, adjusting the version constraint as
appropriate:

```
depends: * bgfx-geometryv ^1.153.0
```

Then import the executable in your `buildfile`:

```
import geometryv = bgfx-geometryv%exe{geometryv}
```


## Importable targets

This package provides the following importable targets:

```
exe{geometryv}
```

The geometry viewer. See the upstream
[tools documentation](https://bkaradzic.github.io/bgfx/tools.html) for usage.


## Configuration variables

This package provides no configuration variables.
