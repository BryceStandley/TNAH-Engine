#pragma once

#include "PhysicsStructs.h"
#include "TNAH/Core/Math.h"
#include <reactphysics3d/reactphysics3d.h>

namespace tnah::Physics 
{
	class Collider : public RefCounted
	{
	public:
		enum ColliderType {Box, Sphere, Capsule};

		Collider();
		Collider(rp3d::CollisionShape* collider, ColliderType c, float mass = 1.0f);

		static Ref<Collider> Create(rp3d::CollisionShape* collider, ColliderType c, float mass = 1.0f);

		void SetPosition(const glm::vec3& pos) { m_Position = pos; }
		void SetOrientation(const glm::quat& orientation) { m_Orientation = orientation; }

		glm::vec3 GetColliderPosition() const { return m_Position; }
		glm::quat GetColliderOrientation() const { return m_Orientation; }

		BodyMass GetColliderMass() const { return m_Mass; }
		ColliderType GetColliderType() const { return m_Type; }
		void SetColliderType(ColliderType c) { m_Type = c; }
		std::pair<ColliderType, rp3d::CollisionShape*> GetCollisionShapePair() { return { m_Type, m_Collider }; }

		InertiaTensor GetLocalColliderInertiaTensor();

	private:

		void InitBoxMass();

		void InitSphereMass();

		void InitCapsuleMass();

	private:
		rp3d::CollisionShape* m_Collider = nullptr;

		ColliderType m_Type = ColliderType::Box;

		glm::vec3 m_Position = {};

		glm::quat m_Orientation = {};

		BodyMass m_Mass;

		InertiaTensor m_LocalColliderInertiaTensor;

		friend class EditorUI;
	};

}



