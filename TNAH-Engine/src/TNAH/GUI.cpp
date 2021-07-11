#include "tnahpch.h"
#include "GUI.h"


void GUI::Init(GlfwWindow* win)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(win->GetGameWindow(), true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    ImGui::StyleColorsDark();
}
