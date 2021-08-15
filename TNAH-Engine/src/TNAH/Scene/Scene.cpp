#include <tnahpch.h>
#include "Scene.h"
#include "GameObject.h"
#include "Components/Components.h"
#include "TNAH/Renderer/Renderer.h"

namespace tnah{

	Scene::Scene()
	{
		
		auto c = CreateGameObject("Main Camera");
		m_ActiveCamera.reset(c);
		m_ActiveCamera->AddComponent<CameraComponent>();

		auto l = CreateGameObject("Main Light");
		m_SceneLight.reset(l);
		auto& light = m_SceneLight->AddComponent<LightComponent>();
		light.Light.reset(Light::CreateDirectional());
		light.Light->m_IsSceneLight = true;
	}

	Scene::~Scene()
	{
	}

	Scene* Scene::CreateSceneFromFile(const std::string& filePath)
	{
		//Do Something here to load a scene file, possibly with the scene serializer

		return new Scene();
	}

	Scene* Scene::CreateEmptyScene()
	{
		return new Scene();
	}

	void Scene::OnUpdate(Timestep deltaTime)
	{
		//Update all transform components and their forward, right and up vectors
		{
			auto view = m_Registry.view<TransformComponent>();
			for (auto obj : view)
			{
				auto& transform = view.get<TransformComponent>(obj);

				glm::vec3 forward = glm::vec3(0.0f);
				glm::vec3 right = glm::vec3(0.0f);
				glm::vec3 up = glm::vec3(0.0f);
				forward.x = cos(glm::radians(transform.Rotation.x)) * cos(glm::radians(transform.Rotation.y));
				forward.y = sin(glm::radians(transform.Rotation.y));
				forward.z = sin(glm::radians(transform.Rotation.x)) * cos(glm::radians(transform.Rotation.y));
				forward = glm::normalize(forward);
				right = glm::normalize(glm::cross(forward, glm::vec3(0, 1, 0)));
				up = glm::normalize(glm::cross(right, forward));

				transform.Forward = forward;
				transform.Right = right;
				transform.Up = up;
			}
		}

		//after the transform is updated, update the camera matrix etc
		{
			auto view = m_Registry.view<TransformComponent, CameraComponent>();
			for(auto entity : view)
			{ 
				auto& camera = view.get<CameraComponent>(entity);
				auto& transform = view.get<TransformComponent>(entity);
				camera.Camera.OnUpdate(transform);
			}
		}

		//Renderer Stuff
		{
			glm::vec3 cameraPosition;
			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
			RenderCommand::Clear();
			{
				auto view = m_Registry.view<TransformComponent, CameraComponent>();
				for(auto entity : view)
				{ 
					auto& camera = view.get<CameraComponent>(entity);
					auto& transform = view.get<TransformComponent>(entity);
					cameraPosition = transform.Position;
					Renderer::BeginScene(camera);
					break;
					TNAH_CORE_ASSERT(false, "The TNAH-Engine only supports rendering from a single camera!")
				}
			}

			std::vector<Ref<Light>> sceneLights;
			{
				auto view = m_Registry.view<LightComponent, TransformComponent>();
				for(auto entity : view)
				{
					auto& light = view.get<LightComponent>(entity);
					auto& transform = view.get<TransformComponent>(entity);
					light.Light->SetPosition(transform.Position);
					light.Light->UpdateShaderLightInfo(cameraPosition);
					sceneLights.push_back(light.Light);
				}
			}

			
			//Render any terrain objects
			{
				auto view = m_Registry.view<TransformComponent, TerrainComponent>();
				for(auto entity : view)
				{
					auto& terrain = view.get<TerrainComponent>(entity);
					auto& transform = view.get<TransformComponent>(entity);

					Renderer::SubmitTerrain(terrain.SceneTerrain->GetVertexArray(), terrain.SceneTerrain->GetMaterial(), sceneLights, transform.GetTransform());
				}
			}

			//Render all mesh components
			{
				auto view = m_Registry.view<TransformComponent, MeshComponent>();
				for(auto entity : view)
				{
					auto& model = view.get<MeshComponent>(entity);
					auto& transform = view.get<TransformComponent>(entity);

					for(auto& mesh : model.Model->GetMeshes())
					{
						Renderer::SubmitMesh(mesh.GetMeshVertexArray(), mesh.GetMeshMaterial(), sceneLights, transform.GetTransform());
					}
				}
			}





			
			Renderer::EndScene();
		}
	}

	void Scene::OnFixedUpdate(PhysicsTimestep time)
	{
		//Physics calculations go here, they are not rendered here however

		//{
		//	auto view = m_Registry.view<TransformComponent, PhysicsComponent>(); //Rigidbody whatever we call it
		//	for (auto entity : view)
		//	{
		//		auto& physics = view.get<PhysicsComponent>(entity);
		//		auto& transform = view.get<TransformComponent>(entity);

		//		//Do the physics stuff around here
		//	}
		//}
	}

	glm::mat4 Scene::GetTransformRelativeToParent(GameObject gameObject)
	{
		glm::mat4 transform(1.0f);

		GameObject parent = FindEntityByUUID(gameObject.GetParentUUID());
		if (parent)
			transform = GetTransformRelativeToParent(parent);

		return transform * gameObject.Transform().GetTransform();
	}

	GameObject* Scene::CreateGameObject(const std::string& name)
	{
		GameObject go = { m_Registry.create(), this };
		auto& idComponent = go.AddComponent<IDComponent>();
		idComponent.ID = {};
		go.AddComponent<TransformComponent>();
		if (!name.empty())
		{
			go.AddComponent<TagComponent>(name);
		}

		go.AddComponent<RelationshipComponent>();

		
		m_GameObjectsInScene[idComponent.ID] = go;
		return &m_GameObjectsInScene[idComponent.ID];
	}


	GameObject Scene::CreateGameObject()
	{
		GameObject go = { m_Registry.create(), this };
		auto& idComponent = go.AddComponent<IDComponent>();
		idComponent.ID = {};
		go.AddComponent<TransformComponent>();
		go.AddComponent<TagComponent>("Default");

		go.AddComponent<RelationshipComponent>();

		m_GameObjectsInScene[idComponent.ID] = go;
		return go;
	}
	
	GameObject Scene::FindEntityByTag(const std::string& tag)
	{
		auto view = m_Registry.view<TagComponent>();
		for (auto entity : view)
		{
			const auto& canditate = view.get<TagComponent>(entity).Tag;
			if (canditate == tag)
				return GameObject(entity, this);
		}

		return GameObject{};
	}

	GameObject Scene::FindEntityByUUID(UUID id)
	{
		auto view = m_Registry.view<IDComponent>();
		for (auto entity : view)
		{
			auto& idComponent = m_Registry.get<IDComponent>(entity);
			if (idComponent.ID == id)
				return GameObject(entity, this);
		}

		return GameObject{};
	}

	GameObject Scene::FindGameObjectByID(const entt::entity& id)
	{
		for(auto go : m_GameObjectsInScene)
		{
			if(go.second.GetID() == id)
			{
				return go.second;
			}
		}
		return GameObject();
	}
	
	void Scene::DestroyGameObject(GameObject gameObject)
	{
		m_Registry.destroy(gameObject.GetID());
	}

	Ref<GameObject> Scene::GetMainCameraGameObject()
	{
		return m_ActiveCamera;
	}

	Ref<GameObject> Scene::GetSceneLightGameObject()
	{
		return m_SceneLight;
	}

	Ref<CameraComponent> Scene::GetMainCameraComponent()
	{
		Ref<CameraComponent> c;
		c.reset(&m_ActiveCamera->GetComponent<CameraComponent>());
		return c;
	}

	Ref<LightComponent> Scene::GetSceneLightComponent()
	{
		Ref<LightComponent> l;
		l.reset(&m_SceneLight->GetComponent<LightComponent>());
		return l;
	}

	Ref<TransformComponent> Scene::GetMainCameraTransform()
	{
		Ref<TransformComponent> t;
		auto& ct = m_ActiveCamera->GetComponent<TransformComponent>();
		t.reset(&ct);
		return t;
	}

	Ref<TransformComponent> Scene::GetSceneLightTransform()
	{
		Ref<TransformComponent> t;
		TransformComponent* lt = &m_SceneLight->GetComponent<TransformComponent>();
		t.reset(lt);
		return t;
	}

	Ref<SceneCamera> Scene::GetMainCamera()
	{
		Ref<SceneCamera> c;
		auto& cam  = m_ActiveCamera->GetComponent<CameraComponent>();
		c.reset(&cam.Camera);
		return c;
	}

	Ref<Light> Scene::GetSceneLight()
	{
		return m_SceneLight->GetComponent<LightComponent>().Light;
	}
}

