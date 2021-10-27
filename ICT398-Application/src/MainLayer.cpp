 #include "MainLayer.h"

#include <TNAH-App.h>

MainLayer::MainLayer()
	:Layer("Main Layer")
{
	m_ActiveScene = tnah::Scene::CreateEmptyScene();
	m_Camera = m_ActiveScene->GetSceneCamera();
	m_SceneLight = m_ActiveScene->GetSceneLight();
	m_Terrain = m_ActiveScene->CreateGameObject("Terrain");
	
	// Camera Init
	{
		auto& ct = m_Camera.Transform();
		auto& cc = m_Camera.GetComponent<tnah::CameraComponent>();
		cc.Camera.SetViewportSize(1280, 720);
		ct.Position = glm::vec3(0, -4, 1);
		cc.ClearMode = tnah::CameraClearMode::Skybox;
		auto& m_Skybox = m_Camera.AddComponent<tnah::SkyboxComponent>();
		auto& as = m_Camera.AddComponent<tnah::AStarObstacleComponent>();
		as.dynamic = true;
		auto& rb = m_Camera.AddComponent<tnah::RigidBodyComponent>(m_Camera);
		//rb.AddCollider({0.2f, 0.8f, 0.2});
		rb.AddCollider(0.5f, 2.0f);
		rb.Body->SetType(tnah::Physics::BodyType::Kinematic);
		rb.Body->SetLinearDampening(0.99);
		rb.Body->GetBodyMass().SetMass(63.0f);
		
		auto & aff = m_Camera.AddComponent<tnah::Affordance>("User");
		m_Camera.AddComponent<tnah::PlayerInteractions>();
		aff.SetActionValues(tnah::Actions::abuse, 1.0f);
		aff.SetActionValues(tnah::Actions::greeting, 1.0f);
	}
	
	// Terrain Init
	{
		m_Terrain.AddComponent<tnah::TerrainComponent>("assets/heightmaps/1k.tga");
		auto& terrT = m_Terrain.Transform();
		terrT.Scale = glm::vec3(5.0f);
		terrT.Position = glm::vec3(-1000, -200, -500);
	}
	
	
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

		auto & a = go.AddComponent<tnah::AStarComponent>(tnah::Int2(-9,1), tnah::Int2(22, 9));
	}

	//Colliders Only
	{
		std::string name = "Front";
		
		auto&go = m_ActiveScene->CreateGameObject(name);
		auto&tt = go.Transform();
		
		tt.Position = {-10.63, 0, 0};
		
		auto& rb = go.AddComponent<tnah::RigidBodyComponent>(go);
		
		rb.AddCollider({1, 40, 60});
		rb.Body->SetType(tnah::Physics::BodyType::Static);
	}

	{
		std::string name = "Floor";
		
		auto&go = m_ActiveScene->CreateGameObject(name);
		auto&tt = go.Transform();
		
		tt.Position = {0, -6, 0};
		

		auto& rb = go.AddComponent<tnah::RigidBodyComponent>(go);
		
		rb.AddCollider({60, 2, 60});
		rb.Body->SetType(tnah::Physics::BodyType::Static);
	}

	
	{
		std::string name = "Back";
		
		auto&go = m_ActiveScene->CreateGameObject(name);
		auto&tt = go.Transform();
		
		tt.Position = {12.4, 0, 2.6};
		
		auto& rb = go.AddComponent<tnah::RigidBodyComponent>(go);
		
		rb.AddCollider({1, 60, 60});
		rb.Body->SetType(tnah::Physics::BodyType::Static);
	}

	{
		std::string name = "Left";
		
		auto&go = m_ActiveScene->CreateGameObject(name);
		auto&tt = go.Transform();
		
		tt.Position = {-1.4, 0, 10};
		
		auto& rb = go.AddComponent<tnah::RigidBodyComponent>(go);
		
		
		rb.AddCollider({65, 50, 1});
		rb.Body->SetType(tnah::Physics::BodyType::Static);
	}

	{
		std::string name = "Right";
		
		auto&go = m_ActiveScene->CreateGameObject(name);
		auto&tt = go.Transform();
		
		tt.Position = {0, 0, 0.2};
		
		auto& rb = go.AddComponent<tnah::RigidBodyComponent>(go);
		
		
		
		rb.AddCollider({65, 50, 1});
		rb.Body->SetType(tnah::Physics::BodyType::Static);
	}

	glm::vec3 pillarSize(0.5, 12, 0.5);
	{
		std::string name = "Pillar (1)";
		
		auto&go = m_ActiveScene->CreateGameObject(name);
		auto&tt = go.Transform();
		auto&as = go.AddComponent<tnah::AStarObstacleComponent>();
		tt.Position = {5.3, 0, 9.0};
		
		auto& rb = go.AddComponent<tnah::RigidBodyComponent>(go);
		
		
		rb.AddCollider({pillarSize});
		rb.Body->SetType(tnah::Physics::BodyType::Static);	
	}

	{
		std::string name = "Pillar (2)";
		
		auto&go = m_ActiveScene->CreateGameObject(name);
		auto&tt = go.Transform();
		auto&as = go.AddComponent<tnah::AStarObstacleComponent>();
		tt.Position = {5.3, 0, 4.6};
		
		auto& rb = go.AddComponent<tnah::RigidBodyComponent>(go);
		
		
		
		rb.AddCollider({pillarSize});
		rb.Body->SetType(tnah::Physics::BodyType::Static);
	}

	{
		std::string name = "Pillar (3)";
		
		auto&go = m_ActiveScene->CreateGameObject(name);
		auto&tt = go.Transform();
		auto&as = go.AddComponent<tnah::AStarObstacleComponent>();
		tt.Position = {-1.8, 0, 4.6};
		
		auto& rb = go.AddComponent<tnah::RigidBodyComponent>(go);
		
		
		
		rb.AddCollider({pillarSize});
		rb.Body->SetType(tnah::Physics::BodyType::Static);	
	}

	{
		std::string name = "Pillar (4)";
		
		auto&go = m_ActiveScene->CreateGameObject(name);
		auto&tt = go.Transform();
		auto&as = go.AddComponent<tnah::AStarObstacleComponent>();
		tt.Position = {-1.8, 0, 9.0};
		
		auto& rb = go.AddComponent<tnah::RigidBodyComponent>(go);
		
		
		
		rb.AddCollider({pillarSize});
		rb.Body->SetType(tnah::Physics::BodyType::Static);	
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

	{
		std::string name = "coffee cup 1";
		glm::vec3 size(0.25, 0.5, 0.25);
		auto&go = m_ActiveScene->CreateGameObject(name);
		auto&tt = go.Transform();
		auto& mesh = go.AddComponent<tnah::MeshComponent>();
		mesh.Model = tnah::Model::Create("assets/meshes/bin.fbx");
		
		tt.Position = {1, -3.7, 3};
		tt.Scale = size;
		/*auto& rb = go.AddComponent<tnah::RigidBodyComponent>(go);
		(glm::vec3(size));
		
		
		rb.SetBodyType(rp3d::BodyType::STATIC);*/
		
		auto& affordance = go.AddComponent<tnah::Affordance>("Coffee");
		affordance.SetActionValues(tnah::Actions::pickup, 1.0f);
		affordance.SetActionValues(tnah::Actions::drink, 1.0f);
		affordance.SetActionValues(tnah::Actions::sit, 0.1f);
	}

	{
		std::string name = "coffee cup 2";
		glm::vec3 size(0.25, 0.5, 0.25);
		auto&go = m_ActiveScene->CreateGameObject(name);
		auto&tt = go.Transform();
		auto& mesh = go.AddComponent<tnah::MeshComponent>();
		mesh.Model = tnah::Model::Create("assets/meshes/cube_texture.fbx");
		
		tt.Position = {8, -3.7, 7};
		tt.Scale = size;
		/*auto& rb = go.AddComponent<tnah::RigidBodyComponent>(go);
		(glm::vec3(size));
		
		
		rb.SetBodyType(rp3d::BodyType::STATIC);*/
		
		auto& affordance = go.AddComponent<tnah::Affordance>("Coffee");
		affordance.SetActionValues(tnah::Actions::pickup, 1.0f);
		affordance.SetActionValues(tnah::Actions::drink, 1.0f);
		affordance.SetActionValues(tnah::Actions::sit, 0.1f);
	}

	{
		std::string name = "rest mat";
		glm::vec3 size(0.25, 0.1, 0.25);
		auto&go = m_ActiveScene->CreateGameObject(name);
		auto&tt = go.Transform();
		auto& mesh = go.AddComponent<tnah::MeshComponent>();
		mesh.Model = tnah::Model::Create("assets/meshes/cube_texture.fbx");
		
		tt.Position = {12, -4.1, 8};
		tt.Scale = size;
		
		auto& affordance = go.AddComponent<tnah::Affordance>("Mat");
		affordance.SetActionValues(tnah::Actions::sleep, 1.0f);
		affordance.SetActionValues(tnah::Actions::sit, 0.5f);
		affordance.SetActionValues(tnah::Actions::pickup, 0.1f);
	}

	{
		std::string name = "rest mat 2";
		glm::vec3 size(0.25, 0.1, 0.25);
		auto&go = m_ActiveScene->CreateGameObject(name);
		auto&tt = go.Transform();
		auto& mesh = go.AddComponent<tnah::MeshComponent>();
		mesh.Model = tnah::Model::Create("assets/meshes/cube_texture.fbx");
		
		tt.Position = {5, -4.1, 4};
		tt.Scale = size;
		
		auto& affordance = go.AddComponent<tnah::Affordance>("Mat");
		affordance.SetActionValues(tnah::Actions::sleep, 1.0f);
		affordance.SetActionValues(tnah::Actions::sit, 0.5f);
		affordance.SetActionValues(tnah::Actions::pickup, 0.1f);
	}

		{
    		std::string name = "Game Console";
    		glm::vec3 size(0.25, 0.1, 0.25);
    		auto&go = m_ActiveScene->CreateGameObject(name);
    		auto&tt = go.Transform();
    		auto& mesh = go.AddComponent<tnah::MeshComponent>();
    		mesh.Model = tnah::Model::Create("assets/meshes/cube_texture.fbx");
    		
    		tt.Position = {7, -4.1, 5};
    		tt.Scale = size;
    		
    		auto& affordance = go.AddComponent<tnah::Affordance>("Game Console");
    		affordance.SetActionValues(tnah::play, 1.0f);
    		affordance.SetActionValues(tnah::Actions::pickup, 0.1f);
    	}
	
	glm::vec3 binSize(1, 1, 1), binScale(0.3, 0.3, 0.3), binRotation(0, 0, 0);
	{
		std::string name = "Bin (1)";
		
		auto&go = m_ActiveScene->CreateGameObject(name);
		auto&tt = go.Transform();
		auto& mesh = go.AddComponent<tnah::MeshComponent>();
		mesh.Model = tnah::Model::Create("assets/meshes/bin.fbx");
		
		tt.Position = {5.3, -3.7, 3.9};
		tt.Rotation = binRotation;
		tt.Scale = binScale / glm::vec3(2);
		auto& rb = go.AddComponent<tnah::RigidBodyComponent>(go);
		
		rb.AddCollider({0.15, 0.15, 0.15});
		rb.Body->SetType(tnah::Physics::BodyType::Static);	
		
		go.AddComponent<tnah::AIComponent>();
		go.AddComponent<tnah::CharacterComponent>(tnah::CharacterNames::Rubbish);
	}
	
	{
		std::string name = "Bin (3)";
		
		m_object = m_ActiveScene->CreateGameObject(name);
		auto&tt = m_object.Transform();
		auto& mesh = m_object.AddComponent<tnah::MeshComponent>();
		mesh.Model = tnah::Model::Create("assets/meshes/bin.fbx");
		
		tt.Position = {0, -3, 1};
		tt.Rotation = binRotation;
		tt.Scale = binScale / glm::vec3(2);
		auto& rb = m_object.AddComponent<tnah::RigidBodyComponent>(m_object);
		
		rb.AddCollider({0.15, 0.15, 0.15});
		rb.Body->SetLinearDampening(0.99);
		rb.Body->GetBodyMass().SetMass(100.0f);
		auto & star = m_object.AddComponent<tnah::AStarObstacleComponent>();
		star.dynamic = true;
		auto & aff = m_object.AddComponent<tnah::Affordance>();
		aff.SetActionValues(tnah::Actions::kick, 1.0f);
		//rb.Body->SetType(tnah::Physics::BodyType::Dynamic);	
	}

	{
		std::string name = "Other object";
		
		auto & go = m_ActiveScene->CreateGameObject(name);
		auto&tt = go.Transform();
		auto& mesh = go.AddComponent<tnah::MeshComponent>();
		mesh.Model = tnah::Model::Create("assets/meshes/cube_texture.fbx");
		
		tt.Position = {10, 0, 1};
		tt.Scale = {1, 1, 0.1};
		auto& rb = go.AddComponent<tnah::RigidBodyComponent>(go);
		
		rb.AddCollider(tt.Scale);
		rb.Body->SetLinearDampening(0.99);
		auto & star = go.AddComponent<tnah::AStarObstacleComponent>();
		star.dynamic = true;
		//auto & aff = m_object.AddComponent<tnah::Affordance>();
		//aff.SetActionValues(tnah::Actions::kick, 1.0f);
		//rb.Body->SetType(tnah::Physics::BodyType::Dynamic);	
	}
	
	{
		std::string name = "Dog";
		glm::vec3 DogCollider = {0.3, 0.4, 0.7};
		auto&go = m_ActiveScene->CreateGameObject(name);
		auto&tt = go.Transform();
		auto& mesh = go.AddComponent<tnah::MeshComponent>();
		mesh.Model = tnah::Model::Create("assets/meshes/Puppy3.fbx");
		
		tt.Position = {12, -3.7, 8};
		tt.Rotation = glm::vec3(0, glm::radians(-90.0f), 0);
		tt.Scale = glm::vec3(0.015);
		auto& rb = go.AddComponent<tnah::RigidBodyComponent>(go);

		rb.AddCollider({DogCollider});
		rb.Body->SetType(tnah::Physics::BodyType::Static);	
		
		go.AddComponent<tnah::AIComponent>();
		go.AddComponent<tnah::CharacterComponent>(tnah::CharacterNames::DogAi);
	}

	{
		std::string name = "Student";
		
		glm::vec3 StudentCollider = { 0.3, 0.6, 0.3 };
		auto& go = m_ActiveScene->CreateGameObject(name);
		auto& tt = go.Transform();
		auto& mesh = go.AddComponent<tnah::MeshComponent>();
		mesh.Model = tnah::Model::Create("assets/meshes/ninja2.fbx");

		tt.Position = {2.0, -3.5, 4.0 };
		tt.Rotation = glm::vec3(0, glm::radians(90.0f), 0);
		tt.Scale = glm::vec3(0.03);
		auto& rb = go.AddComponent<tnah::RigidBodyComponent>(go);

		rb.AddCollider({StudentCollider});
		rb.Body->SetType(tnah::Physics::BodyType::Static);	

		go.AddComponent<tnah::AIComponent>();
		go.AddComponent<tnah::CharacterComponent>(tnah::CharacterNames::StudentAi);
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
		auto&as = go.AddComponent<tnah::AStarObstacleComponent>();
		auto& rb = go.AddComponent<tnah::RigidBodyComponent>(go);
		
		
		
		rb.AddCollider({binScale});
		rb.Body->SetType(tnah::Physics::BodyType::Static);
		
		auto & a = go.AddComponent<tnah::Affordance>("Bin (not alive)");
		a.SetActionValues(tnah::kick, 1);
	}

	glm::vec3 tableScale(0.01, 0.02, 0.01), tableRotation(0, 0, 0), tableSize(0.4, 0.4, 0.6);
	{
		std::string name = "Table (1)";
		
		auto&go = m_ActiveScene->CreateGameObject(name);
		auto&tt = go.Transform();
		auto& mesh = go.AddComponent<tnah::MeshComponent>();
		mesh.Model = tnah::Model::Create("assets/meshes/table.fbx");
		
		tt.Position = {-3, -3.6, 6};
		tt.Rotation = tableRotation;
		tt.Scale = tableScale;
		auto&as = go.AddComponent<tnah::AStarObstacleComponent>();
		auto& rb = go.AddComponent<tnah::RigidBodyComponent>(go);

		
		
		rb.AddCollider({tableSize});
		rb.Body->SetType(tnah::Physics::BodyType::Static);
		
		auto & a = go.AddComponent<tnah::Affordance>("Table");
		a.SetActionValues(tnah::kick, 1);
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
		auto&as = go.AddComponent<tnah::AStarObstacleComponent>();
		auto& rb = go.AddComponent<tnah::RigidBodyComponent>(go);

		
		rb.AddCollider({tableSize});
		rb.Body->SetType(tnah::Physics::BodyType::Static);	
		go.AddComponent<tnah::Affordance>();
		auto & a = go.AddComponent<tnah::Affordance>("Table");
		a.SetActionValues(tnah::kick, 1);
	}
	glm::vec3 chairScale(0.1, 0.1, 0.1);
	{
		std::string name = "Chair (1)";
		
		auto&go = m_ActiveScene->CreateGameObject(name);
		auto&tt = go.Transform();
		auto& mesh = go.AddComponent<tnah::MeshComponent>();
		mesh.Model = tnah::Model::Create("assets/meshes/chair.fbx");
		
		tt.Position = {-4, -4, 6};
		//tt.Rotation = glm::eulglm::vec3(glm::radians(180.0f), 0, 0);
		tt.Scale = chairScale;
		auto&as = go.AddComponent<tnah::AStarObstacleComponent>();
		auto& rb = go.AddComponent<tnah::RigidBodyComponent>(go);

		
		rb.AddCollider({0.25, 1, 0.25});
		rb.Body->SetLinearDampening(0.9);
		rb.Body->SetType(tnah::Physics::BodyType::Static);
		go.AddComponent<tnah::Affordance>();
		auto & a = go.AddComponent<tnah::Affordance>("Chair");
		a.SetActionValues(tnah::kick, 0.5);
		a.SetActionValues(tnah::sit, 1);
		//a.SetActionValues
	}

	{
		std::string name = "Chair (2)";
		
		auto&go = m_ActiveScene->CreateGameObject(name);
		auto&tt = go.Transform();
		auto& mesh = go.AddComponent<tnah::MeshComponent>();
		mesh.Model = tnah::Model::Create("assets/meshes/chair.fbx");
		
		tt.Position = {-2, -4, 6};
		tt.Rotation = glm::vec3(0, glm::radians(180.0f), 0);
		tt.Scale = chairScale;
		auto&as = go.AddComponent<tnah::AStarObstacleComponent>();
		auto& rb = go.AddComponent<tnah::RigidBodyComponent>(go);

		rb.AddCollider({0.25, 1, 0.25});
		rb.Body->SetType(tnah::Physics::BodyType::Static);	
		auto & a = go.AddComponent<tnah::Affordance>("Chair");
		a.SetActionValues(tnah::kick, 0.5);
		a.SetActionValues(tnah::sit, 1);
	}
	
	{
		std::string name = "Chair (3)";
		
		auto&go = m_ActiveScene->CreateGameObject(name);
		auto&tt = go.Transform();
		auto& mesh = go.AddComponent<tnah::MeshComponent>();
		mesh.Model = tnah::Model::Create("assets/meshes/chair.fbx");
		
		tt.Position = {-8, -4, 7};
		tt.Rotation = glm::vec3(0, 0, 0);
		tt.Scale = chairScale;
		auto& rb = go.AddComponent<tnah::RigidBodyComponent>(go);

		rb.AddCollider({0.25, 1, 0.25});
		rb.Body->SetType(tnah::Physics::BodyType::Static);	
		auto&as = go.AddComponent<tnah::AStarObstacleComponent>();
		auto & a = go.AddComponent<tnah::Affordance>("Chair");
		a.SetActionValues(tnah::kick, 0.5);
		a.SetActionValues(tnah::sit, 1);
	}

	{
		std::string name = "Chair (4)";
		
		auto&go = m_ActiveScene->CreateGameObject(name);
		auto&tt = go.Transform();
		auto& mesh = go.AddComponent<tnah::MeshComponent>();
		mesh.Model = tnah::Model::Create("assets/meshes/chair.fbx");
		
		tt.Position = {-6, -4, 7};
		tt.Rotation = glm::vec3(0, glm::radians(180.0f), 0);
		tt.Scale = chairScale;
		auto& rb = go.AddComponent<tnah::RigidBodyComponent>(go);
		
		rb.AddCollider({0.25, 1, 0.25});
		rb.Body->SetType(tnah::Physics::BodyType::Static);	
		auto&as = go.AddComponent<tnah::AStarObstacleComponent>();
		auto & a = go.AddComponent<tnah::Affordance>("Chair");
		a.SetActionValues(tnah::kick, 0.5);
		a.SetActionValues(tnah::sit, 1);
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
	if(m_Camera.HasComponent<tnah::RigidBodyComponent>())
	{
		auto& ct = m_Camera.Transform();
		
		if(m_CameraMovementToggle)
		{
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

			if(m_CameraLookToggle)
			{
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

				ct.QuatRotation = glm::quat(ct.Rotation);
			}
			
			if(tnah::Input::IsKeyPressed(tnah::Key::Space))
			{
				if(!m_space)
				{
					auto & rbObj = m_object.GetComponent<tnah::RigidBodyComponent>();
					rbObj.Body->ResetValues();
					auto & transformObj = m_object.GetComponent<tnah::TransformComponent>();
					transformObj.Position = ct.Position + (ct.Forward * 2.0f);
					transformObj.Rotation = ct.Rotation;
					transformObj.QuatRotation = ct.QuatRotation;
					const auto force = ct.Forward * 20.0f;
					rbObj.Body->AddForce(force);
				}
				m_space = true;
			}
			else
				m_space = false;
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
	// Application Panel
	{ 
		const auto windowSize = ImGui::GetMainViewport()->Size;
		const auto windowPos = ImGui::GetMainViewport()->Pos;
		ImGui::SetNextWindowPos(windowPos);
		auto x = windowSize.x / 5;
		if(x < 500) { x = 500; }
		ImGui::SetNextWindowSize({x, windowSize.y / 2});
		static bool m_ApplicationPanel = true;
		ImGui::Begin("Application", &m_ApplicationPanel);
		
		ImGui::Text("%.1f FPS | %.0f ms", ImGui::GetIO().Framerate, 1000.0f / ImGui::GetIO().Framerate);
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

		if(ImGui::CollapsingHeader("Physics"))
		{
			ImGui::Checkbox("Gravity", &tnah::Physics::PhysicsEngine::GetManager()->GetGravityState());
			if(tnah::Physics::PhysicsEngine::GetManager()->GetGravityState())
			{
				tnah::EditorUI::DrawVec3Control("Force", tnah::Physics::PhysicsEngine::GetManager()->GetGravity());
			}
			ImGui::Checkbox("Allow Sleeping", &tnah::Physics::PhysicsEngine::GetManager()->GetSleepState());
			ImGui::Checkbox("Collider Rendering", &tnah::Physics::PhysicsEngine::GetColliderRendererHandle());
		}
		
		ImGui::Separator();
		
		if(ImGui::CollapsingHeader("Hierarchy"))
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

	// Agent Values Panel
	{
		auto size = ImGui::GetMainViewport()->Size;
		auto pos  = ImGui::GetWindowViewport()->Pos;
		ImGui::SetNextWindowSize({500, size.y / 2});
		ImGui::SetNextWindowPos({pos.x, (pos.y + ( size.y / 2))});
		ImGui::Begin("Agents Values", 0, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground);
		auto queue = tnah::Application::GetLogQueue();
		for(int i = 0; i < queue.size(); i++)
		{
			ImVec4 colour = ImVec4(queue[i].colour.x, queue[i].colour.y, queue[i].colour.z, 1);
			//ImVec4 colour = ImVec4(1, 1, 0.5, 1);
			ImGui::TextColored(colour, queue[i].text.c_str());
		}
		ImGui::End();
	}

	// Interaction Panel
	{
		auto size = ImGui::GetMainViewport()->Size;
		auto pos  = ImGui::GetMainViewport()->Pos;
		ImGui::SetNextWindowSize({400, 500});
		ImGui::SetNextWindowPos({(pos.x + size.x) - 400, pos.y});
		
		ImGui::Begin("Can Interact", 0, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground);
		if(m_ActiveScene->GetPlayerInteraction())
		{
			ImGui::Text("Hold U increase arousal or I decrease arousal");
			ImGui::Text("Hold P increase valence or O decrease valence");
			ImGui::Text(m_ActiveScene->GetTargetString().c_str());
		}
	
		ImGui::End();
	}

	// Exit Image Panel
	if(m_CloseScreen)
	{
		auto size = ImGui::GetMainViewport()->Size;
		auto pos  = ImGui::GetWindowViewport()->Pos;
		ImGui::SetNextWindowSize({size.x + 10, size.y + 10});
		ImGui::SetNextWindowPos({pos.x - 10, pos.y - 10}, true);
		ImGui::Begin("##EndScreen", 0, ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoFocusOnAppearing);

		if(m_EndScreenImage)
		{
			auto windowSpace = ImGui::GetContentRegionAvail();
			ImGui::Image((void*)(intptr_t)m_EndScreenImage->GetRendererID(), windowSpace);
		}
		
	
		ImGui::SetCursorPos({(size.x * 0.5f), (size.y * 0.5f)});
		if(ImGui::Button("Exit"))
		{
			tnah::WindowCloseEvent c = tnah::WindowCloseEvent();
			tnah::Application::Get().OnEvent(c);
		}
		
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
