# bgfx-geometryc - An executable

This is a `build2` package for the [`<UPSTREAM-NAME>`](https://<UPSTREAM-URL>)
executable. It is a <SUMMARY-OF-FUNCTIONALITY>.

Note that the `bgfx-geometryc` executable in this package provides `build2` metadata.


## Usage

To start using `bgfx-geometryc` in your project, add the following build-time
`depends` value to your `manifest`, adjusting the version constraint as
appropriate:

```
depends: * bgfx-geometryc ^<VERSION>
```

Then import the executable in your `buildfile`:

```
import! [metadata] <TARGET> = bgfx-geometryc%exe{<TARGET>}
```


## Importable targets

This package provides the following importable targets:

```
exe{<TARGET>}
```

<DESCRIPTION-OF-IMPORTABLE-TARGETS>


## Configuration variables

This package provides the following configuration variables:

```
[bool] config.bgfx_geometryc.<VARIABLE> ?= false
```

<DESCRIPTION-OF-CONFIG-VARIABLES>
