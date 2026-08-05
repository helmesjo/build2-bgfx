#include <bx/bx.h>
#include <bx/allocator.h>
#include <bx/string.h>

#undef NDEBUG
#include <cassert>

int main ()
{
  // Non-inline: default allocator.
  //
  bx::DefaultAllocator allocator;
  void* p = bx::alloc (&allocator, 64);
  assert (p != nullptr);
  bx::free (&allocator, p);

  // Non-inline string helper.
  //
  char buf[32];
  int32_t n = bx::snprintf (buf, sizeof (buf), "bx-%d", 1);
  assert (n > 0);
  assert (bx::strCmp (buf, "bx-1") == 0);

  return 0;
}
