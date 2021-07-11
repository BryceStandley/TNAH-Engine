//
// Created by Bryce standley on 22/6/21.
//
#pragma once
#ifndef TNAH_PROJECT_PHYSICSMANAGER_H
#define TNAH_PROJECT_PHYSICSMANAGER_H

#include <reactphysics3d/reactphysics3d.h>
#include "Terrain.h"
#include "PhysicsEvents.h"

class TNAH_API PhysicsManager
{
public:
	///Singleton of the physics manager
	static PhysicsManager* GetInstance();


	void CreateTerrainCollider(Terrain* gameTerrain);
	rp3d::CollisionBody* CreateCollisionBody(rp3d::Transform t);
	rp3d::RigidBody* CreateRigidBody(rp3d::Transform t);
	rp3d::CapsuleShape* CreateCapsuleCollider(float radius, float height);
	rp3d::BoxShape* CreateBoxCollider(float halfX, float halfY, float halfZ);
	rp3d::SphereShape* CreateSphereCollider(float radius);

	void Update(float deltaTime);
	void DeletePhysics();
	rp3d::Vector3 GLMVec3toRP3DVec3(glm::vec3 v);


	void SetDebugPhysicsRendering(bool t);
	rp3d::DebugRenderer GetDebugRenderer();
	rp3d::PhysicsWorld* GetPhysicsWorld();
	rp3d::PhysicsCommon* GetPhysicsCommon();

	unsigned int LinesVAO, LinesVBO;
	unsigned int triVAO, triVBO;
	Shader* debugShader;
	rp3d::DefaultLogger* logger;
	float physicsUpdateTimeStep = 60 / 1000.0f;

private:
	rp3d::PhysicsCommon physicsCommon;
	rp3d::PhysicsWorld* physicsWorld;
	PhysicsEvents* eventListener;
	Terrain* gameTerrain;



protected:
	PhysicsManager();
	static PhysicsManager* instance;

};


#endif //TNAH_PROJECT_PHYSICSMANAGER_H
