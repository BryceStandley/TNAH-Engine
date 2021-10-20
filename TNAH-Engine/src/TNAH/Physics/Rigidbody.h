#pragma once

#include "PhysicsStructures.h"
#include <reactphysics3d/reactphysics3d.h>
#include "Collider.h"

namespace tnah::Physics {
    
    class RigidBody : public RefCounted
    {
    public:
        RigidBody();
        RigidBody(BodyMass mass, BodyType type = BodyType::Dynamic);

        static Ref<RigidBody> Create(BodyMass mass, BodyType type = BodyType::Dynamic);

        void OnUpdate(TransformComponent& transform);

        BodyMass GetBodyMass() const { return m_BodyMass; }

        void AddForce(const glm::vec3& force);
        void AddTorque(const glm::vec3& torque);

        void SetCollisionBody(rp3d::CollisionBody* collisionBody) { m_CollisionBody = collisionBody; }
        rp3d::CollisionBody* GetCollisionBody() const { return m_CollisionBody; }

        void AddCollider(Ref<Collider> collider);

        uint32_t GetID() const { return m_ID; }

        void SetType(const BodyType& type) { m_BodyType = type; }
        BodyType GetType() const { return m_BodyType; }

        InertiaTensor GetInertiaTensor() const { return m_InertiaTensor; }

        LinearVelocity GetLinearVelocity() const { return m_LinearVelocity; }
        AngularVelocity GetAngularVelocity() const { return m_AngularVelocity; }
        std::pair<LinearVelocity, AngularVelocity> GetVelocities() { return {m_LinearVelocity, m_AngularVelocity}; }

        void ApplyCollisionImpulse(const glm::vec3& linearVelocity, const glm::vec3& angularVelocity);

        void ResetValues();

        bool& IgnoreGravity() { return m_IgnoreGravity; }
        bool IsSleeping() const { return m_IsSleeping; }
        void Awake() { m_IsSleeping = false; }
        void Sleep() { m_IsSleeping = true; }

        static glm::mat3 CalculateInertiaTensor(Ref<Collider> collider, BodyMass colliderMass);
        static glm::mat3 CalculateInertiaTensor(rp3d::CollisionShape* collider, BodyMass colliderMass, Collider::Type type);

    private:

        void Setup();

        void UpdatePhysicsInformation();

        

        void UpdateInertiaTensor(TransformComponent& transform);

        void SetID(const uint32_t id) { m_ID = id; }
        
    
    private:

        /**
         * @var m_BodyType
         *
         * @brief The type of the Rigidbody. Either Dynamic or static. 
         */
        BodyType m_BodyType;

        /**
        * @var m_BodyMass
        *
        * @brief The BodyMass of the Rigidbody. This is the combined total for the whole Rigidbody with all of its Colliders.
        */
        BodyMass m_BodyMass;

        /**
        * @var m_LinearVelocity
        *
        * @brief The current LinearVelocity of the Rigidbody.
        */
        LinearVelocity m_LinearVelocity;

        /**
        * @var m_AngularVelocity
        *
        * @brief The current AngularVelocity of the Rigidbody.
        */
        AngularVelocity m_AngularVelocity;

        /**
        * @var m_Force
        *
        * @brief Current forces applied to the Rigidbody. These are used and zeroed out every PhysicsSystem::OnUpdate().
        */
        Force m_Force;

        /**
        * @var m_Torque
        *
        * @brief Current torques applied to the Rigidbody. These are used and zeroed out every PhysicsSystem::OnUpdate().
        */
        Torque m_Torque;

        /**
        * @var m_LinearDampening
        *
        * @brief The LinearDampening of the Rigidbody. Values of 0 disable dampening and values of 1 enable full dampening.
        */
        LinearDampening m_LinearDampening;

        /**
        * @var m_AngularDampening
        *
        * @brief The AngularDampening of the Rigidbody. Values of 0 disable dampening and values of 1 enable full dampening.
        */
        AngularDampening m_AngularDampening;

        /**
        * @var m_InertiaTensor
        *
        * @brief The InertiaTensor of the Rigidbody.
        */
        InertiaTensor m_InertiaTensor;

        /**
        * @var m_LocalInertiaTensor
        *
        * @brief The Local InertiaTensor of the Rigidbody.
        */
        InertiaTensor m_LocalInertiaTensor;
        
        /**
        * @var m_Colliders
        *
        * @brief A vector of all colliders on the Rigidbody
        */
        std::vector<Ref<Collider>> m_Colliders;

        /**
        * @var m_CollisionBody
        *
        * @brief The Reactphysics3d Collision body used by the Rigidbody to interact and move within the PhysicsWorld.
        */
        rp3d::CollisionBody* m_CollisionBody = nullptr;

        uint32_t m_ID = 0;

        bool m_IsSleeping = false;

        bool m_IgnoreGravity = false;

        friend class PhysicsEngine;
        friend class EditorUI;
    };
}
