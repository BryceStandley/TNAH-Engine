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

		tnah::Scene* m_Scene = new tnah::Scene();

		auto go = m_Scene->CreateGameObject();

		{
			using namespace tnah;
			go.AddComponent<Transform>();
			go.AddComponent<Transform>();

			go.RemoveComponent<Transform>();
			go.RemoveComponent<Transform>();

			go.GetComponent<Transform>();
		}


	}


	~Game()
	{
	}


};

tnah::Application* tnah::CreateApplication()
{
	return new Game();
}
