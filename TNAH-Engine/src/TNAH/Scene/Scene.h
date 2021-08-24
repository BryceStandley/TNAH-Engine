#pragma once

#include <TNAH/Core/Core.h>
#include "TNAH/Core/UUID.h"
#include "entt.hpp"
#include <vector>

#include "SceneCamera.h"
#include "Components/Components.h"
#include "TNAH/Core/Timestep.h"
#include "TNAH/Core/Math.h"
#include "TNAH/Physics/PhysicsTimestep.h"

namespace tnah {
	class Light;

	class GameObject;

	class Scene
	{
		friend class GameObject;
	public:
		
		static Scene* CreateSceneFromFile(const std::string& filePath);
		static Scene* CreateEmptyScene();

		/**********************************************************************************************//**
		 * @fn	GameObject Scene::CreateGameObject();
		 *
		 * @brief	Creates game object and adds a default transform component to it
		 *
		 * @author	Bryce Standley
		 * @date	18/07/2021
		 *
		 * @returns	The new game object.
		 **************************************************************************************************/

		void OnUpdate(Timestep deltaTime);
		void OnFixedUpdate(PhysicsTimestep deltaTime);

		glm::mat4 GetTransformRelativeToParent(GameObject gameObject);

		GameObject* CreateGameObject(const std::string& name);
		GameObject CreateGameObject();
		
		

		GameObject FindEntityByTag(const std::string& tag);
		GameObject FindEntityByUUID(UUID id);

		GameObject FindGameObjectByID(const entt::entity& id);

		void DestroyGameObject(GameObject gameObject);

		Ref<GameObject> GetMainCameraGameObject();
		Ref<GameObject> GetSceneLightGameObject();

		Ref<CameraComponent> GetMainCameraComponent();
		Ref<LightComponent> GetSceneLightComponent();

		Ref<TransformComponent> GetMainCameraTransform();
		Ref<TransformComponent> GetSceneLightTransform();

		Ref<SceneCamera> GetMainCamera();
		Ref<Light> GetSceneLight();

	private:
		GameObject* CreateEditorCamera();
		static Scene* CreateEditorSceneFromFile(const std::string& filePath);
		static Scene* CreateNewEditorScene();
		static Scene* CreateSceneFromFile(const std::string& filePath, bool editor);

		Ref<GameObject> GetEditorCameraGameObject();
		Ref<Framebuffer> GetEditorSceneFramebuffer() { return m_EditorSceneFramebuffer; }
		Ref<Framebuffer> GetEditorGameFramebuffer() { return m_EditorGameFramebuffer; }

		entt::registry& GetRegistry() { return m_Registry; }
		std::map<UUID, GameObject>& GetGameObjectsInScene();
		GameObject* GetRefGameObject(const UUID id);
		
		Scene(bool editor = false);
		~Scene();
		entt::registry m_Registry;
		std::map<UUID, GameObject> m_GameObjectsInScene;

		Ref<GameObject> m_ActiveCamera;
		Ref<GameObject> m_SceneLight;

		Ref<GameObject> m_EditorCamera;
		Ref<Framebuffer> m_EditorSceneFramebuffer;
		Ref<Framebuffer> m_EditorGameFramebuffer;
		bool m_IsEditorScene = false;
		uint32_t m_RenderPasses = 0;
		
		friend class EditorLayer;
		friend class Editor;
		friend class Serializer;
	};


	

	

}