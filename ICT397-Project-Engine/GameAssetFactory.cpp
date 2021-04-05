#include "GameAssetFactory.h"

GameObject* GameAssetFactory::GetGameObject(std::string type, std::string modelName, std::string shaderV, std::string shaderF, float scale, glm::vec3 position, bool rotate)
{
	if (type == "player" && !playerMade)
	{
		GameObject* obj = new Player();
		obj->SetPos(glm::vec3(position));
		playerMade = true;
		return obj;
	}
	else if (type == "static")
	{
		Shader ourShader(shaderV.c_str(), shaderF.c_str());
		Model ourModel(modelName, renderer);
		GameObject* obj = new Static();
		obj->model = ourModel;
		obj->shader = ourShader;
		obj->SetPos(glm::vec3(position));
		obj->SetScale(scale);
		obj->rotate = rotate;
		return obj;
	}
	else if (type == "enemy")
	{
		Shader ourShader(shaderV.c_str(), shaderF.c_str());
		Model ourModel(modelName, renderer);
		GameObject* obj = new Enemy();
		obj->model = ourModel;
		obj->shader = ourShader;
		obj->SetPos(glm::vec3(position));
		obj->SetScale(scale);
		obj->rotate = rotate;
		return obj;
	}
	else if (type == "token")
	{
		Shader ourShader(shaderV.c_str(), shaderF.c_str());
		Model ourModel(modelName, renderer);
		GameObject* obj = new Token();
		obj->model = ourModel;
		obj->shader = ourShader;
		obj->SetPos(glm::vec3(position));
		obj->SetScale(scale);
		obj->rotate = rotate;
		return obj;
	}
	else
		return nullptr;
}
