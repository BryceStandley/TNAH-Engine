#pragma once
#include <string>
#include <map>
#include "GameObject.h"

typedef std::map<int, GameObject*> Objects;
//typedef std::map<std::string, Objects> EntityMap;

	/**
	 * @class EntityManager
	 * @brief Managers the entities for messages, storing them into a map with their ID and GameObject Pointers
	 *
	 * @author Christopher Logan
	 * @version 01
	 * @date 10/05/2021
	 *
	 **/

class TNAH_API EntityManager
{
private:
	///Int, GameObject* map for holding the gameobjects
	Objects entityMap;
	///Vector that holds the positions on the current map
	std::vector<int> pos;

public:

	
		/**
		* @brief Registers a new game object to the entity map
		* @param newEntity - Add that new gameobject to the entity map
		*/
	void RegisterEntity(GameObject* newEntity);

		/**
		* @brief Removes the given game object from the map
		* @param entity - removes that given gameobject from the map
		*/
	void RemoveEntity(GameObject* entity);

		/**
		* @brief Clears the entity map and pos vector
		*/
	void ClearEntitys();

		/**
		* @brief Returns the game object from the ID location
		* @param id - The id which is being searched for
		* @return gameobject if one is found, otherwise null
		*/
	GameObject* GetEntity(int id);

		/**
		* @brief The size of the map/vector
		* @returns map size
		*/
	int Size();

		/**
		* @brief Gets the value in the map point i
		* @param i - The point being checked
		* @return map key at position i
		*/
	int NumberedPos(int i);
};

