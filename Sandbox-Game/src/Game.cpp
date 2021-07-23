#include <TNAH.h>

class TestLayer : public tnah::Layer
{
public:
	TestLayer() : Layer("TestLayer") {}

	void OnUpdate(tnah::Timestep deltaTime) override
	{

	}

	void OnEvent(tnah::Event& e) override
	{

	}
};


class Game : public tnah::Application
{
public:
	Game()
	{
		PushLayer(new TestLayer);

		
	}


	~Game()
	{
	}


};

tnah::Application* tnah::CreateApplication()
{
	return new Game();
}
