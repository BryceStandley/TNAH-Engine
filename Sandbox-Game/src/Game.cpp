#include <TNAH.h>

class TestLayer : public tnah::Layer
{
public:
	TestLayer() : Layer("TestLayer") {}

	void OnUpdate() override
	{
		if (tnah::Input::IsKeyPressed(tnah::Key::A))
		{
			TNAH_INFO("Key : {0} : {1} Pressed", (char)tnah::Key::A, tnah::Key::A);
		}
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
		PushOverlay(new tnah::DebugLayer());
	}


	~Game()
	{
	}


};

tnah::Application* tnah::CreateApplication()
{
	return new Game();
}
