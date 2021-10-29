#pragma once

#include "PhysicsStructures.h"
#include <reactphysics3d/reactphysics3d.h>
#include "Collider.h"
#include "TNAH/Scene/Components/Components.h"

namespace tnah::Physics {
    
    class RigidBody : public RefCounted
    {
    public:
        RigidBody();
        RigidBody(TransformComponent& transform, BodyMass mass, BodyType type = BodyType::Dynamic);

        static Ref<RigidBody> Create(TransformComponent& transform, BodyMass mass, BodyType type = BodyType::Dynamic);

        void OnUpdate(TransformComponent& transform);

        BodyMass GetBodyMass() const { return m_BodyMass; }

        void AddForce(const glm::vec3& force);
        void AddTorque(const glm::vec3& torque);

        void SetCollisionBody(rp3d::CollisionBody* collisionBody) { m_CollisionBody = collisionBody; }
        rp3d::CollisionBody* GetCollisionBody() const { return m_CollisionBody; }

        void AddCollider(Ref<Collider> collider);
    	std::unordered_map<uint32_t, Ref<Collider>> GetColliders() { return m_Colliders; }

    	bool HasColliders() const { return m_TotalColliders > 0 ? true : false; }
        
        /**
         * @fn tnah::Physics::RigidBody::UpdateBodyProperties()
         * 
         * @brief Updates and recalculates the Local properties of the RigidBody based on its colliders attached.
         *	This overrides any values set. To modify the properties of the body,
         *	address the tnah::Physics::Collider objects directly with RigidBody::GetColliders()
         *
         * @author Bryce Standley
         * @date Monday, 25 October 2021
         * 
         */
        void UpdateBodyProperties();

        uint32_t GetID() const { return m_ID; }

        void SetType(const BodyType& type) { m_BodyType = type; }
        BodyType GetType() const { return m_BodyType; }

        InertiaTensor GetInertiaTensor() const { return m_InertiaTensor; }
        void RecalculateWorldInertiaTensor();
    	
        LinearVelocity GetLinearVelocity() const { return m_LinearVelocity; }
        AngularVelocity GetAngularVelocity() const { return m_AngularVelocity; }
        std::pair<LinearVelocity, AngularVelocity> GetVelocities() { return {m_LinearVelocity, m_AngularVelocity}; }

        void SetLinearRotationalLockFactor(const glm::ivec3& lock) { m_LinearRotationLock = lock; }
        void SetAngularRotationalLockFactor(const glm::ivec3& lock) { m_AngularRotationLock = lock; }

        glm::vec3& GetLinearRotationalLockFactor() { return m_LinearRotationLock; }
        glm::vec3& GetAngularRotationalLockFactor() { return m_AngularRotationLock; }

        void ApplyCollisionImpulse(const glm::vec3& linearVelocity, const glm::vec3& angularVelocity);

        void ResetValues();

        bool& IgnoreGravity() { return m_IgnoreGravity; }
        bool IsSleeping() const { return m_IsSleeping; }
        void Awake() { m_IsSleeping = false; }
        void Sleep();

    	void SetLinearDampening(float value) {m_LinearDampening.Dampening = glm::clamp(value, 0.0f, 1.0f);}
    	void SetAngularDampening(float value) {m_AngularDampening.Dampening = glm::clamp(value, 0.0f, 1.0f);}

        glm::vec3 CalculateLocalInertiaTensor();
    	/**
    	* @var m_CollisionBody
    	*
    	* @brief The Reactphysics3d Collision body used by the Rigidbody to interact and move within the PhysicsWorld.
    	*/
    	rp3d::CollisionBody* m_CollisionBody = nullptr;
    private:

    	glm::vec3 CalculateCentreOfMass();

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
        * @var m_ConstrainedLinearVelocity
        *
        * @brief The current Constrained LinearVelocity of the Rigidbody.
        */
        LinearVelocity m_ConstrainedLinearVelocity;

        /**
        * @var m_ConstrainedAngularVelocity
        *
        * @brief The current Constrained AngularVelocity of the Rigidbody.
        */
        AngularVelocity m_ConstrainedAngularVelocity;

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
        * @brief The InertiaTensor of the Rigidbody with both world and local space data.
        */
        InertiaTensor m_InertiaTensor;
        
        /**
        * @var m_Colliders
        *
        * @brief A vector of all colliders on the Rigidbody
        */
        std::unordered_map<uint32_t, Ref<Collider>> m_Colliders;

    	uint32_t m_TotalColliders = 0;

    	/**
    	 * @var m_ID
    	 * 
    	 * @brief The global ID of the RigidBody.
    	 */
        uint32_t m_ID = 0;

        /**
         * @var m_LinearRotationLock
         *
         * @brief Rotational lock factor for linear velocities. 1 is enabled, 0 is disabled per axis.
         */
        glm::vec3 m_LinearRotationLock = {1,1,1};

        /**
        * @var m_AngularRotationLock
        *
        * @brief Rotational lock factor for angular velocities. 1 is enabled, 0 is disabled per axis.
        */
        glm::vec3 m_AngularRotationLock = {1,1,1};

    	glm::vec3 m_Position = {0,0,0};
    	glm::quat m_Orientation = {0,0,0,0};

    	/**
    	 * @var m_IsSleeping
    	 *
    	 * @brief A flag to note if the RigidBody is currently sleeping thus not being simulated.
    	 */
        bool m_IsSleeping = false;

    	float m_SleepVelocityThreshold = 0.2f;

    	float m_SleepTimeThreshold = 1.0f;

    	float m_SleepTimeAccumulator = 0.0f;

    	/**
    	* @var m_IgnoreGravity
    	*
    	* @brief A flag to note if the RigidBody should ignore gravity within the world.
    	*/
        bool m_IgnoreGravity = false;

        friend class PhysicsEngine;
        friend class EditorUI;
    };
}
