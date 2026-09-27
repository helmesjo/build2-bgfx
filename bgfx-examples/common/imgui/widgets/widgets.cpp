/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#ifndef IMGUI_DEFINE_MATH_OPERATORS
#	define IMGUI_DEFINE_MATH_OPERATORS
#endif

#include <imgui.h>
#include <imgui_internal.h>

namespace ImGui
{
	// bgfx's vendored imgui_widgets.cpp adds these two helpers for
	// range_slider.inl. Packaged imgui provides the float instances of the
	// underlying templates (see "Template functions" in imgui_internal.h).
	//
	extern template IMGUI_API float RoundScalarWithFormatT<float>(const char* format, ImGuiDataType data_type, float v);
	extern template IMGUI_API float ScaleRatioFromValueT<float, float, float>(ImGuiDataType data_type, float v, float v_min, float v_max, float logarithmic_zero_epsilon, float zero_deadzone_size);

	float RoundScalarWithFormatFloat(const char* format, ImGuiDataType data_type, float v)
	{
		return RoundScalarWithFormatT<float>(format, data_type, v);
	}

	float SliderCalcRatioFromValueFloat(ImGuiDataType data_type, float v, float v_min, float v_max, float power, float linear_zero_pos)
	{
		return ScaleRatioFromValueT<float, float, float>(data_type, v, v_min, v_max, power, linear_zero_pos);
	}
} // namespace ImGui

#include "dock.inl"
#include "color_wheel.inl"
#include "range_slider.inl"
