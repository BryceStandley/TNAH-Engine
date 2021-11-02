#pragma once
#pragma warning(push, 0)
#include <reactphysics3d/reactphysics3d.h>

#pragma warning(pop)

#include <entt.hpp>
#include <queue>
#include "PhysicsCollision.h"
#include "PhysicsStructures.h"
#include "Rigidbody.h"
#include "TNAH/Physics/PhysicsTimestep.h"
#include "TNAH/Scene/Components/Components.h"
#include "TNAH/Scene/Components/PhysicsComponents.h"
#include "Rigidbody.h"
#include "TNAH/Core/Timestep.h"
#include "TNAH/Scene/Components/PhysicsComponents.h"

#include "TNAH/Scene/Components/PhysicsComponents.h"

namespace tnah {
    struct RigidBodyComponent;
    class Renderer;
 class GameObject;
}

namespace tnah::Physics
{
    
    class PhysicsManager : public RefCounted
    {
    public:

        PhysicsManager();

        ~PhysicsManager();
    
    private:

        bool Initialise(rp3d::EventListener * collisionEventListener);
     
        void OnFixedUpdate(float deltaTime) const;

        void Destroy();
     
        rp3d::RigidBody* CreateRigidBody(const TransformComponent& transform) const;
     
        void DestroyRigidBody(rp3d::CollisionBody* rigidBody) const;
     
        rp3d::CollisionBody* CreateCollisionBody(const TransformComponent& transform) const;
     
        void DestroyCollisionBody(rp3d::CollisionBody * body) const;
     
        void CreateColliderRenderer();

   
    
    private:
        rp3d::PhysicsCommon PhysicsCommon;
     
        rp3d::PhysicsWorld* PhysicsWorld = nullptr;
     
        rp3d::DefaultLogger* PhysicsLogger = nullptr;
        
        bool ColliderRender = false;
        
      bool ColliderRendererInit = false;
     
      Ref<VertexArray> LinesVertexArray;
        
   Ref<VertexBuffer> LinesVertexBuffer;
        
   Ref<VertexArray> TriangleVertexArray;
        
   Ref<VertexBuffer> TriangleVertexBuffer;
        
   Ref<Shader> Shader;
        
   VertexBufferLayout ColliderLayout;
        
   bool Active = false;
        
   bool Logging = false;

     std::unordered_map<uint32_t, Ref<RigidBody>> Rigidbodies;

     uint32_t TotalRigidbodies = 0;

     std::unordered_map<uint32_t, Ref<Collider>> Colliders;

     uint32_t TotalColliders = 0;
        
        friend class PhysicsEngine;
};
    
    class PhysicsEngine
    {
    public:
        
        static Ref<PhysicsManager> GetManager();

        static void AddCollision(CollisionData &collision);
        
        static bool IsActive();
        
        static bool Initialise(rp3d::EventListener * collisionEventListener);
        
        static void OnFixedUpdate(float deltaTime, entt::registry& componentRegistry);
     
        static void OnUpdate();
     
        static void Destroy();
     
        static void DestroyRigidbody(Ref<RigidBody> rigidbody);
     
        static Ref<RigidBody> CreateRigidbody(GameObject& gameObject);
     
        static void ToggleColliderRendering();
     
        static bool& GetColliderRendererHandle();
     
        static TransformComponent GetColliderRendererTransform();
     
        static Ref<Collider> CreateBoxCollider(Ref<RigidBody> rigidbody, const glm::vec3& halfExtents);
     
        static Ref<Collider> CreateSphereCollider(Ref<RigidBody> rigidbody, const float& radius);

        static Ref<Collider> CreateCapsuleCollider(Ref<RigidBody> rigidbody, const float& radius, const float& height);
    
    private:
     
        static void EnableLogging();
     
        static bool IsColliderRenderingEnabled();
     
        static std::pair<std::pair<Ref<VertexArray>, Ref<VertexBuffer>>, std::pair<Ref<VertexArray>, Ref<VertexBuffer>>> GetColliderRenderObjects();
     
        static Ref<Shader> GetColliderShader();
     
        static void UpdateColliderRenderer();
     
        static rp3d::DebugRenderer* GetColliderRenderer();

        static void PhysicsLoggerInit();

         static void Collisions();
         static void Velocities(const float& deltaTime, RigidBodyComponent& rb, TransformComponent& transform);
         static void Positions(const float& deltaTime, RigidBodyComponent& rb, TransformComponent& transform);
         static void ForcesAndTorques(RigidBodyComponent& rb, TransformComponent& transform);
         static void InertiaTensors(RigidBodyComponent& rb, TransformComponent& transform);
         static void UpdateRbs(RigidBodyComponent& rb, TransformComponent& transform);
    
    private:
     
        static Ref<PhysicsManager> physicsManager;
     
        static TransformComponent ColliderTransform;
        inline static std::queue<CollisionData> collisions = std::queue<CollisionData>();

     friend class tnah::Scene;
     friend class tnah::Renderer;
    };
    

}
