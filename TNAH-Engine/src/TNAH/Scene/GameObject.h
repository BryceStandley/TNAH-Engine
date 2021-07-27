#pragma once
#include <TNAH/Core/Core.h>
#include "Components/Components.h"
#include "Scene.h"
#include "entt.hpp"

namespace tnah {
	class TNAH_API GameObject
	{
	public:

		GameObject() = default;
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

		GameObject(entt::entity id, Scene* scene)
			: m_EntityID(id), m_Scene(scene)
		{}

		~GameObject() {}

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
				return m_Scene->m_Registry.emplace<T>(m_EntityID, std::forward<Args>(args)...);
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
				return m_Scene->m_Registry.get<T>(m_EntityID);
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
			return m_Scene->m_Registry.all_of<T>(m_EntityID);
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
				m_Scene->m_Registry.remove<T>(m_EntityID);
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
			m_Scene->m_Registry.destroy(m_EntityID);
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

		entt::entity GetID() { return m_EntityID; }

		TransformComponent& Transform() { return m_Scene->m_Registry.get<TransformComponent>(m_EntityID); }
		const glm::mat4& Transform() const { return m_Scene->m_Registry.get<TransformComponent>(m_EntityID).GetTransform(); }


		operator uint32_t () const { return (uint32_t)m_EntityID; }
		operator entt::entity() const { return m_EntityID; }
		operator bool() const { return (m_EntityID != entt::null) && m_Scene; }

		bool operator==(const GameObject& other) const
		{
			return m_EntityID == other.m_EntityID && m_Scene == other.m_Scene;
		}

		bool operator!=(const GameObject& other) const
		{
			return !(*this == other);
		}

		void SetParentUUID(UUID parent) { GetComponent<RelationshipComponent>().ParentHandle = parent; }
		UUID GetParentUUID() { return GetComponent<RelationshipComponent>().ParentHandle; }
		std::vector<UUID>& Children() { return GetComponent<RelationshipComponent>().Children; }

		bool HasParent() { return m_Scene->FindEntityByUUID(GetParentUUID()); }

		bool IsAncesterOf(GameObject entity)
		{
			const auto& children = Children();

			if (children.size() == 0)
				return false;

			for (UUID child : children)
			{
				if (child == entity.GetUUID())
					return true;
			}

			for (UUID child : children)
			{
				if (m_Scene->FindEntityByUUID(child).IsAncesterOf(entity))
					return true;
			}

			return false;
		}

		bool IsDescendantOf(GameObject entity)
		{
			return entity.IsAncesterOf(*this);
		}

		UUID GetUUID() { return GetComponent<IDComponent>().ID; }
	private:
		GameObject(const std::string& name);
	private:
		entt::entity m_EntityID{ entt::null };
		Scene* m_Scene = nullptr;

		friend class Scene;
		friend class SceneSerializer;
		friend class ScriptEngine;
	};
}

