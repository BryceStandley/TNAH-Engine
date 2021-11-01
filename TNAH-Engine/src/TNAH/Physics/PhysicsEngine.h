#pragma once
#pragma warning(push, 0)
#include <reactphysics3d/reactphysics3d.h>

#pragma warning(pop)

#include <entt.hpp>

#include "CollisionDetectionEngine.h"
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
 
 /**
     * @class	PhysicsManager
     *
     * @brief	Manager for physics that inherits from the RefCounted class. This class is to remain private and contain
     * all ReactPhysics3D world objects. Any control of the PhysicsManager should be done from tnah::Physics::PhysicsEngine
     *
     * @author	Chris Logan
     * @date	11/09/2021
     */

    class PhysicsManager : public RefCounted
    {
    public:

        PhysicsManager();

        ~PhysicsManager();

     Ref<CollisionDetectionEngine>& GetCollisionDetectionEngine() { return CollisionDetectionEngine; }
    
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
     
        /** @brief	True to collider render */
        bool ColliderRender = false;
     
     /** @brief	True if the collider renderer has been initialized */
      bool ColliderRendererInit = false;
     
      Ref<VertexArray> LinesVertexArray;
     
   /** @brief	Pointer to the buffer for lines vertex data */
   Ref<VertexBuffer> LinesVertexBuffer;

   /** @brief	Pointer to array for triangle vertex data */
   Ref<VertexArray> TriangleVertexArray;

   /** @brief	Pointer to Buffer for triangle vertex data */
   Ref<VertexBuffer> TriangleVertexBuffer;

   /** @brief	Shader used for the collider renderer */
   Ref<Shader> Shader;

   /** @brief	Layout of the collider renderer vertex buffers */
   VertexBufferLayout ColliderLayout;

   /** @brief	True to active */
   bool Active = false;

   /** @brief Used to tell the physics system if the logging should be enabled*/
   bool Logging = false;

     std::unordered_map<uint32_t, Ref<RigidBody>> Rigidbodies;

     uint32_t TotalRigidbodies = 0;

     std::unordered_map<uint32_t, Ref<Collider>> Colliders;

     uint32_t TotalColliders = 0;

     /** @brief a static reference to the active Collision Detection Engine */
     static Ref<CollisionDetectionEngine> CollisionDetectionEngine;

        friend class PhysicsEngine;
};
    
    class PhysicsEngine
    {
    public:
        
        static Ref<PhysicsManager> GetManager();
        
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

     friend class tnah::Scene;
     friend class tnah::Renderer;
    };
    

}
