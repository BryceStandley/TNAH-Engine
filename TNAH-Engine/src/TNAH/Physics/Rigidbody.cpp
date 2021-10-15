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

	void RigidBody::Setup()
	{
		for(auto collider : m_Colliders)
		{
			m_BodyMass.Mass += collider->GetColliderMass().Mass;
		}

		for(auto collider : m_Colliders)
		{
			m_BodyMass.CentreOfMass = (collider->GetColliderPosition() * collider->GetColliderMass().Mass ) / m_BodyMass.Mass;
		}

		if(m_BodyType == BodyType::Static)
		{
			m_BodyMass.Mass = std::numeric_limits<float>::max();
			m_BodyMass.InverseMass = std::numeric_limits<float>::min();
		}
		else
		{
			m_BodyMass.InverseMass = 1.0f /  m_BodyMass.Mass;
		}

		if(!m_Colliders.empty())
		{
			m_InertiaTensor.Tensor = CalculateInertiaTensor(m_Colliders.at(0), m_BodyMass);
			m_InertiaTensor.InverseTensor = glm::inverse(m_InertiaTensor.Tensor);
		}
	}

	void RigidBody::UpdatePhysicsInformation()
	{
		//Update the mass and tensor etc now we have a new collider on the body
		for(auto collider : m_Colliders)
		{
			m_BodyMass.Mass += collider->GetColliderMass().Mass;
		}

		for(auto collider : m_Colliders)
		{
			m_BodyMass.CentreOfMass = (collider->GetColliderPosition() * collider->GetColliderMass().Mass ) / m_BodyMass.Mass;
		}

		if(m_BodyType == BodyType::Static)
		{
			m_BodyMass.Mass = std::numeric_limits<float>::max();
			m_BodyMass.InverseMass = std::numeric_limits<float>::min();
		}
		else
		{
			m_BodyMass.InverseMass = 1.0f /  m_BodyMass.Mass;
		}

		if(!m_Colliders.empty())
		{
			m_InertiaTensor.Tensor = CalculateInertiaTensor(m_Colliders.at(0), m_BodyMass);
			m_InertiaTensor.InverseTensor = glm::inverse(m_InertiaTensor.Tensor);
		}
	}

	glm::mat3 RigidBody::CalculateInertiaTensor(Ref<Collider> collider, BodyMass colliderMass)
	{
		glm::mat3x3 tensor{};
		auto pair = collider->GetCollisionShapePair();
		if(pair.first == Collider::Type::Box)
		{
			const auto box = static_cast<rp3d::BoxShape*>(pair.second);
			constexpr float calc = 1.f / 12.f;
			
			tensor[0][0] = calc * colliderMass.Mass * (box->getHalfExtents().y * box->getHalfExtents().y + box->getHalfExtents().x * box->getHalfExtents().x);
			tensor[1][1] = calc * colliderMass.Mass * (box->getHalfExtents().z * box->getHalfExtents().z + box->getHalfExtents().x * box->getHalfExtents().x);
			tensor[2][2] = calc * colliderMass.Mass * (box->getHalfExtents().z * box->getHalfExtents().z + box->getHalfExtents().y * box->getHalfExtents().y);
			
			return tensor;
		}

		if(pair.first == Collider::Type::Sphere)
		{
			const auto sphere = static_cast<rp3d::SphereShape*>(pair.second);
			constexpr float calc = 2.f / 5.f;
			const float calculation = calc * colliderMass.Mass * sphere->getRadius() * sphere->getRadius();
			tensor[0][0] = calculation;
			tensor[1][1] = calculation;
			tensor[2][2] = calculation;
			return tensor;
		}

		return glm::mat3(0.0f);
	}
}
