#include "tnahpch.h"
#include "Physics.h"

namespace tnah
{
    Ref<PhysicsManager> Physics::m_PhysicsCollision = Ref<PhysicsManager>::Create();

    Ref<PhysicsManager> Physics::GetManager()
    {
        return m_PhysicsCollision;
    }

    bool Physics::IsActive()
    {
        return m_PhysicsCollision->m_Active;
    }

    bool Physics::Initialise(rp3d::EventListener* collisionEventListener)
    {
        const bool success = m_PhysicsCollision->Initialise(collisionEventListener);
        if(success) PhysicsLoggerInit();
        return success;
    }

    rp3d::CollisionBody* Physics::CreateCollisionBody(const TransformComponent& transformValues)
    {
        return m_PhysicsCollision->CreateCollisionBody(transformValues);
    }
    
    void Physics::DestroyCollisionBody(rp3d::CollisionBody* body)
    {
        m_PhysicsCollision->DestroyCollisionBody(body);
    }

    rp3d::CapsuleShape* Physics::CreateCapsuleShape(const float& radius, const float& height)
    {
        return m_PhysicsCollision->m_PhysicsCommon.createCapsuleShape(radius, height);
    }

    rp3d::PolyhedronMesh* Physics::CreatePolyhedronMesh(rp3d::PolygonVertexArray* polygonVertexArray)
    {
        return m_PhysicsCollision->m_PhysicsCommon.createPolyhedronMesh(polygonVertexArray);
    }

    rp3d::ConvexMeshShape* Physics::CreateConvexMeshShape(rp3d::PolyhedronMesh* polyhedronMesh)
    {
        return m_PhysicsCollision->m_PhysicsCommon.createConvexMeshShape(polyhedronMesh);
    }

    rp3d::ConcaveMeshShape* Physics::CreateConcaveMeshShape(rp3d::TriangleMesh* triangleMesh)
    {
        return m_PhysicsCollision->m_PhysicsCommon.createConcaveMeshShape(triangleMesh);
    }

    rp3d::TriangleMesh* Physics::CreateTriangleMesh()
    {
        return m_PhysicsCollision->m_PhysicsCommon.createTriangleMesh();
    }

    void Physics::PhysicsLoggerInit()
    {
        m_PhysicsCollision->m_PhysicsLogger = m_PhysicsCollision->m_PhysicsCommon.createDefaultLogger();
        const rp3d::uint logLevel = static_cast<rp3d::uint>(rp3d::Logger::Level::Warning) | static_cast<rp3d::uint>(rp3d::Logger::Level::Error) | static_cast<rp3d::uint>(rp3d::Logger::Level::Information);
        m_PhysicsCollision->m_PhysicsLogger->addFileDestination("Log/reactphysics3D/rp3d_log.html", logLevel, rp3d::DefaultLogger::Format::HTML);
        m_PhysicsCollision->m_PhysicsCommon.setLogger(m_PhysicsCollision->m_PhysicsLogger);
    }

    void Physics::OnFixedUpdate(PhysicsTimestep timestep)
    {
        m_PhysicsCollision->OnFixedUpdate(timestep);
    }

    void Physics::Destroy()
    {
        m_PhysicsCollision->Destroy();
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