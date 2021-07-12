#include <TNAH.h>
//#include "Scene.h"
#include "TNAH/Events/ApplicationEvent.h"

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
