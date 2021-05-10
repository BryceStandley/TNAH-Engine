#pragma once
#include <string>
#include <map>
#include "GameObject.h"

typedef std::map<int, GameObject*> Objects;
//typedef std::map<std::string, Objects> EntityMap;

class EntityManager
{
private:
	Objects entityMap;
	int max = -1;

public:
	void RegisterEntity(GameObject* newEntity)
	{
		if (newEntity->GetId() > max)
			max = newEntity->GetId();
		std::cout << "Registered enemy -> " << newEntity->GetId() << std::endl;
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

	int Size()
	{
		return max;
	}
};

