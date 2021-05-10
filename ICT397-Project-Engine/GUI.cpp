#include "GUI.h"

void GUI::Init()
{
    Debugger::GetInstance();
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    //ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui_ImplGlfw_InitForOpenGL(Debugger::GetInstance()->windowRef, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    ImGui::StyleColorsDark();
}

void GUI::DrawUI()
{

}

void GUI::DrawDebugUI(Window* w)
{

    std::string windowName = "Debug";

    //Set window size and position before creating the window context from imgui
    ImGui::SetNextWindowSize(ImVec2(0, 0));
    //ImGui::SetNextWindowPos(ImVec2((float)w->SCR_WIDTH + (float)((float)w->SCR_WIDTH - (ImGui::GetWindowWidth() * 1.1f)), 0), true);
    ImGui::SetNextWindowPos(ImVec2(0, 0), true);
    ImGui::Begin(windowName.c_str()); //Create the window

    //debugger.ApplicationFramerate = ImGui::GetIO().Framerate;
    ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
    ImGui::Checkbox("Debug to Console", &Debugger::GetInstance()->debugToConsole);
    ImGui::Checkbox("Debug Collisions to Console", &Debugger::GetInstance()->debugCollisionsToConsole);
    //Add ImGui::Text() fields here to add more data to the debug window


    ImGui::End();
}