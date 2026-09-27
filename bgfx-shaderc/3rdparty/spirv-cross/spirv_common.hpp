// Compatibility shim: shaderc names the SPIRV-Cross namespace spirv_cross,
// but libspirv-cross may be built with a different one
// (config.libspirv_cross.namespace, for example MoltenVK's MVK_spirv_cross).
//
#pragma once
#include <spirv_cross/spirv_common.hpp>

#ifdef SPIRV_CROSS_NAMESPACE_OVERRIDE
namespace spirv_cross = SPIRV_CROSS_NAMESPACE_OVERRIDE;
#endif
