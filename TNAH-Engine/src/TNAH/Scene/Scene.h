#pragma once

#include <TNAH/Core/Core.h>
#include "TNAH/Core/UUID.h"
#include "entt.hpp"
#include <vector>

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

		GameObject CreateGameObject();


		UUID GetUUID() const { return m_SceneID; }
		GameObject FindEntityByTag(const std::string& tag);
		GameObject FindEntityByUUID(UUID id);

	private:
		UUID m_SceneID;
		entt::registry m_Registry;

		friend class GameObject;
	};


	

	

}