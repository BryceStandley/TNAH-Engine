#include "tnahpch.h"
#include "PhysicsEvents.h"

namespace tnah
{
	void PhysicsEvents::onContact(const CollisionCallback::CallbackData &callbackData)
	{
		for(unsigned int i = 0; i < callbackData.getNbContactPairs(); i++)
		{
			auto pair = callbackData.getContactPair(i);
			for(unsigned int j = 0; j < pair.getNbContactPoints(); j++)
			{
				auto point = pair.getContactPoint(j);
				auto contactPosition1 = pair.getCollider1()->getLocalToBodyTransform() * point.getLocalPointOnCollider1();
				auto contactPosition2 = pair.getCollider2()->getLocalToBodyTransform() * point.getLocalPointOnCollider2();

				//Comment this out dont delete
				TNAH_CORE_INFO("Physics Events:          Contact Points 1 x{0} y{1} z{2} : Contact Points 2 x{3} y{4} z{5}", contactPosition1.x, contactPosition1.y, contactPosition1.z, contactPosition2.x, contactPosition2.y, contactPosition2.z);
			}
		}

		//Going to need to somehow get the physics timestep into here
		
		/*rp3d::RigidBody* objectOne = (rp3d::RigidBody*)callbackData.getContactPair(0).getBody1();
		rp3d::RigidBody* objectTwo = (rp3d::RigidBody*)callbackData.getContactPair(0).getBody2();*/
		//auto t1 = reinterpret_cast<entt::entity>(*static_cast<entt::entity*>(objectOne->getUserData()));
		//auto t2 = reinterpret_cast<entt::entity>(*static_cast<entt::entity*>(objectTwo->getUserData()));
		//auto one = callbackData.getContactPair(0).getContactPoint(2).getLocalPointOnCollider1();
		//auto two = callbackData.getContactPair(0).getContactPoint(2).getLocalPointOnCollider2();
		//Check that there is an entity somehow?
		//TNAH_CORE_INFO("Contact point 1: x {0} y {1} z {2} ------ Contact point 2: x {3} y {4} z{5}", one.x, one.y, one.z, two.x, two.y, two.y);
	}

	void PhysicsEvents::onTrigger(const rp3d::OverlapCallback::CallbackData &callbackData)
	{

	}

}