#include "EntityManager.h"

void EntityManager::RegisterEntity(GameObject* newEntity)
{
	entityMap.insert(std::make_pair(newEntity->GetId(), newEntity));
	pos.push_back(newEntity->GetId());
	//std::cout << newEntity->GetId() << std::endl;
}

void EntityManager::RemoveEntity(GameObject* entity)
{
	int removeId = entity->GetId();
	entityMap.erase(entity->GetId());
	std::vector<int>::iterator r;
	r = std::remove(pos.begin(), pos.end(), removeId);
	pos.erase(r);
}

void EntityManager::ClearEntitys()
{
	entityMap.clear();
	pos.clear();
}

GameObject* EntityManager::GetEntity(int id)
{
	Objects::const_iterator ent = entityMap.find(id);
	if (ent == entityMap.end())
		return NULL;
	else
		return ent->second;
}

int EntityManager::Size()
{
	return pos.size();
}

int EntityManager::NumberedPos(int i)
{
	return pos[i];
}