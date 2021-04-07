#include "GameAssetFactory.h"

GameObject* GameAssetFactory::GetGameObject(std::string type, std::string modelName, std::string shaderV, std::string shaderF, float scale, glm::vec3 position, float speed)
{
	if (type == "player" && !playerMade)
	{
        Shader ourShader(shaderV.c_str(), shaderF.c_str());
        Model ourModel(modelName, renderer);
        GameObject* obj = new Player();
        obj->SetModel(ourModel);
        obj->SetShader(ourShader);
        obj->SetPos(glm::vec3(position));
        obj->SetScale(scale);
        obj->SetRotate(false);
        BoundingBox box = BoundingBox();
        box = box.GenerateBoundingBox(&ourModel.meshes[0]);
        obj->SetBoundingBox(box);
        obj->SetCollisionTag(BoundingBox::CollisionTag::PLAYER);
        obj->SetName("Player");
        playerMade = true;
        return obj;

	}
	else if (type == "static")
	{
		Shader ourShader(shaderV.c_str(), shaderF.c_str());
		Model ourModel(modelName, renderer);
		GameObject* obj = new Static();
		obj->SetModel(ourModel);
		obj->SetShader(ourShader);
		obj->SetPos(glm::vec3(position));
		obj->SetScale(scale);
		obj->SetRotate(false);
        BoundingBox box = BoundingBox();
        box = box.GenerateBoundingBox(&ourModel.meshes[0]);
        obj->SetBoundingBox(box);
        obj->SetCollisionTag(BoundingBox::CollisionTag::STATIC_OBJECT);
		obj->SetName("StaticObject");
		return obj;
	}
	else if (type == "enemy")
	{
		Shader ourShader(shaderV.c_str(), shaderF.c_str());
		Model ourModel(modelName, renderer);
		GameObject* obj = new Enemy();
		obj->SetModel(ourModel);
		obj->SetShader(ourShader);
		obj->SetPos(glm::vec3(position));
		obj->SetScale(scale);
		obj->SetRotate(false);
		obj->SetCollisionTag(BoundingBox::CollisionTag::ENEMY);
		obj->SetName("Enemy");
		return obj;
	}
	else if (type == "token")
	{
		Shader ourShader(shaderV.c_str(), shaderF.c_str());
		Model ourModel(modelName, renderer);
		GameObject* obj = new Token();
		obj->SetModel(ourModel);
		obj->SetShader(ourShader);
		obj->SetPos(glm::vec3(position));
		obj->SetScale(scale);
		obj->SetRotate(true);
		obj->SetSpeed(speed);
		obj->SetCollisionTag(BoundingBox::CollisionTag::TOKEN);
		obj->SetName("Token");
		return obj;
	}
	else
		return nullptr;
}
