#include <tnahpch.h>
#include "Scene.h"
#include "GameObject.h"
#include "Components/Components.h"

namespace tnah{

	Scene::Scene()
	{

	}

	Scene::~Scene()
	{
	}

	void Scene::OnUpdate(Timestep deltaTime)
	{
		/*
		auto view = m_Registry.view<TransformComponent>();
		for (auto obj : view)
		{
			TransformComponent& transformComponent = m_Registry.get<TransformComponent>(obj);
			GameObject go = GameObject(obj, this);
			glm::mat4 transform = transformComponent.GetTransform();//GetTransformRelativeToParent(go);
			glm::vec3 translation;
			glm::vec3 rotation;
			glm::vec3 scale;
			tnah::math::DecomposeTransform(transform, translation, rotation, scale);

			glm::quat rotationQuat = glm::quat(rotation);
			transformComponent.Up = glm::normalize(glm::rotate(rotationQuat, glm::vec3(0.0f, 1.0f, 0.0f)));
			transformComponent.Right = glm::normalize(glm::rotate(rotationQuat, glm::vec3(1.0f, 0.0f, 0.0f)));
			transformComponent.Forward = glm::normalize(glm::rotate(rotationQuat, glm::vec3(0.0f, 0.0f, -1.0f)));
		}*/
	}

	glm::mat4 Scene::GetTransformRelativeToParent(GameObject gameObject)
	{
		glm::mat4 transform(1.0f);

		GameObject parent = FindEntityByUUID(gameObject.GetParentUUID());
		if (parent)
			transform = GetTransformRelativeToParent(parent);

		return transform * gameObject.Transform().GetTransform();
	}

	GameObject Scene::CreateGameObject(const std::string& name)
	{
		GameObject go = { m_Registry.create(), this };
		auto idComponent = go.AddComponent<IDComponent>();
		idComponent.ID = {};
		go.AddComponent<TransformComponent>();
		if (!name.empty())
		{
			go.AddComponent<TagComponent>(name);
		}

		go.AddComponent<RelationshipComponent>();

		
		m_GameObjectsInScene[idComponent.ID] = go;
		return go;
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

	void Scene::DestryGameObject(GameObject gameObject)
	{
		m_Registry.destroy(gameObject.GetID());
	}







}

