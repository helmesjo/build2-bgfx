# libbimg-encode

This is a `build2` package for the [bimg](https://github.com/bkaradzic/bimg)
texture encoding library (`bimg_encode` upstream). It compresses images into
GPU formats (BC/DXT, ETC, PVRTC, ASTC, and related helpers).


## Usage

To start using `libbimg-encode` in your project, add the following `depends`
value to your `manifest`, adjusting the version constraint as appropriate:

```
depends: libbimg-encode ^1.153.0
```

Then import the library in your `buildfile`:

```
import libs = libbimg-encode%lib{bimg-encode}
```

Public headers use the `<bimg/encode.h>` include style. They are provided by
the `libbimg` interface dependency.


## Importable targets

This package provides the following importable targets:

```
lib{bimg-encode}
```

The encode library. Depends on `libbimg`, `libastcenc`, and `libsquish`.


## Configuration variables

This package provides no configuration variables.
