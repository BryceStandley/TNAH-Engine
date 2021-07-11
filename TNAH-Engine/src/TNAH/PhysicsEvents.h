//
// Created by Bryce standley on 23/6/21.
//
#pragma once
#ifndef TNAH_PROJECT_PHYSICSEVENTS_H
#define TNAH_PROJECT_PHYSICSEVENTS_H
#include <reactphysics3d/reactphysics3d.h>
#include "Debugger.h"
#include "Terrain.h"
#include "BoundingBox.h"

class TNAH_API PhysicsEvents : public rp3d::EventListener
{
public:
	void onContact(const CollisionCallback::CallbackData &callbackData) override;

	void onTrigger(const rp3d::OverlapCallback::CallbackData &callbackData) override;

	void SetTerrainPointer(Terrain* t) {gameTerrain = t;}

private:
	Terrain* gameTerrain;
};


#endif //TNAH_PROJECT_PHYSICSEVENTS_H
