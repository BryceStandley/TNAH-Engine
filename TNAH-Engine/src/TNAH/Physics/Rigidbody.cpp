#include "tnahpch.h"
#include "Rigidbody.h"

namespace tnah::Physics {


	RigidBody::RigidBody()
	{
		m_BodyType = BodyType::Dynamic;
	}

	RigidBody::RigidBody(tnah::Physics::BodyMass mass, tnah::Physics::BodyType type)
		:m_BodyMass(mass), m_BodyType(type)
	{
		Setup();
	}

	Ref<RigidBody> RigidBody::Create(BodyMass mass, BodyType type)
	{
		return Ref<RigidBody>::Create(mass, type);
	}

	void RigidBody::OnUpdate(TransformComponent& transform)
	{
		m_CollisionBody->setTransform(Math::ToRp3dTransform(transform));
		UpdateInertiaTensor(transform);
	}

	void RigidBody::AddCollider(Ref<Collider> collider)
	{
		m_Colliders.push_back(collider);
		UpdatePhysicsInformation();
	}

	void RigidBody::ApplyCollisionImpulse(const glm::vec3& linearVelocity, const glm::vec3& angularVelocity)
	{
		m_LinearVelocity.Velocity = linearVelocity;
		m_AngularVelocity.Velocity = angularVelocity;
	}

	void RigidBody::ResetValues()
	{
		m_Force = {0.0f, 0.0f, 0.0f};
		m_Torque = {0.0f, 0.0f, 0.0f};
		m_LinearVelocity = {0.0f, 0.0f, 0.0f};
		m_AngularVelocity = {0.0f, 0.0f, 0.0f};
	}

	void RigidBody::Setup()
	{
		if(m_BodyType == BodyType::Static)
		{
			m_BodyMass.Mass = std::numeric_limits<float>::max();
			m_BodyMass.InverseMass = std::numeric_limits<float>::min();
		}
		else
		{
			if(!m_Colliders.empty())
			{
				for(auto collider : m_Colliders)
				{
					m_BodyMass.Mass += collider->GetColliderMass().Mass;
				}

				for(auto collider : m_Colliders)
				{
					m_BodyMass.CentreOfMass = (collider->GetColliderPosition() * collider->GetColliderMass().Mass ) / m_BodyMass.Mass;
				}
			
				m_BodyMass.InverseMass = 1.0f /  m_BodyMass.Mass;
			
				m_InertiaTensor.Tensor = CalculateInertiaTensor(m_Colliders.at(0), m_BodyMass);
				m_InertiaTensor.InverseTensor = glm::inverse(m_InertiaTensor.Tensor);
			}
		}


	}

	void RigidBody::UpdatePhysicsInformation()
	{
		if(m_BodyType == BodyType::Static)
		{
			m_BodyMass.Mass = std::numeric_limits<float>::max();
			m_BodyMass.InverseMass = std::numeric_limits<float>::min();
		}
		else
		{
			if(!m_Colliders.empty())
			{
				for(auto collider : m_Colliders)
				{
					m_BodyMass.Mass += collider->GetColliderMass().Mass;
				}

				for(auto collider : m_Colliders)
				{
					m_BodyMass.CentreOfMass = (collider->GetColliderPosition() * collider->GetColliderMass().Mass ) / m_BodyMass.Mass;
				}
			
				m_BodyMass.InverseMass = 1.0f /  m_BodyMass.Mass;
			
				m_InertiaTensor.Tensor = CalculateInertiaTensor(m_Colliders.at(0), m_BodyMass);
				m_InertiaTensor.InverseTensor = glm::inverse(m_InertiaTensor.Tensor);
			}
		}
	}

	glm::mat3 RigidBody::CalculateInertiaTensor(Ref<Collider> collider, BodyMass colliderMass)
	{
		glm::mat3x3 tensor{};
		auto pair = collider->GetCollisionShapePair();
		if(pair.first == Collider::Type::Box)
		{
			const auto box = static_cast<rp3d::BoxShape*>(pair.second);
			const float calc = 1.0f / 12.0f;
			
			tensor[0][0] = calc * colliderMass.Mass *  (box->getHalfExtents().y * box->getHalfExtents().y + box->getHalfExtents().x * box->getHalfExtents().x);
			tensor[1][1] = calc * colliderMass.Mass *  (box->getHalfExtents().z * box->getHalfExtents().z + box->getHalfExtents().x * box->getHalfExtents().x);
			tensor[2][2] = calc * colliderMass.Mass *  (box->getHalfExtents().z * box->getHalfExtents().z + box->getHalfExtents().y * box->getHalfExtents().y);
			
			
			return tensor;
		}

		if(pair.first == Collider::Type::Sphere || pair.first == Collider::Type::Capsule)
		{
			constexpr float calc = 2.0f / 5.0f;
			float calculation = 0.0f;
			if(pair.first == Collider::Type::Sphere)
			{
				const auto shape = static_cast<rp3d::SphereShape*>(pair.second);
				calculation = calc * colliderMass.Mass * glm::pow<float>(shape->getRadius(), 2);
			}
			else
			{
				const auto shape = static_cast<rp3d::CapsuleShape*>(pair.second);
				calculation = calc * colliderMass.Mass * glm::pow<float>(shape->getRadius(), 2);
			}
			tensor[0][0] = calculation;
			tensor[1][1] = calculation;
			tensor[2][2] = calculation;
			return tensor;
		}

		return glm::mat3(0.0f);
	}

	glm::mat3 RigidBody::CalculateInertiaTensor(rp3d::CollisionShape* collider, BodyMass colliderMass, Collider::Type type)
	{
		glm::mat3x3 tensor{};
		if(type == Collider::Type::Box)
		{
			const auto box = static_cast<rp3d::BoxShape*>(collider);
			const float mass_over_12 = colliderMass.Mass / 12.f;

			const float x = box->getHalfExtents().x * 2.0f;
			const float y = box->getHalfExtents().y * 2.0f;
			const float z = box->getHalfExtents().z * 2.0f;
			
			//tensor[0][0] = mass_over_12 * (box->getHalfExtents().y * box->getHalfExtents().y + box->getHalfExtents().x * box->getHalfExtents().x);
			//tensor[1][1] = mass_over_12 * (box->getHalfExtents().z * box->getHalfExtents().z + box->getHalfExtents().x * box->getHalfExtents().x);
			//tensor[2][2] = mass_over_12 * (box->getHalfExtents().z * box->getHalfExtents().z + box->getHalfExtents().y * box->getHalfExtents().y);
			
			tensor[0][0] = mass_over_12 * (glm::pow<float>(y, 2) + glm::pow<float>(z, 2));
			tensor[1][1] = mass_over_12 * (glm::pow<float>(x, 2) + glm::pow<float>(z, 2));
			tensor[2][2] = mass_over_12 * (glm::pow<float>(y, 2) + glm::pow<float>(y, 2));
			
			
			return tensor;
		}

		if(type == Collider::Type::Sphere || type == Collider::Type::Capsule)
		{
			constexpr float calc = 0.4f;
			float calculation = 0.0f;
			if(type == Collider::Type::Sphere)
			{
				const auto shape = static_cast<rp3d::SphereShape*>(collider);
				calculation = calc * colliderMass.Mass * glm::pow<float>(shape->getRadius(), 2);
			}
			else
			{
				const auto shape = static_cast<rp3d::CapsuleShape*>(collider);
				calculation = calc * colliderMass.Mass * glm::pow<float>(shape->getRadius(), 2);
			}
			tensor[0][0] = calculation;
			tensor[1][1] = calculation;
			tensor[2][2] = calculation;
			return tensor;
		}

		return glm::mat3(0.0f);
	}
	
	void RigidBody::UpdateInertiaTensor(TransformComponent& transform)
	{
		//Get the InertiaTensor based on the transform rotation and then calculate the inverse based on the local inverse
		m_InertiaTensor.Tensor = glm::mat3_cast(glm::quat(transform.Rotation));
		m_InertiaTensor.InverseTensor[0][0] = m_InertiaTensor.Tensor[0][0] * m_LocalInertiaTensor.InverseTensor[0][0];
		m_InertiaTensor.InverseTensor[1][1] = m_InertiaTensor.Tensor[1][1] * m_LocalInertiaTensor.InverseTensor[1][1];
		m_InertiaTensor.InverseTensor[2][2] = m_InertiaTensor.Tensor[2][2] * m_LocalInertiaTensor.InverseTensor[2][2];
	}
}
