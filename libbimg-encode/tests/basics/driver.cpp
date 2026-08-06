#include <bimg/encode.h>
#include <bimg/bimg.h>
#include <bx/allocator.h>
#include <bx/error.h>

#undef NDEBUG
#include <cassert>
#include <cstring>
#include <vector>

int main ()
{
  bx::DefaultAllocator allocator;

  const uint32_t w = 16;
  const uint32_t h = 16;
  std::vector<uint8_t> src (w * h * 4, 0);
  for (uint32_t i = 0; i < w * h; ++i)
  {
    src[i * 4 + 0] = 255;
    src[i * 4 + 1] = 0;
    src[i * 4 + 2] = 0;
    src[i * 4 + 3] = 255;
  }

  bimg::TextureInfo ti;
  bimg::imageGetSize (
    &ti,
    w, h, 1,
    false, false, 1,
    bimg::TextureFormat::BC1);

  assert (ti.storageSize > 0);

  std::vector<uint8_t> dst (ti.storageSize, 0);
  bx::Error err;

  bimg::imageEncodeFromRgba8 (
    &allocator,
    dst.data (),
    src.data (),
    w, h, 1,
    bimg::TextureFormat::BC1,
    bimg::Quality::Fastest,
    &err);

  assert (err.isOk ());

  return 0;
}
