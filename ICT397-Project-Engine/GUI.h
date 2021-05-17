#ifndef GUI_H
#define GUI_H
#include "Debugger.h"
#include "GlfwWindow.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_internal.h"

#include <LuaBridge\LuaBridge.h>


class GUI
{
public:

    virtual void Draw() {}

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    const char* glsl_version = "#version 330";
};


#endif //TNAH_PROJECT_GUI_H
