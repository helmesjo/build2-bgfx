// Compatibility shim: shaderc includes <SPIRV/GlslangToSpv.h> (bgfx's own vendored glslang
// include paths). libglslang installs it as <glslang/SPIRV/GlslangToSpv.h>.
//
#pragma once
#include <glslang/SPIRV/GlslangToSpv.h>
