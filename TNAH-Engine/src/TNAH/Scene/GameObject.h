#pragma once
#include <TNAH/Core/Core.h>
#include "Scene.h"
#include "entt.hpp"

namespace tnah {
	class TNAH_API GameObject
	{
	public:

		/**********************************************************************************************//**
		 * @fn	GameObject::GameObject()
		 *
		 * @brief	Default constructor, Not really meant to be used only over written when a scene makes a 
		 * 			new GameObject
		 *
		 * @author	Bryce Standley
		 * @date	21/07/2021
		 **************************************************************************************************/

		GameObject() { m_EntityID = (entt::entity)0; m_Scene = nullptr; }

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
			if (HasComponent<T>()) 
			{
				TNAH_CORE_ASSERT(HasComponent<T>(), "GameObject already has that component!");
				return GetComponent<T>(); 
			}
			else
			{
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
			if (!HasComponent<T>()) 
			{ 
				TNAH_CORE_ASSERT(!HasComponent<T>(), "GameObject doesn't have that component! You need to add one with AddComponent<>(), Default component added!");
				return AddComponent<T>();
			}
			else
			{
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

			if (!HasComponent<T>())
			{
				TNAH_CORE_ASSERT(!HasComponent<T>, "GameObject doesn't have that component! You can't remove what isn't there!");
				return;
			}
			else
			{
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

