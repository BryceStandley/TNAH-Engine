#include "MenuGUI.h"

void MenuGUI::Init()
{
    Debugger::GetInstance();
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    //ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui_ImplGlfw_InitForOpenGL(Debugger::GetInstance()->windowRef, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    ImGui::StyleColorsDark();
}

void MenuGUI::Draw()
{

}
