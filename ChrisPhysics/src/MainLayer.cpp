#include "MainLayer.h"

#include <imgui.h>
#include <glm/gtc/random.hpp>

#include <TNAH-App.h>

//#include "PhysicsLoader.h"

MainLayer::MainLayer()
	:Layer("Main Layer")
{
	tnah::PhysicsLoader loader("assets/physics.txt");

	m_ActiveScene = tnah::Scene::CreateEmptyScene();
	m_Camera = m_ActiveScene->GetSceneCamera();
	auto& ct = m_Camera.Transform();
	auto& cc = m_Camera.GetComponent<tnah::CameraComponent>();
	cc.Camera.SetViewportSize(1280, 720);
	ct.Position = glm::vec3(-20, 10, -5);
	ct.Rotation = glm::vec3(0, -10, 0);
	cc.ClearMode = tnah::CameraClearMode::Skybox;
	auto& m_Skybox = m_ActiveScene->GetSceneCamera().AddComponent<tnah::SkyboxComponent>();

	tnah::PhysicsProperties p1 = loader.GetObjectAt(0);
	tnah::PhysicsProperties p2 = loader.GetObjectAt(1);
	tnah::PhysicsProperties p3 = loader.GetObjectAt(2);
	m_Box1 = m_ActiveScene->CreateGameObject("Box1");
	m_Box1.AddComponent<tnah::MeshComponent>("assets/meshes/cube_texture.fbx");
	m_Box1.Transform().Position = p1.position;
	m_Box1.Transform().Scale =  p1.lengths;
	auto& rb1 = m_Box1.AddComponent<tnah::RigidBodyComponent>(m_Box1);
	auto col = rb1.AddCollider(p2.lengths);
	col->SetColliderMass(p1.mass);
	rb1.Body->UpdateBodyProperties();


	m_Box2 = m_ActiveScene->CreateGameObject("Box2");
	m_Box2.AddComponent<tnah::MeshComponent>("assets/meshes/cube_texture.fbx");
	m_Box2.Transform().Position = p2.position;
	m_Box2.Transform().Scale = p2.lengths;
	auto& rb2 = m_Box2.AddComponent<tnah::RigidBodyComponent>(m_Box2);
	auto col2 = rb2.AddCollider(p2.lengths);
	col2->SetColliderMass(p2.mass);
	rb2.Body->UpdateBodyProperties();

	m_Ball = m_ActiveScene->CreateGameObject("Ball");
	m_Ball.AddComponent<tnah::MeshComponent>("assets/meshes/sphere.fbx");
	m_Ball.Transform().Position = p3.position;
	m_Ball.Transform().Scale = glm::vec3(p3.radius);
	m_PhysicsSimStartPosition =  m_Ball.Transform().Position;
	auto& rb3 = m_Ball.AddComponent<tnah::RigidBodyComponent>(m_Ball);
	auto col3 = rb3.AddCollider(p3.radius);
	col3->SetColliderMass(p3.mass);
	rb3.Body->UpdateBodyProperties();

	//Set the debug mode to true on launch for physics collider rendering
	tnah::Application::Get().GetDebugModeStatus() = true;
}

void MainLayer::OnUpdate(tnah::Timestep deltaTime)
{
	if (m_CameraMovementToggle)
	{
		auto& ct = m_Camera.Transform();
		if (tnah::Input::IsKeyPressed(tnah::Key::W))
		{
			ct.Position += ct.Forward * m_CameraMovementSpeed * deltaTime.GetSeconds();
		}
		if (tnah::Input::IsKeyPressed(tnah::Key::S))
		{
			ct.Position -= ct.Forward * m_CameraMovementSpeed * deltaTime.GetSeconds();
		}
		if (tnah::Input::IsKeyPressed(tnah::Key::A))
		{
			ct.Position -= ct.Right * m_CameraMovementSpeed * deltaTime.GetSeconds();
		}
		if (tnah::Input::IsKeyPressed(tnah::Key::D))
		{
			ct.Position += ct.Right * m_CameraMovementSpeed * deltaTime.GetSeconds();
		}

		if (tnah::Input::IsKeyPressed(tnah::Key::LeftShift) || tnah::Input::IsKeyPressed(tnah::Key::RightShift))
		{
			if (!m_CameraMovementSpeedOverride)
			{
				m_CameraMovementSpeed = 100.0f;
			}
		}
		else if (!m_CameraMovementSpeedOverride)
		{
			m_CameraMovementSpeed = m_CameraDefaultMovementSpeed;
		}
		else
		{
			m_CameraMovementSpeed = m_CameraOverrideSpeed;
		}
	}
	
	if(m_CameraLookToggle)
	{
		auto& ct = m_Camera.GetComponent<tnah::TransformComponent>();
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
	}

	if(m_StartPhysicsSim)
	{
		TNAH_INFO("Simulation Started");
		auto& rb = m_Ball.GetComponent<tnah::RigidBodyComponent>().Body;
		auto force = glm::vec3(0.0f,0.0f,1.0f) * glm::vec3(0.0f, 0.0f, 5000.0f);
		rb->linearVelocity = {0, 0 ,10};
		m_StartPhysicsSim = false;
	}
	
	//Rendering is managed by the scene!
	m_ActiveScene->OnUpdate(deltaTime);
}

void MainLayer::OnFixedUpdate(tnah::Timestep ts, tnah::PhysicsTimestep ps)
{
	m_ActiveScene->OnFixedUpdate(ts, ps);
}

void MainLayer::OnImGuiRender()
{
	auto windowSize = ImGui::GetMainViewport()->Size;
	const auto windowPos = ImGui::GetMainViewport()->Pos;
	ImGui::SetNextWindowPos(windowPos);
	auto x = windowSize.x / 5.0f;
	if(x < 400) { x = 400; }
	ImGui::SetNextWindowSize({x, windowSize.y});
	static bool m_ApplicationPanel = true;
	ImGui::Begin("Application", &m_ApplicationPanel);
	
	ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
	ImGui::Text("Options");
	if(ImGui::Checkbox("Debug Mode", &tnah::Application::Get().GetDebugModeStatus()))
	{
		tnah::Application::Get().SetDebugStatusChange();
	}
	if(ImGui::CollapsingHeader("Controls & Toggles"))
	{
		ImGui::Text("Key Controls");
		ImGui::BulletText("0 - Debug");
		ImGui::BulletText("1 - Cursor");
		ImGui::BulletText("2 - Wireframe mode");
		ImGui::BulletText("3 - Borderless fullscreen");
		ImGui::BulletText("4 - VSync");
		ImGui::BulletText("5 - Camera look");
		ImGui::BulletText("6 - Camera move");
		ImGui::BulletText("L/R Shift - Camera speed override");
		ImGui::BulletText("ESC - Quit");
		ImGui::NewLine();
		auto& app = tnah::Application::Get();
		ImGui::Text("Toggles");
		ImGui::Checkbox("Cursor", &m_CursorVisible);
		ImGui::Checkbox("Wireframe", &m_Wireframe);
		ImGui::Checkbox("VSync", &m_VSync);
		ImGui::Checkbox("Fullscreen", &m_Fullscreen);
		ImGui::Checkbox("Camera Look", &m_CameraLookToggle);
		ImGui::Checkbox("Camera Movement", &m_CameraMovementToggle);
	}
	if(tnah::Application::Get().GetDebugModeStatus())
	{
		if(ImGui::CollapsingHeader("Debug"))
		{
			ImGui::BulletText("Any application debug controls can go here");
		}
	}
	
	
	
	
	ImGui::Separator();
	
	ImGui::Text("Scene Hierarchy");
	
	ImGui::Separator();
	
	ImGui::Text("Simulation Controls");
	
	ImGui::Text("Physics");
	{
	}
	
	auto size = ImGui::GetContentRegionAvail();
	if(ImGui::Button("Play", {size.x, 30}))
	{
		m_StartPhysicsSim = true;
	}
	if(ImGui::Button("Reset", {size.x, 30}))
	{
		/*auto& m1t = m_Box1.Transform();
		m1t.Position = {0.0f, 10.0f, 0.0f};
		m1t.Rotation = {0.0f, 0.0f, 0.0f};
		m1t.Scale =  {4.0f, 4.0f, 0.5f};
				
		auto& m2t = m_Box2.Transform();
		m2t.Position = {0.0f, 8.0f, 2.0f};
		m2t.Rotation = {0.0f, 0.0f, 0.0f};
		m2t.Scale = {4.0f, 4.0f, 0.5f};

		
		auto& m3t = m_Ball.Transform();
		m3t.Position = m_PhysicsSimStartPosition;
		m3t.Rotation = {0,0,0};
		m_StartPhysicsSim = false;*/
	}
	
	ImGui::End();
	
}

void MainLayer::OnEvent(tnah::Event& event)
{
	//Update the cameras viewport when the window resize event is triggered
	if (event.GetEventType() == tnah::EventType::WindowResize)
	{
		auto& re = (tnah::WindowResizeEvent&)event;
		uint32_t  width = re.GetWidth();
		uint32_t height = re.GetHeight();
		auto& c = m_Camera.GetComponent<tnah::CameraComponent>();
		c.Camera.SetViewportSize(width, height);
	
	}

	if (event.GetEventType() == tnah::EventType::KeyPressed)
	{
		auto& k = (tnah::KeyPressedEvent&)event;
		
		//Toggle the Cursor on or off
		if (k.GetKeyCode() == tnah::Key::D1)
		{
			m_CursorVisible = !m_CursorVisible;
			tnah::Application::Get().GetWindow().SetCursorDisabled(m_CursorVisible);
		}
		//Toggle Wireframe on or off
		if (k.GetKeyCode() == tnah::Key::D2)
		{
			m_Wireframe = !m_Wireframe;
			tnah::RenderCommand::SetWireframe(m_Wireframe);
		}

		//Toggle Fullscreen
		if (k.GetKeyCode() == tnah::Key::D3)
		{
			m_Fullscreen = !m_Fullscreen;
			tnah::Application::Get().GetWindow().ToggleFullScreen(m_Fullscreen);
		}

		//Toggle VSync
		if (k.GetKeyCode() == tnah::Key::D4)
		{
			m_VSync = !m_VSync;
			tnah::Application::Get().GetWindow().SetVSync(m_VSync);
		}

		if (k.GetKeyCode() == tnah::Key::D5)
		{
			m_CameraLookToggle = !m_CameraLookToggle;
		}

		if (k.GetKeyCode() == tnah::Key::D6)
		{
			m_CameraMovementToggle = !m_CameraMovementToggle;
		}
		
		
		if (k.GetKeyCode() == tnah::Key::D0)
		{
			auto& debug = tnah::Application::Get().GetDebugModeStatus();
			debug = !debug;
			tnah::Application::Get().SetDebugStatusChange();
		}
	}
}
