#include "tnahpch.h"
#include "Physics.h"

#include "PhysicsCommand.h"

namespace tnah
{
    
#pragma region InitAndHelpers

    void Physics::Initialise()
    {
        PhysicsCommand::Init();
    }

    void Physics::OnFixedUpdate(PhysicsTimestep timestep)
    {
        PhysicsCommand::OnFixedUpdate(timestep);
    }

    void Physics::Destroy()
    {
        PhysicsCommand::Destroy();
    }
#pragma endregion 

#pragma region ColliderRenderer
    bool& Physics::GetColliderRendererHandle()
    {
        return  PhysicsCommand::GetColliderRendererHandler();
    }

    TransformComponent Physics::GetColliderRendererTransform()
    {
       return PhysicsCommand::GetColliderRendererTransform();
    }

    void Physics::EnableLogging()
    {
        PhysicsCommand::EnableLogging();
    }

    bool Physics::IsColliderRenderingEnabled()
    {
        return  PhysicsCommand::IsColliderRenderingEnabled();
    }

    std::pair<std::pair<Ref<VertexArray>, Ref<VertexBuffer>>, std::pair<Ref<VertexArray>, Ref<VertexBuffer>>> Physics::
    GetColliderRenderObjects()
    {
        return PhysicsCommand::GetColliderRenderObjects();
    }

    Ref<Shader> Physics::GetColliderShader()
    {
        return  PhysicsCommand::GetColliderShader();
    }
#pragma endregion 

/*
#pragma region RigidbodyAndCollider
    rp3d::CollisionBody* Physics::CreateCollisionBody(const TransformComponent& transformValues)
    {
        if(m_PhysicsManager->m_Active)
            return m_PhysicsManager->CreateCollisionBody(transformValues);
        return nullptr;
    }
    
    void Physics::DestroyCollisionBody(rp3d::CollisionBody* body)
    {
        if(m_PhysicsManager->m_Active)
            m_PhysicsManager->DestroyCollisionBody(body);
    }

    void Physics::DestroyRigidbody(rp3d::RigidBody* body)
    {
        if(m_PhysicsManager->m_Active)
            m_PhysicsManager->DestroyRigidBody(body);
    }

    rp3d::RigidBody* Physics::CreateRigidbody(const TransformComponent& transform)
    {
        if(m_PhysicsManager->m_Active)
            return m_PhysicsManager->m_PhysicsWorld->createRigidBody(Math::ToRp3dTransform(transform));
        return nullptr;
    }

    rp3d::RigidBody* Physics::CreateRigidbody(const rp3d::Transform transform)
    {
        if(m_PhysicsManager->m_Active)
            return m_PhysicsManager->m_PhysicsWorld->createRigidBody(transform);
        return nullptr;
    }

    rp3d::RigidBody* Physics::CreateRigidbody(const glm::vec3& position, const glm::vec3& rotation)
    {
        if(m_PhysicsManager->m_Active)
        {
            const TransformComponent transform  = TransformComponent(position, rotation, {1,1,1});
            return m_PhysicsManager->m_PhysicsWorld->createRigidBody(Math::ToRp3dTransform(transform));
        }
        return nullptr;
    }

    void Physics::CreateTerrainCollider(Terrain* terrain)
    {
        if(IsActive())
        {
            //TODO: Set up the terrain/Height field collider
        }
    }

    rp3d::BoxShape* Physics::CreateBoxShape(const float& halfX, const float& halfY, const float& halfZ)
    {
        if(m_PhysicsManager->m_Active)
            return m_PhysicsManager->m_PhysicsCommon.createBoxShape(rp3d::Vector3(halfX, halfY, halfZ));
        return nullptr;
    }

    rp3d::BoxShape* Physics::CreateBoxShape(const glm::vec3& halfExtents)
    {
        if(m_PhysicsManager->m_Active)
            return m_PhysicsManager->m_PhysicsCommon.createBoxShape(Math::ToRp3dVec3(halfExtents));
        return nullptr;
    }

    rp3d::BoxShape* Physics::CreateBoxShape(const rp3d::Vector3& halfExtents) 
    {
        if(m_PhysicsManager->m_Active)
            return m_PhysicsManager->m_PhysicsCommon.createBoxShape(halfExtents);
        return nullptr;
    }

    rp3d::SphereShape* Physics::CreateSphereShape(const float& radius)
    {
        if(m_PhysicsManager->m_Active)
            return m_PhysicsManager->m_PhysicsCommon.createSphereShape(radius);
        return nullptr;
    }

    rp3d::CapsuleShape* Physics::CreateCapsuleShape(const float& radius, const float& height)
    {
        if(m_PhysicsManager->m_Active)
            return m_PhysicsManager->m_PhysicsCommon.createCapsuleShape(radius, height);

        return nullptr;
    }

    rp3d::HeightFieldShape* Physics::CreateHeightFieldShape(const int &columns, const int& rows, const float &minHeight, const float& maxHeight, const float* terrainColliderHeightData)
    {
        if(m_PhysicsManager->m_Active)
            return m_PhysicsManager->m_PhysicsCommon.createHeightFieldShape(columns, rows, minHeight, maxHeight, terrainColliderHeightData, rp3d::HeightFieldShape::HeightDataType::HEIGHT_FLOAT_TYPE);
        return nullptr;
    }

    rp3d::PolyhedronMesh* Physics::CreatePolyhedronMesh(rp3d::PolygonVertexArray* polygonVertexArray)
    {
        if(m_PhysicsManager->m_Active)
            return m_PhysicsManager->m_PhysicsCommon.createPolyhedronMesh(polygonVertexArray);
        return nullptr;
    }

    rp3d::ConvexMeshShape* Physics::CreateConvexMeshShape(rp3d::PolyhedronMesh* polyhedronMesh)
    {
        if(m_PhysicsManager->m_Active)
            return m_PhysicsManager->m_PhysicsCommon.createConvexMeshShape(polyhedronMesh);
        return nullptr;
    }

    rp3d::ConcaveMeshShape* Physics::CreateConcaveMeshShape(rp3d::TriangleMesh* triangleMesh)
    {
        if(m_PhysicsManager->m_Active)
            return m_PhysicsManager->m_PhysicsCommon.createConcaveMeshShape(triangleMesh);
        return nullptr;
    }

    rp3d::TriangleMesh* Physics::CreateTriangleMesh()
    {
        if(m_PhysicsManager->m_Active)
            return m_PhysicsManager->m_PhysicsCommon.createTriangleMesh();
        return nullptr;
    }
#pragma endregion 

#pragma endregion

    
 /**************************************#1#

    
#pragma region PhysicsManager
        
    PhysicsManager::PhysicsManager()
    {
    }

    PhysicsManager::~PhysicsManager()
    {
        Destroy();
    }

    void PhysicsManager::Destroy()
    {
        if(m_PhysicsLogger) m_PhysicsCommon.destroyDefaultLogger(m_PhysicsLogger);
        if(m_PhysicsWorld) m_PhysicsCommon.destroyPhysicsWorld(m_PhysicsWorld);
        m_Active = false;
    }

    rp3d::RigidBody* PhysicsManager::CreateRigidBody(const TransformComponent& transform) const
    {
        if(m_Active)
        {
            return m_PhysicsWorld->createRigidBody(Math::ToRp3dTransform(transform));
        }

        return nullptr;
    }

    void PhysicsManager::DestroyRigidBody(rp3d::RigidBody* rigidBody) const
    {
        if(m_PhysicsWorld)
        {
            m_PhysicsWorld->destroyRigidBody(rigidBody);
        }
    }

    void PhysicsManager::DestroyCollisionBody(rp3d::CollisionBody* body) const
    {
        if(m_PhysicsWorld)
        {
            m_PhysicsWorld->destroyCollisionBody(body);
        }
    }
    
    rp3d::CollisionBody* PhysicsManager::CreateCollisionBody(const TransformComponent& transform) const
    {
        if(m_Active)
        {
            return m_PhysicsWorld->createCollisionBody(Math::ToRp3dTransform(transform));
        }
        
        return nullptr;
    }

    void PhysicsManager::CreateColliderRenderer()
    {
        m_LinesVertexArray = VertexArray::Create();
        m_LinesVertexBuffer = VertexBuffer::Create();


        m_TriangleVertexArray = VertexArray::Create();
        m_TriangleVertexBuffer = VertexBuffer::Create();
        m_ColliderLayout = {
            {ShaderDataType::Float3, "a_Position"},
            {ShaderDataType::UInt, "a_VertexColor"}
        };
        m_LinesVertexBuffer->SetLayout(m_ColliderLayout);
        m_LinesVertexArray->AddVertexBuffer(m_LinesVertexBuffer);

        m_TriangleVertexBuffer->SetLayout(m_ColliderLayout);
        m_TriangleVertexArray->AddVertexBuffer(m_TriangleVertexBuffer);
        
        m_Shader = Shader::Create("Resources/shaders/default/physics/physics_vertex.glsl","Resources/shaders/default/physics/physics_fragment.glsl");

        m_ColliderRendererInit = true;
    }

    
    
    bool PhysicsManager::Initialise(rp3d::EventListener* collisionEventListener)
    {
        m_PhysicsWorld = m_PhysicsCommon.createPhysicsWorld();
        if(m_PhysicsWorld == nullptr || collisionEventListener == nullptr)
            return false;
        
        m_PhysicsWorld->setEventListener(collisionEventListener);
        m_Active = true;
        
        return true;
    }

    void PhysicsManager::OnFixedUpdate(PhysicsTimestep timestep) const
    {
        m_PhysicsWorld->getDebugRenderer().setIsDebugItemDisplayed(rp3d::DebugRenderer::DebugItem::COLLISION_SHAPE, true);
        m_PhysicsWorld->getDebugRenderer().setIsDebugItemDisplayed(rp3d::DebugRenderer::DebugItem::COLLIDER_AABB, true);
        
        m_PhysicsWorld->update(timestep.GetSimulationSpeed());
        
    }
#pragma endregion 
*/



}
