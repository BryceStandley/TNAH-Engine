#include "MainLayer.h"

#include <imgui.h>
#include <glm/gtc/random.hpp>

#include <TNAH-App.h>
#include <glm/gtx/string_cast.hpp>

//#include "PhysicsLoader.h"

MainLayer::MainLayer()
	:Layer("Main Layer")
{
	loader.LoadFile("assets/physics.txt");
	m_ActiveScene = tnah::Scene::CreateEmptyScene();
	m_Camera = m_ActiveScene->GetSceneCamera();
	auto& ct = m_Camera.Transform();
	auto& cc = m_Camera.GetComponent<tnah::CameraComponent>();
	cc.Camera.SetViewportSize(1280, 720);
	ct.Position = glm::vec3(-15, 10, -5);
	ct.Rotation = glm::vec3(0, -10, 0);
	cc.ClearMode = tnah::CameraClearMode::Skybox;
	auto& m_Skybox = m_ActiveScene->GetSceneCamera().AddComponent<tnah::SkyboxComponent>();

	{
		auto & go = 	m_ActiveScene->CreateGameObject("Background hehe");
		go.AddComponent<tnah::MeshComponent>("assets/meshes/background.fbx");
		go.Transform().Position = {20, 10, 0};
		go.Transform().Scale = {1, 50, 50};
	}
	
	tnah::PhysicsProperties p1 = loader.GetObjectAt(0);
	tnah::PhysicsProperties p2 = loader.GetObjectAt(1);
	tnah::PhysicsProperties p3 = loader.GetObjectAt(2);
	m_Box1 = m_ActiveScene->CreateGameObject("Box1");
	m_Box1.AddComponent<tnah::MeshComponent>("assets/meshes/texturecube.fbx");
	m_Box1.Transform().Position = p1.position;
	m_Box1.Transform().Scale =  p1.lengths;
	auto& rb1 = m_Box1.AddComponent<tnah::RigidBodyComponent>(m_Box1);
	auto col = rb1.AddCollider(p2.lengths);
	col->SetColliderMass(p1.mass);
	rb1.Body->UpdateBodyProperties();


	m_Box2 = m_ActiveScene->CreateGameObject("Box2");
	m_Box2.AddComponent<tnah::MeshComponent>("assets/meshes/texturecube.fbx");
	m_Box2.Transform().Position = p2.position;
	m_Box2.Transform().Scale = p2.lengths;
	auto& rb2 = m_Box2.AddComponent<tnah::RigidBodyComponent>(m_Box2);
	auto col2 = rb2.AddCollider(p2.lengths);
	col2->SetColliderMass(p2.mass);
	rb2.Body->UpdateBodyProperties();

	m_Ball = m_ActiveScene->CreateGameObject("Ball");
	m_Ball.AddComponent<tnah::MeshComponent>("assets/meshes/s23b.fbx");
	m_Ball.Transform().Position = p3.position;
	startingPos = p3.position;
	m_Ball.Transform().Scale = glm::vec3(p3.radius);
	auto& rb3 = m_Ball.AddComponent<tnah::RigidBodyComponent>(m_Ball);
	auto col3 = rb3.AddCollider(p3.radius);
	col3->SetColliderMass(p3.mass);
	rb3.Body->UpdateBodyProperties();

	//Set the debug mode to true on launch for physics collider rendering
	tnah::Application::Get().GetDebugModeStatus() = true;
}

void MainLayer::OnUpdate(tnah::Timestep deltaTime)
{

	if(tnah::Input::IsKeyPressed(tnah::Key::Down))
	{
		auto& transform = m_Ball.GetComponent<tnah::TransformComponent>();
		transform.Position.y -= 2 * deltaTime.GetSeconds();
		startingPos = transform.Position;
	}

	if(tnah::Input::IsKeyPressed(tnah::Key::Up))
	{
		auto& transform = m_Ball.GetComponent<tnah::TransformComponent>();
		transform.Position.y += 2 * deltaTime.GetSeconds();
		startingPos = transform.Position;
	}
	
	if(m_StartPhysicsSim)
	{
		tnah::PhysicsProperties p1 = loader.GetObjectAt(0);
		tnah::PhysicsProperties p2 = loader.GetObjectAt(1);
		tnah::PhysicsProperties p3 = loader.GetObjectAt(2);
		TNAH_INFO("Simulation Started");
		{
			auto& rb = m_Box1.GetComponent<tnah::RigidBodyComponent>().Body;
			auto& transform = m_Box1.GetComponent<tnah::TransformComponent>();
			transform.Position = p1.position;
			rb->Orientation = {1.0, 0, 0, 0};
			rb->linearVelocity = {0, 0 ,0};
			rb->angularVelocity = {0,0,0};
		}
		
		{
			auto& rb = m_Box2.GetComponent<tnah::RigidBodyComponent>().Body;
			auto& transform = m_Box2.GetComponent<tnah::TransformComponent>();
			
			transform.Position = p2.position;
			rb->Orientation = {1.0, 0, 0, 0};
			rb->linearVelocity = {0, 0 ,0};
			rb->angularVelocity = {0,0,0};
		}
		
		{
			auto& rb = m_Ball.GetComponent<tnah::RigidBodyComponent>().Body;
			auto& transform = m_Ball.GetComponent<tnah::TransformComponent>();
			transform.Position = startingPos;
			rb->Orientation = {1.0, 0, 0, 0};
			rb->linearVelocity = {0, 0 ,2};
			rb->angularVelocity = {0,0,1};
		}
		m_StartPhysicsSim = false;
	}
	
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
	ImGui::Text("Options");
	
	if(ImGui::Checkbox("Debug Mode", &tnah::Application::Get().GetDebugModeStatus()))
	{
		tnah::Application::Get().SetDebugStatusChange();
	}
	
	ImGui::Separator();
	
	ImGui::Text("Game Objects");
	{
		auto& rb = m_Box1.GetComponent<tnah::RigidBodyComponent>().Body;
		auto& transform = m_Box1.GetComponent<tnah::TransformComponent>();
		auto tag = m_Box1.GetComponent<tnah::TagComponent>();
		std::string position = "Position: " + glm::to_string(transform.Position);
		std::string rotation = "Orientation: " + glm::to_string(glm::degrees(glm::eulerAngles(transform.QuatRotation)));
		std::string linearVelocity = "linearVelocity: " + glm::to_string(rb->linearVelocity);
		std::string angularVelocity = "angularVelocity: " + glm::to_string(rb->angularVelocity);
		ImGui::Text(tag.Tag.c_str());
		ImGui::Text(position.c_str());
		ImGui::Text(rotation.c_str());
		ImGui::Text(linearVelocity.c_str());
		ImGui::Text(angularVelocity.c_str());
		ImGui::Separator();
	}
		
	{
		auto& rb = m_Box2.GetComponent<tnah::RigidBodyComponent>().Body;
		auto& transform = m_Box2.GetComponent<tnah::TransformComponent>();
		auto tag = m_Box2.GetComponent<tnah::TagComponent>();
		std::string position = "Position: " + glm::to_string(transform.Position);
		std::string rotation = "Orientation: " + glm::to_string(glm::degrees(glm::eulerAngles(transform.QuatRotation)));
		std::string linearVelocity = "linearVelocity: " + glm::to_string(rb->linearVelocity);
		std::string angularVelocity = "angularVelocity: " + glm::to_string(rb->angularVelocity);
		ImGui::Text(tag.Tag.c_str());
		ImGui::Text(position.c_str());
		ImGui::Text(rotation.c_str());
		ImGui::Text(linearVelocity.c_str());
		ImGui::Text(angularVelocity.c_str());
		ImGui::Separator();
	}
		
	{
		auto& rb = m_Ball.GetComponent<tnah::RigidBodyComponent>().Body;
		auto& transform = m_Ball.GetComponent<tnah::TransformComponent>();
		auto tag = m_Ball.GetComponent<tnah::TagComponent>();
		std::string position = "Position: " + glm::to_string(transform.Position);
		std::string rotation = "Orientation: " + glm::to_string(glm::degrees(glm::eulerAngles(transform.QuatRotation)));
		std::string linearVelocity = "linearVelocity: " + glm::to_string(rb->linearVelocity);
		std::string angularVelocity = "angularVelocity: " + glm::to_string(rb->angularVelocity);
		ImGui::Text(tag.Tag.c_str());
		ImGui::Text(position.c_str());
		ImGui::Text(rotation.c_str());
		ImGui::Text(linearVelocity.c_str());
		ImGui::Text(angularVelocity.c_str());
		ImGui::Separator();
	}

	ImGui::Text("Move ball using up and down (for y axis)");
	ImGui::Separator();

	if(ImGui::Button("Physics 1"))
	{
		loader.LoadFile("assets/physics.txt");
		tnah::PhysicsProperties p1 = loader.GetObjectAt(0);
		tnah::PhysicsProperties p2 = loader.GetObjectAt(1);
		tnah::PhysicsProperties p3 = loader.GetObjectAt(2);
		TNAH_INFO("Loaded physics 1");
		{
			auto& rb = m_Box1.GetComponent<tnah::RigidBodyComponent>().Body;
			auto& transform = m_Box1.GetComponent<tnah::TransformComponent>();
			transform.Position = p1.position;
			rb->Orientation = {1.0, 0, 0, 0};
			rb->linearVelocity = {0, 0 ,0};
			rb->angularVelocity = {0,0,0};
		}
		
		{
			auto& rb = m_Box2.GetComponent<tnah::RigidBodyComponent>().Body;
			auto& transform = m_Box2.GetComponent<tnah::TransformComponent>();
			
			transform.Position = p2.position;
			rb->Orientation = {1.0, 0, 0, 0};
			rb->linearVelocity = {0, 0 ,0};
			rb->angularVelocity = {0,0,0};
		}
		
		{
			auto& rb = m_Ball.GetComponent<tnah::RigidBodyComponent>().Body;
			auto& transform = m_Ball.GetComponent<tnah::TransformComponent>();
			startingPos = p3.position;
			transform.Position = startingPos;
			rb->Orientation = {1.0, 0, 0, 0};
			rb->linearVelocity = {0, 0 ,0};
			rb->angularVelocity = {0,0,0};
		}
	}

	if(ImGui::Button("Physics 2"))
	{
		loader.LoadFile("assets/physics2.txt");
		tnah::PhysicsProperties p1 = loader.GetObjectAt(0);
		tnah::PhysicsProperties p2 = loader.GetObjectAt(1);
		tnah::PhysicsProperties p3 = loader.GetObjectAt(2);
		TNAH_INFO("Loaded physics 2");
		{
			auto& rb = m_Box1.GetComponent<tnah::RigidBodyComponent>().Body;
			auto& transform = m_Box1.GetComponent<tnah::TransformComponent>();
			transform.Position = p1.position;
			rb->Orientation = {1.0, 0, 0, 0};
			rb->linearVelocity = {0, 0 ,0};
			rb->angularVelocity = {0,0,0};
		}
		
		{
			auto& rb = m_Box2.GetComponent<tnah::RigidBodyComponent>().Body;
			auto& transform = m_Box2.GetComponent<tnah::TransformComponent>();
			
			transform.Position = p2.position;
			rb->Orientation = {1.0, 0, 0, 0};
			rb->linearVelocity = {0, 0 ,0};
			rb->angularVelocity = {0,0,0};
		}
		
		{
			auto& rb = m_Ball.GetComponent<tnah::RigidBodyComponent>().Body;
			auto& transform = m_Ball.GetComponent<tnah::TransformComponent>();
			startingPos = p3.position;
			transform.Position = startingPos;
			rb->Orientation = {1.0, 0, 0, 0};
			rb->linearVelocity = {0, 0 ,0};
			rb->angularVelocity = {0,0,0};
		}
	}

	if(ImGui::Button("Physics 3"))
	{
		loader.LoadFile("assets/physics3.txt");
		tnah::PhysicsProperties p1 = loader.GetObjectAt(0);
		tnah::PhysicsProperties p2 = loader.GetObjectAt(1);
		tnah::PhysicsProperties p3 = loader.GetObjectAt(2);
		TNAH_INFO("Loaded physics 3");
		{
			auto& rb = m_Box1.GetComponent<tnah::RigidBodyComponent>().Body;
			auto& transform = m_Box1.GetComponent<tnah::TransformComponent>();
			transform.Position = p1.position;
			rb->Orientation = {1.0, 0, 0, 0};
			rb->linearVelocity = {0, 0 ,0};
			rb->angularVelocity = {0,0,0};
		}
		
		{
			auto& rb = m_Box2.GetComponent<tnah::RigidBodyComponent>().Body;
			auto& transform = m_Box2.GetComponent<tnah::TransformComponent>();
			
			transform.Position = p2.position;
			rb->Orientation = {1.0, 0, 0, 0};
			rb->linearVelocity = {0, 0 ,0};
			rb->angularVelocity = {0,0,0};
		}
		
		{
			auto& rb = m_Ball.GetComponent<tnah::RigidBodyComponent>().Body;
			auto& transform = m_Ball.GetComponent<tnah::TransformComponent>();
			startingPos = p3.position;
			transform.Position = startingPos;
			rb->Orientation = {1.0, 0, 0, 0};
			rb->linearVelocity = {0, 0 ,0};
			rb->angularVelocity = {0,0,0};
		}
	}
	ImGui::Separator();
	auto size = ImGui::GetContentRegionAvail();
	if(ImGui::Button("FIRE!", {size.x, 50}))
	{
		m_StartPhysicsSim = true;
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
