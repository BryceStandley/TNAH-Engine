#include "tnahpch.h"
#include "Collider.h"
#include "Rigidbody.h"

namespace tnah::Physics {


	Collider::Collider()
	{}

	Collider::Collider(rp3d::CollisionShape* collider, Type type, float mass)
		:m_Collider(collider), m_Type(type)
	{
		m_Mass.SetMass(mass);
		
		switch (m_Type)
		{
			case Type::Box:
				InitializeBoxMass();
				break;
			case Type::Sphere:
				InitializeSphereMass();
				break;
			case Type::Capsule:
				InitializeCapsuleMass();
				break;
			default:
				break;
		}
	}

	Ref<Collider> Collider::Create(rp3d::CollisionShape* collider, Type type, float mass)
	{
		return Ref<Collider>::Create(collider, type, mass);
	}

	void Collider::InitializeBoxMass()
	{
		rp3d::BoxShape* box = static_cast<rp3d::BoxShape*>(m_Collider);
		//m_Mass.CentreOfMass = Math::FromRp3dVec3(box->getHalfExtents());
	}

	void Collider::InitializeSphereMass()
	{
		rp3d::SphereShape* sphere = static_cast<rp3d::SphereShape*>(m_Collider);

	}

	void Collider::InitializeCapsuleMass()
	{
		rp3d::CapsuleShape* capsule = static_cast<rp3d::CapsuleShape*>(m_Collider);
	}

	InertiaTensor Collider::GetLocalColliderInertiaTensor()
	{
		m_LocalColliderInertiaTensor.Tensor = RigidBody::CalculateInertiaTensor(this->m_Collider, this->m_Mass, this->m_Type);
		auto bodySpace = glm::mat3_cast(m_Orientation);
		bodySpace[0][0] *= m_LocalColliderInertiaTensor.Tensor[0][0];
		bodySpace[1][1] *= m_LocalColliderInertiaTensor.Tensor[1][1];
		bodySpace[2][2] *= m_LocalColliderInertiaTensor.Tensor[2][2];

		auto offset = m_Position - m_Mass.CentreOfMass;
		auto offset_sqr = offset;
		for(int i = 0; i < 3; ++i)
		{
			offset_sqr[i] = glm::pow<float>(offset_sqr[i], 2);
		}

		glm::mat3 offset_mat;
		auto axis_offsets = glm::vec3(offset_sqr.y + offset_sqr.z,
			offset_sqr.x + offset_sqr.z,
			offset_sqr.x + offset_sqr.y);

		for(int i = 0; i < 3; ++i)
		{
			for(int j = 0; j < 3; ++j)
			{
				offset_mat[j][i] += axis_offsets[i];
			}
		}

		offset_mat *= m_Mass.Mass;

		m_LocalColliderInertiaTensor.Tensor += bodySpace + offset_mat;
		m_LocalColliderInertiaTensor.InverseTensor = glm::inverse(m_LocalColliderInertiaTensor.Tensor);
		return m_LocalColliderInertiaTensor;
	}
}
