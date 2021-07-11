#pragma once
#include <string>
#include <glad/glad.h>
#include <imgui.h>
#include "Platform/OpenGL/imgui_impl_glfw.h"
#include "Platform/OpenGL/imgui_impl_opengl3.h"
#include <imgui_internal.h>
#include "luaManager.h"
#include "stb_image.h"
#include "singleton.h"
#include "Manager.h"
#include "SettingsManager.h"

/**
 * @brief Main menu GUI functions
 * @file MainMenuGUI.h
 * @author Bryce Standley
 * @date MAY 2021
 */

class TNAH_API MainMenuGUI
{
public:
	/**
	 * @brief Singleton get function
	 * @return
	 */
    static MainMenuGUI* GetInstance();

    /**
     * @brief Draw main menu function
     */
    void Draw();

    /**
     * @brief ImGui Texture loader
     * @param filename
     * @param out_texture
     * @param out_width
     * @param out_height
     * @return
     */
    bool LoadTextureFromFile(std::string filename, GLuint* out_texture, int* out_width, int* out_height);

    /**
     * @brief Toggles different bools to display the settings menu
     */
    void DisplaySettings();

	/**
	 * @brief Toggles different bools to display the main menu
	 */
    void DisplayMainMenu();

	/**
	 * @brief Toggles different bools to display the pause menu
	 */
    void DisplayPauseMenu();

	/**
	 * @brief Toggles different bools to display the difficulty menu
	 */
	void DisplayDifficultyMenu();

	/**
	 * @brief Toggles different bools to display the controls menu
	 */
	void DisplayControlsMenu();

	/**
	 * @brief Toggles different bools to display the death screen
	 */
	void DisplayDeathScreen();

	/**
	 * @brief Toggles different bools to hide all menus
	 */
    void HideMenus();

    /**
     * @defgroup MainMenuToggles
     * @brief Different toggles for the main menu to trigger different behaviour
     */

    /** @ingroup MainMenuToggles */
    bool displayMainMenu = true;
	/** @ingroup MainMenuToggles */
    bool displayPauseMenu = false;
	/** @ingroup MainMenuToggles */
    bool displaySettings = false;
	/** @ingroup MainMenuToggles */
	bool displayDifficulty = false;
	/** @ingroup MainMenuToggles */
	bool displayControls = false;
	/** @ingroup MainMenuToggles */
	bool displayDeathScreen = false;
	/** @ingroup MainMenuToggles */
    bool canDisplayPauseMenu = false;
	/** @ingroup MainMenuToggles */
    bool mainMenuClosed = false;
	/** @ingroup MainMenuToggles */
    bool quitClicked = false;
	/** @ingroup MainMenuToggles */
    bool saveGameClicked = false;
	/** @ingroup MainMenuToggles */
    bool showSavedText = false;
	/** @ingroup MainMenuToggles */
    bool loadGameClicked = false;
	/** @ingroup MainMenuToggles */
    bool noSaveFileFound = false;
	/** @ingroup MainMenuToggles */
    bool newGameClicked = false;
	/** @ingroup MainMenuToggles */
    bool endScreenButtonClicked = false;
	/** @ingroup MainMenuToggles */
	bool displayingAMenu = false;
	/** @ingroup MainMenuToggles */
	bool playAgainClicked = false;

	/**
	 * @brief Enum to track the last menu visible to the user
	 */
    enum PreviousMenu
    {
        MainMenu,
        PauseMenu,
        SettingsMenu,
	    DifficultyMenu,
	    ControlsMenu
    };

    /**
     * @brief Previous menu object
     */
    PreviousMenu previousMenu;

    /**
     * @brief Easy access to the settings manager
     */
    SettingsManager* settingsManager;

	/** @defgroup MenuImageInformation */

	/** @ingroup MenuImageInformation */
    std::string gameNameImagePath = "./res/images/ZOOM.png";
	/** @ingroup MenuImageInformation */
    int my_image_width = 0;
	/** @ingroup MenuImageInformation */
    int my_image_height = 0;
	/** @ingroup MenuImageInformation */
    GLuint my_image_texture = 0;
	/** @ingroup MenuImageInformation */
    float imageAspec = 0;

	/** @ingroup MenuImageInformation */
	std::string pausedImagePath = "./res/images/paused.png";
	/** @ingroup MenuImageInformation */
	int pausedWidth = 0;
	/** @ingroup MenuImageInformation */
	int pausedHeight = 0;
	/** @ingroup MenuImageInformation */
	GLuint pausedTexture = 0;
	/** @ingroup MenuImageInformation */
	float pausedImageAspect = 0;

	/** @ingroup MenuImageInformation */
	std::string settingsImagePath = "./res/images/settings.png";
	int settingsWidth = 0;
	/** @ingroup MenuImageInformation */
	int settingsHeight = 0;
	/** @ingroup MenuImageInformation */
	GLuint settingsTexture = 0;
	/** @ingroup MenuImageInformation */
	float settingsImageAspect = 0;

	/** @ingroup MenuImageInformation */
	std::string diffImagePath = "./res/images/difficulty.png";
	/** @ingroup MenuImageInformation */
	int diffWidth = 0;
	/** @ingroup MenuImageInformation */
	int diffHeight = 0;
	/** @ingroup MenuImageInformation */
	GLuint diffTexture = 0;
	/** @ingroup MenuImageInformation */
	float diffImageAspect = 0;

	/** @ingroup MenuImageInformation */
	std::string controlsImagePath = "./res/images/controls.png";
	/** @ingroup MenuImageInformation */
	int controlsWidth = 0;
	/** @ingroup MenuImageInformation */
	int controlsHeight = 0;
	/** @ingroup MenuImageInformation */
	GLuint controlsTexture = 0;
	/** @ingroup MenuImageInformation */
	float controlsImageAspect = 0;

protected:
    explicit MainMenuGUI(std::string scriptPath);
    static MainMenuGUI* instance;

};