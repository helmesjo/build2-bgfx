#ifndef IMGUI_H_HEADER_GUARD
#define IMGUI_H_HEADER_GUARD

// Overlay compiled out until dear-imgui is a package. Examples still call
// imguiCreate / showExampleDialog / ImGui widgets. Those calls are no-ops.
// Settings stay at their defaults.

#include <bgfx/bgfx.h>
#include <bx/bx.h>

#define IMGUI_MBUT_LEFT   0x01
#define IMGUI_MBUT_RIGHT  0x02
#define IMGUI_MBUT_MIDDLE 0x04

inline uint32_t imguiRGBA(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a = 255)
{
  return 0
    | (uint32_t (_r) <<  0)
    | (uint32_t (_g) <<  8)
    | (uint32_t (_b) << 16)
    | (uint32_t (_a) << 24)
    ;
}

struct ImVec2
{
  float x, y;
  ImVec2 () : x (0.0f), y (0.0f) {}
  ImVec2 (float _x, float _y) : x (_x), y (_y) {}
};

struct ImVec4
{
  float x, y, z, w;
  ImVec4 () : x (0.0f), y (0.0f), z (0.0f), w (0.0f) {}
  ImVec4 (float _x, float _y, float _z, float _w) : x (_x), y (_y), z (_z), w (_w) {}
};

enum ImGuiCond_
{
  ImGuiCond_None          = 0,
  ImGuiCond_Always        = 1 << 0,
  ImGuiCond_Once          = 1 << 1,
  ImGuiCond_FirstUseEver  = 1 << 2
};

typedef int ImGuiCond;

namespace bx { struct AllocatorI; }

void imguiCreate (float _fontSize = 18.0f, bx::AllocatorI* _allocator = NULL);
void imguiDestroy ();

void imguiBeginFrame (int32_t _mx, int32_t _my, uint8_t _button, int32_t _scroll,
                      uint16_t _width, uint16_t _height,
                      int _inputChar = -1, bgfx::ViewId _view = 255);
void imguiEndFrame ();

namespace entry { class AppI; }
void showExampleDialog (entry::AppI* _app, const char* _errorText = NULL);

namespace ImGui
{
  inline void SetNextWindowPos (const ImVec2&, ImGuiCond = 0) {}
  inline void SetNextWindowSize (const ImVec2&, ImGuiCond = 0) {}
  inline bool Begin (const char*, bool* = NULL, int = 0) { return false; }
  inline void End () {}
  inline bool Checkbox (const char*, bool*) { return false; }
  inline bool Combo (const char*, int*, const char* const[], int) { return false; }
  inline void Text (const char*, ...) {}
  inline void TextColored (const ImVec4&, const char*, ...) {}
  inline void TextWrapped (const char*, ...) {}
  inline bool SliderFloat (const char*, float*, float, float) { return false; }
  inline bool SliderInt (const char*, int*, int, int) { return false; }
  inline bool RadioButton (const char*, int*, int) { return false; }
  inline bool RadioButton (const char*, bool) { return false; }
  inline void SameLine (float = 0.0f) {}
  inline void Separator () {}
  inline void BeginDisabled (bool = true) {}
  inline void EndDisabled () {}
  inline bool MouseOverArea () { return false; }
}

#endif
