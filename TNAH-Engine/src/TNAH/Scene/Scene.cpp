#include <tnahpch.h>
#include "Scene.h"
#include "GameObject.h"
#include "Components/Components.h"

namespace tnah{

	Scene::Scene()
	{
		//Creating component dependencies on scene creation
		// Cameras always need a transform
		m_Regestry.on_construct<tnah::Camera>().connect<&entt::registry::emplace_or_replace<tnah::Transform>>();

	}

	Scene::~Scene()
	{
	}

	GameObject Scene::CreateGameObject()
	{
		GameObject go = { m_Regestry.create(), this };
		go.AddComponent<Transform>();
		return go;
	}

	template<typename T>
	std::vector<entt::entity> Scene::FindEntitiesWithType()
	{
		std::vector<entt::entity> entities;
		auto view = this->m_Regestry.view<T>();

		for (entt::entity e : view)
		{
			entities.emplace_back(e);
		}
		return entities;

	}





}

