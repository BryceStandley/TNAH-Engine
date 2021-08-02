#include <TNAH.h>

#include <imgui.h>

class TestLayer : public tnah::Layer
{
public:
	TestLayer()
		: Layer("Example")
	{
		
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

		m_Shader.reset(tnah::Shader::Create("assets/shaders/default_vertex.glsl", "assets/shaders/default_fragment.glsl"));


		m_ActiveScene = new tnah::Scene();
		m_Camera = m_ActiveScene->CreateGameObject("Camera");
		auto& cam = m_Camera.AddComponent<tnah::CameraComponent>();
		//cam.Camera.SetViewportSize(1280, 720);
		
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

		auto& terr = m_Terrain.GetComponent<tnah::TransformComponent>();

		tnah::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		tnah::RenderCommand::Clear();	

		m_ActiveScene->OnUpdate(deltaTime);
		tnah::Renderer::BeginScene(m_Camera.GetComponent<tnah::CameraComponent>());

		tnah::Renderer::Submit(m_TerrainVAO, m_TerrainShader, terr.GetTransform());

		tnah::Renderer::Submit(m_VAO, m_Shader);

		

		tnah::Renderer::EndScene();

	}

	virtual void OnImGuiRender() override
	{
		auto& cam = m_Camera.GetComponent<tnah::TransformComponent>();
		auto& terr = m_Terrain.GetComponent<tnah::TransformComponent>();

		ImGui::Begin("Controls");
		ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
		ImGui::Text("Control the camera with the sliders!");
		ImGui::SliderFloat3("Camera Pos", glm::value_ptr(cam.Position), -10000, 10000);
		ImGui::SliderFloat3("Camera Rotation", glm::value_ptr(cam.Rotation), -360, 360);

		ImGui::SliderFloat3("Terrain Scale", glm::value_ptr(terr.Scale), 1, 5);
		ImGui::End();
	}

	void OnEvent(tnah::Event& event) override
	{
		//Update the cameras viewport when the window resize event is triggered
		if (event.GetEventType() == tnah::EventType::WindowResize)
		{
			auto& re = (tnah::WindowResizeEvent&)event;
			uint32_t  width = re.GetWidth();
			uint32_t height = re.GetHeight();
			m_Camera.GetComponent<tnah::CameraComponent>().Camera.SetViewportSize(width, height);
		}
	}


private:
	tnah::Ref<tnah::Shader> m_Shader;
	tnah::Ref<tnah::VertexArray> m_VAO;

	tnah::Scene* m_ActiveScene;
	tnah::GameObject m_Camera;

	tnah::GameObject m_Terrain;
	tnah::Ref<tnah::Shader> m_TerrainShader;
	tnah::Ref<tnah::VertexArray> m_TerrainVAO;

};

class Editor : public tnah::Application
{
public:
	//Create a new Application called Editor and push a test layer onto the layerstack
	Editor()
		:tnah::Application("TNAH Editor")
	{
		PushLayer(new TestLayer());
	}


	~Editor()
	{
	}

	
	void OnEvent(tnah::Event& e)
	{
		//Close the application on press of Escape
		tnah::Application::OnEvent(e);
		if (e.GetEventType() == tnah::EventType::KeyPressed)
		{
			auto k = (tnah::KeyPressedEvent&)e;
			if (k.GetKeyCode() == tnah::Key::Escape)
			{
				tnah::WindowCloseEvent c = tnah::WindowCloseEvent();
				tnah::Application::OnEvent(c);
			}
		}


		//Dispatch an event to the application on window resize
		if (e.GetEventType() == tnah::EventType::WindowResize)
		{
			auto& re = (tnah::WindowResizeEvent&)e;
			tnah::Application::OnEvent(e);
		}
	}

};


//This is required to make a new application with our set layers inside this project.
// this is a single project and only uses engine classes and doesn't have access to all engine specific
// functions like raw OpenGL calls, thats a job for the engine to handle internally.
tnah::Application* tnah::CreateApplication()
{
	return new Editor();
}
