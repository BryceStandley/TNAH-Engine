#pragma once
#include "PhysicsStructs.h"
#include <reactphysics3d/reactphysics3d.h>
#include "Collider.h"

namespace tnah::Physics
{
	class Rigidbody : public RefCounted
	{
	public:
		Rigidbody();
		Rigidbody(BodyMass mass, BodyType type = BodyType::Dynamic);

		static Ref<Rigidbody> Create(BodyMass mass, BodyType type = BodyType::Dynamic);

		void OnUpdate(TransformComponent& transform);

		BodyMass GetBodyMass() const { return m_BodyMass; }

		void AddForce(const glm::vec3& force);
		void AddTorque(const glm::vec3& torque);

		void SetCollisionBody(rp3d::CollisionBody* collisionBody) { m_CollisionBody = collisionBody; }
		rp3d::CollisionBody* GetCollisionBody() const { return m_CollisionBody; }

		void AddCollider(Ref<Collider> collider);

		uint32_t GetID() const { return m_ID; }

		void SetBodyType(const BodyType& type) { m_BodyType = type; }
		BodyType GetBodyType() const { return m_BodyType; }

		InertiaTensor GetInertiaTensor() const { return m_InertiaTensor; }

		LinearVelocity GetLinearVelocity() const { return m_LinearVelocity; }
		AngularVelocity GetAngularVelocity() const { return m_AngularVelocity; }

		std::pair<LinearVelocity, AngularVelocity> GetVelocities() { return { m_LinearVelocity, m_AngularVelocity }; }

		void ApplyCollisionImpulse(const glm::vec3& linearVelocity, const glm::vec3& angularVelocity);

		void ResetValues();

		bool& HasGravity() { return m_Gravity; }
		bool Sleeping() { return m_Sleep; }
		void Awake() { m_Sleep = false; }
		void Sleep() { m_Sleep = true; }

		static glm::mat3 CalculateInertiaTensor(Ref<Collider> collider, BodyMass colliderMass);
		static glm::mat3 CalculateInertiaTensor(rp3d::CollisionShape* collider, BodyMass colliderMass, Collider::ColliderType type);

	private:

		void Setup();

		//void UpdatePhysicsInformation();

		void UpdateInertiaTensor(TransformComponent& transform);

		void SetID(const uint32_t id) { m_ID = id; }

	private:
		BodyType m_BodyType;

		BodyMass m_BodyMass;

		LinearVelocity m_LinearVelocity;

		AngularVelocity m_AngularVelocity;

		Force m_Force;

		Torque m_Torque;

		LinearDampening m_LinearDampening;

		AngularDampening m_angularDampening;

		InertiaTensor m_InertiaTensor;

		InertiaTensor m_LocalInertiaTensor;

		std::vector<Ref<Collider>> m_Colliders;

		rp3d::CollisionBody* m_CollisionBody = nullptr;

		uint32_t m_ID = 0;

		bool m_Sleep = false;

		bool m_Gravity = true;

		friend class PhysicsEngine;
		friend class EditorUI;
	};
}

