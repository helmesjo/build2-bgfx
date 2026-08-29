// Compatibility shim: bgfx sources include <meshoptimizer/src/meshoptimizer.h>
// (bgfx's own vendored path). libmeshoptimizer exports <meshoptimizer.h>
// unqualified (upstream v1.2 layout).
//
#pragma once
#include <meshoptimizer.h>
