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
	rp3d::uint logLevel = static_cast<rp3d::uint>(static_cast<rp3d::uint>(rp3d::Logger::Level::Warning) | static_cast<rp3d::uint>(rp3d::Logger::Level::Error) | static_cast<rp3d::uint>(rp3d::Logger::Level::Information));
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
	float minHeight = 0;
	float maxHeight = 0;

	int size = nbRows * nbColumns;
	std::vector<float> terrainHeights = gameTerrain->GetTerrainHeights();
	gameTerrain->terrainColliderHeightData = (float*) malloc(size * sizeof(float));

	for(int z = 0; z < nbRows; ++z)
	{
		for(int x = 0; x < nbColumns; ++x)
		{
			int index = z * nbRows + x;
			float temp = terrainHeights[index];

			gameTerrain->terrainColliderHeightData[index] = temp;
			if(x == 0 && z == 0)
			{
				minHeight = temp;
				maxHeight = temp;
			}
			if(temp < minHeight){minHeight = temp;}
			if(temp > maxHeight){maxHeight = temp;}
		}
	}

	glm::vec3 s = gameTerrain->GetScales();
	rp3d::HeightFieldShape* col = physicsCommon.createHeightFieldShape(nbRows, nbColumns, minHeight, maxHeight, gameTerrain->terrainColliderHeightData, rp3d::HeightFieldShape::HeightDataType::HEIGHT_FLOAT_TYPE);
	rp3d::Vector3 scales(gameTerrain->GetScales().x, gameTerrain->GetScales().y, gameTerrain->GetScales().z);
	col->setScale(scales);

	rp3d::Transform transform = rp3d::Transform::identity();
	rp3d::RigidBody* rb = physicsWorld->createRigidBody(transform);
	rb->setType(rp3d::BodyType::KINEMATIC);
	rb->enableGravity(false);
	float posX = ((float)nbRows * scales.x) / 2.0f;
	float posY = (maxHeight * scales.y) / 2.0f;
	float posZ = ((float)nbColumns * scales.z) / 2.0f;
	transform.setPosition(rp3d::Vector3(posX, posY, posZ));
	rb->setTransform(transform);
	gameTerrain->terrainCollider = rb->addCollider(col, rp3d::Transform::identity());
	gameTerrain->terrainRB = rb;
	//gameTerrain->terrainCB = rb;
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

rp3d::CollisionBody* PhysicsManager::CreateCollisionBody(rp3d::Transform t)
{
	rp3d::CollisionBody* cb = physicsWorld->createCollisionBody(t);
	return cb;
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

rp3d::Vector3 PhysicsManager::GLMVec3toRP3DVec3(glm::vec3 v)
{
	rp3d::Vector3 temp(0,0,0);
	temp.x = v.x;
	temp.y = v.y;
	temp.z = v.z;
	return temp;
}