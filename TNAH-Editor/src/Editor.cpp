#include <TNAH.h>

#include <imgui.h>

class TestLayer : public tnah::Layer
{
public:
	TestLayer()
		: Layer("Example"), m_CameraPosition(0.0f)
	{
		

		m_Scene = new tnah::Scene();
		m_Camera = m_Scene->CreateGameObject();
		m_Camera.AddComponent<tnah::CameraComponent>();
		m_Terrain = m_Scene->CreateGameObject();
		m_Terrain.AddComponent<tnah::TerrainComponent>("assets/heightmap/1k.tga");
		m_TerrainShader.reset(tnah::Shader::Create("assets/shaders/default_terrain.glsl"));

	}

	void OnUpdate(tnah::Timestep deltaTime) override
	{

		if (tnah::Input::IsKeyPressed(tnah::Key::W))
		{
			m_Camera.GetComponent<tnah::TransformComponent>().Position.y += m_CameraMoveSpeed * deltaTime.GetSeconds();
		}
		else if (tnah::Input::IsKeyPressed(tnah::Key::S))
		{
			m_Camera.GetComponent<tnah::TransformComponent>().Position.y -= m_CameraMoveSpeed * deltaTime.GetSeconds();
		}

		if (tnah::Input::IsKeyPressed(tnah::Key::D))
		{
			m_Camera.GetComponent<tnah::TransformComponent>().Position.x += m_CameraMoveSpeed * deltaTime.GetSeconds();
		}
		else if (tnah::Input::IsKeyPressed(tnah::Key::A))
		{
			m_Camera.GetComponent<tnah::TransformComponent>().Position.x -= m_CameraMoveSpeed * deltaTime.GetSeconds();
		}

		tnah::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		tnah::RenderCommand::Clear();		
		glm::mat4 transform = m_Camera.GetComponent<tnah::TransformComponent>().GetTransform();
		tnah::Renderer::BeginScene(m_Camera.GetComponent<tnah::CameraComponent>().Camera, transform);
		tnah::Renderer::EndScene();


		m_Camera.GetComponent<tnah::TransformComponent>().Position.z -= 10.0f;
		transform = m_Camera.GetComponent<tnah::TransformComponent>().GetTransform();
		tnah::Renderer::BeginScene(m_Camera.GetComponent<tnah::CameraComponent>().Camera, transform);
		tnah::Terrain* terrain = m_Terrain.GetComponent<tnah::TerrainComponent>().SceneTerrain;
		tnah::Renderer::Submit(terrain->GetVertexArray(), m_TerrainShader);

		tnah::Renderer::EndScene();

	}

	virtual void OnImGuiRender() override
	{

	}

	void OnEvent(tnah::Event& event) override
	{
		tnah::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<tnah::KeyPressedEvent>(TNAH_BIND_EVENTS_FN(TestLayer::OnKeyPressed));
		
	}

	bool OnKeyPressed(tnah::KeyPressedEvent& e)
	{

		return false;
		
	}

private:

	tnah::Scene* m_Scene;
	tnah::GameObject m_Camera;
	tnah::GameObject m_Terrain;
	tnah::Ref<tnah::Shader> m_TerrainShader;

	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 0.1f;
	glm::vec3 m_CameraRotationRadians = glm::vec3(0);
};

class Editor : public tnah::Application
{
public:
	Editor()
		:tnah::Application("TNAH Editor")
	{
		PushOverlay(new TestLayer());
	}


	~Editor()
	{
	}


};

tnah::Application* tnah::CreateApplication()
{
	return new Editor();
}
