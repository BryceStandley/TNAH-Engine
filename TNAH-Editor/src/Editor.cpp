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
		camT.Position = glm::vec3(500,60, 500);
		
		m_Terrain = m_ActiveScene->CreateGameObject("Terrain");
		m_Terrain.AddComponent<tnah::TerrainComponent>("assets/heightmaps/1k.tga");

		//Set the terrain to the same scale as zoom!
		auto& terrT = m_Terrain.GetComponent<tnah::TransformComponent>();
		terrT.Scale = glm::vec3(5.0f);

		m_MeshObject = m_ActiveScene->CreateGameObject("MeshObject");

		//Test Cube
		auto& mesh = m_MeshObject.AddComponent<tnah::MeshComponent>();
		mesh.Model.reset(tnah::Model::Create("assets/meshes/cube_texture.fbx"));
		auto& meshT = m_MeshObject.GetComponent<tnah::TransformComponent>();
		meshT.Position = glm::vec3(600, 60.0f, 600);

		m_DirectionalLight = m_ActiveScene->CreateGameObject("Direction Light");
		auto& light = m_DirectionalLight.AddComponent<tnah::LightComponent>(tnah::Light::LightType::Directional);
		glm::vec3 ambient(0.2f, 0.2f, 0.2f);
		glm::vec3 diffuse(0.5f, 0.5f, 0.5f);
		glm::vec3 specular(1.0f, 1.0f, 1.0f);
		glm::vec3 direction(-0.2f, -1.0f, -0.3f);
		light.Light.reset(tnah::Light::CreateDirectional(direction, ambient, diffuse, specular));

	}

	void OnUpdate(tnah::Timestep deltaTime) override
	{
		
		auto& cameraT = m_Camera.GetComponent<tnah::TransformComponent>();

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

		if(tnah::Input::IsKeyPressed(tnah::Key::LeftShift) || tnah::Input::IsKeyPressed(tnah::Key::RightShift))
		{
			if(!m_CameraMovementSpeedOverride)
			{
				m_CameraMovementSpeed = 100.0f;
			}
		}
		else if(!m_CameraMovementSpeedOverride)
		{
			m_CameraMovementSpeed = m_CameraDefaultMovementSpeed;
		}
		else
		{
			m_CameraMovementSpeed = m_CameraOverrideSpeed;
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


		auto& mesh = m_MeshObject.GetComponent<tnah::TransformComponent>();
		mesh.Rotation.y += 1.0f * deltaTime;
		
		//Rendering is managed by the scene loaded and checks all the required objects to render
		m_ActiveScene->OnUpdate(deltaTime);
	}

	void OnFixedUpdate(tnah::PhysicsTimestep ps) override
	{
		m_ActiveScene->OnFixedUpdate(ps);
	}

	virtual void OnImGuiRender() override
	{
		auto& cam = m_Camera.GetComponent<tnah::TransformComponent>();
		auto& terr = m_Terrain.GetComponent<tnah::TransformComponent>();
		auto& light = m_DirectionalLight.GetComponent<tnah::LightComponent>();
		
		static const char* resolutions[]
		{
			"1280x720", "1920x1080", "2560x1080", "2560x1440"
		};
		static int selectedRes = 0;
		ImGui::Begin("Controls");
		ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
		ImGui::Text("Press 1 to toggle mouse lock");
		ImGui::Text("Press 2 to toggle wireframe mode");
		ImGui::Text("Press 3 to toggle borderless fullscreen");
		ImGui::Text("Press 4 to toggle VSync");
		ImGui::Text("Hold Either Shift to move the camera faster");
		ImGui::Text("Press ESC to exit");
		
		ImGui::Text("");
		ImGui::SliderFloat3("Camera Pos", glm::value_ptr(cam.Position), -10000, 10000);
		ImGui::SliderFloat3("Camera Rotation", glm::value_ptr(cam.Rotation), -360, 360);
		ImGui::Checkbox("Camera Speed Override", &m_CameraMovementSpeedOverride);
		if(m_CameraMovementSpeedOverride)
		{
			ImGui::SliderFloat("Camera Movement Speed", &m_CameraOverrideSpeed, 1, m_MaxCameraMovementSpeed);
		}
		else
		{
			ImGui::Text("Camera Movement Speed: %0.1f", m_CameraMovementSpeed);
		}
		
		ImGui::Text("");
		ImGui::SliderFloat3("Terrain Scale", glm::value_ptr(terr.Scale), 1, 20);
		
		ImGui::Text("");
		ImGui::SliderFloat3("Light Direction", glm::value_ptr(light.Light->GetDirection()), -1, 1);
		ImGui::SliderFloat("Light Intensity", &light.Light->GetIntensity(), 0, 10);
		ImGui::ColorPicker3("Light Color", glm::value_ptr(light.Light->GetColor()));
		ImGui::SliderFloat3("Light Ambient", glm::value_ptr(light.Light->GetAmbient()), 0, 1);
		ImGui::SliderFloat3("Light Diffuse", glm::value_ptr(light.Light->GetDiffuse()), 0, 1);
		ImGui::SliderFloat3("Light Specular", glm::value_ptr(light.Light->GetSpecular()), 0, 1);
		
		ImGui::Text("");
		ImGui::Text("Not Implimented Yet!");
		ImGui::Combo("Window Resolution", &selectedRes, resolutions, IM_ARRAYSIZE(resolutions));
		
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
	tnah::GameObject m_DirectionalLight;

	float m_CameraMovementSpeed = 20.0f;
	float m_CameraOverrideSpeed = 20.0f;
	const float m_CameraDefaultMovementSpeed = 20.0f;
	const float m_MaxCameraMovementSpeed = 200.0f;
	bool m_CameraMovementSpeedOverride = false;
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
		GetWindow().SetVSync(m_VSync);
		PushLayer(new TestLayer());
	}


	~Editor()
	{
	}
	
	void OnEvent(tnah::Event& e) override
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

			//Toggle Fullscreen
			if (k.GetKeyCode() == tnah::Key::D3)
			{
				m_Fullscreen = !m_Fullscreen;
				GetWindow().ToggleFullScreen(m_Fullscreen);
			}

			//Toggle VSync
			if (k.GetKeyCode() == tnah::Key::D4)
			{
				m_VSync = !m_VSync;
				GetWindow().SetVSync(m_VSync);
			}
		}
		
		//Dispatch an event to the application on window resize
		if (e.GetEventType() == tnah::EventType::WindowResize)
		{
			auto& re = (tnah::WindowResizeEvent&)e;
			tnah::Application::OnEvent(e);
		}

		if(e.GetEventType() == tnah::EventType::MonitorResolutionChange)
		{
			TNAH_CORE_INFO("Application Received resolution change");
		}
	}

	bool m_CursorDisabled = false;
	bool m_WireframeEnabled = false;
	bool m_Fullscreen = false;
	bool m_VSync = false;
};


//This is required to make a new application with our set layers inside this project.
// this is a single project and only uses engine classes and doesn't have access to all engine specific
// functions like raw OpenGL calls, thats a job for the engine to handle internally.
tnah::Application* tnah::CreateApplication()
{
	return new Editor();
}


