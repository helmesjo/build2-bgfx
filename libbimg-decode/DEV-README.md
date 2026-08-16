# libbimg-decode packaging notes

## AVIF

AVIF support needs `dav1d` and `libavif`, which are not packaged. This
package compiles with `BIMG_CONFIG_PARSE_AVIF=0` until those exist. HEIF
stays off (upstream default, LGPL).
