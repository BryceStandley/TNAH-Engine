#ifndef GUI_H
#define GUI_H
#include "Debugger.h"
#include "Window.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_internal.h"


class GUI
{
public:
    GUI() = default;

    void Init();

    void DrawUI();
    void DrawDebugUI(Window* w);

private:
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    ;
    const char* glsl_version = "#version 330";
};


#endif //TNAH_PROJECT_GUI_H
