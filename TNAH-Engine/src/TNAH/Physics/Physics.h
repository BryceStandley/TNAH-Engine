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
        void OnFixedUpdate(PhysicsTimestep timestep) const;
        void Destroy();
        rp3d::RigidBody* CreateRigidBody(const TransformComponent& transform) const;
        void DestroyRigidBody(rp3d::RigidBody* rigidBody) const;
        rp3d::CollisionBody* CreateCollisionBody(const TransformComponent& transform) const;
        void DestroyCollisionBody(rp3d::CollisionBody * body) const;
    
    private:
        void CreateColliderRenderer();
        
        rp3d::PhysicsCommon m_PhysicsCommon;
        rp3d::PhysicsWorld* m_PhysicsWorld = nullptr;
        rp3d::DefaultLogger* m_PhysicsLogger = nullptr;

        bool m_ColliderRender = false;
        bool m_ColliderRendererInit = false;
        Ref<VertexArray> m_LinesVertexArray;
        Ref<VertexBuffer> m_LinesVertexBuffer;
        
        Ref<VertexArray> m_TriangleVertexArray;
        Ref<VertexBuffer> m_TriangleVertexBuffer;
        
        Ref<Shader> m_Shader;
        VertexBufferLayout m_ColliderLayout;
        
        bool m_Active = false;
        /** @brief Used to tell the physics system if the logging should be enabled*/
        bool m_Logging = false;
        friend class Physics;
    };
    
    class Physics
    {
    public:
        static Ref<PhysicsManager> GetManager();

        static bool IsActive();
        
        static bool Initialise(rp3d::EventListener * collisionEventListener);
        static void OnFixedUpdate(PhysicsTimestep timestep);
        static void Destroy();
        static rp3d::CollisionBody* CreateCollisionBody(const TransformComponent& transformValues);
        static void DestroyCollisionBody(rp3d::CollisionBody * body);
        static void DestroyRigidbody(rp3d::RigidBody* body);
        static rp3d::RigidBody* CreateRigidbody(const TransformComponent& transform);
        static rp3d::RigidBody* CreateRigidbody(const rp3d::Transform transform);
        static rp3d::RigidBody* CreateRigidbody(const glm::vec3& position, const glm::vec3& rotation);

        static void ToggleColliderRendering();
        

        // could use the Transform component and half each of its values?
        static rp3d::BoxShape* CreateBoxShape(const float& halfX, const float& halfY, const float& halfZ);
        static rp3d::BoxShape* CreateBoxShape(const glm::vec3& halfExtents);
        static rp3d::BoxShape* CreateBoxShape(const rp3d::Vector3& halfExtents);
        static rp3d::SphereShape* CreateSphereShape(const float& radius);
        static rp3d::CapsuleShape* CreateCapsuleShape(const float& radius, const float& height);
        static rp3d::HeightFieldShape* CreateHeightFieldShape(const int& columns, const int& rows, const float& minHeight, const float& maxHeight, const float* terrainColliderHeightData);

        static rp3d::PolyhedronMesh* CreatePolyhedronMesh(rp3d::PolygonVertexArray* polygonVertexArray);
        static rp3d::ConvexMeshShape* CreateConvexMeshShape(rp3d::PolyhedronMesh* polyhedronMesh);
        static rp3d::ConcaveMeshShape* CreateConcaveMeshShape(rp3d::TriangleMesh* triangleMesh);
        static rp3d::TriangleMesh* CreateTriangleMesh();

        void CreateTerrainCollider(tnah::Terrain* terrain);
    
    private:
        static void EnableLogging();
        
        static bool IsColliderRenderingEnabled();
        static std::pair<std::pair<Ref<VertexArray>, Ref<VertexBuffer>>, std::pair<Ref<VertexArray>, Ref<VertexBuffer>>> GetColliderRenderObjects();
        static Ref<Shader> GetColliderShader();
        static void UpdateColliderRenderer();
        static rp3d::DebugRenderer* GetColliderRenderer();
        static void PhysicsLoggerInit();
    
    private:
        static Ref<PhysicsManager> m_PhysicsManager;

        friend class Scene;
        friend class Renderer;
    };

    
}