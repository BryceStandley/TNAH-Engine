#include "GameAssetFactory.h"

GameObject* GameAssetFactory::GetGameObject(std::string type, std::string script, float scale, glm::vec3 position)
{
    if(Debugger::GetInstance()->debugToConsole) std::cout << "script -> " << script << std::endl;
	if (type == "player" && !playerMade)
	{
        if(Debugger::GetInstance()->debugToConsole) std::cout << "Player done" << std::endl;
        GameObject* obj = new Player(position, glm::vec3(0, 0, 0), scale, renderer, script);
        BoundingBox box = BoundingBox();
        //box = box.GenerateBoundingBox(obj->GetModel().GetMesh(0));
        //obj->SetBoundingBox(box);
        //obj->SetCollisionTag(BoundingBox::CollisionTag::PLAYER);
        playerMade = true;
        return obj;

	}
	else if (type == "static")
	{
        if(Debugger::GetInstance()->debugToConsole) std::cout << "static done" << std::endl;
		GameObject* obj = new Static(position, glm::vec3(0, 0, 0), scale, renderer, script);
        BoundingBox box = BoundingBox();
        box = box.GenerateBoundingBox(obj->GetModel().GetMesh(0));
        obj->SetBoundingBox(box);
        obj->SetCollisionTag(BoundingBox::CollisionTag::STATIC_OBJECT);
		obj->SetName("StaticObject");
		obj->SetType("static");
		return obj;
	}
	else if (type == "enemy")
	{
        if(Debugger::GetInstance()->debugToConsole) std::cout << "Enemy done" << std::endl;
		GameObject* obj = new Enemy(position, glm::vec3(0, 0, 0), renderer, script);
		obj->SetCollisionTag(BoundingBox::CollisionTag::ENEMY);
		obj->SetName("Enemy");
		obj->SetType("enemy");
		obj->SetId(id);
		id++;
		//if (first)
			//first = false;
		return obj;
	}
	else if (type == "token")
	{
        if(Debugger::GetInstance()->debugToConsole) std::cout << "token done" << std::endl;
		GameObject* obj = new Token(position, glm::vec3(0, 0, 0), scale, renderer, script);
		obj->SetCollisionTag(BoundingBox::CollisionTag::TOKEN);
		obj->SetName("Token");
		obj->SetType("token");
		return obj;
	}
	else if(type == "water")
    {
        if(Debugger::GetInstance()->debugToConsole) std::cout << "water done" << std::endl;
        GameObject* obj = new Water(position, glm::vec3(0, 0, 0), scale, renderer, script);
        obj->SetCollisionTag(BoundingBox::CollisionTag::WATER);
        obj->SetName("Water");
		obj->SetType("water");
        return obj;
    }
	else
		return nullptr;
}

GameObject* GameAssetFactory::GetGameObjectSave(std::string type, std::string script, float scale, glm::vec3 position, float health, float ammo, std::string state, int savedPoints, int savedTokens, int savedKills)
{
    if(Debugger::GetInstance()->debugToConsole) std::cout << "script -> " << script << std::endl;
	if (type == "player" && !playerMade)
	{
        if(Debugger::GetInstance()->debugToConsole) std::cout << "Player done" << std::endl;
        GameObject* obj = new Player(position, glm::vec3(0, 0, 0), scale, renderer, script, health, state, savedPoints, savedTokens, savedKills);
        BoundingBox box = BoundingBox();
        //box = box.GenerateBoundingBox(obj->GetModel().GetMesh(0));
        //obj->SetBoundingBox(box);
        //obj->SetCollisionTag(BoundingBox::CollisionTag::PLAYER);
        playerMade = true;
        return obj;

	}
	else if (type == "static")
	{
        if(Debugger::GetInstance()->debugToConsole) std::cout << "static done" << std::endl;
		GameObject* obj = new Static(position, glm::vec3(0, 0, 0), scale, renderer, script);
        BoundingBox box = BoundingBox();
        box = box.GenerateBoundingBox(obj->GetModel().GetMesh(0));
        obj->SetBoundingBox(box);
        obj->SetCollisionTag(BoundingBox::CollisionTag::STATIC_OBJECT);
		obj->SetName("StaticObject");
		obj->SetType("static");
		return obj;
	}
	else if (type == "enemy")
	{
        if(Debugger::GetInstance()->debugToConsole) std::cout << "Enemy done" << std::endl;
		GameObject* obj = new Enemy(position, glm::vec3(0, 0, 0), scale, renderer, script, health, ammo, state);
		obj->SetCollisionTag(BoundingBox::CollisionTag::ENEMY);
		obj->SetName("Enemy");
		obj->SetType("enemy");
		obj->SetId(id);
		id++;
		if (first)
			first = false;
		return obj;
	}
	else if (type == "token")
	{
        if(Debugger::GetInstance()->debugToConsole) std::cout << "token done" << std::endl;
		GameObject* obj = new Token(position, glm::vec3(0, 0, 0), scale, renderer, script);
		obj->SetCollisionTag(BoundingBox::CollisionTag::TOKEN);
		obj->SetName("Token");
		obj->SetType("token");
		return obj;
	}
	else if(type == "water")
    {
        if(Debugger::GetInstance()->debugToConsole) std::cout << "water done" << std::endl;
        GameObject* obj = new Water(position, glm::vec3(0, 0, 0), scale, renderer, script);
        obj->SetCollisionTag(BoundingBox::CollisionTag::WATER);
        obj->SetName("Water");
		obj->SetType("water");
        return obj;
    }
	else
		return nullptr;
}

void GameAssetFactory::ResetFactory()
{
	playerMade = false; 
	first = true; 
	id = 0;
}
