#include "MainMenuGUI.h"

MainMenuGUI* MainMenuGUI::instance = 0;
MainMenuGUI* MainMenuGUI::GetInstance()
{
    if(instance == nullptr)
    {
        instance = new MainMenuGUI("./res/scripts/menus/mainMenu.lua");
    }
    return instance;
}

MainMenuGUI::MainMenuGUI(std::string scriptPath)
{
    lua_State* L = LuaManager::getInstance().getLuaState();

    if (!luaL_dofile(L, scriptPath.c_str()))
    {
        luabridge::LuaRef m = luabridge::getGlobal(L, "displayMainMenu");
        luabridge::LuaRef p = luabridge::getGlobal(L, "displayPauseMenu");
        luabridge::LuaRef s = luabridge::getGlobal(L, "displaySettings");
        luabridge::LuaRef image = luabridge::getGlobal(L, "gameNameImagePath");
        luabridge::LuaRef pausedImage = luabridge::getGlobal(L, "pausedImagePath");
        luabridge::LuaRef settingImage = luabridge::getGlobal(L, "settingsImagePath");



        if (m.isBool()) displayMainMenu = m.cast<bool>();
        if (p.isBool()) displayPauseMenu = p.cast<bool>();
        if (s.isBool()) displaySettings = s.cast<bool>();
        if (image.isString()) gameNameImagePath = image.cast<std::string>();
        if (pausedImage.isString()) pausedImagePath = pausedImage.cast<std::string>();
        if (settingImage.isString()) settingsImagePath = settingImage.cast<std::string>();

    }
    else
    {
        displayMainMenu = true;
        displayPauseMenu = false;
        displaySettings = false;
        displayingAMenu = true;
        gameNameImagePath = "./res/images/ZOOM.png";
        pausedImagePath = "./res/images/paused.png";
        settingsImagePath = "./res/images/settings.png";
    }

    bool ret = LoadTextureFromFile(gameNameImagePath, &my_image_texture, &my_image_width, &my_image_height);
    IM_ASSERT(ret);

    ret = LoadTextureFromFile(pausedImagePath, &pausedTexture, &pausedWidth, &pausedHeight);
    IM_ASSERT(ret);

    ret = LoadTextureFromFile(settingsImagePath, &settingsTexture, &settingsWidth, &settingsHeight);
    IM_ASSERT(ret);

    imageAspec = (float)my_image_height / (float)my_image_width;
    pausedImageAspect = (float)pausedHeight / (float)pausedWidth;
    settingsImageAspect = (float)settingsHeight / (float)settingsWidth;
}

void MainMenuGUI::Draw()
{
    bool open = false;
    bool* open_ptr = &open;

    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoBackground;
    window_flags |= ImGuiWindowFlags_NoTitleBar;

    std::string windowName = "GameMenuBG";
    ImVec2 size = ImGui::GetIO().DisplaySize;
    ImGui::SetNextWindowSize(size); // fill the whole application window
    ImGui::SetNextWindowPos(ImVec2(0, 0), true); // set to draw from the top left corner
    ImGui::Begin(windowName.c_str(), open_ptr, window_flags); //Create the window
    ImGui::End();

    windowName = "GameMenus";
    ImGui::SetNextWindowSize(size); // fill the whole application window
    ImGui::SetNextWindowPos(ImVec2(size.x / 3.0f , (size.y / 5.0f)), true); // set to draw from the top left corner
    ImGui::Begin(windowName.c_str(), open_ptr, window_flags); //Create the window

    ImVec2 centerPos = ImVec2(0, 20.0f);
    centerPos.x = (size.x / 3.0f);

    if(displayMainMenu)
    {
        //Draw the main menu
        ImGui::Image((void*)(intptr_t)my_image_texture, ImVec2(centerPos.x, centerPos.x * imageAspec));
        if(ImGui::Button("NEW GAME", centerPos))
        {
            newGameClicked = true;
        }
        if(ImGui::Button("LOAD GAME", centerPos))
        {
            loadGameClicked = true;
        }
        if(ImGui::Button("SETTINGS", centerPos))
        {
            previousMenu = MainMenu;
            DisplaySettings();
        }
        if(ImGui::Button("CLOSE SCREEN", centerPos))
        {
            endScreenButtonClicked = true;
        }
        if(ImGui::Button("QUIT", centerPos))
        {
            quitClicked = true;
        }
    }
    else if(displayPauseMenu)
    {
        //draw the pause menu
        ImGui::Image((void*)(intptr_t)pausedTexture, ImVec2(centerPos.x, centerPos.x * pausedImageAspect));
        if(ImGui::Button("SAVE GAME", centerPos))
        {
            saveGameClicked = true;
        }
        if(ImGui::Button("SETTINGS", centerPos))
        {
            previousMenu = PauseMenu;
            DisplaySettings();
        }
        if(ImGui::Button("CLOSE SCREEN", centerPos))
        {
            endScreenButtonClicked = true;
        }
        if(ImGui::Button("QUIT", centerPos))
        {
            quitClicked = true;
        }
    }
    else if(displaySettings)
    {
        //todo: add settings manager
        //draw the settings menu
        ImGui::Image((void*)(intptr_t)settingsTexture, ImVec2(centerPos.x, centerPos.x * settingsImageAspect));

        if(ImGui::Button("BACK", centerPos))
        {
            if(previousMenu == MainMenu)
            {
                previousMenu = SettingsMenu;
                DisplayMainMenu();
            }
            else if(previousMenu == PauseMenu)
            {
                previousMenu = SettingsMenu;
                DisplayPauseMenu();
            }
        }
        if(ImGui::Button("CLOSE SCREEN", centerPos))
        {
            endScreenButtonClicked = true;
        }

        if(ImGui::Button("QUIT", centerPos))
        {
            quitClicked = true;
        }
    }




    ImGui::End();
}

void MainMenuGUI::DisplaySettings()
{
    displayingAMenu = true;
    displaySettings = true;
    displayMainMenu = false;
    displayPauseMenu = false;
    canDisplayPauseMenu = false;

}
void MainMenuGUI::DisplayMainMenu()
{
    displayingAMenu = true;
    displayMainMenu = true;
    displayPauseMenu = false;
    displaySettings = false;
    canDisplayPauseMenu = false;
}
void MainMenuGUI::DisplayPauseMenu()
{
    displayingAMenu = true;
    displayPauseMenu = true;
    displaySettings = false;
    displayMainMenu = false;
}
void MainMenuGUI::HideMenus()
{
    displayingAMenu = false;
    displayPauseMenu = false;
    displayMainMenu = false;
    displaySettings = false;
}

void MainMenuGUI::DisplaySettingsFromMainMenu()
{
    displayingAMenu = true;
    displaySettings = true;
    displayMainMenu = true;
    displayPauseMenu = false;
    canDisplayPauseMenu = false;
}



// Simple helper function to load an image into a OpenGL texture with common settings
bool MainMenuGUI::LoadTextureFromFile(std::string filename, GLuint* out_texture, int* out_width, int* out_height)
{
    if (filename.find(".png") != std::string::npos) // if the image is a png, flip
    {
        stbi_set_flip_vertically_on_load(false);
    }

    // Load from file
    int image_width = 0;
    int image_height = 0;
    unsigned char* image_data = stbi_load(filename.c_str() , &image_width, &image_height, nullptr, 4);
    if (image_data == nullptr)
        return false;

    // Create a OpenGL texture identifier
    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

    // Upload pixels into texture
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    stbi_image_free(image_data);

    *out_texture = image_texture;
    *out_width = image_width;
    *out_height = image_height;

    return true;
}
