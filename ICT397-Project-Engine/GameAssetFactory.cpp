#include "GameAssetFactory.h"
#include "Player.h"

GameObject* GameAssetFactory::GetGameObject(GameObjectType t, std::string fileName, glm::vec3 position, float scale, glm::vec3 fixRotation, glm::vec3 rotation)
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
