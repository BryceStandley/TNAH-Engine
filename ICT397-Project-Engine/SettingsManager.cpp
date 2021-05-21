#include "SettingsManager.h"

SettingsManager::SettingsManager()
{
	fullscreen = false;
	toggledFullscreen = false;
}

SettingsManager* SettingsManager::instance = 0;
SettingsManager* SettingsManager::GetInstance()
{
	if(instance == nullptr)
	{
		instance = new SettingsManager();
	}

	return instance;
}