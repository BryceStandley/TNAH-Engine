#include "GameAssetFactory.h"
#include "Player.h"

GameObject* GameAssetFactory::GetGameObject(GameObjectType t)
{
	switch (t)
	{
		case TypePlayer:
			return new Player();
		case TypeStatic:
			return new Static();
		case TypeEnemy:
			return new Enemy();
		default:
			return nullptr;
	}
}
