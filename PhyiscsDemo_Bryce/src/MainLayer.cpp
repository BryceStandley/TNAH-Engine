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
	ct.Position = glm::vec3(-50, 30, 50);
	ct.Rotation = glm::vec3(-45, -25, 0);
	cc.ClearMode = tnah::CameraClearMode::Skybox;
	

	auto& m_Skybox = m_ActiveScene->GetSceneCamera().AddComponent<tnah::SkyboxComponent>();

	m_Box1 = m_ActiveScene->CreateGameObject("Box1");
	auto& m1 = m_Box1.AddComponent<tnah::MeshComponent>();
	m1.Model = tnah::Model::Create("assets/meshes/cube_texture.fbx");
	auto& m1t = m_Box1.Transform();
	m1t.Position = {0.0f, 10.0f, 0.0f};
	m1t.Scale =  {4.0f, 4.0f, 0.5f};
	m_Box1.AddComponent<tnah::RigidBodyComponent>(m_Box1);
	m_Box1.GetComponent<tnah::RigidBodyComponent>().AddCollider({4.0f, 4.0f, 0.5f});


	m_Box2 = m_ActiveScene->CreateGameObject("Box2");
	auto& m2 = m_Box2.AddComponent<tnah::MeshComponent>();
	m2.Model = tnah::Model::Create("assets/meshes/cube_texture.fbx");
	auto& m2t = m_Box2.Transform();
	m2t.Position = {0.0f, 8.0f, 2.0f};
	m2t.Scale = {4.0f, 4.0f, 0.5f};
	m_Box2.AddComponent<tnah::RigidBodyComponent>(m_Box2);
	m_Box2.GetComponent<tnah::RigidBodyComponent>().AddCollider({4.0f, 4.0f, 0.5f});

	m_Ground = m_ActiveScene->CreateGameObject("TempGround");
	auto& m = m_Ground.AddComponent<tnah::MeshComponent>();
	m.Model = tnah::Model::Create("assets/meshes/cube_texture.fbx");
	auto& mt = m_Ground.Transform();
	mt.Position = {0.0f, 0.0f, 0.0f};
	mt.Scale = {20.0f, 1.0f, 20.0f};
	m_Ground.AddComponent<tnah::RigidBodyComponent>(m_Ground, tnah::Physics::BodyType::Static);
	m_Ground.GetComponent<tnah::RigidBodyComponent>().AddCollider({20.0f, 1.0f, 20.0f});
	

}

void MainLayer::OnUpdate(tnah::Timestep deltaTime)
{
	//Camera Movement in a first person way.
		//This can be changed to also look like a 3rd person camera. Similar to a FPS camera in Unity and C#
		//Only move the camera if its enabled
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
	//Rendering is managed by the scene!
	m_ActiveScene->OnUpdate(deltaTime);
}

void MainLayer::OnFixedUpdate(tnah::Timestep ts, tnah::PhysicsTimestep ps)
{
	m_ActiveScene->OnFixedUpdate(ts, ps);
}

void MainLayer::OnImGuiRender()
{
	auto& ct = m_Camera.Transform();
	
	ImGui::Begin("Controls");
	
	ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
	ImGui::Text("Application Options");
	ImGui::Separator();
	ImGui::Text("Press 0 to toggle debug mode");
	if(ImGui::Checkbox("Debug Mode", &tnah::Application::Get().GetDebugModeStatus()))
	{
		tnah::Application::Get().SetDebugStatusChange();
	}
	ImGui::NewLine();
	if(ImGui::CollapsingHeader("Controls & Toggles"))
	{
		ImGui::BulletText("Press 1 to toggle the cursor");
		ImGui::BulletText("Press 2 to toggle wireframe mode");
		ImGui::BulletText("Press 3 to toggle borderless fullscreen");
		ImGui::BulletText("Press 4 to toggle VSync");
		ImGui::BulletText("Press 5 to toggle camera look");
		ImGui::BulletText("Press 6 to toggle camera movement");
		ImGui::BulletText("Hold left or right Shift to increase camera movement speed");
		ImGui::BulletText("Press ESC to close the application");
		ImGui::Separator();
		auto& app = tnah::Application::Get();
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
			if(ImGui::Button("Reset Scene"))
			{
				tnah::Physics::PhysicsEngine::GetManager()->SetGravityState(false);
				tnah::Physics::PhysicsEngine::GetManager()->SetGravity({0.0f, -9.8f, 0.0f});
				auto& rb1 = m_Box1.GetComponent<tnah::RigidBodyComponent>();
				auto& rb2 = m_Box2.GetComponent<tnah::RigidBodyComponent>();
				rb1.Body->ResetValues();
				rb2.Body->ResetValues();

				auto& m1t = m_Box1.Transform();
				m1t.Position = {0.0f, 10.0f, 0.0f};
				m1t.Rotation = {0.0f, 0.0f, 0.0f};
				m1t.Scale =  {4.0f, 4.0f, 0.5f};
				
				auto& m2t = m_Box2.Transform();
				m2t.Position = {0.0f, 8.0f, 2.0f};
				m2t.Rotation = {0.0f, 0.0f, 0.0f};
				m2t.Scale = {4.0f, 4.0f, 0.5f};
				
			}
		}
	}

	ImGui::Separator();
	if(ImGui::CollapsingHeader("Physics"))
	{
		ImGui::Checkbox("Gravity", &tnah::Physics::PhysicsEngine::GetManager()->GetGravityState());
		if(tnah::Physics::PhysicsEngine::GetManager()->GetGravityState())
		{
			tnah::EditorUI::DrawVec3Control("Gravity Values", tnah::Physics::PhysicsEngine::GetManager()->GetGravity());
		}
		ImGui::Checkbox("Collider Rendering", &tnah::Physics::PhysicsEngine::GetColliderRendererHandle());
	}
	
	if (ImGui::CollapsingHeader("Camera"))
	{
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
	ImGui::NewLine();
	ImGui::Separator();
	
	
	if(ImGui::CollapsingHeader("Scene Objects"))
	{
		
		for(auto& go : m_ActiveScene->GetGameObjectsInScene())
		{
			constexpr static bool selected = false;
			std::string name = go.second.GetComponent<tnah::TagComponent>().Tag;
			if(name.find("Camera") == std::string::npos && name.find("Light") == std::string::npos)
			{
				if(ImGui::TreeNode(name.c_str()))
				{
					tnah::EditorUI::DrawComponentProperties(go.second, false);
					ImGui::TreePop();
				}
			}
		}
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
