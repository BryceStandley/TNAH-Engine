#include <TNAH.h>

class Game : public tnah::Application
{
public:
	Game()
	{
		PushOverlay(new tnah::ImGuiLayer());
	}


	~Game()
	{
	}


};

tnah::Application* tnah::CreateApplication()
{
	return new Game();
}
