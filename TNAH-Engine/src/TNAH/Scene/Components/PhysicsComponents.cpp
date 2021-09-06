#include <tnahpch.h>
#include "PhysicsComponents.h"

namespace tnah
{
    RigidBodyComponent::RigidBodyComponent()
    {
        if(Physics::IsActive())
        {
            m_Transform = Math::ToRp3dTransform({Position, Rotation, {1,1,1}});
            Body = Physics::CreateRigidbody(m_Transform);
        }
    }

    RigidBodyComponent::RigidBodyComponent(const glm::vec3& position, const glm::vec3& rotation)
        :Position(position), Rotation(rotation)
    {
        if(Physics::IsActive())
        {
            m_Transform = Math::ToRp3dTransform({Position, Rotation, {1,1,1}});
            Body = Physics::CreateRigidbody(m_Transform);
        }
    }

    RigidBodyComponent::RigidBodyComponent(const TransformComponent& transform)
        :Position(transform.Position), Rotation(transform.Rotation)
    {
        if(Physics::IsActive())
        {
            m_Transform = Math::ToRp3dTransform(transform);
            Body = Physics::CreateRigidbody(m_Transform);
        }
    }

    RigidBodyComponent::RigidBodyComponent(const rp3d::Transform& transform)
    {
        auto p = transform.getPosition();
        Position = {p.x, p.y, p.z};
        auto o = transform.getOrientation();
        Orientation = {o.x, o.y, o.z, o.w};
        m_Transform = transform;
        if(Physics::IsActive())
        {
            Body = Physics::CreateRigidbody(m_Transform);
        }
    }

    RigidBodyComponent::RigidBodyComponent(const rp3d::Vector3& position, const rp3d::Vector3& rotation)
    {
        Position = {position.x, position.y, position.z};
        Rotation = {rotation.x, rotation.y, rotation.z};
        if(Physics::IsActive())
        {
            m_Transform = Math::ToRp3dTransform({Position, Rotation, {1,1,1,}});
            Body = Physics::CreateRigidbody(m_Transform);
        }
    }

    RigidBodyComponent::RigidBodyComponent(const rp3d::Vector3& position, const rp3d::Quaternion orientation)
    {
        Position = {position.x, position.y, position.z};
        Orientation = {orientation.x, orientation.y, orientation.x, orientation.w};
        if(Physics::IsActive())
        {
            m_Transform = rp3d::Transform(position, orientation);
            Body = Physics::CreateRigidbody(m_Transform);
        }
    }

    void RigidBodyComponent::AddCollider(rp3d::CollisionShape* collider, const TransformComponent& transform) const
    {
        if(Physics::IsActive() && Body)
        {
            Body->addCollider(collider, Math::ToRp3dTransform(transform));
        }
    }

    void RigidBodyComponent::RemoveCollider(rp3d::Collider* collider)
    {
        if(Physics::IsActive() && Body)
        {
            Body->removeCollider(collider);
        }
    }

    void RigidBodyComponent::ApplyForce(const ForceType& forceType, const glm::vec3& direction, const glm::vec3& force, const glm::vec3& forcePoint) const
    {
        if(Physics::IsActive() && Body)
        {
            auto finalForce = direction * force;
            switch (forceType)
            {
            case ForceType::FromWorld:
                {
                    Body->applyForceAtWorldPosition(Math::ToRp3dVec3(finalForce), Math::ToRp3dVec3(forcePoint));
                    break;
                }
            case ForceType::FromLocal:
                {
                    Body->applyForceAtLocalPosition(Math::ToRp3dVec3(finalForce), Math::ToRp3dVec3(forcePoint));
                    break;
                }
            case ForceType::FromCentre:
                {
                    Body->applyForceToCenterOfMass(Math::ToRp3dVec3(finalForce));
                    break;
                }
            default: break;
            }
        }
    }

    void RigidBodyComponent::ApplyTorque(const glm::vec3& torque) const
    {
        if(Physics::IsActive() && Body)
        {
            Body->applyTorque(Math::ToRp3dVec3(torque));
        }
    }


    BoxColliderComponent::BoxColliderComponent()
    {
        if(Physics::IsActive())
        {
            // make each measurement of the box, half extents as react requires half
            Collider = Physics::CreateBoxShape(Size * 0.5f);
        }
    }

    BoxColliderComponent::BoxColliderComponent(const glm::vec3& size)
        :Size(size)
    {
        if(Physics::IsActive())
        {
            Collider = Physics::CreateBoxShape(Size * 0.5f);
        }
    }

    BoxColliderComponent::BoxColliderComponent(const rp3d::Vector3& size)
    {
        Size = {size.x, size.y, size.z};
        if(Physics::IsActive())
        {
            Collider = Physics::CreateBoxShape(Size * 0.5f);
        }
    }

    BoxColliderComponent::BoxColliderComponent(const float& x, const float& y, const float& z)
    {
        Size = {x, y, z};
        if(Physics::IsActive())
        {
            Collider = Physics::CreateBoxShape(Size * 0.5f);
        }
    }

    HeightFieldColliderComponent::HeightFieldColliderComponent()
    {
        if(Physics::IsActive())
        {
            HeightData.resize(TotalColumns * TotalRows);
            for(uint32_t x = 0; x < TotalColumns; x++)
            {
                for(uint32_t z = 0; z < TotalRows; z++)
                {
                    float val = Math::Random(0,1);
                    if(val > MaxHeight) MaxHeight = val;
                    if(val < MinHeight) MinHeight = val;
                    HeightData.push_back(val);
                }
            }
            
            Collider = Physics::CreateHeightFieldShape(TotalColumns, TotalRows, MinHeight, MaxHeight, &HeightData[0]);
        }
    }

    HeightFieldColliderComponent::HeightFieldColliderComponent(const TerrainComponent& terrain)
    {
        if(Physics::IsActive())
        {
            //Todo: Get the info from the terrain component and assign each item then create the collider
            Collider = Physics::CreateHeightFieldShape(TotalColumns, TotalRows, MinHeight, MaxHeight, &HeightData[0]);
        }
    }


    SphereColliderComponent::SphereColliderComponent()
    {
        if(Physics::IsActive())
        {
            Collider = Physics::CreateSphereShape(Radius);
        }
    }

    SphereColliderComponent::SphereColliderComponent(const float& radius)
        :Radius(radius)
    {
        if(Physics::IsActive())
        {
            Collider = Physics::CreateSphereShape(Radius);
        }
    }

    CapsuleColliderComponent::CapsuleColliderComponent()
    {
        if(Physics::IsActive())
        {
            Collider = Physics::CreateCapsuleShape(Radius, Height);
        }
    }

    CapsuleColliderComponent::CapsuleColliderComponent(const float& radius, const float& height)
        :Radius(radius), Height(height)
    {
        if(Physics::IsActive())
        {
            Collider = Physics::CreateCapsuleShape(Radius, Height);
        }
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
