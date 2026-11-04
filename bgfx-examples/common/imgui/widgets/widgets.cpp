/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#ifndef IMGUI_DEFINE_MATH_OPERATORS
#	define IMGUI_DEFINE_MATH_OPERATORS
#endif

#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>

#include <imgui.h>
#include <imgui_internal.h> // dock.inl

#include "range_slider.h"

namespace ImGui
{
	// Single-track, two-handle range slider declared in range_slider.h, built
	// on the public imgui API only. power maps the value range along the
	// track as t^power, 1.0f is linear.
	//
	static float rangeSliderClamp01(float _t)
	{
		return _t < 0.0f ? 0.0f : (_t > 1.0f ? 1.0f : _t);
	}

	static float rangeSliderRatio(float _v, float _min, float _max, float _power)
	{
		const float range = _max - _min;
		const float t = range != 0.0f ? rangeSliderClamp01( (_v - _min) / range) : 0.0f;
		return _power != 1.0f ? std::pow(t, 1.0f / _power) : t;
	}

	static float rangeSliderValue(float _t, float _min, float _max, float _power)
	{
		const float t = _power != 1.0f ? std::pow(_t, _power) : _t;
		return _min + (_max - _min) * t;
	}

	bool RangeSliderFloat(const char* _label, float* _v1, float* _v2, float _min, float _max, const char* _format, float _power)
	{
		const ImGuiStyle& style = GetStyle();
		if (_power <= 0.0f)
		{
			_power = 1.0f;
		}

		PushID(_label);

		const ImVec2 pos    = GetCursorScreenPos();
		const float  width  = CalcItemWidth();
		const float  height = GetFrameHeight();
		InvisibleButton("##range", ImVec2(width, height) );

		const bool hovered = IsItemHovered();
		const bool active  = IsItemActive();

		const float pad        = 2.0f;
		const float trackSize  = width - pad * 2.0f;
		const float grabSize   = trackSize > style.GrabMinSize ? style.GrabMinSize : (trackSize > 0.0f ? trackSize : 0.0f);
		const float usableMin  = pos.x + pad + grabSize * 0.5f;
		const float usableSize = trackSize - grabSize > 0.0f ? trackSize - grabSize : 0.0f;

		bool changed = false;
		if (active)
		{
			const float t     = usableSize > 0.0f ? rangeSliderClamp01( (GetIO().MousePos.x - usableMin) / usableSize) : 0.0f;
			const float value = rangeSliderValue(t, _min, _max, _power);

			// The grab nearest to the click is dragged until release.
			ImGuiStorage* storage = GetStateStorage();
			const ImGuiID grabId  = GetID("##grab");
			if (IsItemActivated() )
			{
				const float d1 = std::fabs(value - *_v1);
				const float d2 = std::fabs(value - *_v2);
				const bool first = d1 != d2 ? d1 < d2 : value < *_v1;
				storage->SetInt(grabId, first ? 0 : 1);
			}

			const bool first = 0 == storage->GetInt(grabId, 0);
			float* v = first ? _v1 : _v2;
			const float clamped = first
				? (value < *_v2 ? value : *_v2)
				: (value > *_v1 ? value : *_v1)
				;

			if (*v != clamped)
			{
				*v = clamped;
				changed = true;
			}
		}

		ImDrawList* drawList = GetWindowDrawList();
		const ImVec2 frameMax(pos.x + width, pos.y + height);
		drawList->AddRectFilled(pos, frameMax
			, GetColorU32(active ? ImGuiCol_FrameBgActive : (hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg) )
			, style.FrameRounding
			);

		const float x1 = usableMin + usableSize * rangeSliderRatio(*_v1, _min, _max, _power);
		const float x2 = usableMin + usableSize * rangeSliderRatio(*_v2, _min, _max, _power);
		const ImU32 grabColor = GetColorU32(active ? ImGuiCol_SliderGrabActive : ImGuiCol_SliderGrab);

		drawList->AddRectFilled(ImVec2(x1, pos.y + height * 0.3f), ImVec2(x2, pos.y + height * 0.7f), GetColorU32(ImGuiCol_SliderGrab), style.GrabRounding);
		drawList->AddRectFilled(ImVec2(x1 - grabSize * 0.5f, pos.y + pad), ImVec2(x1 + grabSize * 0.5f, frameMax.y - pad), grabColor, style.GrabRounding);
		drawList->AddRectFilled(ImVec2(x2 - grabSize * 0.5f, pos.y + pad), ImVec2(x2 + grabSize * 0.5f, frameMax.y - pad), grabColor, style.GrabRounding);

		char text[64];
		std::snprintf(text, sizeof(text), NULL != _format ? _format : "(%.3f, %.3f)", double(*_v1), double(*_v2) );
		const ImVec2 textSize = CalcTextSize(text);
		drawList->PushClipRect(pos, frameMax, true);
		drawList->AddText(ImVec2(pos.x + (width - textSize.x) * 0.5f, pos.y + (height - textSize.y) * 0.5f), GetColorU32(ImGuiCol_Text), text);
		drawList->PopClipRect();

		const char* labelEnd = std::strstr(_label, "##");
		if (labelEnd != _label && '\0' != _label[0])
		{
			SameLine(0.0f, style.ItemInnerSpacing.x);
			TextUnformatted(_label, labelEnd);
		}

		PopID();

		return changed;
	}
} // namespace ImGui

#include "dock.inl"
#include "color_wheel.inl"
