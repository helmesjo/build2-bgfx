// Compatibility shim: bgfx sources include <metal-cpp/metal.hpp>.
// libmetal-cpp exports the multi-header Apple layout.
//
#pragma once
#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>
#include <QuartzCore/QuartzCore.hpp>
