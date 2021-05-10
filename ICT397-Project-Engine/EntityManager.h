#pragma once
#include <string>
#include <map>
#include "GameObjects.h"

typedef std::map<int, GameObject*> Objects;
//typedef std::map<std::string, Objects> EntityMap;

class EntityManager
{
private:
	Objects entityMap;

public:
	void RegisterEntity(GameObject* newEntity)
	{
		entityMap.insert(std::make_pair(newEntity->GetId(), newEntity));
	}

	void RemoveEntity(GameObject* entity)
	{
		entityMap.erase(entity->GetId());
	}

	GameObject* GetEntity(int id)
	{
		Objects::const_iterator ent = entityMap.find(id);
		if (ent == entityMap.end())
			return NULL;
		else
			return ent->second;
	}
};

