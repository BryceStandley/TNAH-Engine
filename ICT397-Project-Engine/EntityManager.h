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
	std::vector<int> pos;

public:
	void RegisterEntity(GameObject* newEntity)
	{
		entityMap.insert(std::make_pair(newEntity->GetId(), newEntity));
		pos.push_back(newEntity->GetId());
		//std::cout << newEntity->GetId() << std::endl;
	}

	void RemoveEntity(GameObject* entity)
	{
		int removeId = entity->GetId();
		entityMap.erase(entity->GetId());
		std::vector<int>::iterator r;
		r = std::remove(pos.begin(), pos.end(), removeId);
		pos.erase(r);
	}

	void ClearEntitys()
	{
		entityMap.clear();
		pos.clear();
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
		return pos.size();
	}

	int NumberedPos(int i)
	{
		return pos[i];
	}
};

