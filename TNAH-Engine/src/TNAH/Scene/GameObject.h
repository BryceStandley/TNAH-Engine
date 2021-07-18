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
		 * @fn	template<typename T, typename... Args> T& GameObject::AddComponent(Args&&... args)
		 *
		 * @brief	Adds component to a game object
		 *
		 * @tparam	T   	Generic type parameter.
		 * @tparam	Args	Type of the arguments.
		 * @param 	args	Variable arguments providing [in,out] The arguments.
		 *
		 * @returns	A reference to a T.
		 **************************************************************************************************/

		template<typename T, typename... Args>
		inline T& AddComponent(Args&&... args)
		{
			if (HasComponent<T>()) 
			{
				TNAH_CORE_ERROR("GameObject already has that component! You can't add it again!"); 
				return GetComponent<T>(); 
			}
			else
			{
				TNAH_CORE_INFO("Added Component to GameObject: {0}", m_EntityID);
				return m_Scene->m_Regestry.emplace<T>(m_EntityID, std::forward<Args>(args)...);
			}
		}

		/**********************************************************************************************//**
		 * @fn	template<typename T> T& GameObject::GetComponent()
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
			if (!HasComponent<T>()) 
			{ 
				TNAH_CORE_ERROR("GameObject does not have this component! You need to add one with GetComponent<>(), One has been added with default values!");
				return AddComponent<T>();
			}
			else
			{
				TNAH_CORE_INFO("Got Component from GameObject: {0}", m_EntityID);
				return m_Scene->m_Regestry.get<T>(m_EntityID);
			}
		}

		/**********************************************************************************************//**
		 * @fn	template<typename T> bool GameObject::HasComponent()
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
		 * @fn	template<typename T> void GameObject::RemoveComponent()
		 *
		 * @brief	Removes the component from a game object
		 *
		 * @tparam	T	Generic type parameter.
		 **************************************************************************************************/

		template<typename T>
		inline void RemoveComponent()
		{
			if (!HasComponent<T>())
			{
				TNAH_CORE_ERROR("GameObject doesnt have a component of that type! You can't remove what isn't there!");
				return;
			}
			else
			{
				TNAH_CORE_INFO("Removed Component from GameObject: {0}",  m_EntityID);
				m_Scene->m_Regestry.remove<T>(m_EntityID);
			}
		}

		/**********************************************************************************************//**
		 * @fn	void GameObject::Destroy();
		 *
		 * @brief	Destroys the game object
		 *
		 * @author	Bryce Standley
		 * @date	18/07/2021
		 **************************************************************************************************/

		inline void Destroy()
		{
			TNAH_CORE_INFO("Destroyed GameObject: {0}", m_EntityID);
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

