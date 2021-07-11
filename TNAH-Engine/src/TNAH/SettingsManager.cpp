#include "tnahpch.h"
#include "SettingsManager.h"

SettingsManager::SettingsManager()
{
	fullscreen = false;
	toggledFullscreen = false;
}

SettingsManager* SettingsManager::instance = nullptr;
SettingsManager* SettingsManager::GetInstance()
{
	if(instance == nullptr)
	{
		instance = new SettingsManager();
	}

	return instance;
}

void SettingsManager::ToggleFullscreen()
{
	if(fullscreen)
	{
		glfwSetWindowMonitor(windowRef, glfwGetPrimaryMonitor(), 0, 0, (int)windowSize.x, (int)windowSize.y, GLFW_DONT_CARE);
	}
	else
	{
		glfwSetWindowMonitor(windowRef, nullptr, 0, 0, (int)windowSize.x, (int)windowSize.y , GLFW_DONT_CARE);
	}

}