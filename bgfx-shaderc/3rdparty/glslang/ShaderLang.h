// Compatibility shim: shaderc includes <ShaderLang.h> (bgfx's own vendored glslang
// include paths). libglslang installs it as <glslang/Public/ShaderLang.h>.
//
#pragma once
#include <glslang/Public/ShaderLang.h>
