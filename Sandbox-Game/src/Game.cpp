#include <TNAH.h>

class Game : public tnah::Application
{
public:
	Game()
	{
	}


	~Game()
	{
	}

	void Run();

};

void Game::Run()
{
	Engine* e = new Engine();
	e->Run();
}


tnah::Application* tnah::CreateApplication()
{
	return new Game();
}
