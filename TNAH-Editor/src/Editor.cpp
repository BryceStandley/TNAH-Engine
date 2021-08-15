#include <TNAH.h>

#include <imgui.h>
#include <glm/gtc/random.hpp>
class TestLayer : public tnah::Layer
{
public:
	TestLayer()
		: Layer("Example")
    {
		m_ActiveScene = tnah::Scene::CreateEmptyScene();
		m_Camera = m_ActiveScene->GetMainCameraGameObject();
		auto& ct = m_Camera->GetComponent<tnah::TransformComponent>();
		auto& cc = m_Camera->GetComponent<tnah::CameraComponent>();
		cc.Camera.SetViewportSize(1280, 720);
		ct.Position = glm::vec3(500,60, 500);

		m_SceneLight = m_ActiveScene->GetSceneLightGameObject();
		
		m_Terrain = m_ActiveScene->CreateGameObject("Terrain");
		m_Terrain->AddComponent<tnah::TerrainComponent>("assets/heightmaps/1k.tga");
		auto& terrT = m_Terrain->GetComponent<tnah::TransformComponent>();
		terrT.Scale = glm::vec3(5.0f);

		m_PointLight = m_ActiveScene->CreateGameObject("PointLight");
		auto& light = m_PointLight->GetComponent<tnah::LightComponent>();
		light.Light->CreatePoint();

		for(int i = 0; i < 100; i++)
		{
			//Test Cube
			std::string name = "Cube" + std::to_string(i);
			auto go = m_ActiveScene->CreateGameObject(name);
			
			auto& mesh = go->AddComponent<tnah::MeshComponent>();
			mesh.Model.reset(tnah::Model::Create("assets/meshes/cube_texture.fbx"));
			auto& meshT = go->GetComponent<tnah::TransformComponent>();

			glm::vec3 p(glm::linearRand(500, 700), glm::linearRand(50, 100), glm::linearRand(500, 700));
			meshT.Position = p;
			m_MeshObjects.push_back(go);
		}

	}

	void OnUpdate(tnah::Timestep deltaTime) override
	{
		auto& ct = m_Camera->GetComponent<tnah::TransformComponent>();
		//Camera Movement in a first person way.
		//This can be changed to also look like a 3rd person camera. Similar to a FPS camera in Unity and C#
		if(tnah::Input::IsKeyPressed(tnah::Key::W))
		{
			ct.Position += ct.Forward * m_CameraMovementSpeed * deltaTime.GetSeconds();
		}
		if(tnah::Input::IsKeyPressed(tnah::Key::S))
		{
			ct.Position -= ct.Forward * m_CameraMovementSpeed * deltaTime.GetSeconds();
		}
		if(tnah::Input::IsKeyPressed(tnah::Key::A))
		{
			ct.Position -= ct.Right * m_CameraMovementSpeed * deltaTime.GetSeconds();
		}
		if(tnah::Input::IsKeyPressed(tnah::Key::D))
		{
			ct.Position += ct.Right * m_CameraMovementSpeed * deltaTime.GetSeconds();
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
		ct.Rotation.x += offsetX;
		ct.Rotation.y += offsetY;
		if (ct.Rotation.y > 89.0f)
		{
			ct.Rotation.y = 89.0f;
		}
		if (ct.Rotation.y < -89.0f)
		{
			ct.Rotation.y = -89.0f;
		}


		for(auto go : m_MeshObjects)
		{
			auto& mesh = go->GetComponent<tnah::TransformComponent>();
			mesh.Rotation.y += 1.0f * deltaTime;
		}
		
		//Rendering is managed by the scene!
		m_ActiveScene->OnUpdate(deltaTime);
	}

	void OnFixedUpdate(tnah::PhysicsTimestep ps) override
	{
		m_ActiveScene->OnFixedUpdate(ps);
	}

	virtual void OnImGuiRender() override
	{
		auto& terr = m_Terrain->GetComponent<tnah::TransformComponent>();
		auto& ct = m_Camera->GetComponent<tnah::TransformComponent>();
		auto& l = m_SceneLight->GetComponent<tnah::LightComponent>();
		auto& lt = m_SceneLight->GetComponent<tnah::TransformComponent>();

		auto& plt = m_PointLight->GetComponent<tnah::TransformComponent>();
		auto& pl = m_PointLight->GetComponent<tnah::LightComponent>();
		static int lightType = 0;
		static const char* LightTypes[]
		{
			"Directional", "Point", "Spot"	
		};

		static int lightDistance = 0;
		static const char* lightDistances[]
		{
			"10", "15", "20", "50", "100", "200"
		};
		
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
		ImGui::SliderFloat3("Camera Pos", glm::value_ptr(ct.Position), -10000, 10000);
		ImGui::SliderFloat3("Camera Rotation", glm::value_ptr(ct.Rotation), -360, 360);
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
		ImGui::Text("Global Scene Light");
		ImGui::SliderFloat3("Light Position", glm::value_ptr(lt.Position), -1000, 1000);
		ImGui::SliderFloat3("Light Direction", glm::value_ptr(l.Light->GetDirection()), -1, 1);
		ImGui::SliderFloat("Light Intensity", &l.Light->GetIntensity(), 0, 10);
		ImGui::ColorEdit3("Light Color", glm::value_ptr(l.Light->GetColor()));
		ImGui::SliderFloat3("Light Ambient", glm::value_ptr(l.Light->GetAmbient()), 0, 1);
		ImGui::SliderFloat3("Light Diffuse", glm::value_ptr(l.Light->GetDiffuse()), 0, 1);
		ImGui::SliderFloat3("Light Specular", glm::value_ptr(l.Light->GetSpecular()), 0, 1);

		ImGui::SliderFloat3("Point Position", glm::value_ptr(plt.Position), -1000, 1000);
		ImGui::ColorEdit3("Point Color", glm::value_ptr(pl.Light->GetColor()));
		ImGui::SliderFloat("Point Intensity", &pl.Light->GetIntensity(), 0, 10);
		
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
			if(m_Camera != nullptr)
			{
				auto& c = m_Camera->GetComponent<tnah::CameraComponent>();
				c.Camera.SetViewportSize(width, height);	
			}
		}
	}


private:
	tnah::Scene* m_ActiveScene;
	tnah::Ref<tnah::GameObject> m_Camera;
	tnah::GameObject* m_Terrain;
	std::vector<tnah::GameObject*> m_MeshObjects;
	tnah::Ref<tnah::GameObject> m_SceneLight;

	tnah::GameObject* m_PointLight;

	float m_LightCutoff = 12.5f;
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

	friend class TestLayer;
};


//This is required to make a new application with our set layers inside this project.
// this is a single project and only uses engine classes and doesn't have access to all engine specific
// functions like raw OpenGL calls, thats a job for the engine to handle internally.
tnah::Application* tnah::CreateApplication()
{
	return new Editor();
}


