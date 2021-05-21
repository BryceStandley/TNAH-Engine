
class SettingsManager
{
public:
	static SettingsManager* GetInstance();

	bool fullscreen = false;

	bool toggledFullscreen = false;


protected:
	SettingsManager();
	static SettingsManager* instance;
};

