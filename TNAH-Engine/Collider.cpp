#include "tnahpch.h"
#include "Collider.h"
#include "Rigidbody.h"

namespace tnah 
{
	Collider::Collider() {}

	Collider::Collider(rp3d::CollisionShape* collider, ColliderType c, float mass)
		: m_Collider(collider)
	{
		SetColliderType(c);
		m_Mass.SetMass(mass);

		if (GetColliderType() == ColliderType::Box)
			InitBoxMass();
		else if (GetColliderType() == ColliderType::Sphere)
			InitSphereMass();
		else if (GetColliderType() == ColliderType::Capsule)
			InitCapsuleMass();
		else
			std::cout << "Invalid ColliderType!" << std::endl;
	}

	Ref<Collider> Collider::Create(rp3d::CollisionShape* collider, ColliderType c, float mass) 
	{
		return Ref<Collider>::Create(collider, c, mass);
	}

	void Collider::InitBoxMass() 
	{
		rp3d::BoxShape* box = static_cast<rp3d::BoxShape*>(m_Collider);
	}

	void Collider::InitSphereMass() 
	{
		rp3d::SphereShape* sphere = static_cast<rp3d::SphereShape*>(m_Collider);
	}

	void Collider::InitCapsuleMass() 
	{
		rp3d::CapsuleShape* capsule = static_cast<rp3d::CapsuleShape*>(m_Collider);
	}

	InertiaTensor Collider::GetLocalColliderInertiaTensor() 
	{
		m_LocalColliderInertiaTensor = Rigidbody::
	}


}