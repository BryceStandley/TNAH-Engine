#include <TNAH.h>

#include <imgui.h>

class TestLayer : public tnah::Layer
{
public:
	TestLayer()
		: Layer("Example")
    {
	
		m_ActiveScene = new tnah::Scene();
		m_Camera = m_ActiveScene->CreateGameObject("Camera");
		auto& cam = m_Camera.AddComponent<tnah::CameraComponent>();
		cam.Camera.SetViewportSize(1280, 720);
		auto& camT = m_Camera.GetComponent<tnah::TransformComponent>();
		camT.Position = glm::vec3(100,5, 100);
		
		m_Terrain = m_ActiveScene->CreateGameObject("Terrain");
		m_Terrain.AddComponent<tnah::TerrainComponent>("assets/heightmaps/1k.tga");

		m_MeshObject = m_ActiveScene->CreateGameObject("MeshObject");
		
		//auto& mesh = m_MeshObject.AddComponent<tnah::MeshComponent>();
		//mesh.Mesh.reset(new tnah::Mesh("assets/meshes/cube.fbx"));

	}

	void OnUpdate(tnah::Timestep deltaTime) override
	{
		
		auto& cameraT = m_Camera.GetComponent<tnah::TransformComponent>();

		auto& terr = m_Terrain.GetComponent<tnah::TransformComponent>();

		//Camera Movement in a first person way.
		//This can be changed to also look like a 3rd person camera. Similar to a FPS camera in Unity and C#
		if(tnah::Input::IsKeyPressed(tnah::Key::W))
		{
			cameraT.Position += cameraT.Forward * m_CameraMovementSpeed * deltaTime.GetSeconds();
		}
		if(tnah::Input::IsKeyPressed(tnah::Key::S))
		{
			cameraT.Position -= cameraT.Forward * m_CameraMovementSpeed * deltaTime.GetSeconds();
		}
		if(tnah::Input::IsKeyPressed(tnah::Key::A))
		{
			cameraT.Position -= cameraT.Right * m_CameraMovementSpeed * deltaTime.GetSeconds();
		}
		if(tnah::Input::IsKeyPressed(tnah::Key::D))
		{
			cameraT.Position += cameraT.Right * m_CameraMovementSpeed * deltaTime.GetSeconds();
		}

		//Camera Mouse rotation controls
		auto mousePos = tnah::Input::GetMousePos();
		if (m_FirstMouseInput)
		{
			m_LastMouseXPos = mousePos.first;
			m_LastMouseYPos = mousePos.second;
			m_FirstMouseInput = false;
		}

		float offsetX = mousePos.first - m_LastMouseXPos;
		float offsetY = m_LastMouseYPos - mousePos.second;
		m_LastMouseXPos = mousePos.first;
		m_LastMouseYPos = mousePos.second;
		offsetX *= m_CameraMouseSensitivity;
		offsetY *= m_CameraMouseSensitivity;
		cameraT.Rotation.x += offsetX;
		cameraT.Rotation.y += offsetY;
		if (cameraT.Rotation.y > 89.0f)
		{
			cameraT.Rotation.y = 89.0f;
		}
		if (cameraT.Rotation.y < -89.0f)
		{
			cameraT.Rotation.y = -89.0f;
		}

		//Rendering is managed by the scene loaded and checks all the required objects to render
		m_ActiveScene->OnUpdate(deltaTime);
		

	}

	virtual void OnImGuiRender() override
	{
		auto& cam = m_Camera.GetComponent<tnah::TransformComponent>();
		auto& terr = m_Terrain.GetComponent<tnah::TransformComponent>();

		ImGui::Begin("Controls");
		ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
		ImGui::Text("Press 1 to toggle mouse lock");
		ImGui::Text("Press 2 to toggle wireframe mode");
		ImGui::Text("Press ESC to exit");
		ImGui::SliderFloat3("Camera Pos", glm::value_ptr(cam.Position), -10000, 10000);
		ImGui::SliderFloat3("Camera Rotation", glm::value_ptr(cam.Rotation), -360, 360);
		ImGui::SliderFloat("Camera Movement Speed", &m_CameraMovementSpeed, 1, 100);

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
	tnah::Scene* m_ActiveScene;
	tnah::GameObject m_Camera;
	tnah::GameObject m_Terrain;
	tnah::GameObject m_MeshObject;

	float m_CameraMovementSpeed = 20.0f;
	float m_CameraMouseSensitivity = 0.1f;
	float m_LastMouseXPos = 0.0f;
	float m_LastMouseYPos = 0.0f;
	bool m_FirstMouseInput = true;
};

class Editor : public tnah::Application
{
public:
	//Create a new Application called Editor and push a test layer onto the layerstack
	Editor()
		:tnah::Application("TNAH Editor")
	{
		GetWindow().SetCursorDisabled(m_CursorDisabled);
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
			//Toggle the Cursor on or off
			if (k.GetKeyCode() == tnah::Key::D1)
			{
				m_CursorDisabled = !m_CursorDisabled;
				GetWindow().SetCursorDisabled(m_CursorDisabled);
			}
			//Toggle Wireframe on or off
			if (k.GetKeyCode() == tnah::Key::D2)
			{
				m_WireframeEnabled = !m_WireframeEnabled;
				tnah::RenderCommand::SetWireframe(m_WireframeEnabled);
			}
		}
		
		//Dispatch an event to the application on window resize
		if (e.GetEventType() == tnah::EventType::WindowResize)
		{
			auto& re = (tnah::WindowResizeEvent&)e;
			tnah::Application::OnEvent(e);
		}
	}

	bool m_CursorDisabled = true;
	bool m_WireframeEnabled = false;
};


//This is required to make a new application with our set layers inside this project.
// this is a single project and only uses engine classes and doesn't have access to all engine specific
// functions like raw OpenGL calls, thats a job for the engine to handle internally.
tnah::Application* tnah::CreateApplication()
{
	return new Editor();
}
