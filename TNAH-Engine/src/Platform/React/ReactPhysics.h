#pragma once
#include "TNAH/Physics/PhysicsAPI.h"
#pragma warning(push, 0)
#include <reactphysics3d/reactphysics3d.h>
#pragma warning(pop)
#include<unordered_map>

namespace tnah
{
    class ReactPhysics : public PhysicsAPI
    {
    public:
        ~ReactPhysics() override;
        
        void OnFixedUpdate() override;
        
        Ref<RigidBody> CreateRigidBody(const TransformComponent& transform) override;
        
        void CreateBoxShape(const glm::vec3& halfValues, Ref<RigidBody> rb) override;

        void CreateSphereShape(const float& radius, Ref<RigidBody> rb) override;

        void CreateCapsuleShape(const float& radius, const float& height, Ref<RigidBody> rb) override;

        //static void CreateHeightFieldShape(const int& columns, const int& rows, const float& minHeight, const float& maxHeight, const float* terrainColliderHeightData);

        //static void CreatePolyhedronMesh(rp3d::PolygonVertexArray* polygonVertexArray);

        //static void CreateConvexMeshShape(rp3d::PolyhedronMesh* polyhedronMesh);

        //static void CreateConcaveMeshShape(rp3d::TriangleMesh* triangleMesh);

        //static void CreateTriangleMesh();

        void CreateTerrainCollider(tnah::Terrain* terrain) override;
    private:
        
        struct ReactRigidBody
        {
            ReactRigidBody()
            {
                m_RigidBody = nullptr;
                m_Body = nullptr;
            }
            ReactRigidBody(tnah::Ref<tnah::RigidBody> universal, rp3d::RigidBody * body)
            {
                m_RigidBody = universal;
                m_Body = body;
            }
            
            tnah::Ref<tnah::RigidBody> m_RigidBody;
            rp3d::RigidBody * m_Body;
            std::vector<rp3d::CollisionBody*> m_CollisionBodies;
        };
        
        void UpdateRigidBodies();
        
        std::unordered_map<unsigned int, ReactRigidBody> m_RigidBody;
        unsigned int uniqueIds = 1;
        rp3d::PhysicsCommon m_PhysicsCommon;
        rp3d::PhysicsWorld* m_PhysicsWorld = nullptr;
    };
}
