#include "GameAssetFactory.h"


GameObject GameAssetFactory::GetGameObject(std::string objectType)
{
	if (objectType == "")
	{
		//NULL operator will be implemented
		//
	}
	
	if (objectType == "Terrain")
	{
		// = new Terrain()
	}
	else if (objectType == "StaticObject")
	{
		// = new StaticObject()
	}
	else if (objectType == "Character")
	{
		// = new Character()
	}
	else if (objectType == "PlayerBoundAsset")
	{
		// = new PlayerBoundAsset()
	}
	GameObject g;
	return g;
}
