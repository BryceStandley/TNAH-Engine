#include "tnahpch.h"
#include "PhysicsEvents.h"

#include "TNAH/Scene/GameObject.h"

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
				auto contactNormal = point.getWorldNormal();
				auto gameObject1 = (*static_cast<GameObject*>(pair.getBody1()->getUserData()));
				auto gameObject2 = (*static_cast<GameObject*>(pair.getBody2()->getUserData()));
				auto&scene = gameObject1.m_Scene;
				auto time = scene->m_PhysicsTime;
				if(scene != nullptr)
				{
					//auto &tt = scene->FindEntityByUUID(gameObject1.GetUUID()).GetComponent<TransformComponent>();
					TNAH_CORE_INFO("PE: Contact Points 1 x{0} y{1} z{2} : Contact Points 2 x{3} y{4} z{5} | Normal: x{6} y{7} z{8} | ids: 1.{9} 2.{10} ", contactPosition1.x, contactPosition1.y, contactPosition1.z, contactPosition2.x, contactPosition2.y, contactPosition2.z, contactNormal.x, contactNormal.y, contactNormal.z, gameObject1.GetUUID(), gameObject2.GetUUID());	
				}
			}
		}
	}

	void PhysicsEvents::onTrigger(const rp3d::OverlapCallback::CallbackData &callbackData)
	{

	}

}
