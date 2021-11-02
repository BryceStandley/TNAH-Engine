#include "tnahpch.h"
#include "PhysicsEvents.h"
#include "TNAH/Physics/PhysicsCollision.h"
#include "TNAH/Scene/GameObject.h"

namespace tnah {
	namespace Physics {
		
		void PhysicsEvents::onContact(const CollisionCallback::CallbackData &callbackData)
		{
			for(unsigned int i = 0; i < callbackData.getNbContactPairs(); i++)
			{
				ContactPair contactPair = callbackData.getContactPair(i);
				for(int i = 0; i < contactPair.getNbContactPoints(); i++)
				{
					CollisionData col;
			
					auto point = contactPair.getContactPoint(i);
					col.body1ContactPosition = Math::FromRp3dVec3(contactPair.getCollider1()->getLocalToWorldTransform() * point.getLocalPointOnCollider1());
					col.body2ContactPosition =  Math::FromRp3dVec3(contactPair.getCollider2()->getLocalToWorldTransform() * point.getLocalPointOnCollider2());
					col.contactNormal = Math::FromRp3dVec3(point.getWorldNormal());
					col.body1GameObject = static_cast<GameObject*>(contactPair.getBody1()->getUserData());
					col.body2GameObject = static_cast<GameObject*>(contactPair.getBody2()->getUserData());
					col.body1RigidBody = col.body1GameObject->GetComponent<RigidBodyComponent>().Body;
					col.body2RigidBody = col.body2GameObject->GetComponent<RigidBodyComponent>().Body;
					col.penetrationDepth = static_cast<float>(point.getPenetrationDepth());
					PhysicsEngine::AddCollision(col);
				}
			}
		}

		void PhysicsEvents::onTrigger(const rp3d::OverlapCallback::CallbackData &callbackData)
		{

		}
	}
}
