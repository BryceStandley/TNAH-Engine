#include "tnahpch.h"
#include "Collider.h"
#include "Rigidbody.h"

namespace tnah::Physics {


	Collider::Collider()
	{}

	Collider::Collider(rp3d::CollisionShape* c, Type t)
		:collider(c), type(t)
	{
		
		switch (type)
		{
			case Type::Box:
				InitializeBox();
				break;
			case Type::Sphere:
				InitializeSphere();
				break;
			default:
				break;
		}
	}

	Ref<Collider> Collider::Create(rp3d::CollisionShape* collider, Type type)
	{
		return Ref<Collider>::Create(collider, type);
	}

	void Collider::SetColliderMass(float m)
	{
		if(type == Type::Box)
		{
			mass.SetMass(m);
			type = Type::Box;
			float factor = 1.0f / 12.0f * mass.mass;
			glm::vec3 tensor = glm::vec3(factor * (size.y + size.z), factor * (size.x + size.y),
			                             factor * (size.x + size.z));
			inertiaTensor.LocalInertiaTensor = tensor;
		}
		else
		{
			mass.SetMass(m);
			float diag = 0.5f * mass.mass * (radius * radius);
			glm::vec3 tensor = glm::vec3(diag, diag, diag);
			inertiaTensor.LocalInertiaTensor = tensor;	
		}
	}
	
	void Collider::InitializeBox()
	{
		rp3d::BoxShape* box = static_cast<rp3d::BoxShape*>(collider);

		const auto fullExtents = Math::FromRp3dVec3(box->getHalfExtents() * 2.0f);
		
		volume =  fullExtents.x * fullExtents.y * fullExtents.z;
		mass.SetMass(density * volume);
		type = Type::Box;

		//1/12 . plwh(mass)
		float value = 1.0f / 12.0f * mass.mass;

		float x = box->getHalfExtents().x * box->getHalfExtents().x;//l
		float y = box->getHalfExtents().y * box->getHalfExtents().y;//h
		float z = box->getHalfExtents().z * box->getHalfExtents().z;//w
		
		size = glm::vec3(x, y, z);

		//X = 1/12 . plwh(mass).(h^2 + w^2)
		//Y = 1/12 . plwh(mass).(l^2 + h^2)
		//Z = 1/12 . plwh(mass).(l^2 + w^2)
		glm::vec3 tensor = glm::vec3(value * (y + z), value * (x + y), value * (x + z));
		inertiaTensor.LocalInertiaTensor = tensor;
	}

	void Collider::InitializeSphere()
	{
		rp3d::SphereShape* sphere = static_cast<rp3d::SphereShape*>(collider);
		type = Type::Sphere;
		volume = (4/3) * glm::pi<float>() * glm::pow(sphere->getRadius(), 3);
		mass.SetMass(density * volume);

		//Restitution(need to get it to grab it from physics before i forget
		//4pi/15pabc = mass
		//AS all circles have to be of a full size and not oddly shaped radius ^ 2 can be used

		//4pi/15pabc(mass) . r^2
		float value = mass.mass * (sphere->getRadius() * sphere->getRadius());
		radius = sphere->getRadius();
		glm::vec3 tensor = glm::vec3(value, value, value);
		inertiaTensor.LocalInertiaTensor = tensor;
	}

	glm::vec3 Collider::GetLocalColliderInertiaTensor()
	{
		return inertiaTensor.LocalInertiaTensor;
	}
}
