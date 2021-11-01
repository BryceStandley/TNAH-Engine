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
        RigidBody(TransformComponent& transform, BodyMass mass);

        static Ref<RigidBody> Create(TransformComponent& transform, BodyMass mass);

        void OnUpdate(TransformComponent& transform);

        BodyMass GetBodyMass() const { return bodyMass; }

        void AddForce(const glm::vec3& force);
        void AddTorque(const glm::vec3& torque);

        void SetCollisionBody(rp3d::CollisionBody* collisionBody) { CollisionBody = collisionBody; }
        rp3d::CollisionBody* GetCollisionBody() const { return CollisionBody; }

        void AddCollider(Ref<Collider> collider);
    	std::unordered_map<uint32_t, Ref<Collider>> GetColliders() { return Colliders; }

    	bool HasColliders() const { return TotalColliders > 0 ? true : false; }
    	
        void UpdateBodyProperties();

        uint32_t GetID() const { return ID; }

        InertiaTensor GetInertiaTensor() const { return InertiaTensor; }
        void RecalculateWorldInertiaTensor();
    	
        LinearVelocity GetLinearVelocity() const { return linearVelocity; }
        AngularVelocity GetAngularVelocity() const { return angularVelocity; }
        std::pair<LinearVelocity, AngularVelocity> GetVelocities() { return {linearVelocity, angularVelocity}; }
    	

        void ApplyCollisionImpulse(const glm::vec3& linearVelocity, const glm::vec3& angularVelocity);

        void ResetValues();

    	void SetLinearDampening(float value) {LinearDampening.Dampening = glm::clamp(value, 0.0f, 1.0f);}
    	void SetAngularDampening(float value) {AngularDampening.Dampening = glm::clamp(value, 0.0f, 1.0f);}

        glm::vec3 CalculateLocalInertiaTensor();

    	rp3d::CollisionBody* CollisionBody = nullptr;
    private:

    	glm::vec3 CalculateCentreOfMass();

        void SetID(const uint32_t id) { ID = id; }
        
    
    private:

        /**
        * @var BodyMass
        *
        * @brief The BodyMass of the Rigidbody. This is the combined total for the whole Rigidbody with all of its Colliders.
        */
        BodyMass bodyMass;

        /**
        * @var LinearVelocity
        *
        * @brief The current LinearVelocity of the Rigidbody.
        */
        LinearVelocity linearVelocity;
    	
        AngularVelocity angularVelocity;
    	
        LinearVelocity ConstrainedLinearVelocity;
    	
        AngularVelocity ConstrainedAngularVelocity;

        Force Force;
    	
        Torque Torque;

        LinearDampening LinearDampening;
    	
        AngularDampening AngularDampening;
    	
        InertiaTensor InertiaTensor;
    	
        std::unordered_map<uint32_t, Ref<Collider>> Colliders;

    	uint32_t TotalColliders = 0;

    	/**
    	 * @var ID
    	 * 
    	 * @brief The global ID of the RigidBody.
    	 */
        uint32_t ID = 0;

    	glm::vec3 centralPosition = {0,0,0};
    	glm::quat Orientation = {0,0,0,0};

        friend class PhysicsEngine;
        friend class EditorUI;
    };
}
