#pragma once
#include <string>
#include <glad/glad.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_internal.h"
#include "luaManager.h"
#include "stb_image.h"

class MainMenuGUI
{
public:
    static MainMenuGUI* GetInstance();

    void Draw();

    bool LoadTextureFromFile(std::string filename, GLuint* out_texture, int* out_width, int* out_height);

    void DisplaySettings();
    void DisplayMainMenu();
    void DisplayPauseMenu();

    void HideMenus();

    bool displayMainMenu = true;
    bool displayPauseMenu = false;
    bool displaySettings = false;
    bool canDisplayPauseMenu = false;
    bool mainMenuClosed = false;
    bool quitClicked = false;
    bool saveGameClicked = false;
    bool loadGameClicked = true;

    /**
     * @brief toggled when any menu is active
     */
    bool displayingAMenu = false;

    std::string gameNameImagePath = "./res/images/ZOOM.png";
    int my_image_width = 0;
    int my_image_height = 0;
    GLuint my_image_texture = 0;
    float imageAspec = 0;

protected:
    explicit MainMenuGUI(std::string scriptPath);
    static MainMenuGUI* instance;

};