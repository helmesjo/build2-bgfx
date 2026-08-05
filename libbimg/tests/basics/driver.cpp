#include <bimg/bimg.h>
#include <bx/allocator.h>

#undef NDEBUG
#include <cassert>

int main ()
{
  // Non-inline texture info helper from the core library.
  //
  bimg::TextureInfo ti;
  bimg::imageGetSize (
    &ti,
    64, 64, 1,
    false, false, 1,
    bimg::TextureFormat::RGBA8);

  assert (ti.width == 64);
  assert (ti.height == 64);
  assert (ti.storageSize > 0);

  return 0;
}
