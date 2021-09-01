#pragma once

#include <TNAH/Core/Core.h>
#include "TNAH/Core/UUID.h"
#include "entt.hpp"
#include <vector>

#include "SceneCamera.h"
#include "Components/Components.h"
#include "TNAH/Core/Timestep.h"
#include "TNAH/Core/Math.h"
#include "TNAH/Core/Ref.h"
#include "TNAH/Physics/PhysicsTimestep.h"

namespace tnah {
	class Light;

	class GameObject;

	class Scene : public RefCounted
	{
		friend class GameObject;
	public:

		struct ActiveScene
		{
			Ref<Scene> Scene;
			
		};
		
		Scene(bool editor = false);
		~Scene();

		static ActiveScene s_ActiveScene;
		static void ClearActiveScene();
		
		static Ref<Scene> CreateEmptyScene();

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

		GameObject& CreateGameObject(const std::string& name);
		GameObject CreateGameObject();
		
		

		GameObject FindEntityByTag(const std::string& tag);
		GameObject FindEntityByUUID(UUID id);

		GameObject FindGameObjectByID(const entt::entity& id);

		void DestroyGameObject(GameObject gameObject);

		GameObject& GetSceneCamera();
		GameObject& GetSceneLight();

	private:
		GameObject CreateEditorCamera();

		void Destroy();
		
		static Ref<Scene> CreateNewEditorScene();

		GameObject& GetEditorCamera();
		Ref<Framebuffer> GetEditorSceneFramebuffer() { return m_EditorSceneFramebuffer; }
		Ref<Framebuffer> GetEditorGameFramebuffer() { return m_EditorGameFramebuffer; }

		entt::registry& GetRegistry() { return m_Registry; }
		std::map<UUID, GameObject>& GetGameObjectsInScene();
		GameObject* GetRefGameObject(const UUID id);
		
		entt::registry m_Registry;
		std::map<UUID, GameObject> m_GameObjectsInScene;
		
		UUID m_ActiveCamera;
		UUID m_SceneLight;

		UUID m_EditorCamera;
		Ref<Framebuffer> m_EditorSceneFramebuffer;
		Ref<Framebuffer> m_EditorGameFramebuffer;
		bool m_IsEditorScene = false;
		uint32_t m_RenderPasses = 0;

		entt::entity m_SceneEntity;
		UUID m_SceneID;
		
		friend class EditorLayer;
		friend class Editor;
		friend class Serializer;
	};


	

	

}