#include <TNAH.h>

class TestLayer : public tnah::Layer
{
public:
	TestLayer() : Layer("TestLayer") {}

	void OnUpdate() override
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
		PushOverlay(new tnah::DebugLayer());

		tnah::Scene* m_Scene = new tnah::Scene();

		auto go = m_Scene->CreateGameObject();


		go.AddComponent<tnah::Transform>();
		go.AddComponent<tnah::Transform>();

		go.RemoveComponent<tnah::Transform>();
		go.RemoveComponent<tnah::Transform>();

		go.GetComponent<tnah::Transform>();

		int i;

	}


	~Game()
	{
	}


};

tnah::Application* tnah::CreateApplication()
{
	return new Game();
}
