#include <TNAH.h>

#include <imgui.h>


#include "TNAH/Temp/tempCamera.h"
class TestLayer : public tnah::Layer
{
public:
	TestLayer()
		: Layer("Example")
	{

		m_Scene = tnah::CreateRef<tnah::Scene>();
		m_Camera = m_Scene->CreateGameObject("Camera");
		auto& m_CameaTransform = m_Camera.GetComponent<tnah::TransformComponent>();
		auto& m_cam = m_Camera.AddComponent<tnah::CameraComponent>(m_CameaTransform.GetTransform());


		m_Terrain = m_Scene->CreateGameObject("Terrain");
		m_Terrain.AddComponent<tnah::TerrainComponent>("assets/heightmap/1k.tga");
		m_TerrainShader = tnah::Shader::Create("assets/shaders/terrain/terrain_vertex.glsl", "assets/shaders/terrain/terrain_fragment.glsl");
		

		std::vector<glm::vec3> triPoints;
		triPoints.push_back(glm::vec3(-0.5f, 0.0f, 0.0f));
		triPoints.push_back(glm::vec3(0.5f, 0.0f, 0.0f));
		triPoints.push_back(glm::vec3(0.0f, 0.5f, 0.0f));


		std::vector<uint32_t> triInd;
		triInd.push_back(0);
		triInd.push_back(1);
		triInd.push_back(2);

		m_triangle = tnah::VertexArray::Create();
		triangle = m_triangle->OldGLSetup(triPoints, triInd);
		m_triangleShader = tnah::Shader::Create("assets/shaders/default_vertex.glsl", "assets/shaders/default_fragment.glsl");
	}

	void OnUpdate(tnah::Timestep deltaTime) override
	{
		auto& cam = m_Camera.GetComponent<tnah::CameraComponent>().Camera;
		auto& cameraTransform = m_Camera.GetComponent<tnah::TransformComponent>();
		cam.SetCameraRefTransform(cameraTransform.GetTransform());


		std::unordered_map<std::string, glm::vec3> camPos = cam.OnUpdate(deltaTime, tnah::SceneCamera::CameraMovement::Still);
		cameraTransform.Forward = camPos["forward"];
		cameraTransform.Up = camPos["up"];
		cameraTransform.Right = camPos["right"];
		cameraTransform.Position = camPos["position"];

		auto& t = m_Terrain.GetComponent<tnah::TerrainComponent>();
		std::unordered_map<std::string, uint32_t> terrainIDs = t.SceneTerrain->GetBufferIDs();

		tnah::RenderCommand::Clear();
		//cam.SetViewportSize(1280, 720);

		tnah::Renderer::BeginScene(cam);

		tnah::Renderer::Submit(m_TerrainShader, terrainIDs["VAO"], terrainIDs["VBO"], terrainIDs["IBO"], terrainIDs["IndexSize"], m_Terrain.GetComponent<tnah::TransformComponent>().GetTransform());

		tnah::Renderer::Submit(m_triangleShader, triangle["VAO"], triangle["VBO"], triangle["IBO"], triangle["IndexSize"]);

		tnah::Renderer::EndScene();

		//m_Scene->OnUpdate(deltaTime);

	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Other Debug");
		ImGui::SliderFloat3("Camera Position", glm::value_ptr(m_Camera.GetComponent<tnah::TransformComponent>().Position), 0, 1280);
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
			tnah::RenderCommand::SetViewport(0, 0, width, height);
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

	std::unordered_map<std::string, uint32_t> triangle;

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
		//Disable the cursor on launch
		GetWindow().SetCursorDisabled(false);
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
