//
// Created by Bryce standley on 23/6/21.
//

#include "PhysicsEvents.h"

void PhysicsEvents::onContact(const CollisionCallback::CallbackData &callbackData)
{
	std::cout << "physics collision happened yall" << std::endl;
}