#include "tnahpch.h"
#include "PhysicsEvents.h"

#include "TNAH/Scene/GameObject.h"

namespace tnah
{
	void PhysicsEvents::onContact(const CollisionCallback::CallbackData &callbackData)
	{
		for(unsigned int i = 0; i < callbackData.getNbContactPairs(); ++i)
		{
			auto pair = callbackData.getContactPair(i);
			for(unsigned int j = 0; j < pair.getNbContactPoints(); j++)
			{
				auto point = pair.getContactPoint(j);
				auto contactPosition1 = pair.getCollider1()->getLocalToWorldTransform() * point.getLocalPointOnCollider1();
				auto contactPosition2 = pair.getCollider2()->getLocalToWorldTransform() * point.getLocalPointOnCollider2();
				auto contactNormal = point.getWorldNormal();
				auto gameObject1 = (*static_cast<GameObject*>(pair.getBody1()->getUserData()));
				auto gameObject2 = (*static_cast<GameObject*>(pair.getBody2()->getUserData()));
				auto&scene = gameObject1.m_Scene;
				auto time = scene->m_PhysicsTime;
				auto& rb1 = gameObject1.GetComponent<RigidBodyComponent>();
				auto& rb2 = gameObject2.GetComponent<RigidBodyComponent>();
				auto penetration = point.getPenetrationDepth();
				if((rb1.Body->GetType() == Physics::BodyType::Static || rb1.Body->IsSleeping()) && (rb2.Body->GetType() == Physics::BodyType::Static || rb2.Body->IsSleeping()))
					continue;
				
				if(scene != nullptr)
				{
					//This is where physics collision resolution is applied
					constexpr float restitution = 0.6f;
					
					
					auto& t1 = gameObject1.Transform();
					glm::vec3 lv1 = rb1.Body->GetLinearVelocity();
					glm::vec3 av1 = rb1.Body->GetAngularVelocity();
					
					
					auto& t2 = gameObject2.Transform();
					glm::vec3 lv2 = rb2.Body->GetLinearVelocity();
					glm::vec3 av2 = rb2.Body->GetAngularVelocity();

					glm::vec3 cp1 = Math::FromRp3dVec3(contactPosition1);
					glm::vec3 cp2 = Math::FromRp3dVec3(contactPosition2);
					glm::vec3 cn = Math::FromRp3dVec3(contactNormal);
					

					glm::vec3 r1 = cp1 - (t1.Position + rb1.Body->GetBodyMass().CentreOfMass);
					glm::vec3 r2 = cp2 - (t2.Position + rb2.Body->GetBodyMass().CentreOfMass);

					if(rb1.Body->GetType() != Physics::BodyType::Static && !rb1.Body->IsSleeping())
					{
						t1.Position += cn * ((penetration / 2) * -1);
					}
					if(rb2.Body->GetType() != Physics::BodyType::Static && !rb2.Body->IsSleeping())
					{
						t2.Position -= cn * ((penetration / 2) * -1);
					}
					
					//Transfer of momentum

			        //         -(1 + ε) * (n̂ • (v⁻₁ - v⁻₂) + w⁻₁ • (r₁ x n̂) - w₂ • (r₂ x n̂))
			        // __________________________________________________________________________ * n̂
			        // (m₁⁻¹ + m₂⁻¹) + ((r₁ x n̂)ᵀ J₁⁻¹ * (r₁ x n̂) + (r₂ x n̂)ᵀ * J₂⁻¹ * (r₂ x n̂)

			        //  -(1 + ε)
			        auto restitution_multiplier = -(1.0f + restitution);

			        // (v⁻₁ - v⁻₂)
			        auto relative_velocity = lv1 - lv2;

			        //(r₁ x n̂)
			        auto r1xn = glm::cross(r1, cn);

			        //(r₂ x n̂)
			        auto r2xn = glm::cross(r2, cn);

			        // (m₁⁻¹ + m₂⁻¹)
			        auto total_inverse_mass = rb1.Body->GetBodyMass().InverseMass + rb2.Body->GetBodyMass().InverseMass;

			        //-(1 + ε) * (n̂ • (v⁻₁ - v⁻₂) + w⁻₁ • (r₁ x n̂) - w₂ • (r₂ x n̂))
			        auto numerator = restitution_multiplier * (glm::dot(cn, relative_velocity) + glm::dot(av1, r1xn) - glm::dot(av2, r2xn));

			        // (m₁⁻¹ + m₂⁻¹) + ((r₁ x n̂)ᵀ * J₁⁻¹ * (r₁ x n̂) + (r₂ x n̂)ᵀ * J₂⁻¹ * (r₂ x n̂)
			        float denominator = total_inverse_mass + (glm::dot(r1xn, rb1.Body->GetInertiaTensor().InverseTensor * r1xn) + glm::dot(r2xn, rb2.Body->GetInertiaTensor().InverseTensor * r2xn));

			        //         -(1 + ε) * (n̂ • (v⁻₁ - v⁻₂) + w⁻₁ • (r₁ x n̂) - w₂ • (r₂ x n̂))
			        // __________________________________________________________________________ * n̂
			        // (m₁⁻¹ + m₂⁻¹) + ((r₁ x n̂)ᵀ * J₁⁻¹ * (r₁ x n̂) + (r₂ x n̂)ᵀ * J₂⁻¹ * (r₂ x n̂)

			        //Transfer of momentum
			        auto lambda = (numerator / denominator);

			        //linear impulse
			        auto linear_impulse = lambda * cn;

			        if (lambda < 0)
			        {
			            // v⁺₁ = v⁻₁
			            //lv1 += linear_impulse * rb1.Body->GetBodyMass().InverseMass;
			            lv1 += linear_impulse * rb1.Body->GetBodyMass().InverseMass;
			            // v⁺₂ = v⁻₂
			            lv2 -= linear_impulse * rb2.Body->GetBodyMass().InverseMass;

			            av1 = av1 + (lambda * rb1.Body->GetInertiaTensor().InverseTensor) * r1xn;
			            av2 = av2 - (lambda * rb2.Body->GetInertiaTensor().InverseTensor) * r2xn;
					}

					if(rb1.Body->GetType() != Physics::BodyType::Static || !rb1.Body->IsSleeping()) rb1.Body->ApplyCollisionImpulse(lv1, av1);
					if(rb2.Body->GetType() != Physics::BodyType::Static || !rb2.Body->IsSleeping()) rb2.Body->ApplyCollisionImpulse(lv2, av2);
					
					//TODO: Add some sort of player/camera check to make sure were not applying velocity forces to a player controller


					
				}
			}
		}
	}

	void PhysicsEvents::onTrigger(const rp3d::OverlapCallback::CallbackData &callbackData)
	{

	}

}
