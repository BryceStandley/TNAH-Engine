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
		m_TerrainShader = tnah::Shader::Create("assets/shaders/default.glsl");

		m_triangle = tnah::VertexArray::Create();
		float points[3 * 3] = {
			-0.5f, 0.0f, 0.0f,
			0.5f, 0.0f, 0.0f,
			0.0f, 0.5f, 0.0f
		};
		m_triangleVB.reset(tnah::VertexBuffer::Create(points, sizeof(points)));

		uint32_t ind[3] = { 0,1,2 };
		m_triangleIB.reset(tnah::IndexBuffer::Create(ind, sizeof(ind) / sizeof(uint32_t)));


		tnah::BufferLayout layout = {
		{ tnah::ShaderDataType::Float3, "a_Position" }
		};
		m_triangleVB->SetLayout(layout);
		m_triangle->AddVertexBuffer(m_triangleVB);
		
		m_triangle->SetIndexBuffer(m_triangleIB);
		m_triangleShader = tnah::Shader::Create("assets/shaders/default.glsl");

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

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		tnah::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		tnah::RenderCommand::Clear();		

		auto transform = m_Terrain.GetComponent<tnah::TransformComponent>();
		transform.Position -= 10;

		auto cc = m_Camera.GetComponent<tnah::CameraComponent>();
		cc.Camera.SetViewportSize(1280, 720);
		auto camTransform = m_Camera.GetComponent<tnah::TransformComponent>().GetTransform();
		tnah::Renderer::BeginScene(m_Camera.GetComponent<tnah::CameraComponent>().Camera, camTransform);


		glm::mat4 terrainTransform = glm::translate(glm::mat4(1.0f), m_Terrain.GetComponent<tnah::TransformComponent>().Position) * scale;

		tnah::Terrain* terrain = m_Terrain.GetComponent<tnah::TerrainComponent>().SceneTerrain;
		
		tnah::Renderer::Submit(m_triangle, m_triangleShader, terrainTransform);
		tnah::Renderer::Submit(terrain->GetVertexArray(), m_TerrainShader, terrainTransform);

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


	tnah::Ref<tnah::VertexArray> m_triangle;
	tnah::Ref<tnah::VertexBuffer> m_triangleVB;
	tnah::Ref<tnah::IndexBuffer> m_triangleIB;
	tnah::Ref<tnah::Shader> m_triangleShader;
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
