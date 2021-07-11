#ifndef GUI_H
#define GUI_H
#include "Debugger.h"
#include <string>
#include "GlfwWindow.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_internal.h"



#include <LuaBridge/LuaBridge.h>

/**
 * @brief Base class for all GUI
 * @file GUI.h
 * @author Bryce Standley
 * @date MAY 2021
 *
 */
class TNAH_API GUI
{
public:

    virtual void Init(GlfwWindow* win);

    virtual void Draw() {}

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    const char* glsl_version = "#version 330";
};


#endif //TNAH_PROJECT_GUI_H
