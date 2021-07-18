#pragma once

#include <TNAH/Core/Core.h>
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

		/**********************************************************************************************//**
		 * @fn	template<typename T> std::vector<entt::entity> Scene::FindEntitiesWithType();
		 *
		 * @brief	Searches for entities with a type
		 *
		 * @tparam	T	Generic type parameter.
		 *
		 * @returns	The found entities with type.
		 **************************************************************************************************/
		template<typename T>
		std::vector<entt::entity> FindEntitiesWithType();

	protected:
		entt::registry m_Regestry;
	};


	

	

}