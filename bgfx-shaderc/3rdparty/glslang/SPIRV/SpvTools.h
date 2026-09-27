// Compatibility shim: shaderc includes <SPIRV/SpvTools.h> (bgfx's own vendored glslang
// include paths). libglslang installs it as <glslang/SPIRV/SpvTools.h>.
//
#pragma once
#include <glslang/SPIRV/SpvTools.h>
