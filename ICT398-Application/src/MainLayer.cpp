#include "MainLayer.h"

#include <imgui.h>
#include <glm/gtc/random.hpp>
#include <TNAH/Scene/Components/SkyboxComponent.h>

#include <TNAH-App.h>

#include "TNAH/Editor/EditorUI.h"
#include "TNAH/Scene/Components/AI/Affordance.h"
#include "TNAH/Scene/Components/AI/AIComponent.h"
#include "TNAH/Scene/Components/AI/PlayerInteractions.h"

MainLayer::MainLayer()
	:Layer("Main Layer")
{
	tnah::AStar::Init(tnah::Int2(-9,1), tnah::Int2(22, 9));
	m_ActiveScene = tnah::Scene::CreateEmptyScene();
	m_Camera = m_ActiveScene->GetSceneCamera();
	auto& ct = m_Camera.Transform();
	auto& cc = m_Camera.GetComponent<tnah::CameraComponent>();
	cc.Camera.SetViewportSize(1280, 720);
	ct.Position = glm::vec3(0, 0, 1);
	cc.ClearMode = tnah::CameraClearMode::Skybox;
	auto& m_Skybox = m_Camera.AddComponent<tnah::SkyboxComponent>();
	
	{
		auto& rb = m_Camera.AddComponent<tnah::RigidBodyComponent>(ct);
		auto& box = m_Camera.AddComponent<tnah::BoxColliderComponent>(glm::vec3(0.2f, 0.8f, 0.2f));
		box.Components.TransformRelativeToCollisionBody.setPosition({0, -0.7f, 0});
		
		box.Components.BodyCollider = rb.AddCollider(box.Components);
		rb.Body->setAngularLockAxisFactor({0,1,0}); // Lock the rigidbody from falling over
		rb.SetBodyType(rp3d::BodyType::DYNAMIC);
		//m_Camera.AddComponent<tnah::AIComponent>();
		//m_Camera.AddComponent<tnah::CharacterComponent>();
		auto & aff = m_Camera.AddComponent<tnah::Affordance>();
		m_Camera.AddComponent<tnah::PlayerInteractions>();
		aff.SetActionValues(tnah::Actions::abuse, 1.0f);
		aff.SetActionValues(tnah::Actions::greeting, 1.0f);
	}
	
	
	m_SceneLight = m_ActiveScene->GetSceneLight();

	m_Terrain = m_ActiveScene->CreateGameObject("Terrain");
	m_Terrain.AddComponent<tnah::TerrainComponent>("assets/heightmaps/1k.tga");
	auto& terrT = m_Terrain.Transform();
	terrT.Scale = glm::vec3(5.0f);
	terrT.Position = glm::vec3(-1000, -200, -500);

	
	
#pragma region SceneCreation
	// Note this is a temp solution to building our scene.
	//
	// 
	// Scene Serialization is currently undergoing testing and bug fixes
	{
		std::string name = "World";
		auto go = m_ActiveScene->CreateGameObject(name);

		auto& mesh = go.AddComponent<tnah::MeshComponent>();
		mesh.Model = tnah::Model::Create("assets/meshes/wholething3.fbx");
		go.Transform().Position = {-1.1f, -4.3f, 0.6f};
		go.Transform().Rotation = {glm::radians(-90.0f), 0, 0};
		
	
	}

	//Astar testing
	{
		std::string name = "AStar";
		auto go = m_ActiveScene->CreateGameObject(name);

		auto& mesh = go.AddComponent<tnah::MeshComponent>();
		mesh.Model = tnah::Model::Create("assets/meshes/sphere.fbx");
		go.Transform().Position = {-5000.0f, -5000.0f, -5000.0f};
		go.Transform().Rotation = {0, 0, 0};
		go.Transform().Scale = {0.1, 0.1, 0.1};

		auto & a = go.AddComponent<tnah::AStarComponent>();
	}

	//Colliders Only
	{
		std::string name = "Front";
		
		auto&go = m_ActiveScene->CreateGameObject(name);
		auto&tt = go.Transform();
		
		tt.Position = {-10.63, 0, 0};
		
		auto& rb = go.AddComponent<tnah::RigidBodyComponent>(tt);
		auto& box = go.AddComponent<tnah::BoxColliderComponent>(glm::vec3(1, 40, 60));
		
		box.Components.BodyCollider = rb.AddCollider(box.Components.Shape, rp3d::Transform::identity());
		
		rb.SetBodyType(rp3d::BodyType::KINEMATIC);	
	}

	{
		std::string name = "Floor";
		
		auto&go = m_ActiveScene->CreateGameObject(name);
		auto&tt = go.Transform();
		
		tt.Position = {0, -4.5, 0};
		
		auto& rb = go.AddComponent<tnah::RigidBodyComponent>(tt);
		auto& box = go.AddComponent<tnah::BoxColliderComponent>(glm::vec3(60, 2, 60));

		box.Components.BodyCollider = rb.AddCollider(box.Components.Shape, rp3d::Transform::identity());
		
		rb.SetBodyType(rp3d::BodyType::KINEMATIC);	
	}

	{
		std::string name = "Back";
		
		auto&go = m_ActiveScene->CreateGameObject(name);
		auto&tt = go.Transform();
		
		tt.Position = {12.4, 0, 2.6};
		
		auto& rb = go.AddComponent<tnah::RigidBodyComponent>(tt);
		auto& box = go.AddComponent<tnah::BoxColliderComponent>(glm::vec3(1, 60, 60));
		
		box.Components.BodyCollider = rb.AddCollider(box.Components.Shape, rp3d::Transform::identity());
		
		rb.SetBodyType(rp3d::BodyType::KINEMATIC);	
	}

	{
		std::string name = "Left";
		
		auto&go = m_ActiveScene->CreateGameObject(name);
		auto&tt = go.Transform();
		
		tt.Position = {-1.4, 0, 10};
		
		auto& rb = go.AddComponent<tnah::RigidBodyComponent>(tt);
		auto& box = go.AddComponent<tnah::BoxColliderComponent>(glm::vec3(65, 50, 1));
		
		box.Components.BodyCollider = rb.AddCollider(box.Components.Shape, rp3d::Transform::identity());
		
		rb.SetBodyType(rp3d::BodyType::KINEMATIC);	
	}

	{
		std::string name = "Right";
		
		auto&go = m_ActiveScene->CreateGameObject(name);
		auto&tt = go.Transform();
		
		tt.Position = {0, 0, 0.2};
		
		auto& rb = go.AddComponent<tnah::RigidBodyComponent>(tt);
		auto& box = go.AddComponent<tnah::BoxColliderComponent>(glm::vec3(65, 50, 1));
		
		box.Components.BodyCollider = rb.AddCollider(box.Components.Shape, rp3d::Transform::identity());
		
		rb.SetBodyType(rp3d::BodyType::KINEMATIC);	
	}

	glm::vec3 pillarSize(0.5, 12, 0.5);
	{
		std::string name = "Pillar (1)";
		
		auto&go = m_ActiveScene->CreateGameObject(name);
		auto&tt = go.Transform();
		tt.astar = true;
		tt.Position = {5.3, 0, 9.0};
		
		auto& rb = go.AddComponent<tnah::RigidBodyComponent>(tt);
		auto& box = go.AddComponent<tnah::BoxColliderComponent>(glm::vec3(pillarSize));
		
		box.Components.BodyCollider = rb.AddCollider(box.Components.Shape, rp3d::Transform::identity());
		
		rb.SetBodyType(rp3d::BodyType::KINEMATIC);	
	}

	{
		std::string name = "Pillar (2)";
		
		auto&go = m_ActiveScene->CreateGameObject(name);
		auto&tt = go.Transform();
		tt.astar = true;
		tt.Position = {5.3, 0, 4.6};
		
		auto& rb = go.AddComponent<tnah::RigidBodyComponent>(tt);
		auto& box = go.AddComponent<tnah::BoxColliderComponent>(glm::vec3(pillarSize));
		
		box.Components.BodyCollider = rb.AddCollider(box.Components.Shape, rp3d::Transform::identity());
		
		rb.SetBodyType(rp3d::BodyType::KINEMATIC);	
	}

	{
		std::string name = "Pillar (3)";
		
		auto&go = m_ActiveScene->CreateGameObject(name);
		auto&tt = go.Transform();
		tt.astar = true;
		tt.Position = {-1.8, 0, 4.6};
		
		auto& rb = go.AddComponent<tnah::RigidBodyComponent>(tt);
		auto& box = go.AddComponent<tnah::BoxColliderComponent>(glm::vec3(pillarSize));
		
		box.Components.BodyCollider = rb.AddCollider(box.Components.Shape, rp3d::Transform::identity());
		
		rb.SetBodyType(rp3d::BodyType::KINEMATIC);	
	}

	{
		std::string name = "Pillar (4)";
		
		auto&go = m_ActiveScene->CreateGameObject(name);
		auto&tt = go.Transform();
		tt.astar = true;
		tt.Position = {-1.8, 0, 9.0};
		
		auto& rb = go.AddComponent<tnah::RigidBodyComponent>(tt);
		auto& box = go.AddComponent<tnah::BoxColliderComponent>(glm::vec3(pillarSize));
		
		box.Components.BodyCollider = rb.AddCollider(box.Components.Shape, rp3d::Transform::identity());
		
		rb.SetBodyType(rp3d::BodyType::KINEMATIC);	
	}

	glm::vec3 bushScale(1.5f), bushRotation(-1.75, 0, 0);
	{
		std::string name = "Bush (1)";
		
		auto&go = m_ActiveScene->CreateGameObject(name);
		auto&tt = go.Transform();
		tt.Position = {2.35, -5.03, -4.63};
		tt.Rotation = bushRotation;
		tt.Scale = bushScale;
		auto& mesh = go.AddComponent<tnah::MeshComponent>();
		mesh.Model = tnah::Model::Create("assets/meshes/newBush.fbx");
	}
	{
		std::string name = "Bush (2)";
		
		auto&go = m_ActiveScene->CreateGameObject(name);
		auto&tt = go.Transform();
		tt.Position = {6, -5.03, -4.63};
		tt.Rotation = bushRotation;
		tt.Scale = bushScale;
		auto& mesh = go.AddComponent<tnah::MeshComponent>();
		mesh.Model = tnah::Model::Create("assets/meshes/newBush.fbx");
	}

	{
		std::string name = "Bush (3)";
		
		auto&go = m_ActiveScene->CreateGameObject(name);
		auto&tt = go.Transform();
		tt.Position = {10, -5.03, -4.63};
		tt.Rotation = bushRotation;
		tt.Scale = bushScale;
		auto& mesh = go.AddComponent<tnah::MeshComponent>();
		mesh.Model = tnah::Model::Create("assets/meshes/newBush.fbx");
	}

	{
		std::string name = "Bush (4)";
		
		auto&go = m_ActiveScene->CreateGameObject(name);
		auto&tt = go.Transform();
		tt.Position = {-6.5, -5.03, -1.5};
		tt.Rotation = bushRotation;
		tt.Scale = bushScale - glm::vec3(0.5);
		auto& mesh = go.AddComponent<tnah::MeshComponent>();
		mesh.Model = tnah::Model::Create("assets/meshes/newBush.fbx");
	}
	{
		std::string name = "Bush (5)";
		
		auto&go = m_ActiveScene->CreateGameObject(name);
		auto&tt = go.Transform();
		tt.Position = {-6.75, -5.03, -2.0};
		tt.Rotation = bushRotation;
		//tt.Scale = bushScale - glm::vec3(0.76);
		auto& mesh = go.AddComponent<tnah::MeshComponent>();
		mesh.Model = tnah::Model::Create("assets/meshes/newBush.fbx");
	}
	
	glm::vec3 binSize(1, 1, 1), binScale(0.3, 0.3, 0.3), binRotation(-1.55, 0, 0);
	{
		std::string name = "Bin (1)";
		
		auto&go = m_ActiveScene->CreateGameObject(name);
		auto&tt = go.Transform();
		auto& mesh = go.AddComponent<tnah::MeshComponent>();
		mesh.Model = tnah::Model::Create("assets/meshes/bin.fbx");
		
		tt.Position = {5.3, -3.7, 3.9};
		tt.Rotation = binRotation;
		tt.Scale = binScale;
		auto& rb = go.AddComponent<tnah::RigidBodyComponent>(tt);
		auto& box = go.AddComponent<tnah::BoxColliderComponent>(glm::vec3(binSize));
		
		box.Components.BodyCollider = rb.AddCollider(box.Components.Shape, rp3d::Transform::identity());
		rb.SetBodyType(rp3d::BodyType::STATIC);
		
		go.AddComponent<tnah::AIComponent>();
		go.AddComponent<tnah::CharacterComponent>(tnah::CharacterNames::Rubbish);
	}

	{
		std::string name = "Bin (2)";
		
		auto&go = m_ActiveScene->CreateGameObject(name);
		auto&tt = go.Transform();
		auto& mesh = go.AddComponent<tnah::MeshComponent>();
		mesh.Model = tnah::Model::Create("assets/meshes/bin.fbx");
		
		tt.Position = {-2, -3.7, 4};
		tt.Rotation = binRotation;
		tt.Scale = binScale;
		tt.astar = true;
		auto& rb = go.AddComponent<tnah::RigidBodyComponent>(tt);
		auto& box = go.AddComponent<tnah::BoxColliderComponent>(glm::vec3(binSize));
		
		box.Components.BodyCollider = rb.AddCollider(box.Components.Shape, rp3d::Transform::identity());
		
		rb.SetBodyType(rp3d::BodyType::KINEMATIC);
		go.AddComponent<tnah::Affordance>();
		auto & a = go.GetComponent<tnah::Affordance>();
		a.SetActionValues(tnah::kick, 1);
	}

	glm::vec3 tableScale(0.01, 0.02, 0.01), tableRotation(0, 0, 0), tableSize(1);
	{
		std::string name = "Table (1)";
		
		auto&go = m_ActiveScene->CreateGameObject(name);
		auto&tt = go.Transform();
		auto& mesh = go.AddComponent<tnah::MeshComponent>();
		mesh.Model = tnah::Model::Create("assets/meshes/table.fbx");
		
		tt.Position = {-3, -3.6, 6};
		tt.Rotation = tableRotation;
		tt.Scale = tableScale;
		tt.astar = true;
		auto& rb = go.AddComponent<tnah::RigidBodyComponent>(tt);
		auto& box = go.AddComponent<tnah::BoxColliderComponent>(tableSize);

		box.Components.BodyCollider = rb.AddCollider(box.Components.Shape, rp3d::Transform::identity());
		
		rb.SetBodyType(rp3d::BodyType::KINEMATIC);	
	}
	
	{
		std::string name = "Table (2)";
		
		auto&go = m_ActiveScene->CreateGameObject(name);
		auto&tt = go.Transform();
		auto& mesh = go.AddComponent<tnah::MeshComponent>();
		mesh.Model = tnah::Model::Create("assets/meshes/table.fbx");
		
		tt.Position = {-7, -3.6, 7};
		tt.Rotation = tableRotation;
		tt.Scale = tableScale;
		tt.astar = true;
		auto& rb = go.AddComponent<tnah::RigidBodyComponent>(tt);
		auto& box = go.AddComponent<tnah::BoxColliderComponent>(tableSize);

		box.Components.BodyCollider = rb.AddCollider(box.Components.Shape, rp3d::Transform::identity());
		
		rb.SetBodyType(rp3d::BodyType::KINEMATIC);
		go.AddComponent<tnah::Affordance>();
	}
	glm::vec3 chairScale(0.1, 0.1, 0.1);
	{
		std::string name = "Chair (1)";
		
		auto&go = m_ActiveScene->CreateGameObject(name);
		auto&tt = go.Transform();
		auto& mesh = go.AddComponent<tnah::MeshComponent>();
		mesh.Model = tnah::Model::Create("assets/meshes/chair.fbx");
		
		tt.Position = {-4, -3.8, 6};
		//tt.Rotation = glm::vec3(glm::radians(180.0f), 0, 0);
		tt.Scale = chairScale;
		tt.astar = true;
		auto& rb = go.AddComponent<tnah::RigidBodyComponent>(tt);
		auto& box = go.AddComponent<tnah::BoxColliderComponent>(glm::vec3(1, 1, 1));

		box.Components.BodyCollider = rb.AddCollider(box.Components.Shape, rp3d::Transform::identity());
		
		rb.SetBodyType(rp3d::BodyType::KINEMATIC);
		go.AddComponent<tnah::Affordance>();
		auto & a = go.GetComponent<tnah::Affordance>();
		a.SetActionValues(tnah::sit, 1);
	}

	{
		std::string name = "Chair (2)";
		
		auto&go = m_ActiveScene->CreateGameObject(name);
		auto&tt = go.Transform();
		auto& mesh = go.AddComponent<tnah::MeshComponent>();
		mesh.Model = tnah::Model::Create("assets/meshes/chair.fbx");
		
		tt.Position = {-2, -3.8, 6};
		tt.Rotation = glm::vec3(0, glm::radians(180.0f), 0);
		tt.Scale = chairScale;
		tt.astar = true;
		auto& rb = go.AddComponent<tnah::RigidBodyComponent>(tt);
		auto& box = go.AddComponent<tnah::BoxColliderComponent>(glm::vec3(1, 1, 1));

		box.Components.BodyCollider = rb.AddCollider(box.Components.Shape, rp3d::Transform::identity());
		
		rb.SetBodyType(rp3d::BodyType::KINEMATIC);	
	}
	
	{
		std::string name = "Chair (3)";
		
		auto&go = m_ActiveScene->CreateGameObject(name);
		auto&tt = go.Transform();
		auto& mesh = go.AddComponent<tnah::MeshComponent>();
		mesh.Model = tnah::Model::Create("assets/meshes/chair.fbx");
		
		tt.Position = {-8, -3.8, 7};
		tt.Rotation = glm::vec3(0, 0, 0);
		tt.Scale = chairScale;
		auto& rb = go.AddComponent<tnah::RigidBodyComponent>(tt);
		auto& box = go.AddComponent<tnah::BoxColliderComponent>(glm::vec3(1, 1, 1));

		box.Components.BodyCollider = rb.AddCollider(box.Components.Shape, rp3d::Transform::identity());
		tt.astar = true;
		rb.SetBodyType(rp3d::BodyType::KINEMATIC);	
	}

	{
		std::string name = "Chair (4)";
		
		auto&go = m_ActiveScene->CreateGameObject(name);
		auto&tt = go.Transform();
		auto& mesh = go.AddComponent<tnah::MeshComponent>();
		mesh.Model = tnah::Model::Create("assets/meshes/chair.fbx");
		
		tt.Position = {-6, -3.8, 7};
		tt.Rotation = glm::vec3(0, glm::radians(180.0f), 0);
		tt.Scale = chairScale;
		auto& rb = go.AddComponent<tnah::RigidBodyComponent>(tt);
		auto& box = go.AddComponent<tnah::BoxColliderComponent>(glm::vec3(1, 1, 1));
		
		box.Components.BodyCollider = rb.AddCollider(box.Components.Shape, rp3d::Transform::identity());
		tt.astar = true;
		rb.SetBodyType(rp3d::BodyType::KINEMATIC);	
	}
#pragma endregion SceneCreation
	
}

void MainLayer::OnAttach()
{
	tnah::Application::Get().GetWindow().SetCursorDisabled(m_CursorVisible);

	m_EndScreenImage = tnah::Texture2D::Create("assets/images/team.png");
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
		/*
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
		*/
		if(m_CameraMovementToggle)
		{
			if(tnah::Input::IsKeyPressed(tnah::Key::W))
			{
				ct.Position += ct.Forward * m_CameraMovementSpeed * deltaTime.GetSeconds();
				rp3d::Transform rt = rb.Body->getTransform();
				rt.setPosition(tnah::Math::ToRp3dVec3(ct.Position));
				rb.Body->setTransform(rt);
				//rb.ApplyForce(tnah::RigidBodyComponent::ForceType::FromCentre, ct.Forward, glm::vec3(5), glm::vec3(0));
			}
			if(tnah::Input::IsKeyPressed(tnah::Key::S))
			{
				ct.Position -= ct.Forward * m_CameraMovementSpeed * deltaTime.GetSeconds();
				rp3d::Transform rt = rb.Body->getTransform();
				rt.setPosition(tnah::Math::ToRp3dVec3(ct.Position));
				rb.Body->setTransform(rt);
				//rb.ApplyForce(tnah::RigidBodyComponent::ForceType::FromCentre, -ct.Forward, glm::vec3(5), glm::vec3(0));
			}
			if(tnah::Input::IsKeyPressed(tnah::Key::A))
			{
				ct.Position -= ct.Right * m_CameraMovementSpeed * deltaTime.GetSeconds();
				rp3d::Transform rt = rb.Body->getTransform();
				rt.setPosition(tnah::Math::ToRp3dVec3(ct.Position));
				rb.Body->setTransform(rt);
				//rb.ApplyForce(tnah::RigidBodyComponent::ForceType::FromCentre, -ct.Right, glm::vec3(5), glm::vec3(0));
			}
			if(tnah::Input::IsKeyPressed(tnah::Key::D))
			{
				ct.Position += ct.Right * m_CameraMovementSpeed * deltaTime.GetSeconds();
				rp3d::Transform rt = rb.Body->getTransform();
				rt.setPosition(tnah::Math::ToRp3dVec3(ct.Position));
				rb.Body->setTransform(rt);
				//rb.ApplyForce(tnah::RigidBodyComponent::ForceType::FromCentre, ct.Right, glm::vec3(5), glm::vec3(0));
			}
		}
	}

	/*
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
	*/
	
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

	ImGui::Begin("Control Panel", 0, ImGuiWindowFlags_NoDocking);
	
	ImGui::Text("%.1f FPS | %.1f ms", ImGui::GetIO().Framerate, 1000.0f / ImGui::GetIO().Framerate);
	ImGui::Text("This Window can be dragged around and even pulled off the window!");
	ImGui::BulletText("Press ESC to display the team!");
	
	if(ImGui::Button("Team Screen"))
	{
		m_CloseScreen = !m_CloseScreen;
		if(m_CloseScreen)
		{
			m_CameraLookToggle = false;
			m_CameraMovementToggle = false;
			m_CursorVisible = true;
			tnah::Application::Get().GetWindow().SetCursorDisabled(!m_CursorVisible);
		}
		else
		{
			m_CameraLookToggle = true;
			m_CameraMovementToggle = true;
			m_CursorVisible = false;
			tnah::Application::Get().GetWindow().SetCursorDisabled(!m_CursorVisible);
		}
	}
	
	ImGui::Separator();
	
	if(ImGui::CollapsingHeader("Application Options", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::Text("Debug mode allows physics colliders to be rendered");
		if(ImGui::Checkbox("Debug Mode", &tnah::Application::Get().GetDebugModeStatus()))
		{
			tnah::Application::Get().SetDebugStatusChange();
		}
		ImGui::Separator();
		
		if(ImGui::CollapsingHeader("Controls"))
		{
			ImGui::BulletText("Press 0 to toggle debug mode");
			ImGui::BulletText("Press 1 to toggle the cursor");
			ImGui::BulletText("Press 2 to toggle wireframe mode");
			ImGui::BulletText("Press 3 to toggle borderless fullscreen");
			ImGui::BulletText("Press 4 to toggle VSync");
			ImGui::BulletText("Press 5 to toggle camera look");
			ImGui::BulletText("Press 6 to toggle camera movement");
			ImGui::BulletText("Hold Either Shift to move the camera faster");
			ImGui::BulletText("Press ESC to display the team");
			ImGui::BulletText("Press any mouse button to close when displaying the team");
		}
	
		if(ImGui::CollapsingHeader("Toggles"))
		{
			auto& app = tnah::Application::Get();
			if(ImGui::Checkbox("Cursor", &m_CursorVisible))
			{
				tnah::Application::Get().GetWindow().SetCursorDisabled(m_CursorVisible);
			}
			if(ImGui::Checkbox("Wireframe", &m_Wireframe))
			{
				tnah::RenderCommand::SetWireframe(m_Wireframe);
			}
			if(ImGui::Checkbox("VSync", &m_VSync))
			{
				tnah::Application::Get().GetWindow().SetVSync(m_VSync);
			}
			if(ImGui::Checkbox("Fullscreen", &m_Fullscreen))
			{
				tnah::Application::Get().GetWindow().ToggleFullScreen(m_Fullscreen);
			}
			if(ImGui::Checkbox("Camera Look", &m_CameraLookToggle))
			{
			
			}
			if(ImGui::Checkbox("Camera Movement", &m_CameraMovementToggle))
			{
			
			}
		}

		if(ImGui::CollapsingHeader("Scene"))
		{
			if (ImGui::CollapsingHeader("Main Camera"))
			{
				ImGui::DragFloat3("Position", glm::value_ptr(ct.Position));
				ImGui::DragFloat3("Rotation", glm::value_ptr(ct.Rotation), 1, -360, 360);
				ImGui::Checkbox("Speed Override", &m_CameraMovementSpeedOverride);
				if (m_CameraMovementSpeedOverride)
				{
					ImGui::DragFloat("Movement Speed", &m_CameraOverrideSpeed, 1, 1, m_MaxCameraMovementSpeed);
				}
				else
				{
					ImGui::Text("Movement Speed: %0.1f", m_CameraMovementSpeed);
				}
			}

			if (ImGui::CollapsingHeader("Terrain"))
			{
				ImGui::DragFloat3("Position", glm::value_ptr(terr.Position));
				ImGui::DragFloat3("Rotation", glm::value_ptr(terr.Rotation), 1, -360, 360);
				ImGui::DragFloat3("Scale", glm::value_ptr(terr.Scale), 0.1f, 0.1f, 20);
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

			ImGui::NewLine();
			ImGui::Separator();
			ImGui::NewLine();
			if(ImGui::CollapsingHeader("Objects"))
			{
				ImGui::Text("All objects within the scene. Each object and their components controlled");
				ImGui::BulletText("Note this portion of the UI is using editor UI functions to display properties for each object");
				ImGui::NewLine();
				ImGui::Separator();
				ImGui::NewLine();
				for(auto& go : m_ActiveScene->GetGameObjectsInScene())
				{
					std::string name = go.second.GetComponent<tnah::TagComponent>().Tag;
					if(ImGui::CollapsingHeader(name.c_str()))
					{
						tnah::EditorUI::DrawComponentProperties(go.second, false);
					}
				}
			}
		}
	}
	
	ImGui::End();

	auto io = ImGui::GetIO();
	auto display = ImGui::GetIO().DisplaySize;
	auto pos  = ImGui::GetWindowViewport()->Pos;
	//ImGui::SetNextWindowSize({size.x, size.y});
	ImGui::SetNextWindowSize({500, display.y});
	ImGui::SetNextWindowPos({pos.x, pos.y}, true);
	//ImGui::SetNextWindowPos({io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f}, ImGuiCond_Always, {0.5f, 0.5f});
	ImGui::Begin("Agents Values", 0, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground);
		auto queue = tnah::Application::GetLogQueue();
		for(int i = 0; i < queue.size(); i++)
		{
			ImVec4 colour = ImVec4(queue[i].colour.x, queue[i].colour.y, queue[i].colour.z, 1);
			//ImVec4 colour = ImVec4(1, 1, 0.5, 1);
			ImGui::TextColored(colour, queue[i].text.c_str());
		}
	ImGui::End();

	ImGui::SetNextWindowSize({400, 500});
	ImGui::SetNextWindowPos({display.x - 400, pos.y}, true);
								
	ImGui::Begin("Can Interact", 0, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground);
	
	if(m_ActiveScene->GetPlayerInteraction())
	{
		ImGui::Text("U to pump them up (increase arousal)");
		ImGui::Text("I to calm them down (decrease arousal)");
		ImGui::Text("P to compliment them (increase valence)");
		ImGui::Text("O to insult them (decrease valence)");
	}
	
	ImGui::End();	
	
	if(m_CloseScreen)
	{
		auto io = ImGui::GetIO();
		auto display = ImGui::GetIO().DisplaySize;
		auto pos  = ImGui::GetWindowViewport()->Pos;
		//ImGui::SetNextWindowSize({size.x, size.y});
		ImGui::SetNextWindowSize({display.x + 10, display.y + 10});
		ImGui::SetNextWindowPos({pos.x - 10, pos.y - 10}, true);
		//ImGui::SetNextWindowPos({io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f}, ImGuiCond_Always, {0.5f, 0.5f});
		ImGui::Begin("##EndScreen", 0, ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoFocusOnAppearing);

		if(m_EndScreenImage)
		{
			auto windowSpace = ImGui::GetContentRegionAvail();
			ImGui::Image((void*)(intptr_t)m_EndScreenImage->GetRendererID(), windowSpace);
		}
		
	/*
		ImGui::SetCursorPos({(io.DisplaySize.x * 0.5f), (io.DisplaySize.y * 0.5f)});
		if(ImGui::Button("Exit"))
		{
			tnah::WindowCloseEvent c = tnah::WindowCloseEvent();
			tnah::Application::Get().OnEvent(c);
		}
	*/
		
		ImGui::End();

		if(ImGui::GetIO().MouseClicked[tnah::Mouse::ButtonLeft] || ImGui::GetIO().MouseClicked[tnah::Mouse::ButtonRight])
		{
			tnah::WindowCloseEvent c = tnah::WindowCloseEvent();
			tnah::Application::Get().OnEvent(c);
		}
	}
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

		if (k.GetKeyCode() == tnah::Key::Escape)
		{
			m_CloseScreen = !m_CloseScreen;
			if(m_CloseScreen)
			{
				m_CameraLookToggle = false;
				m_CameraMovementToggle = false;
				m_CursorVisible = false;
				tnah::Application::Get().GetWindow().SetCursorDisabled(!m_CursorVisible);
			}
			else
			{
				m_CameraLookToggle = true;
				m_CameraMovementToggle = true;
				m_CursorVisible = true;
				tnah::Application::Get().GetWindow().SetCursorDisabled(!m_CursorVisible);
			}
		}
		
		//Toggle the Cursor on or off
		if (k.GetKeyCode() == tnah::Key::D1 && m_EndScreenImage)
		{
			m_CursorVisible = !m_CursorVisible;
			tnah::Application::Get().GetWindow().SetCursorDisabled(!m_CursorVisible);
		}
		//Toggle Wireframe on or off
		if (k.GetKeyCode() == tnah::Key::D2 && m_EndScreenImage)
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
		
		if (k.GetKeyCode() == tnah::Key::D5 && m_EndScreenImage)
		{
			m_CameraLookToggle = !m_CameraLookToggle;
		}
		
		if (k.GetKeyCode() == tnah::Key::D6 && m_EndScreenImage)
		{
			m_CameraMovementToggle = !m_CameraMovementToggle;
		}

		if (k.GetKeyCode() == tnah::Key::D0 && m_EndScreenImage)
		{
			auto& debug = tnah::Application::Get().GetDebugModeStatus();
			debug = !debug;
			tnah::Application::Get().SetDebugStatusChange();
		}
	}
}
