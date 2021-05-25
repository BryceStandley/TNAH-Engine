#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class SettingsManager
{
public:
	/**
	 * @brief Singelton return of a single static settings manager object
	 * @return instance
	 */
	static SettingsManager* GetInstance();

	/**
	 * @brief Toggle for enabling/disabling the funscreen mode
	 */
	bool fullscreen = false;

	bool toggledFullscreen = false;


	/**
	 * @brief Reference to the GLFW window to enable and disable settings
	 */
	GLFWwindow* windowRef;

	void ToggleFullscreen();

	glm::vec2 windowSize;

protected:
	SettingsManager();
	static SettingsManager* instance;
};

