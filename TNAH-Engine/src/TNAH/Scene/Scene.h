#pragma once

#include <TNAH/Core/Core.h>
#include "TNAH/Core/UUID.h"
#include "entt.hpp"
#include <vector>
#include "TNAH/Core/Timestep.h"
#include "TNAH/Core/Math.h"
#include "TNAH/Physics/PhysicsTimestep.h"

namespace tnah {

	class GameObject;

	class TNAH_API Scene
	{
		friend class GameObject;
	public:
		Scene();
		~Scene();

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

		GameObject CreateGameObject(const std::string& name);


		GameObject FindEntityByTag(const std::string& tag);
		GameObject FindEntityByUUID(UUID id);

		/**
		 *
		 */
		GameObject FindGameObjectByID(const entt::entity& id);

		void DestryGameObject(GameObject gameObject);

	private:
		entt::registry m_Registry;
		std::unordered_map<UUID, GameObject> m_GameObjectsInScene;

		friend class GameObject;
	};


	

	

}