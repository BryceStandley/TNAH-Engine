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
        tnah::Terrain* gameTerrain;
        bool m_Active = false;
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


        // could use the Transform component and half each of its values?
        static rp3d::BoxShape* CreateBoxShape(const rp3d::Vector3& halfExtents);
        static rp3d::SphereShape* CreateSphereShape(const float& radius);
        static rp3d::CapsuleShape* CreateCapsuleShape(const float& radius, const float& height);
        static rp3d::HeightFieldShape* CreateHeightFieldShape(const int& columns, const int& rows, const float& minHeight, const float& maxHeight, const float* terrainColliderHeightData, rp3d::HeightFieldShape::HeightDataType& heightDataType);

        static rp3d::PolyhedronMesh* CreatePolyhedronMesh(rp3d::PolygonVertexArray* polygonVertexArray);
        static rp3d::ConvexMeshShape* CreateConvexMeshShape(rp3d::PolyhedronMesh* polyhedronMesh);
        static rp3d::ConcaveMeshShape* CreateConcaveMeshShape(rp3d::TriangleMesh* triangleMesh);
        static rp3d::TriangleMesh* CreateTriangleMesh();

        void CreateTerrainCollider(tnah::Terrain* terrain);
    
    private:
        static void PhysicsLoggerInit();
    
    private:
        static Ref<PhysicsManager> m_PhysicsManager;
    };

    
}