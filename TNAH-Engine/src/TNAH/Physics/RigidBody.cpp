#include "tnahpch.h"
#include "Rigidbody.h"

namespace tnah::Physics 
{
	Rigidbody::Rigidbody() 
	{
		m_BodyType = BodyType::Dynamic;
	}

	Rigidbody::Rigidbody(tnah::Physics::BodyMass mass, tnah::Physics::BodyType type)
		:m_BodyMass(mass), m_BodyType(type) 
	{
		Setup();
	}

	Ref<Rigidbody> Rigidbody::Create(BodyMass mass, BodyType type) 
	{
		return Ref<Rigidbody>::Create(mass, type);
	}

	void Rigidbody::OnUpdate(TransformComponent& transform) 
	{
		m_CollisionBody->setTransform(Math::ToRp3dTransform(transform));
		UpdateInertiaTensor(transform);
	}

	void Rigidbody::AddForce(const glm::vec3& force) 
	{
		m_Force.Force += (force * 1000.0f);
	}

	void Rigidbody::AddTorque(const glm::vec3& torque) 
	{
		m_Torque.Torque += torque;
	}

	void Rigidbody::AddCollider(Ref<Collider> collider) 
	{
		m_Colliders.push_back(collider);
		UpdatePhysicsInformation();
	}

	void Rigidbody::ApplyCollisionImpulse(const glm::vec3& linearVelocity, const glm::vec3& angularVelocity) 
	{
		m_LinearVelocity.Velocity = linearVelocity;
		m_AngularVelocity.AngularVelocity = angularVelocity;
	}

	void Rigidbody::ResetValues() 
	{
		m_LinearVelocity.Velocity = {0.0f,0.0f,0.0f};
		m_AngularVelocity.AngularVelocity= {0.0f,0.0f,0.0f};

		m_Force.Force = {0.0f, 0.0f, 0.0f};
		m_Torque.Torque = {0.0f, 0.0f, 0.0f};

	}

	void Rigidbody::Setup() //also updatePhysicsInformation
	{
		if(m_BodyType == BodyType::Static)
		{
			m_BodyMass.Mass = std::numeric_limits<float>::max();
			m_BodyMass.InverseMass = std::numeric_limits<float>::min();
		}
		else 
		{
			if (m_Colliders.empty() == true) 
			{
				for (auto collider : m_Colliders) 
					m_BodyMass.Mass += collider->GetColliderMass().Mass;

				for (auto collider : m_Colliders)
					m_BodyMass.CentreOfMass = (collider->GetColliderPosition() * collider->GetColliderMass().Mass) / m_BodyMass.Mass;
			}
			m_BodyMass.InverseMass = 1.0f / m_BodyMass.Mass;

			m_InertiaTensor.InertiaTensor = CalculateInertiaTensor(m_Colliders.at(0), m_BodyMass);
			m_InertiaTensor.InvesrseInertiaTensor = glm::inverse(m_InertiaTensor.InertiaTensor);
		}
	}

	glm::mat3 Rigidbody::CalculateInertiaTensor(Ref<Collider> collider, BodyMass colliderMass) 
	{
		glm::mat3x3 tensor{};
		auto pair = collider->GetCollisionShapePair();

		if (pair.first == Collider::ColliderType::Box) 
		{
			const auto box = static_cast<rp3d::BoxShape*>(pair.second);
			const float calculation = (1.0f / 12.0f);	
			const float byTwo = 2;

			// Ixx = (1/12)m(a^2+l^2); - PLEASE REVISIT
			tensor[0][0] = calculation * colliderMass.Mass * (box->getHalfExtents().y * byTwo + box->getHalfExtents().x * byTwo);

			// Iyy = (1/12)m(b^2+l^2) - PLEASE REVISIT
			tensor[1][1] = calculation * colliderMass.Mass * (box->getHalfExtents().z * byTwo + box->getHalfExtents().x * byTwo);

			// Izz = (1/12)m(a^2+b^2) - PLEASE REVISIT
			tensor[2][2] = calculation * colliderMass.Mass * (box->getHalfExtents().y * byTwo + box->getHalfExtents().z* byTwo);

			return tensor;
		}

		if (pair.first == Collider::ColliderType::Sphere || Collider::ColliderType::Capsule) 
		{
			const float twoOverFive = (0.4f); // 2/5
			float calculation = 0.0f;
			
			if (pair.first == Collider::ColliderType::Sphere) 
			{
				const auto shape = static_cast<rp3d::SphereShape*>(pair.second);
				calculation = twoOverFive * colliderMass.Mass * (shape->getRadius() * 2);
			}
			else
			{
				const auto shape = static_cast<rp3d::CapsuleShape*>(pair.second);
				calculation = twoOverFive * colliderMass.Mass * (shape->getRadius() * 2);
			}			

			tensor[0][0] = calculation;
			tensor[1][1] = calculation;
			tensor[2][2] = calculation;

			return tensor;
		}

		//else if none of the listed colliders
		return glm::mat3(0.0f);

	}

	glm::mat3 Rigidbody::CalculateInertiaTensor(rp3d::CollisionShape* collider, BodyMass colliderMass, Collider::ColliderType type)
	{
		glm::mat3x3 tensor{};

		if (type == Collider::ColliderType::Box)
		{
			const auto box = static_cast<rp3d::BoxShape*>(collider);
			const float calculation = (1.0f / 12.0f);
			const float byTwo = 2;

			// Ixx = (1/12)m(a^2+l^2); - PLEASE REVISIT
			tensor[0][0] = calculation * colliderMass.Mass * (box->getHalfExtents().y * byTwo + box->getHalfExtents().x * byTwo);

			// Iyy = (1/12)m(b^2+l^2) - PLEASE REVISIT
			tensor[1][1] = calculation * colliderMass.Mass * (box->getHalfExtents().z * byTwo + box->getHalfExtents().x * byTwo);

			// Izz = (1/12)m(a^2+b^2) - PLEASE REVISIT
			tensor[2][2] = calculation * colliderMass.Mass * (box->getHalfExtents().y * byTwo + box->getHalfExtents().z * byTwo);

			return tensor;
		}

		if (type == Collider::ColliderType::Sphere || Collider::ColliderType::Capsule)
		{
			const float twoOverFive = (0.4f); // 2/5
			float calculation = 0.0f;

			if (type == Collider::ColliderType::Sphere)
			{
				const auto shape = static_cast<rp3d::SphereShape*>(collider);
				calculation = twoOverFive * colliderMass.Mass * (shape->getRadius() * 2);
			}
			else
			{
				const auto shape = static_cast<rp3d::CapsuleShape*>(collider);
				calculation = twoOverFive * colliderMass.Mass * (shape->getRadius() * 2);
			}

			tensor[0][0] = calculation;
			tensor[1][1] = calculation;
			tensor[2][2] = calculation;

			return tensor;
		}

		//else if none of the listed colliders
		return glm::mat3(0.0f);

	}

	void Rigidbody::UpdateInertiaTensor(TransformComponent& transform) 
	{
		//Gets the inertia tensor based on the transform rotation and calculates the inverse tensor based on the local inverse
		m_InertiaTensor.InertiaTensor = glm::mat3_cast(glm::quat(transform.Rotation));
		m_InertiaTensor.InvesrseInertiaTensor[0][0] = m_InertiaTensor.InertiaTensor[0][0] * m_LocalInertiaTensor.InvesrseInertiaTensor[0][0];
		m_InertiaTensor.InvesrseInertiaTensor[1][1] = m_InertiaTensor.InertiaTensor[1][1] * m_LocalInertiaTensor.InvesrseInertiaTensor[1][1];
		m_InertiaTensor.InvesrseInertiaTensor[2][2] = m_InertiaTensor.InertiaTensor[2][2] * m_LocalInertiaTensor.InvesrseInertiaTensor[2][2];
	}

	
}