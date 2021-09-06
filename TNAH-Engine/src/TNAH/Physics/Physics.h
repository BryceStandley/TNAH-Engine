#pragma once
#pragma warning(push, 0)
#include <reactphysics3d/reactphysics3d.h>
#include "TNAH/Physics/PhysicsTimestep.h"
#include "TNAH/Scene/Components/Components.h"
#pragma warning(pop)

namespace tnah
{
    class PhysicsManager : public RefCounted
    {
    public:
        PhysicsManager();
        ~PhysicsManager();
        bool Initialise(rp3d::EventListener * collisionEventListener);
        void OnFixedUpdate(PhysicsTimestep timestep);
        void Destroy();
        rp3d::RigidBody* CreateRigidBody(const TransformComponent& transform);
        void DestroyRigidBody(rp3d::RigidBody* rigidBody);
        rp3d::CollisionBody* CreateCollisionBody(const TransformComponent& transform);
        void DestroyCollisionBody(rp3d::CollisionBody * body);
    
    private:
        rp3d::PhysicsCommon m_PhysicsCommon;
        rp3d::PhysicsWorld* m_PhysicsWorld = nullptr;
        rp3d::DefaultLogger* m_PhysicsLogger = nullptr;
        bool m_Active = false;
        friend class Physics;
    };
    
    class Physics
    {
    public:
        static Ref<PhysicsManager> GetManager();
        
        static bool Initialise(rp3d::EventListener * collisionEventListener);
        static void OnFixedUpdate(PhysicsTimestep timestep);
        static void Destroy();
        static rp3d::CollisionBody* CreateCollisionBody(const TransformComponent& transformValues);
        static void DestroyCollisionBody(rp3d::CollisionBody * body);

    private:
        static void PhysicsLoggerInit();
        static Ref<PhysicsManager> m_PhysicsCollision;
    };

    
}