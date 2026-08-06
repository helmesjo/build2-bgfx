#include <bgfx/bgfx.h>
#include <bgfx/defines.h>

#undef NDEBUG
#include <cassert>

int main ()
{
  // Non-inline API: query supported renderers without creating a window.
  //
  bgfx::RendererType::Enum types[8];
  uint8_t n = bgfx::getSupportedRenderers (8, types);
  assert (n > 0);

  bool has_noop = false;
  bool has_vulkan = false;
  for (uint8_t i = 0; i < n; ++i)
  {
    if (types[i] == bgfx::RendererType::Noop)
      has_noop = true;
    if (types[i] == bgfx::RendererType::Vulkan)
      has_vulkan = true;
  }

  // Noop is always available. Vulkan is enabled in this package build.
  //
  assert (has_noop);
  assert (has_vulkan);

  assert (BGFX_API_VERSION == 153);

  return 0;
}
