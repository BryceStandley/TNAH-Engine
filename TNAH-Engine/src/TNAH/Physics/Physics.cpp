#include "tnahpch.h"
#include "Physics.h"

namespace tnah
{
    Ref<PhysicsManager> Physics::m_PhysicsManager = Ref<PhysicsManager>::Create();

    Ref<PhysicsManager> Physics::GetManager()
    {
        return m_PhysicsManager;
    }

    bool Physics::IsActive()
    {
        return m_PhysicsManager->m_Active;
    }

    bool Physics::Initialise(rp3d::EventListener* collisionEventListener)
    {
        const bool success = m_PhysicsManager->Initialise(collisionEventListener);
        if(success) PhysicsLoggerInit();
        return success;
    }

    rp3d::CollisionBody* Physics::CreateCollisionBody(const TransformComponent& transformValues)
    {
        return m_PhysicsManager->CreateCollisionBody(transformValues);
    }
    
    void Physics::DestroyCollisionBody(rp3d::CollisionBody* body)
    {
        m_PhysicsManager->DestroyCollisionBody(body);
    }

    rp3d::BoxShape* Physics::CreateBoxShape(const rp3d::Vector3& halfExtents) 
    {
        return m_PhysicsManager->m_PhysicsCommon.createBoxShape(halfExtents);
    }

    rp3d::SphereShape* Physics::CreateSphereShape(const float& radius)
    {
        return m_PhysicsManager->m_PhysicsCommon.createSphereShape(radius);
    }

    rp3d::CapsuleShape* Physics::CreateCapsuleShape(const float& radius, const float& height)
    {
        return m_PhysicsManager->m_PhysicsCommon.createCapsuleShape(radius, height);
    }

    rp3d::HeightFieldShape* Physics::CreateHeightFieldShape(const int &columns, const int& rows, const float &minHeight, const float& maxHeight, const float* terrainColliderHeightData, rp3d::HeightFieldShape::HeightDataType &heightDataType)
    {
        return m_PhysicsManager->m_PhysicsCommon.createHeightFieldShape(columns, rows, minHeight, maxHeight, terrainColliderHeightData, heightDataType);
    }

    rp3d::PolyhedronMesh* Physics::CreatePolyhedronMesh(rp3d::PolygonVertexArray* polygonVertexArray)
    {
        return m_PhysicsManager->m_PhysicsCommon.createPolyhedronMesh(polygonVertexArray);
    }

    rp3d::ConvexMeshShape* Physics::CreateConvexMeshShape(rp3d::PolyhedronMesh* polyhedronMesh)
    {
        return m_PhysicsManager->m_PhysicsCommon.createConvexMeshShape(polyhedronMesh);
    }

    rp3d::ConcaveMeshShape* Physics::CreateConcaveMeshShape(rp3d::TriangleMesh* triangleMesh)
    {
        return m_PhysicsManager->m_PhysicsCommon.createConcaveMeshShape(triangleMesh);
    }

    rp3d::TriangleMesh* Physics::CreateTriangleMesh()
    {
        return m_PhysicsManager->m_PhysicsCommon.createTriangleMesh();
    }

    void Physics::CreateTerrainCollider(tnah::Terrain* terrain)
    {
        // gameTerrain = terrain;
        // gameTerrain->SetCollisionTag(BoundingBox::TERRAIN);
        int rows = terrain->GetSize().x;
        int columns = terrain->GetSize().y;

        float minHeight = terrain->GetMinHeight().y;
        float maxHeight = terrain->GetMaxHeight().y;

        int size = rows * columns;
        //std::vector<float> terrainHeights = terrain->GetTerrainHeights();



    }

    void Physics::PhysicsLoggerInit()
    {
        m_PhysicsManager->m_PhysicsLogger = m_PhysicsManager->m_PhysicsCommon.createDefaultLogger();
        const rp3d::uint logLevel = static_cast<rp3d::uint>(rp3d::Logger::Level::Warning) | static_cast<rp3d::uint>(rp3d::Logger::Level::Error) | static_cast<rp3d::uint>(rp3d::Logger::Level::Information);
        m_PhysicsManager->m_PhysicsLogger->addFileDestination("Log/reactphysics3D/rp3d_log.html", logLevel, rp3d::DefaultLogger::Format::HTML);
        m_PhysicsManager->m_PhysicsCommon.setLogger(m_PhysicsManager->m_PhysicsLogger);
    }

    void Physics::OnFixedUpdate(PhysicsTimestep timestep)
    {
        m_PhysicsManager->OnFixedUpdate(timestep);
    }

    void Physics::Destroy()
    {
        m_PhysicsManager->Destroy();
    }

/********************* Physics Collision ***************************/

    
    PhysicsManager::PhysicsManager()
    {
    }

    PhysicsManager::~PhysicsManager()
    {
        Destroy();
    }

    void PhysicsManager::Destroy()
    {
        m_PhysicsCommon.destroyDefaultLogger(m_PhysicsLogger);
        m_PhysicsCommon.destroyPhysicsWorld(m_PhysicsWorld);
        m_Active = false;
    }

    rp3d::RigidBody* PhysicsManager::CreateRigidBody(const TransformComponent& transform)
    {
        if(m_Active)
        {
            return m_PhysicsWorld->createRigidBody(Math::ToRp3dTransform(transform));
        }

        return nullptr;
    }

    void PhysicsManager::DestroyRigidBody(rp3d::RigidBody* rigidBody)
    {
        if(m_PhysicsWorld)
        {
            m_PhysicsWorld->destroyRigidBody(rigidBody);
        }
    }

    void PhysicsManager::DestroyCollisionBody(rp3d::CollisionBody* body)
    {
        if(m_PhysicsWorld)
        {
            m_PhysicsWorld->destroyCollisionBody(body);
        }
    }

    rp3d::CollisionBody* PhysicsManager::CreateCollisionBody(const TransformComponent& transform)
    {
        if(m_Active)
        {
            return m_PhysicsWorld->createCollisionBody(Math::ToRp3dTransform(transform));
        }
        
        return nullptr;
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

    void PhysicsManager::OnFixedUpdate(PhysicsTimestep timestep)
    {
        
    }




}