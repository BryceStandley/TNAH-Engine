//
// Created by Bryce standley on 22/6/21.
//
#pragma once
#ifndef TNAH_PROJECT_PHYSICSMANAGER_H
#define TNAH_PROJECT_PHYSICSMANAGER_H

#include <reactphysics3d/reactphysics3d.h>
#include "Terrain.h"
#include "PhysicsEvents.h"

class PhysicsManager
{
public:
	///Singleton of the physics manager
	static PhysicsManager* GetInstance();


	void CreateTerrainCollider(Terrain* gameTerrain);
	rp3d::RigidBody* CreateRigidBody(rp3d::Transform t);
	rp3d::CapsuleShape* CreateCapsuleCollider(float radius, float height);
	rp3d::BoxShape* CreateBoxCollider(float halfX, float halfY, float halfZ);

	void Update(float deltaTime);
	void DeletePhysics();


	void SetDebugPhysicsRendering(bool t);
	rp3d::DebugRenderer GetDebugRenderer();
	rp3d::PhysicsWorld* GetPhysicsWorld();
	rp3d::PhysicsCommon* GetPhysicsCommon();

	uint LinesVAO, LinesVBO;
	uint triVAO, triVBO;
	Shader* debugShader;
	rp3d::DefaultLogger* logger;

private:
	rp3d::PhysicsCommon physicsCommon;
	rp3d::PhysicsWorld* physicsWorld;
	PhysicsEvents* eventListener;



protected:
	PhysicsManager();
	static PhysicsManager* instance;

};


#endif //TNAH_PROJECT_PHYSICSMANAGER_H
