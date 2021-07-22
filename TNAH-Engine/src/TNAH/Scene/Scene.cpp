#include <tnahpch.h>
#include "Scene.h"
#include "GameObject.h"
#include "Components/Components.h"

namespace tnah{

	Scene::Scene()
		:m_SceneID(0)
	{

	}

	Scene::~Scene()
	{
	}

	GameObject Scene::CreateGameObject()
	{
		GameObject go = { m_Registry.create(), this };
		go.AddComponent<IDComponent>();
		go.AddComponent<RelationshipComponent>();
		go.AddComponent<TransformComponent>();
		
		
		return go;
	}

	GameObject Scene::FindEntityByTag(const std::string& tag)
	{
		// TODO: If this becomes used often, consider indexing by tag
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







}

