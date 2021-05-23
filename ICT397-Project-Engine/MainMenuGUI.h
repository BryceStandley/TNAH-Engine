#pragma once
#include <string>
#include <glad/glad.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_internal.h"
#include "luaManager.h"
#include "stb_image.h"
#include "singleton.h"
#include "Manager.h"
#include "SettingsManager.h"

class MainMenuGUI
{
public:
    static MainMenuGUI* GetInstance();

    void Draw();

    bool LoadTextureFromFile(std::string filename, GLuint* out_texture, int* out_width, int* out_height);

    void DisplaySettings();
    void DisplayMainMenu();
    void DisplayPauseMenu();
	void DisplayDifficultyMenu();
	void DisplayControlsMenu();
	void DisplayDeathScreen();



    void HideMenus();

    bool displayMainMenu = true;
    bool displayPauseMenu = false;
    bool displaySettings = false;
	bool displayDifficulty = false;
	bool displayControls = false;
	bool displayDeathScreen = false;
    bool canDisplayPauseMenu = false;
    bool mainMenuClosed = false;
    bool quitClicked = false;
    bool saveGameClicked = false;
    bool showSavedText = false;
    bool loadGameClicked = false;
    bool noSaveFileFound = false;
    bool newGameClicked = false;
    bool endScreenButtonClicked = false;

    enum PreviousMenu
    {
        MainMenu,
        PauseMenu,
        SettingsMenu,
	    DifficultyMenu,
	    ControlsMenu
    };

    PreviousMenu previousMenu;

    /**
     * @brief Easy access to the settings manager
     */
    SettingsManager* settingsManager;


    /**
     * @brief toggled when any menu is active
     */
    bool displayingAMenu = false;

    std::string gameNameImagePath = "./res/images/ZOOM.png";
    int my_image_width = 0;
    int my_image_height = 0;
    GLuint my_image_texture = 0;
    float imageAspec = 0;

	std::string pausedImagePath = "./res/images/paused.png";
	int pausedWidth = 0;
	int pausedHeight = 0;
	GLuint pausedTexture = 0;
	float pausedImageAspect = 0;

	std::string settingsImagePath = "./res/images/settings.png";
	int settingsWidth = 0;
	int settingsHeight = 0;
	GLuint settingsTexture = 0;
	float settingsImageAspect = 0;

	std::string diffImagePath = "./res/images/difficulty.png";
	int diffWidth = 0;
	int diffHeight = 0;
	GLuint diffTexture = 0;
	float diffImageAspect = 0;

	std::string controlsImagePath = "./res/images/controls.png";
	int controlsWidth = 0;
	int controlsHeight = 0;
	GLuint controlsTexture = 0;
	float controlsImageAspect = 0;

protected:
    explicit MainMenuGUI(std::string scriptPath);
    static MainMenuGUI* instance;

};