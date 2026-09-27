# bgfx-geometryc - Geometry compiler for the bgfx rendering library

This is a `build2` package for the [`geometryc`](https://github.com/bkaradzic/bgfx)
executable. It is a geometry compiler that converts Wavefront `.obj` and
glTF 2.0 (`.gltf`, `.glb`) meshes into the `bgfx` mesh format.

Note that the `geometryc` executable in this package provides `build2`
metadata.


## Usage

To start using `bgfx-geometryc` in your project, add the following build-time
`depends` value to your `manifest`, adjusting the version constraint as
appropriate:

```
depends: * bgfx-geometryc ^1.153.0
```

Then import the executable in your `buildfile`:

```
import! [metadata] geometryc = bgfx-geometryc%exe{geometryc}
```


## Importable targets

This package provides the following importable targets:

```
exe{geometryc}
```

The geometry compiler command line tool. See `geometryc --help` and the
upstream [tools documentation](https://bkaradzic.github.io/bgfx/tools.html)
for usage.


## Configuration variables

This package provides no configuration variables.
