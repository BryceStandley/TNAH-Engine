#include "tnahpch.h"
#include "PhysicsEvents.h"

namespace tnah
{
	void PhysicsEvents::onContact(const CollisionCallback::CallbackData &callbackData)
	{
		if(callbackData.getNbContactPairs() < 1) return;

		rp3d::CollisionBody* objectOne = callbackData.getContactPair(0).getBody1();
		rp3d::CollisionBody* objectTwo = callbackData.getContactPair(0).getBody2();
		auto t1 = reinterpret_cast<entt::entity>(*static_cast<entt::entity*>(objectOne->getUserData()));
		auto t2 = reinterpret_cast<entt::entity>(*static_cast<entt::entity*>(objectTwo->getUserData()));

		//Check that there is an entity somehow?
		//Do stuff
	
	}

	void PhysicsEvents::onTrigger(const rp3d::OverlapCallback::CallbackData &callbackData)
	{

	}
}