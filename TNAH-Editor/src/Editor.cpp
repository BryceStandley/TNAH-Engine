#include <TNAH.h>

#include <imgui.h>

class TestLayer : public tnah::Layer
{
public:
	TestLayer()
		: Layer("Example"), m_CameraPosition(0.0f)
	{
		/*
		m_VAO.reset(tnah::VertexArray::Create());


		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<tnah::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(tnah::VertexBuffer::Create(vertices, sizeof(vertices)));
		tnah::BufferLayout layout = {
			{ tnah::ShaderDataType::Float3, "a_Position" },
			{ tnah::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VAO->AddVertexBuffer(vertexBuffer);



		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<tnah::IndexBuffer> indexBuffer;
		indexBuffer.reset(tnah::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VAO->SetIndexBuffer(indexBuffer);


		m_Shader.reset(tnah::Shader::Create("assets/shaders/Default.glsl"));
		*/
		m_ActiveScene = new tnah::Scene();
		m_Camera = m_ActiveScene->CreateGameObject("Camera");
		m_Camera.AddComponent<tnah::CameraComponent>();

		m_Terrain = m_ActiveScene->CreateGameObject("Terrain");
		auto& t = m_Terrain.AddComponent<tnah::TerrainComponent>("assets/heightmaps/1k.tga");



		m_TerrainVAO.reset(tnah::VertexArray::Create());
		tnah::Ref<tnah::VertexBuffer> terrainVBO;
		terrainVBO.reset(tnah::VertexBuffer::Create(t.SceneTerrain->GetTotalData(), t.SceneTerrain->GetTotalDataSize()));
		terrainVBO->SetLayout(t.SceneTerrain->GetBufferLayout());
		m_TerrainVAO->AddVertexBuffer(terrainVBO);

		tnah::Ref<tnah::IndexBuffer> terrainIBO;
		terrainIBO.reset(tnah::IndexBuffer::Create(t.SceneTerrain->GetIndicesData(), t.SceneTerrain->GetIndicesSize()));
		m_TerrainVAO->SetIndexBuffer(terrainIBO);


		m_TerrainShader.reset(tnah::Shader::Create("assets/shaders/terrain/terrain_vertex.glsl", "assets/shaders/terrain/terrain_fragment.glsl"));

	}

	void OnUpdate(tnah::Timestep deltaTime) override
	{
		
		auto& cameraT = m_Camera.GetComponent<tnah::TransformComponent>();
		if (tnah::Input::IsKeyPressed(tnah::Key::W))
		{
			cameraT.Position.y += m_CameraMoveSpeed * deltaTime.GetSeconds();
		}
		else if (tnah::Input::IsKeyPressed(tnah::Key::S))
		{
			cameraT.Position.y -= m_CameraMoveSpeed * deltaTime.GetSeconds();
		}

		if (tnah::Input::IsKeyPressed(tnah::Key::D))
		{
			cameraT.Position.x += m_CameraMoveSpeed * deltaTime.GetSeconds();
		}
		else if (tnah::Input::IsKeyPressed(tnah::Key::A))
		{
			cameraT.Position.x -= m_CameraMoveSpeed * deltaTime.GetSeconds();
		}


		auto& terr = m_Terrain.GetComponent<tnah::TransformComponent>();

		tnah::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		tnah::RenderCommand::Clear();		
		m_ActiveScene->OnUpdate(deltaTime);
		glm::mat4 transform = cameraT.GetTransform();
		tnah::Renderer::BeginScene(m_Camera.GetComponent<tnah::CameraComponent>().Camera, transform);

		tnah::Renderer::Submit(m_TerrainVAO, m_TerrainShader, terr.GetTransform());

		//tnah::Renderer::Submit(m_VAO, m_Shader);

		

		tnah::Renderer::EndScene();

	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Controls");
		ImGui::Text("WASD to move the camera Up, Down, Left and Right");
		ImGui::End();
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
	tnah::Ref<tnah::Shader> m_Shader;
	tnah::Ref<tnah::VertexArray> m_VAO;

	tnah::Scene* m_ActiveScene;
	tnah::GameObject m_Camera;

	tnah::GameObject m_Terrain;
	tnah::Ref<tnah::Shader> m_TerrainShader;
	tnah::Ref<tnah::VertexArray> m_TerrainVAO;

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
