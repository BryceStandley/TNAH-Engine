#include "tnahpch.h"
#include "Collider.h"

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
		m_Mass.CentreOfMass = Math::FromRp3dVec3(box->getHalfExtents());
	}

	void Collider::InitializeSphereMass()
	{
		rp3d::SphereShape* sphere = static_cast<rp3d::SphereShape*>(m_Collider);

	}

	void Collider::InitializeCapsuleMass()
	{
		rp3d::CapsuleShape* capsule = static_cast<rp3d::CapsuleShape*>(m_Collider);
	}
}
