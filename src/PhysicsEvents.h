//
// Created by Bryce standley on 23/6/21.
//
#pragma once
#ifndef TNAH_PROJECT_PHYSICSEVENTS_H
#define TNAH_PROJECT_PHYSICSEVENTS_H
#include <reactphysics3d/reactphysics3d.h>
#include "Debugger.h"

class PhysicsEvents : public rp3d::EventListener
{
	void onContact(const CollisionCallback::CallbackData &callbackData) override;
};


#endif //TNAH_PROJECT_PHYSICSEVENTS_H
