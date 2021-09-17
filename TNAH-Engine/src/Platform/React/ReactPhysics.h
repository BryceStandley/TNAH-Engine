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
        ReactPhysics();
        ~ReactPhysics() override;
        void Init() override;
        void Destroy() override;

        bool& GetColliderRendererHandle() override;

        inline TransformComponent GetColliderRendererTransform() override {return m_ColliderTransform;}
        
        void OnFixedUpdate(PhysicsTimestep timestep) override;
        
        Ref<RigidBody> CreateRigidBody(const TransformComponent& transform) override;
        
        void CreateBoxShape(const glm::vec3& halfValues, Ref<RigidBody> rb) override;

        void CreateSphereShape(const float& radius, Ref<RigidBody> rb) override;

        void CreateCapsuleShape(const float& radius, const float& height, Ref<RigidBody> rb) override;

        void CreateTerrainCollider(tnah::Terrain* terrain) override;

        std::pair<std::pair<Ref<VertexArray>, Ref<VertexBuffer>>, std::pair<Ref<VertexArray>, Ref<VertexBuffer>>> GetColliderRenderObjects() override;

        bool IsColliderRenderingEnabled() override;

        void EnableLogging() override;

        Ref<Shader> GetColliderShader() override;

        void CreateColliderRenderer() override;
        //static void CreateHeightFieldShape(const int& columns, const int& rows, const float& minHeight, const float& maxHeight, const float* terrainColliderHeightData);

        //static void CreatePolyhedronMesh(rp3d::PolygonVertexArray* polygonVertexArray);

        //static void CreateConvexMeshShape(rp3d::PolyhedronMesh* polyhedronMesh);

        //static void CreateConcaveMeshShape(rp3d::TriangleMesh* triangleMesh);

        //static void CreateTriangleMesh();

        inline int GetLines() override
        {
            return m_PhysicsWorld->getDebugRenderer().getNbLines();
        }
        
        inline  int GetTriangles() override
        {
            return m_PhysicsWorld->getDebugRenderer().getNbTriangles();
        }
        

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
            std::unordered_map<unsigned int, rp3d::CollisionBody*> m_CollisionBodies;
        private:
            unsigned int colliderIds = 0;
        };
        
        void UpdateRigidBodies();
        void TollgeColliderRendering();
        void UpdateColliderRenderer();
        void PhysicsLoggerInit();
        
        std::unordered_map<unsigned int, ReactRigidBody> m_RigidBody;
        unsigned int uniqueIds = 1;
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
        TransformComponent m_ColliderTransform;
        bool m_Logging = false;
    };
}
