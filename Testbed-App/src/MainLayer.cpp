#include "MainLayer.h"

#include <imgui.h>
#include <glm/gtc/random.hpp>
#include "TNAH/Editor/EditorUI.h"

#include <TNAH-App.h>

MainLayer::MainLayer()
	:Layer("Main Layer")
{
	m_ActiveScene = tnah::Scene::CreateEmptyScene();
	m_Camera = m_ActiveScene->GetSceneCamera();
	auto& ct = m_Camera.Transform();
	auto& cc = m_Camera.GetComponent<tnah::CameraComponent>();
	cc.Camera.SetViewportSize(1280, 720);
	ct.Position = glm::vec3(-20, 10, -10);
	ct.Rotation = glm::vec3(0, -10, 0);
	cc.ClearMode = tnah::CameraClearMode::Skybox;
	auto& m_Skybox = m_ActiveScene->GetSceneCamera().AddComponent<tnah::SkyboxComponent>();


	m_Box1 = m_ActiveScene->CreateGameObject("Box1");
	m_Box1.AddComponent<tnah::MeshComponent>("assets/meshes/cube_texture.fbx");
	m_Box1.Transform().Position = { 0.0f, 10.0f, 0.0f };
	m_Box1.Transform().Scale = { 4.0f, 4.0f, 0.5f };
	auto& rb1 = m_Box1.AddComponent<tnah::RigidBodyComponent>(m_Box1);
	rb1.AddCollider({ 4.0f, 4.0f, 0.5f });


	m_Box2 = m_ActiveScene->CreateGameObject("Box2");
	m_Box2.AddComponent<tnah::MeshComponent>("assets/meshes/cube_texture.fbx");
	m_Box2.Transform().Position = { 0.0f, 6.0f, 2.0f };
	m_Box2.Transform().Scale = { 4.0f, 4.0f, 0.5f };
	auto& rb2 = m_Box2.AddComponent<tnah::RigidBodyComponent>(m_Box2);
	rb2.AddCollider({ 4.0f, 4.0f, 0.5f });

	m_Ball = m_ActiveScene->CreateGameObject("Ball");
	m_Ball.AddComponent<tnah::MeshComponent>("assets/meshes/sphere.fbx");
	m_Ball.Transform().Position = { 3.5f, 8.0f, -10.0f };
	m_PhysicsSimStartPosition = m_Ball.Transform().Position;
	auto& rb3 = m_Ball.AddComponent<tnah::RigidBodyComponent>(m_Ball);
	rb3.AddCollider({ 1.0f });

	m_Ground = m_ActiveScene->CreateGameObject("Ground");
	m_Ground.AddComponent<tnah::MeshComponent>("assets/meshes/cube_texture.fbx");
	m_Ground.Transform().Position = { 0.0f, 0.0f, 0.0f };
	m_Ground.Transform().Scale = { 40.0f, 1.0f, 40.0f };
	auto& rb4 = m_Ground.AddComponent<tnah::RigidBodyComponent>(m_Ground, tnah::Physics::BodyType::Static);
	rb4.AddCollider({ 40.0f, 1.0f, 40.0f });

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

	if (m_CameraLookToggle)
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

	if (m_StartPhysicsSim)
	{
		TNAH_INFO("Simulation Started");
		m_Ball.Transform().Position = m_PhysicsSimStartPosition;
		auto& rb = m_Ball.GetComponent<tnah::RigidBodyComponent>().Body;
		auto force = glm::vec3(0.0f, 0.0f, 1.0f) * glm::vec3(0.0f, 0.0f, 500.0f);
		rb->AddForce(force);
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
	if (x < 400) { x = 400; }
	ImGui::SetNextWindowSize({ x, windowSize.y });
	static bool m_ApplicationPanel = true;
	ImGui::Begin("Application", &m_ApplicationPanel);

	ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
	ImGui::Text("Options");
	if (ImGui::Checkbox("Debug Mode", &tnah::Application::Get().GetDebugModeStatus()))
	{
		tnah::Application::Get().SetDebugStatusChange();
	}
	if (ImGui::CollapsingHeader("Controls & Toggles"))
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
	if (tnah::Application::Get().GetDebugModeStatus())
	{
		if (ImGui::CollapsingHeader("Debug"))
		{
			ImGui::BulletText("Any application debug controls can go here");
		}
	}
	if (ImGui::CollapsingHeader("Camera"))
	{
		auto& ct = m_Camera.Transform();
		tnah::EditorUI::DrawVec3Control("Position", ct.Position);
		tnah::EditorUI::DrawVec3Control("Rotation", ct.Rotation);
		ImGui::Separator();
		ImGui::Checkbox("Camera Speed Override", &m_CameraMovementSpeedOverride);
		if (m_CameraMovementSpeedOverride)
		{
			tnah::EditorUI::DrawFloatControl("Speed", m_CameraMovementSpeed, 1, 100, false);
		}
		else
		{
			tnah::EditorUI::DrawFloatControl("Speed", m_CameraMovementSpeed, 1, 100, true);
		}
	}




	ImGui::Separator();

	ImGui::Text("Scene Hierarchy");
	if (ImGui::CollapsingHeader("GameObjects"))
	{

		for (auto& go : m_ActiveScene->GetGameObjectsInScene())
		{
			constexpr static bool selected = false;
			std::string name = go.second.GetComponent<tnah::TagComponent>().Tag;
			if (name.find("Camera") == std::string::npos && name.find("Light") == std::string::npos)
			{
				if (ImGui::TreeNode(name.c_str()))
				{
					tnah::EditorUI::DrawComponentProperties(go.second, false);
					ImGui::TreePop();
				}
			}
		}
	}

	ImGui::Separator();

	ImGui::Text("Simulation Controls");

	ImGui::Text("Physics");
	{
		ImGui::Checkbox("Use Gravity", &tnah::Physics::PhysicsEngine::GetManager()->GetGravityState());
		if (tnah::Physics::PhysicsEngine::GetManager()->GetGravityState())
		{
			tnah::EditorUI::DrawVec3Control("Gravity", tnah::Physics::PhysicsEngine::GetManager()->GetGravity());
		}
		ImGui::Checkbox("Collider Rendering", &tnah::Physics::PhysicsEngine::GetColliderRendererHandle());
	}

	auto size = ImGui::GetContentRegionAvail();
	if (ImGui::Button("Play", { size.x, 30 }))
	{
		m_StartPhysicsSim = true;
	}
	if (ImGui::Button("Reset", { size.x, 30 }))
	{
		tnah::Physics::PhysicsEngine::GetManager()->SetGravityState(false);
		tnah::Physics::PhysicsEngine::GetManager()->SetGravity({ 0.0f, -9.8f, 0.0f });
		auto& rb1 = m_Box1.GetComponent<tnah::RigidBodyComponent>();
		auto& rb2 = m_Box2.GetComponent<tnah::RigidBodyComponent>();
		auto& rb3 = m_Ball.GetComponent<tnah::RigidBodyComponent>();
		rb1.Body->ResetValues();
		rb2.Body->ResetValues();
		rb3.Body->ResetValues();

		auto& m1t = m_Box1.Transform();
		m1t.Position = { 0.0f, 10.0f, 0.0f };
		m1t.Rotation = { 0.0f, 0.0f, 0.0f };
		m1t.Scale = { 4.0f, 4.0f, 0.5f };

		auto& m2t = m_Box2.Transform();
		m2t.Position = { 0.0f, 8.0f, 2.0f };
		m2t.Rotation = { 0.0f, 0.0f, 0.0f };
		m2t.Scale = { 4.0f, 4.0f, 0.5f };


		auto& m3t = m_Ball.Transform();
		m3t.Position = m_PhysicsSimStartPosition;
		m3t.Rotation = { 0,0,0 };
		m_StartPhysicsSim = false;
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