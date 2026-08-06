# libbimg package

Image encoding and decoding used by bgfx (core library plus astc-encoder).

## Usage

```
import libs = libbimg%lib{bimg}
exe{hello}: cxx{**} $libs
```

Depends on `libbx`. Public headers use the `<bimg/...>` include style.

Shared libraries use automatic DLL symbol exporting on Windows (generated
`.def` on MSVC, `--export-all-symbols` on MinGW).
