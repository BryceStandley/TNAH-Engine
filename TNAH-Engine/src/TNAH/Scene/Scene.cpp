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
		//Update all transform components and their forward, right and up vectors
		{
			auto view = m_Registry.view<TransformComponent>();
			for (auto obj : view)
			{
				auto& transform = view.get<TransformComponent>(obj);

				glm::vec3 forward = glm::vec3(0.0f);
				glm::vec3 right = glm::vec3(0.0f);
				glm::vec3 up = glm::vec3(0.0f);
				forward.x = cos(glm::radians(transform.Rotation.x)) * cos(glm::radians(transform.Rotation.y));
				forward.y = sin(glm::radians(transform.Rotation.y));
				forward.z = sin(glm::radians(transform.Rotation.x)) * cos(glm::radians(transform.Rotation.y));
				transform.Forward = glm::normalize(forward);
				transform.Right = glm::normalize(glm::cross(forward, glm::vec3(0, 1, 0)));
				transform.Up = glm::normalize(glm::cross(right, forward));
			}
		}

		//after the transform is updated, update the camera matrix etc
		{
			auto view = m_Registry.view<TransformComponent, CameraComponent>();
			for(auto entity : view)
			{ 
				auto& camera = view.get<CameraComponent>(entity);
				auto& transform = view.get<TransformComponent>(entity);
				camera.Camera.OnUpdate(transform);
			}
		}
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
		auto& idComponent = go.AddComponent<IDComponent>();
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

