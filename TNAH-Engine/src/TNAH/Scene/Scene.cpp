#include <tnahpch.h>
#include "Scene.h"
#include "GameObject.h"
#include "Components.h"
namespace tnah{

	Scene::Scene()
	{
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

