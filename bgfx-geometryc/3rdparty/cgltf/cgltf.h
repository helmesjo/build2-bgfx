// Compatibility shim: geometryc includes <cgltf/cgltf.h> (bgfx's own vendored
// path) after defining CGLTF_IMPLEMENTATION. libcgltf compiles the
// implementation into the library and exports <cgltf.h> unqualified.
//
#pragma once
#undef CGLTF_IMPLEMENTATION
#include <cgltf.h>
