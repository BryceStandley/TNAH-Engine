//
// Created by Bryce standley on 22/6/21.
//

#include "PhysicsManager.h"

PhysicsManager* PhysicsManager::instance = nullptr;

PhysicsManager* PhysicsManager::GetInstance()
{
	if(instance == nullptr)
	{
		instance = new PhysicsManager();
	}

	return instance;
}

PhysicsManager::PhysicsManager()
{
	logger = physicsCommon.createDefaultLogger();
	uint logLevel = static_cast<uint>(static_cast<uint>(rp3d::Logger::Level::Warning) | static_cast<uint>(rp3d::Logger::Level::Error) | static_cast<uint>(rp3d::Logger::Level::Information));
	logger->addFileDestination("./res/logs/rp3d_log.html", logLevel, rp3d::DefaultLogger::Format::HTML);
	physicsCommon.setLogger(logger);

	rp3d::PhysicsWorld::WorldSettings settings;
	settings.worldName = "TNAH-Engine";

	// create the physics world
	physicsWorld = physicsCommon.createPhysicsWorld(settings);
	debugShader = new Shader("./res/shader/physicsVert.glsl", "./res/shader/physicsFrag.glsl", nullptr);
	LinesVAO = 0; LinesVBO = 0;
	triVBO = 0; triVAO = 0;


	eventListener = new PhysicsEvents();

	physicsWorld->setEventListener(eventListener);
}

void PhysicsManager::Update(float deltaTime)
{
	physicsWorld->getDebugRenderer().setIsDebugItemDisplayed(rp3d::DebugRenderer::DebugItem::COLLISION_SHAPE, true);
	physicsWorld->getDebugRenderer().setIsDebugItemDisplayed(rp3d::DebugRenderer::DebugItem::COLLIDER_AABB, true);

	physicsWorld->update(deltaTime);

}

void PhysicsManager::CreateTerrainCollider(Terrain *gameTerrain)
{
	int nbRows = gameTerrain->getSize();
	int nbColumns = nbRows;
	float minHeight = gameTerrain->GetMinHeight().y;
	float maxHeight = gameTerrain->GetMaxHeight().y;

	std::vector<float> tempHeightValues;
	for(int x = 0; x < nbRows; x++)
	{
		for(int z = 0; z < nbColumns; z++)
		{
			tempHeightValues.emplace_back(gameTerrain->GetVertexHeight(x, z));
		}
	}
	int size = nbRows * nbColumns;
	float heightValues[size];

	for(int i = 0; i < size; i++)
	{
		heightValues[i] = tempHeightValues[i];
	}

	glm::vec3 s = gameTerrain->GetScales();
	rp3d::HeightFieldShape* col = physicsCommon.createHeightFieldShape(nbColumns, nbRows, minHeight, maxHeight, heightValues, rp3d::HeightFieldShape::HeightDataType::HEIGHT_FLOAT_TYPE);
	rp3d::Vector3 scales(gameTerrain->GetScales().x, gameTerrain->GetScales().y, gameTerrain->GetScales().z);
	col->setScale(scales);



	rp3d::Transform transform = rp3d::Transform::identity();
	rp3d::RigidBody* rb = physicsWorld->createRigidBody(transform);
	gameTerrain->terrainCollider = rb->addCollider(col, rp3d::Transform::identity());
	gameTerrain->terrainRigidbody = rb;
	gameTerrain->terrainRigidbody->setType(rp3d::BodyType::STATIC);
}

void PhysicsManager::DeletePhysics()
{
	physicsCommon.destroyPhysicsWorld(physicsWorld);
}

rp3d::RigidBody* PhysicsManager::CreateRigidBody(rp3d::Transform t)
{
	rp3d::RigidBody* rb = physicsWorld->createRigidBody(t);
	return rb;
}

rp3d::CapsuleShape* PhysicsManager::CreateCapsuleCollider(float radius, float height)
{
	return physicsCommon.createCapsuleShape(radius, height);
}

rp3d::BoxShape* PhysicsManager::CreateBoxCollider(float halfX, float halfY, float halfZ)
{
	const rp3d::Vector3 halfExtents(halfX, halfY, halfZ);
	return physicsCommon.createBoxShape(halfExtents);
}

void PhysicsManager::SetDebugPhysicsRendering(bool t)
{
	physicsWorld->setIsDebugRenderingEnabled(t);
	rp3d::DebugRenderer debugRenderer = GetDebugRenderer();
}

rp3d::DebugRenderer PhysicsManager::GetDebugRenderer()
{
	return physicsWorld->getDebugRenderer();
}

rp3d::PhysicsWorld* PhysicsManager::GetPhysicsWorld()
{
	return physicsWorld;
}

rp3d::PhysicsCommon* PhysicsManager::GetPhysicsCommon()
{
	return &physicsCommon;
}