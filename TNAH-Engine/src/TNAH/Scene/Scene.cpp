#include <tnahpch.h>
#include "Scene.h"
#include "GameObject.h"
#include "Components/Components.h"
#include "TNAH/Core/Application.h"
#include "TNAH/Core/Input.h"
#include "TNAH/Renderer/Renderer.h"
#include "TNAH/Audio/Audio.h"

namespace tnah{

	std::unordered_map<UUID, Scene*> s_ActiveScenes;

	struct SceneComponent
	{
		UUID SceneID;
	};
	
	std::map<UUID, GameObject>& Scene::GetGameObjectsInScene()
	{
		return m_GameObjectsInScene;
	}

	GameObject* Scene::GetRefGameObject(const UUID id)
	{
		return &m_GameObjectsInScene[id];
	}

	Scene::Scene(bool editor)
	{
		m_SceneEntity = m_Registry.create();
		m_Registry.emplace<SceneComponent>(m_SceneEntity, m_SceneID);
		if(editor)
		{
			m_EditorCamera.reset(CreateEditorCamera());
			FramebufferSpecification fbspec = {1280, 720};
			m_EditorSceneFramebuffer.reset(Framebuffer::Create(fbspec));
			m_EditorGameFramebuffer.reset(Framebuffer::Create(fbspec));
			m_IsEditorScene = true;
			m_EditorCamera->AddComponent<SkyboxComponent>();
			m_RenderPasses = 2;
		}

		auto c = CreateGameObject("Main Camera");
		m_ActiveCamera.reset(c);
		m_ActiveCamera->AddComponent<CameraComponent>();
		
		
		
		auto l = CreateGameObject("Main Light");
		m_SceneLight.reset(l);
		auto& light = m_SceneLight->AddComponent<LightComponent>();
		light.Light.reset(Light::CreateDirectional());
		light.Light->m_IsSceneLight = true;

		s_ActiveScenes[m_SceneID] = this;
	}

	Scene::~Scene()
	{
		m_Registry.clear();
		s_ActiveScenes.erase(m_SceneID);
		m_EditorGameFramebuffer.reset();
		m_EditorSceneFramebuffer.reset();
		//m_GameObjectsInScene.clear();
		//m_ActiveCamera.reset();
		//m_EditorCamera.reset();
		//m_SceneLight.reset();
	}

	Scene* Scene::CreateNewEditorScene()
	{
		return new Scene(true);
	}
	

	Ref<GameObject> Scene::GetEditorCameraGameObject()
	{
		return m_EditorCamera;
	}

	Scene* Scene::CreateEmptyScene()
	{
		return new Scene();
	}

	void Scene::OnUpdate(Timestep deltaTime)
	{
		//TODO: Actually test the player controller component
		// Process any PlayerControllers before updating anything else in the scene
		{
			auto e = EditorComponent();

			Audio::Update();
			
			auto view = m_Registry.view<PlayerControllerComponent, TransformComponent>();
			for(auto obj : view)
			{
				auto& editor = m_EditorCamera->GetComponent<EditorComponent>();
				//Only run this update for a player controller if the editor isnt empty, were in play mode to test the scene
				// or this scene isnt being ran in a editor ie in the runtime
				if((m_EditorCamera != nullptr && editor.m_EditorMode == EditorComponent::EditorMode::Play) || (!m_IsEditorScene && this->FindGameObjectByID(obj).IsActive()))
				{
					auto& transform = view.get<TransformComponent>(obj);
					auto& player = view.get<PlayerControllerComponent>(obj);
					// Only continue if the component is active/enabled
					if(player.IsActive())
					{
						if(!player.m_MouseDisabled) Application::Get().GetWindow().SetCursorDisabled(true); player.m_MouseDisabled = true;
						float s = 0.0f;
						// if were sprinting, use sprint speed else if were crouched use crouched speed else use the normal movement speed
						auto speed = (player.IsSprinting()) ? player.SprintSpeed : (s = (player.IsCrouched()) ? player.CrouchSpeed : player.MovementSpeed);
				
						if(Input::IsKeyPressed(player.Forward)) transform.Position += transform.Forward * speed * deltaTime.GetSeconds();
						if(Input::IsKeyPressed(player.Backward)) transform.Position -= transform.Forward * speed * deltaTime.GetSeconds();
						if(Input::IsKeyPressed(player.Left)) transform.Position -= transform.Right * speed * deltaTime.GetSeconds();
						if(Input::IsKeyPressed(player.Right)) transform.Position += transform.Right * speed * deltaTime.GetSeconds();
						player.ProcessMouseRotation(transform);
					}
				}
			}
			
		}
		
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

		uint32_t passes = 0;
		

		do
		{
			if(m_IsEditorScene)
			{
				if(passes == 0)
				{
					m_EditorSceneFramebuffer->Bind(0);
				}
				
				if(passes == 1)
				{
					
					m_EditorGameFramebuffer->Bind(0);
				}
			}
		
			//after the transform is updated, update the camera matrix etc 
			{
				if(m_IsEditorScene && passes == 0)
				{
					auto& camera = m_EditorCamera->GetComponent<EditorCameraComponent>().EditorCamera;
					auto& transform = m_EditorCamera->GetComponent<TransformComponent>();
					camera.OnUpdate(transform);
				}
				else
				{
					auto view = m_Registry.view<TransformComponent, CameraComponent>();
					for(auto entity : view)
					{ 
						auto& camera = view.get<CameraComponent>(entity);
						auto& transform = view.get<TransformComponent>(entity);
						camera.Camera.OnUpdate(transform);
					}
				}
			}

			//Renderer Stuff
			{
				glm::vec3 cameraPosition;
				bool usingSkybox = false;
			
			
				{
					//Check if its were in the editor, if so render from the perspective of the editor camera
					if(m_IsEditorScene && passes == 0)
					{
						auto& camera = m_EditorCamera->GetComponent<EditorCameraComponent>();
						auto transform = m_EditorCamera->GetComponent<TransformComponent>();
						cameraPosition = transform.Position;
						if(camera.ClearMode == CameraClearMode::Color)
						{
							RenderCommand::SetClearColor(camera.ClearColor);
							RenderCommand::Clear();
						
						}
						else if(camera.ClearMode == CameraClearMode::Skybox)
						{
							RenderCommand::SetClearColor({0.0f, 0.0f, 0.0f, 1.0f});
							RenderCommand::Clear();
							usingSkybox = true;
						}
					
						Renderer::BeginScene(camera, transform);
					
					}
					else
					{
						auto view = m_Registry.view<TransformComponent, CameraComponent>();
						for(auto entity : view)
						{ 
							auto& camera = view.get<CameraComponent>(entity);
							auto& transform = view.get<TransformComponent>(entity);
							cameraPosition = transform.Position;
							if(camera.ClearMode == CameraClearMode::Color)
							{
								RenderCommand::SetClearColor(camera.ClearColor);
								RenderCommand::Clear();
							}
							else if(camera.ClearMode == CameraClearMode::Skybox)
							{
								RenderCommand::SetClearColor({0.0f, 0.0f, 0.0f, 1.0f});
								RenderCommand::Clear();
								usingSkybox = true;
							}
						
							Renderer::BeginScene(camera, transform);
							break;
							TNAH_CORE_ASSERT(false, "The TNAH-Engine only supports rendering from a single camera!")
						}
					}
				}

				// Skybox
				if(usingSkybox)
				{
					auto view = m_Registry.view<SkyboxComponent>();
					for(auto obj : view)
					{
						auto& skybox = view.get<SkyboxComponent>(obj);
						// Bind the skybox shader
						// Do any skybox render setup
						Renderer::SubmitSkybox(skybox.SceneSkybox->GetVertexArray(), skybox.SceneSkybox->GetMaterial());
					}
				}

				

				std::vector<Ref<Light>> sceneLights;
				{
					auto view = m_Registry.view<LightComponent, TransformComponent>();
					for(auto entity : view)
					{
						auto& light = view.get<LightComponent>(entity);
						auto& transform = view.get<TransformComponent>(entity);
						if(light.Light == nullptr) continue; 
						light.Light->SetPosition(transform.Position);
						light.Light->UpdateShaderLightInfo(cameraPosition);
						sceneLights.push_back(light.Light);
					}
				}
				////
			
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

				//Handle audio
				{
					auto view = m_Registry.view<TransformComponent, AudioSource3D>();
					for(auto entity : view)
					{
						auto& sound = view.get<AudioSource3D>(entity);
						auto& transform = view.get<TransformComponent>(entity);

						if(sound.m_Loaded)
						{
							if(sound.m_Shoot)
							{
								sound.m_Shoot = false;
								Audio::PlayAudioSource(sound, transform);
							}
							else if(sound.m_Playing)
							{
								Audio::UpdateSound(sound, transform);
							}
						}
						else
						{
							sound.m_Loaded = Audio::Add3DAudioSource(sound);
						}
					}
				}

				//Handles audio listeners
				{
					auto view = m_Registry.view<TransformComponent, AudioListener>();
					for(auto entity : view)
					{
						auto& listen = view.get<AudioListener>(entity);
						auto& transform = view.get<TransformComponent>(entity);

						if(listen.m_ActiveListing)
							Audio::SetListener(transform);
						
						// auto hear = m_Registry.view<AudioSource3D>();
						// for(auto sound : hear)
						// {
						// 		//Call a OnAudioListenEnter type function where we can check distance
						// }
					}
				}
				
			
				Renderer::EndScene();
			}
			
			passes++;
		}while(passes < m_RenderPasses);

		//Only need to call this on one buffer as its always going to bind FBO 0 ie no framebuffer
		if(m_IsEditorScene) m_EditorSceneFramebuffer->Unbind();
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

	GameObject* Scene::CreateEditorCamera()
	{
		auto go = CreateGameObject("Editor Camera");
		auto& c = go->AddComponent<EditorCameraComponent>();
		auto& t = go->GetComponent<TransformComponent>();
		c.EditorCamera.SetViewportSize(1280, 720);
		t.Position = {0,0,0};
		return go;
	}

	void Scene::Destroy()
	{
		m_EditorGameFramebuffer->~Framebuffer();
		m_EditorSceneFramebuffer->~Framebuffer();
		//m_EditorCamera->~GameObject();
		//m_ActiveCamera ->~GameObject();
		//m_SceneLight->~GameObject();
		
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

