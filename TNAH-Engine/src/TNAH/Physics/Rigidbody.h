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
    	
        std::pair<glm::vec3, glm::vec3> GetVelocities() { return {linearVelocity, angularVelocity}; }

        void ResetValues();

        glm::vec3 CalculateLocalInertiaTensor();

    	rp3d::CollisionBody* CollisionBody = nullptr;

    	glm::vec3 CalculateCentreOfMass();

        void SetID(const uint32_t id) { ID = id; }
    	
        BodyMass bodyMass;
    	
        glm::vec3 linearVelocity;
    	
        glm::vec3 angularVelocity;

        glm::vec3 Force;
    	
        glm::vec3 Torque;
    	
        InertiaTensor inertiaTensor;
    	
        std::unordered_map<uint32_t, Ref<Collider>> Colliders;

    	uint32_t TotalColliders = 0;
    	
        uint32_t ID = 0;

    	glm::vec3 centralPosition = {0,0,0};
    	glm::quat Orientation = {0,0,0,0};
    };
}
