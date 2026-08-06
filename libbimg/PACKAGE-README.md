# libbimg - Image encoding and decoding used by bgfx

This is a `build2` package for the [bimg](https://github.com/bkaradzic/bimg) C++
library. It provides image encoding and decoding used by bgfx.


## Usage

To start using `libbimg` in your project, add the following `depends`
value to your `manifest`, adjusting the version constraint as appropriate:

```
depends: libbimg ^1.153.0
```

Then import the library in your `buildfile`:

```
import libs = libbimg%lib{bimg}
```

Public headers use the `<bimg/...>` include style.


## Importable targets

This package provides the following importable targets:

```
lib{bimg}
```

The image library. Depends on `libbx` and `libastcenc`.


## Configuration variables

This package provides no configuration variables.
