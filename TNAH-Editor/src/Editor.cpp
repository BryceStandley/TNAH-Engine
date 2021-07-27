#include <TNAH.h>

#include <imgui.h>

class TestLayer : public tnah::Layer
{
public:
	TestLayer()
		: Layer("Example")
	{

		m_Scene = tnah::CreateRef<tnah::Scene>();
		m_Camera = m_Scene->CreateGameObject("Camera");
		auto& m_CameaTransform = m_Camera.GetComponent<tnah::TransformComponent>();
		m_Camera.AddComponent<tnah::CameraComponent>(m_CameaTransform.Position);

		m_Terrain = m_Scene->CreateGameObject("Terrain");
		m_Terrain.AddComponent<tnah::TerrainComponent>("assets/heightmap/1k.tga");
		m_TerrainShader = tnah::Shader::Create("assets/shaders/default_terrain.glsl");

		m_triangle = tnah::VertexArray::Create();
		float points[3 * 3] = {
			-0.5f, 0.0f, 0.0f,
			0.5f, 0.0f, 0.0f,
			0.0f, 0.5f, 0.0f
		};
		m_triangle->Bind();
		m_triangleVB = tnah::VertexBuffer::Create(points, sizeof(points));

		std::vector<uint32_t> ind = { 0,1,2 };
		m_triangleIB = tnah::IndexBuffer::Create(ind, sizeof(ind) / sizeof(uint32_t));
		tnah::BufferLayout layout = {
			{tnah::ShaderDataType::Float3, "a_Position"}
		};
		m_triangleVB->SetLayout(layout);
		m_triangle->AddVertexBuffer(m_triangleVB);
		m_triangle->SetIndexBuffer(m_triangleIB);
		m_triangleShader = tnah::Shader::Create("assets/shaders/default.glsl");
	}

	void OnUpdate(tnah::Timestep deltaTime) override
	{
		auto& cam = m_Camera.GetComponent<tnah::CameraComponent>().Camera;
		auto& cameraTransform = m_Camera.GetComponent<tnah::TransformComponent>();
		cam.SetCameraRefPosition(cameraTransform.Position);
		std::unordered_map<std::string, glm::vec3> cameraMap = cam.OnUpdate(deltaTime, tnah::SceneCamera::CameraMovement::Still);

		if (tnah::Input::IsKeyPressed(tnah::Key::W))
		{
			cameraMap = cam.OnUpdate(deltaTime, tnah::SceneCamera::CameraMovement::Forward);
		}
		else if (tnah::Input::IsKeyPressed(tnah::Key::S))
		{
			cameraMap = cam.OnUpdate(deltaTime, tnah::SceneCamera::CameraMovement::Backward);
		}


		if (tnah::Input::IsKeyPressed(tnah::Key::D))
		{
			cameraMap = cam.OnUpdate(deltaTime, tnah::SceneCamera::CameraMovement::Right);
		}
		else if (tnah::Input::IsKeyPressed(tnah::Key::A))
		{
			cameraMap = cam.OnUpdate(deltaTime, tnah::SceneCamera::CameraMovement::Left);
		}


		tnah::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		tnah::RenderCommand::Clear();		
		
		//Update the transform of the camera with the modified information from the camera component
		cameraTransform.Forward = cameraMap["forward"];
		cameraTransform.Right = cameraMap["right"];
		cameraTransform.Up = cameraMap["up"];
		cameraTransform.Position = cameraMap["position"];
		tnah::Renderer::BeginScene(cam);

		auto& terrain = m_Terrain.GetComponent<tnah::TerrainComponent>();
		auto& terrainTransform = m_Terrain.GetComponent<tnah::TransformComponent>();

		
		tnah::Renderer::Submit(m_TerrainShader, terrain.SceneTerrain->GetVertexArray(), terrainTransform.GetTransform());

		tnah::Renderer::Submit(m_triangleShader, m_triangle);


		tnah::Renderer::EndScene();

		//m_Scene->OnUpdate(deltaTime);

	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Other Debug");
		ImGui::Text("%.1f", ImGui::GetIO().Framerate);
		ImGui::End();
	}

	void OnEvent(tnah::Event& event) override
	{
		tnah::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<tnah::KeyPressedEvent>(TNAH_BIND_EVENTS_FN(TestLayer::OnKeyPressed));

		if (event.GetEventType() == tnah::EventType::WindowResize)
		{
			auto& re = (tnah::WindowResizeEvent&)event;

			//This is a temp thing as my display uses dynamic resolution and opengl doesnt know it
			uint32_t  width = re.GetWidth();
			uint32_t height = re.GetHeight();

			if (width > 2560) { width = 2560; }
			if (height > 1080) { height = 1080; }

			m_Camera.GetComponent<tnah::CameraComponent>().Camera.SetViewportSize(width, height);
		}

		if (event.GetEventType() == tnah::EventType::MouseMoved)
		{
			auto mouse = (tnah::MouseMovedEvent&)event;
			tnah::SceneCamera& cam = m_Camera.GetComponent<tnah::CameraComponent>().Camera;
			cam.OnMouseMovement(mouse.GetX(), mouse.GetY(), true);
		}

		
	}

	bool OnKeyPressed(tnah::KeyPressedEvent& e)
	{

		return false;
		
	}

private:
	int m_ViewportWidth, m_ViewportHeight;

	tnah::Ref<tnah::Scene> m_Scene;
	tnah::GameObject m_Camera;
	tnah::GameObject m_Terrain;
	tnah::Ref<tnah::Shader> m_TerrainShader;

	float m_CameraMoveSpeed = 1.0f;
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
		//Disable the corsor on launch
		GetWindow().SetCursorDisabled(true);
		TestLayer* editor = new TestLayer();
		PushOverlay(editor);
	}


	~Editor()
	{
	}

	//Close the application on press of Escape
	void OnEvent(tnah::Event& e)
	{
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

	}

};

tnah::Application* tnah::CreateApplication()
{
	return new Editor();
}
