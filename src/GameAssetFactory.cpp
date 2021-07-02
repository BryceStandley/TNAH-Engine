#include "GameAssetFactory.h"

GameObject* GameAssetFactory::GetGameObject(std::string type, std::string script, float scale, glm::vec3 position)
{
    if(Debugger::GetInstance()->debugToConsole) std::cout << "script -> " << script << std::endl;
	if (type == "player" && !playerMade)
	{
        if(Debugger::GetInstance()->debugToConsole) std::cout << "Player done" << std::endl;
        GameObject* obj = new Player(position, glm::vec3(0, 0, 0), scale, renderer, script);
        BoundingBox box = BoundingBox();
        obj->SetCollisionTag(BoundingBox::CollisionTag::PLAYER);

		//Physics setup
		rp3d::CollisionShape* col = PhysicsManager::GetInstance()->CreateCapsuleCollider(4,8);
		rp3d::Transform transform = rp3d::Transform::identity();
		rp3d::RigidBody* rb = PhysicsManager::GetInstance()->CreateRigidBody(rp3d::Transform::identity());
		float posX = ((float)position.x * 10) / 2;
		float posY = (position.y * 10) / 2;
		float posZ = ((float)position.z * 10) / 2;
		transform.setPosition(rp3d::Vector3(posX, posY, posZ));
		rb->setTransform(transform);
		rb->setAngularLockAxisFactor(rp3d::Vector3(0, 1, 0));
		obj->collider = rb->addCollider(col, rp3d::Transform::identity());
		rb->updateMassPropertiesFromColliders();
		rb->setMass(10.0f);
		rb->setIsAllowedToSleep(false);
		rb->setUserData(static_cast<void*>(obj->GetTag()));
		obj->rigidBody = rb;


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

		//rp3d::CapsuleShape* col = PhysicsManager::GetInstance()->CreateCapsuleCollider(1.0f, 2.0f);
		rp3d::CollisionShape* col = PhysicsManager::GetInstance()->CreateBoxCollider(25, 25, 25);
		rp3d::Transform transform = rp3d::Transform::identity();
		rp3d::RigidBody* rb = PhysicsManager::GetInstance()->CreateRigidBody(rp3d::Transform::identity());
		float posX = ((float)position.x * 10) / 2;
		float posY = (position.y * 10) / 2;
		float posZ = ((float)position.z * 10) / 2;
		transform.setPosition(rp3d::Vector3(posX, posY, posZ));
		rb->setTransform(transform);
		rb->setUserData(static_cast<void*>(obj->GetTag()));
		rb->setType(rp3d::BodyType::STATIC);
		rb->enableGravity(false);
		obj->collider = rb->addCollider(col, rp3d::Transform::identity());
		rb->updateMassPropertiesFromColliders();
		obj->rigidBody = rb;



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

		rp3d::CollisionShape* col = PhysicsManager::GetInstance()->CreateCapsuleCollider(4,8);
		rp3d::Transform transform = rp3d::Transform::identity();
		rp3d::RigidBody* rb = PhysicsManager::GetInstance()->CreateRigidBody(rp3d::Transform::identity());
		float posX = ((float)position.x * 10) / 2;
		float posY = (position.y * 10) / 2;
		float posZ = ((float)position.z * 10) / 2;
		transform.setPosition(rp3d::Vector3(posX, posY, posZ));
		rb->setTransform(transform);
		rb->setUserData(static_cast<void*>(obj->GetTag()));
		obj->collider = rb->addCollider(col, rp3d::Transform::identity());
		rb->updateMassPropertiesFromColliders();
		rb->setMass(1.0f);
		obj->rigidBody = rb;


		return obj;
	}
	else if (type == "token")
	{
        if(Debugger::GetInstance()->debugToConsole) std::cout << "token done" << std::endl;
		GameObject* obj = new Token(position, glm::vec3(0, 0, 0), scale, renderer, script);
		obj->SetCollisionTag(BoundingBox::CollisionTag::TOKEN);
		obj->SetName("Token");
		obj->SetType("token");


		rp3d::CollisionShape* col = PhysicsManager::GetInstance()->CreateSphereCollider(3);
		rp3d::Transform transform = rp3d::Transform::identity();
		rp3d::RigidBody* rb = PhysicsManager::GetInstance()->CreateRigidBody(rp3d::Transform::identity());
		float posX = ((float)position.x * 10) / 2;
		float posY = (position.y * 10) / 2;
		float posZ = ((float)position.z * 10) / 2;
		transform.setPosition(rp3d::Vector3(posX, posY, posZ));
		rb->setTransform(transform);
		rb->setUserData(static_cast<void*>(obj->GetTag()));
		obj->collider = rb->addCollider(col, rp3d::Transform::identity());
		rb->updateMassPropertiesFromColliders();
		obj->rigidBody = rb;


		return obj;
	}
	else if(type == "water")
    {
        if(Debugger::GetInstance()->debugToConsole) std::cout << "water done" << std::endl;
        GameObject* obj = new Water(position, glm::vec3(0, 0, 0), scale, renderer, script);
        obj->SetCollisionTag(BoundingBox::CollisionTag::WATER);
        obj->SetName("Water");
		obj->SetType("water");

	    rp3d::CollisionShape* col = PhysicsManager::GetInstance()->CreateBoxCollider(50, 50, 50);
	    rp3d::Transform transform = rp3d::Transform::identity();
	    rp3d::RigidBody* rb = PhysicsManager::GetInstance()->CreateRigidBody(rp3d::Transform::identity());
	    float posX = ((float)position.x * 10) / 2;
	    float posY = (position.y * 10) / 2;
	    float posZ = ((float)position.z * 10) / 2;
	    transform.setPosition(rp3d::Vector3(posX, posY, posZ));
	    rb->setTransform(transform);
	    rb->setUserData(static_cast<void*>(obj->GetTag()));
	    rb->setType(rp3d::BodyType::STATIC);
	    rb->enableGravity(false);
	    obj->collider = rb->addCollider(col, rp3d::Transform::identity());
	    rb->updateMassPropertiesFromColliders();
	    obj->rigidBody = rb;
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
