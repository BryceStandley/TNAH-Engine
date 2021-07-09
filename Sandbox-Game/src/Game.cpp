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

};


tnah::Application* tnah::CreateApplication()
{
	return new Game();
}
