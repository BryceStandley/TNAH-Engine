#pragma once
#include "TNAH/Physics/RigidBody.h"
namespace tnah
{
    class PhysicsAPI
    {
        enum API
        {
            none = 0, tnah = 1, react = 2
        };
    
    public:
        
        enum Collider
        {
            box = 0, sphere = 1, capsule = 2, heightmap = 3, concaveMesh = 4, convexMesh = 5
        };
        
        virtual ~PhysicsAPI() = default;
        //Creates the physics API
        static Scope<PhysicsAPI> Create();
        //Updates the rigidbodies, applying all the new values
        virtual void OnFixedUpdate() = 0;

        //Creates a new rigidbody
        virtual Ref<RigidBody> CreateRigidBody(const TransformComponent& transform) = 0;

        //Creates a collider of type collider
        virtual void CreateCollider(PhysicsAPI::Collider collider, Ref<RigidBody> rb) = 0;
        
        virtual void CreateBoxShape(const glm::vec3& halfValues, Ref<RigidBody> rb) = 0;

        virtual void CreateSphereShape(const float& radius, Ref<RigidBody> rb) = 0;

        virtual void CreateCapsuleShape(const float& radius, const float& height, Ref<RigidBody> rb) = 0;

        virtual void CreateTerrainCollider(tnah::Terrain* terrain) = 0;
        
    private:
        static API p_Api;
    };
}
