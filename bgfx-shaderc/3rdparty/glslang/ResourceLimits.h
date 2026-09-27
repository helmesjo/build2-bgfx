// Compatibility shim: shaderc includes <ResourceLimits.h> (bgfx's own vendored glslang
// include paths). libglslang installs it as <glslang/Public/ResourceLimits.h>.
//
#pragma once
#include <glslang/Public/ResourceLimits.h>
