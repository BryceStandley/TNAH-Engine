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

    void Physics::ToggleColliderRendering()
    {
        if(m_PhysicsManager->m_Active)
        {
            m_PhysicsManager->m_ColliderRender = !m_PhysicsManager->m_ColliderRender;
            m_PhysicsManager->m_PhysicsWorld->setIsDebugRenderingEnabled(m_PhysicsManager->m_ColliderRender);
            TNAH_CORE_INFO("THIS IS CALLLLED");
        }
    }

    rp3d::DebugRenderer Physics::GetColliderRenderer()
    {
        if(m_PhysicsManager->m_Active)
        {
            return m_PhysicsManager->m_PhysicsWorld->getDebugRenderer();
        }
    }

    void Physics::CreateTerrainCollider(Terrain* terrain)
    {
    }

    std::pair<std::pair<Ref<VertexArray>, Ref<VertexBuffer>>, std::pair<Ref<VertexArray>, Ref<VertexBuffer>>> Physics::
    GetColliderRenderObjects()
    {
        std::pair<Ref<VertexArray>, Ref<VertexBuffer>> lines;
        lines.first = m_PhysicsManager->m_LinesVertexArray;
        lines.second = m_PhysicsManager->m_LinesVertexBuffer;

        std::pair<Ref<VertexArray>, Ref<VertexBuffer>> triangles;
        triangles.first = m_PhysicsManager->m_TriangleVertexArray;
        triangles.second = m_PhysicsManager->m_TriangleVertexBuffer;

        return {lines, triangles};
    }

    Ref<Shader> Physics::GetColliderShader()
    {
        return m_PhysicsManager->m_Shader;
    }

    void Physics::UpdateColliderRenderer()
    {
        if(m_PhysicsManager->m_Active)
        {
            const rp3d::uint nbLines = GetColliderRenderer().getNbLines();
            if(nbLines > 0)
            {
                const GLsizei size = static_cast<GLsizei>(nbLines * sizeof(rp3d::DebugRenderer::DebugLine));
                m_PhysicsManager->m_LinesVertexBuffer->SetData(size, GetColliderRenderer().getLinesArray(), DrawType::STREAM, TypeMode::DRAW);
            }

            // Triangles
            const rp3d::uint nbTriangles = GetColliderRenderer().getNbTriangles();
            if(nbTriangles > 0)
            {
                GLsizei size = static_cast<GLsizei>(nbTriangles * sizeof(rp3d::DebugRenderer::DebugTriangle));
                m_PhysicsManager->m_LinesVertexBuffer->SetData(size, GetColliderRenderer().getTrianglesArray(), DrawType::STREAM, TypeMode::DRAW);
            }
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

    

    void Physics::PhysicsLoggerInit()
    {
        m_PhysicsManager->m_PhysicsLogger = m_PhysicsManager->m_PhysicsCommon.createDefaultLogger();
        const rp3d::uint logLevel = static_cast<rp3d::uint>(rp3d::Logger::Level::Warning) | static_cast<rp3d::uint>(rp3d::Logger::Level::Error) | static_cast<rp3d::uint>(rp3d::Logger::Level::Information);
        m_PhysicsManager->m_PhysicsLogger->addFileDestination("rp3d_log.html", logLevel, rp3d::DefaultLogger::Format::HTML);
        m_PhysicsManager->m_PhysicsCommon.setLogger(m_PhysicsManager->m_PhysicsLogger);
    }

    void Physics::OnFixedUpdate(PhysicsTimestep timestep)
    {
        if(IsActive())
            m_PhysicsManager->OnFixedUpdate(timestep);
    }

    void Physics::Destroy()
    {
        m_PhysicsManager->Destroy();
    }

/********************* Physics Manager ***************************/

        
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

    void PhysicsManager::CreateColliderRenderer()
    {
        m_LinesVertexArray = VertexArray::Create();
        m_LinesVertexBuffer = VertexBuffer::Create();

        m_TriangleVertexArray = VertexArray::Create();
        m_TriangleVertexBuffer = VertexBuffer::Create();

        m_Shader = Shader::Create("Resources/shaders/default/physics/physics_vertex.glsl","Resources/shaders/default/physics/physics_fragment.glsl");
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
        m_PhysicsWorld->setIsDebugRenderingEnabled(true);
        m_Active = true;

        CreateColliderRenderer();
        return true;
    }

    void PhysicsManager::OnFixedUpdate(PhysicsTimestep timestep)
    {
        if(m_ColliderRender)
        {
            m_PhysicsWorld->getDebugRenderer().setIsDebugItemDisplayed(rp3d::DebugRenderer::DebugItem::COLLISION_SHAPE, true);
            m_PhysicsWorld->getDebugRenderer().setIsDebugItemDisplayed(rp3d::DebugRenderer::DebugItem::COLLIDER_AABB, true);
        }
        //m_PhysicsWorld->getDebugRenderer().setIsDebugItemDisplayed(rp3d::DebugRenderer::DebugItem::COLLIDER_AABB, true);
        
        m_PhysicsWorld->update(timestep.GetSimulationSpeed());
        
    }




}