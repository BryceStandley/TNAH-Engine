#include "MainLayer.h"

#include <imgui.h>
#include <glm/gtc/random.hpp>
#include <TNAH/Scene/Components/SkyboxComponent.h>

#include <TNAH-App.h>

MainLayer::MainLayer()
	:Layer("Main Layer")
{
	m_ActiveScene = tnah::Scene::CreateEmptyScene();
	m_Camera = m_ActiveScene->GetSceneCamera();
	auto& ct = m_Camera.Transform();
	auto& cc = m_Camera.GetComponent<tnah::CameraComponent>();
	cc.Camera.SetViewportSize(1280, 720);
	ct.Position = glm::vec3(500, 60, 500);
	cc.ClearMode = tnah::CameraClearMode::Skybox;

	auto& rb = m_Camera.AddComponent<tnah::RigidBodyComponent>(ct);
	auto& box = m_Camera.AddComponent<tnah::BoxColliderComponent>(glm::vec3(10, 10, 10));
	rb.Body->addCollider(box.Collider, rp3d::Transform::identity());
	//rb.AddCollider(box.Collider, ct);

	
	
	m_SceneLight = m_ActiveScene->GetSceneLight();

	m_Terrain = m_ActiveScene->CreateGameObject("Terrain");
	m_Terrain.AddComponent<tnah::TerrainComponent>("assets/heightmaps/1k.tga");
	auto& terrT = m_Terrain.Transform();
	terrT.Scale = glm::vec3(5.0f);

	auto& m_Skybox = m_ActiveScene->GetSceneCamera().AddComponent<tnah::SkyboxComponent>();

	m_PointLight = m_ActiveScene->CreateGameObject("PointLight");
	auto& light = m_PointLight.GetComponent<tnah::LightComponent>();
	light.Light = tnah::Light::CreatePoint();

	for (int i = 0; i < 1; i++)
	{
		//Test Cube
		std::string name = "Cube" + std::to_string(i);
		auto go = m_ActiveScene->CreateGameObject(name);

		auto& mesh = go.AddComponent<tnah::MeshComponent>();
		mesh.Model = tnah::Model::Create("assets/meshes/girl/girl_3d_model.fbx");
		
		//mesh.Model = tnah::Model::Create("assets/meshes/cube_texture.fbx");
		auto& meshT = go.Transform();

		glm::vec3 p(glm::linearRand(500, 700), glm::linearRand(50, 100), glm::linearRand(500, 700));
		meshT.Position = p;

		go.AddComponent<tnah::AnimatorComponent>(mesh.Animation);
		m_MeshObjects.push_back(go);
	}
	
	auto go = m_ActiveScene->CreateGameObject("Floor is lava");
		
	//mesh.Model = tnah::Model::Create("assets/meshes/cube_texture.fbx");
	auto& tt = go.Transform();

	tt.Position = glm::vec3(500, 0, 500);	

	auto& rb2 = go.AddComponent<tnah::RigidBodyComponent>(tt);
	auto& b = go.AddComponent<tnah::BoxColliderComponent>(glm::vec3(1000, 10, 1000));
	//rb2.AddCollider(b.Collider, rp3d::Transform::identity());
	b.colliderPointer = rb2.AddCollider(b.Collider, rp3d::Transform::identity());
	rb2.Body->setType(rp3d::BodyType::KINEMATIC);
	rb2.RemoveCollider(b.colliderPointer);
}

void MainLayer::OnUpdate(tnah::Timestep deltaTime)
{
	//Camera Movement in a first person way.
		//This can be changed to also look like a 3rd person camera. Similar to a FPS camera in Unity and C#
		//Only move the camera if its enabled
	if(m_Camera.HasComponent<tnah::RigidBodyComponent>())
	{
		auto& rb = m_Camera.GetComponent<tnah::RigidBodyComponent>();
		auto& ct = m_Camera.Transform();
		auto vel = rb.Body->getLinearVelocity();
		if(vel.x > m_Velocity.x)
		{
			vel.x = m_Velocity.x;
		}
		else if(vel.x < -m_Velocity.x)
		{
			vel.x = -m_Velocity.x;
		}

		if(vel.y > m_Velocity.y)
		{
			vel.y = m_Velocity.y;
		}
		else if(vel.y < -m_Velocity.y)
		{
			vel.y = -m_Velocity.y;
		}

		if(vel.z > m_Velocity.z)
		{
			vel.z = m_Velocity.z;
		}
		else if(vel.z < -m_Velocity.z)
		{
			vel.z = -m_Velocity.z;
		}

		rb.Body->setLinearVelocity(vel);
		
		if(tnah::Input::IsKeyPressed(tnah::Key::W))
			rb.ApplyForce(tnah::RigidBodyComponent::ForceType::FromCentre, ct.Forward, glm::vec3(5), glm::vec3(0));
		if(tnah::Input::IsKeyPressed(tnah::Key::S))
			rb.ApplyForce(tnah::RigidBodyComponent::ForceType::FromCentre, -ct.Forward, glm::vec3(5), glm::vec3(0));
		if(tnah::Input::IsKeyPressed(tnah::Key::A))
			rb.ApplyForce(tnah::RigidBodyComponent::ForceType::FromCentre, -ct.Right, glm::vec3(5), glm::vec3(0));
		if(tnah::Input::IsKeyPressed(tnah::Key::D))
			rb.ApplyForce(tnah::RigidBodyComponent::ForceType::FromCentre, ct.Right, glm::vec3(5), glm::vec3(0));
	}
	
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


	for (auto go : m_MeshObjects)
	{
		auto& mesh = go.GetComponent<tnah::TransformComponent>();
		mesh.Rotation.y += 1.0f * deltaTime;
		mesh.Rotation.z += 1.0f * deltaTime;
	}


	//Rendering is managed by the scene!
	m_ActiveScene->OnUpdate(deltaTime);
}

void MainLayer::OnFixedUpdate(tnah::PhysicsTimestep ps)
{
	m_ActiveScene->OnFixedUpdate(ps);
}

void MainLayer::OnImGuiRender()
{
	auto& terr = m_Terrain.Transform();
	auto& ct = m_Camera.Transform();
	auto& l = m_SceneLight.GetComponent<tnah::LightComponent>();
	auto& lt = m_SceneLight.Transform();

	auto& plt = m_PointLight.Transform();
	auto& pl = m_PointLight.GetComponent<tnah::LightComponent>();
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
	ImGui::Text("Application Options");
	ImGui::Separator();
	ImGui::BulletText("Press 1 to toggle the cursor");
	ImGui::BulletText("Press 2 to toggle wireframe mode");
	ImGui::BulletText("Press 3 to toggle borderless fullscreen");
	ImGui::BulletText("Press 4 to toggle VSync");
	ImGui::BulletText("Press 5 to toggle camera look");
	ImGui::BulletText("Press 6 to toggle camera movement");
	ImGui::BulletText("Hold Either Shift to move the camera faster");
	ImGui::BulletText("Press ESC to exit");
	ImGui::Separator();
	
	if(ImGui::CollapsingHeader("Toggles"))
	{
		auto& app = tnah::Application::Get();
		ImGui::Checkbox("Cursor", &app.GetCursorToggleStatus());
		ImGui::Checkbox("Wireframe", &app.GetWireframeToggleStatus());
		ImGui::Checkbox("VSync", &app.GetVSyncToggleStatus());
		ImGui::Checkbox("Fullscreen", &app.GetFullscreenToggleStatus());
		ImGui::Checkbox("Camera Look", &m_CameraLookToggle);
		ImGui::Checkbox("Camera Movement", &m_CameraMovementToggle);
	}

	if (ImGui::CollapsingHeader("Camera"))
	{
		ImGui::SliderFloat3("Camera Pos", glm::value_ptr(ct.Position), -10000, 10000);
		ImGui::SliderFloat3("Camera Rotation", glm::value_ptr(ct.Rotation), -360, 360);
		ImGui::Separator();
		ImGui::SliderFloat3("Camera Forward", glm::value_ptr(ct.Forward), 0, 0, "%.3f",ImGuiInputTextFlags_ReadOnly);
		ImGui::SliderFloat3("Camera Right", glm::value_ptr(ct.Right), 0, 0, "%.3f",ImGuiInputTextFlags_ReadOnly);
		ImGui::SliderFloat3("Camera Up", glm::value_ptr(ct.Up), 0, 0, "%.3f",ImGuiInputTextFlags_ReadOnly);
		ImGui::Separator();
		ImGui::Checkbox("Camera Speed Override", &m_CameraMovementSpeedOverride);
		if (m_CameraMovementSpeedOverride)
		{
			ImGui::SliderFloat("Camera Movement Speed", &m_CameraOverrideSpeed, 1, m_MaxCameraMovementSpeed);
		}
		else
		{
			ImGui::Text("Camera Movement Speed: %0.1f", m_CameraMovementSpeed);
		}
	}

	if (ImGui::CollapsingHeader("Terrain"))
	{
		ImGui::SliderFloat3("Terrain Scale", glm::value_ptr(terr.Scale), 1, 20);
	}

	if (ImGui::CollapsingHeader("Global Lighting"))
	{
		ImGui::SliderFloat3("Light Direction", glm::value_ptr(l.Light->GetDirection()), -1, 1);
		ImGui::SliderFloat("Light Intensity", &l.Light->GetIntensity(), 0, 10);
		ImGui::ColorEdit3("Light Color", glm::value_ptr(l.Light->GetColor()));
		ImGui::SliderFloat3("Light Ambient", glm::value_ptr(l.Light->GetAmbient()), 0, 1);
		ImGui::SliderFloat3("Light Diffuse", glm::value_ptr(l.Light->GetDiffuse()), 0, 1);
		ImGui::SliderFloat3("Light Specular", glm::value_ptr(l.Light->GetSpecular()), 0, 1);
	}

	if (ImGui::CollapsingHeader("Point Lighting"))
	{
		ImGui::SliderFloat3("Point Position", glm::value_ptr(plt.Position), -1000, 1000);
		ImGui::SliderFloat("Point Intensity", &pl.Light->GetIntensity(), 0, 10);
		ImGui::ColorEdit3("Point Color", glm::value_ptr(pl.Light->GetColor()));
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
		auto& e = (tnah::KeyPressedEvent&)event;
		if (e.GetKeyCode() == tnah::Key::D5)
		{
			m_CameraLookToggle = !m_CameraLookToggle;
		}
	}

	if (event.GetEventType() == tnah::EventType::KeyPressed)
	{
		auto& e = (tnah::KeyPressedEvent&)event;
		if (e.GetKeyCode() == tnah::Key::D6)
		{
			m_CameraMovementToggle = !m_CameraMovementToggle;
		}
	}
}
