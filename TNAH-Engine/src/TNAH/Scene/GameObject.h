#pragma once
#include <TNAH/Core/Core.h>
#include "Scene.h"
#include "entt.hpp"

namespace tnah {
	class TNAH_API GameObject
	{
	public:

		/**********************************************************************************************//**
		 * @fn	GameObject::GameObject(entt::entity id, Scene* scene);
		 *
		 * @brief	Default constructor that adds the game object to the scene
		 *
		 * @author	Bryce Standley
		 * @date	18/07/2021
		 *
		 * @param 		  	id   	The identifier.
		 * @param [in,out]	scene	If non-null, the scene.
		 **************************************************************************************************/

		GameObject(entt::entity id, Scene* scene);

		/**********************************************************************************************//**
		 * @fn	GameObject::GameObject(const GameObject& other) = default;
		 *
		 * @brief	Defaulted copy constructor
		 *
		 * @author	Bryce Standley
		 * @date	18/07/2021
		 *
		 * @param 	other	The other.
		 **************************************************************************************************/

		GameObject(const GameObject& other) = default;

		/**********************************************************************************************//**
		 * @fn	template<typename T, typename... Args> inline T& GameObject::AddComponent(Args&&... args)
		 *
		 * @brief	Adds component to a game object
		 *
		 * @tparam	T   	Generic type parameter.
		 * @tparam	Args	Type of the arguments.
		 * @param 	args	Variable arguments providing [in,out] The arguments.
		 *
		 * @returns	A reference to the component.
		 **************************************************************************************************/

		template<typename T, typename... Args>
		inline T& AddComponent(Args&&... args)
		{
			std::string name = typeid(T).name();
			name.erase(0, 13);
			if (HasComponent<T>()) 
			{
				TNAH_CORE_ERROR("GameObject already has a {0} component! You can't add it again!", name); 
				return GetComponent<T>(); 
			}
			else
			{
				TNAH_CORE_INFO("Added Component: {0} to GameObject: {1}", name, m_EntityID);
				return m_Scene->m_Regestry.emplace<T>(m_EntityID, std::forward<Args>(args)...);
			}
		}

		/**********************************************************************************************//**
		 * @fn	template<typename T> inline T& GameObject::GetComponent()
		 *
		 * @brief	Gets the component of a game object
		 *
		 * @tparam	T	Generic type parameter.
		 *
		 * @returns	The component.
		 **************************************************************************************************/

		template<typename T>
		inline T& GetComponent()
		{
			std::string name = typeid(T).name();
			name.erase(0, 13);
			if (!HasComponent<T>()) 
			{ 
				TNAH_CORE_ERROR("GameObject doesn't have a {0} component! You need to add one with AddComponent<>(), Default component added!", name);
				return AddComponent<T>();
			}
			else
			{
				TNAH_CORE_INFO("Got {0} Component from GameObject: {1}", name, m_EntityID);
				return m_Scene->m_Regestry.get<T>(m_EntityID);
			}
		}

		/**********************************************************************************************//**
		 * @fn	template<typename T> inline bool GameObject::HasComponent()
		 *
		 * @brief	Query if the game object has a component
		 *
		 * @tparam	T	Generic type parameter.
		 *
		 * @returns	True if component, false if not.
		 **************************************************************************************************/

		template<typename T>
		inline bool HasComponent()
		{
			return m_Scene->m_Regestry.all_of<T>(m_EntityID);
		}

		/**********************************************************************************************//**
		 * @fn	template<typename T> inline void GameObject::RemoveComponent()
		 *
		 * @brief	Removes the component from a game object
		 *
		 * @tparam	T	Generic type parameter.
		 **************************************************************************************************/

		template<typename T>
		inline void RemoveComponent()
		{
			std::string name = typeid(T).name();
			name.erase(0, 13);
			if (!HasComponent<T>())
			{
				TNAH_CORE_ERROR("GameObject doesn't have a {0} component! You can't remove what isn't there!", name);
				return;
			}
			else
			{
				TNAH_CORE_INFO("Removed {0} Component from GameObject: {1}", name, m_EntityID);
				m_Scene->m_Regestry.remove<T>(m_EntityID);
			}
		}

		/**********************************************************************************************//**
		 * @fn	inline void GameObject::Destroy()
		 *
		 * @brief	Destroys the game object
		 *
		 * @author	Bryce Standley
		 * @date	18/07/2021
		 **************************************************************************************************/

		inline void Destroy()
		{
			TNAH_CORE_INFO("Destroyed GameObject: {0} and all its components", m_EntityID);
			m_Scene->m_Regestry.destroy(m_EntityID);
			delete this;
		}

		/**********************************************************************************************//**
		 * @fn	entt::entity GameObject::GetEntityID()
		 *
		 * @brief	Gets entity identifier
		 *
		 * @author	Bryce Standley
		 * @date	18/07/2021
		 *
		 * @returns	The entity identifier.
		 **************************************************************************************************/

		entt::entity GetEntityID() { return m_EntityID; }


	protected:
		entt::entity m_EntityID;
		Scene* m_Scene;
	};
}

