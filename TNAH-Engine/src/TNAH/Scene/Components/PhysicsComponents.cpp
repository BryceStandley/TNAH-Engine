#include <tnahpch.h>
#include "PhysicsComponents.h"

namespace tnah
{
    CapsuleColliderComponent::CapsuleColliderComponent()
    {
        Collider = Physics::CreateCapsuleShape(Radius, Height);
    }

    CapsuleColliderComponent::CapsuleColliderComponent(const float& radius, const float& height)
        :Radius(radius), Height(height)
    {
        Collider = Physics::CreateCapsuleShape(Radius, Height);
    }





    
    MeshColliderComponent::MeshColliderComponent()
    {} // Maybe add something here to check and see if the gameobject the component is on
    // has a mesh and create one with out passing in values

    MeshColliderComponent::MeshColliderComponent(const MeshColliderComponent& other)
    {}

    MeshColliderComponent::MeshColliderComponent(const Mesh& mesh)
    {
        MeshVertexPositions = mesh.GetVertexPositions();
        MeshIndices = mesh.GetIndices();
        
        if(Physics::IsActive())
        {
            auto manager = Physics::GetManager();
            switch (ColliderType)
            {
            case ShapeType::Convex:
                {
                    CreateConvexPolygonArray();
                    m_PolyhedronMesh = Physics::CreatePolyhedronMesh(m_PolygonVertexArray);
                    m_ConvexCollider = Physics::CreateConvexMeshShape(m_PolyhedronMesh);
                    break;
                }
            case ShapeType::Concave:
                {
                    CreateTriangleVertexArray();
                    m_TriangleMesh = Physics::CreateTriangleMesh();
                    m_TriangleMesh->addSubpart(m_TriangleVertexArray);
                    m_ConcaveCollider = Physics::CreateConcaveMeshShape(m_TriangleMesh);
                    break;
                }
            default: break;
            }
        }
    }

    void MeshColliderComponent::CreateConvexPolygonArray()
    {
        m_PolygonFace = new rp3d::PolygonVertexArray::PolygonFace[MeshIndices.size()];
        rp3d::PolygonVertexArray::PolygonFace* face = m_PolygonFace;
        for(uint32_t i = 0; i < MeshIndices.size(); i++)
        {
            face->indexBase = i * 3;
            face->nbVertices = 3;
            face++;
        }


        m_PolygonVertexArray =
            new rp3d::PolygonVertexArray(MeshVertexPositions.size(),
                &MeshVertexPositions[0],
                sizeof(glm::vec3), &MeshIndices[0], sizeof(uint32_t),
                MeshIndices.size(), m_PolygonFace,
                rp3d::PolygonVertexArray::VertexDataType::VERTEX_FLOAT_TYPE,
                rp3d::PolygonVertexArray::IndexDataType::INDEX_INTEGER_TYPE);
    }

    void MeshColliderComponent::CreateTriangleVertexArray()
    {
        m_TriangleVertexArray =
            new rp3d::TriangleVertexArray(MeshVertexPositions.size(),
            &MeshVertexPositions[0], sizeof(glm::vec3),
                      MeshIndices.size() / 3, &MeshIndices[0], 3 * sizeof(uint32_t),
                      rp3d::TriangleVertexArray::VertexDataType::VERTEX_FLOAT_TYPE,
                      rp3d::TriangleVertexArray::IndexDataType::INDEX_INTEGER_TYPE);
        
    }
}
