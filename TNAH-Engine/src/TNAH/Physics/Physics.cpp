#include "tnahpch.h"
#include "Physics.h"

namespace tnah
{
    
#pragma region Physics
    Ref<PhysicsManager> Physics::m_PhysicsManager = Ref<PhysicsManager>::Create();
    TransformComponent Physics::m_ColliderTransform = TransformComponent();

#pragma region InitAndHelpers
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
        const bool result = m_PhysicsManager->Initialise(collisionEventListener);
        ToggleColliderRendering();
        return result;
    }

    void Physics::ToggleColliderRendering()
    {
        if(m_PhysicsManager->m_Active)
        {
            m_PhysicsManager->m_ColliderRender = !m_PhysicsManager->m_ColliderRender;
            if(m_PhysicsManager->m_ColliderRendererInit)
            {
                m_PhysicsManager->m_PhysicsWorld->setIsDebugRenderingEnabled(m_PhysicsManager->m_ColliderRender);
            }
            else
            {
                m_ColliderTransform.Scale = glm::vec3(1.0f);
                m_PhysicsManager->CreateColliderRenderer();
                m_PhysicsManager->m_PhysicsWorld->setIsDebugRenderingEnabled(m_PhysicsManager->m_ColliderRender);
            }
        }
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
        {
            m_PhysicsManager->OnFixedUpdate(timestep);
            UpdateColliderRenderer();
        }
    }

    void Physics::Destroy()
    {
        m_PhysicsManager->Destroy();
    }
#pragma endregion 

#pragma region ColliderRenderer
    bool& Physics::GetColliderRendererHandle()
    {
        return m_PhysicsManager->m_ColliderRender;
    }

    TransformComponent Physics::GetColliderRendererTransform()
    {
        if(m_PhysicsManager->m_Active)
        {
            return m_ColliderTransform;
        }
        
        return TransformComponent();

    }

    rp3d::DebugRenderer* Physics::GetColliderRenderer()
    {
        if(m_PhysicsManager->m_Active)
        {
            return &m_PhysicsManager->m_PhysicsWorld->getDebugRenderer();
        }
        return nullptr;
    }

    void Physics::EnableLogging()
    {
        if(IsActive())
        {
            m_PhysicsManager->m_Logging = true;
            PhysicsLoggerInit();
        }
    }

    bool Physics::IsColliderRenderingEnabled()
    {
        return m_PhysicsManager->m_ColliderRender;
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
            //Check and return if the collider rendering objects haven't been created yet
            // Only check one object, if one is null then they all are
            if(m_PhysicsManager->m_LinesVertexArray == nullptr) return;
            if(!m_PhysicsManager->m_ColliderRendererInit) return;

            //Check and only update if we really want to render the colliders
            if(m_PhysicsManager->m_ColliderRender)
            {
                auto renderer = GetColliderRenderer();
                const rp3d::uint nbLines = renderer->getNbLines();
                if(nbLines > 0)
                {
                    const uint32_t size = nbLines * sizeof(rp3d::DebugRenderer::DebugLine);
                    m_PhysicsManager->m_LinesVertexArray->Bind();
                    m_PhysicsManager->m_LinesVertexBuffer->SetData(size, renderer->getLinesArray(), DrawType::STREAM, TypeMode::DRAW);
                    m_PhysicsManager->m_LinesVertexArray->SetIndexSize(nbLines * 2);

                    VertexBufferLayout layout = m_PhysicsManager->m_LinesVertexBuffer->GetLayout();
                    layout.SetStride(sizeof(rp3d::Vector3) + sizeof(rp3d::uint32));
                    auto& elements = layout.GetElements();
                    elements.at(1).Offset = sizeof(rp3d::Vector3);
                    m_PhysicsManager->m_LinesVertexBuffer->SetLayout(layout);
                    m_PhysicsManager->m_LinesVertexBuffer->Unbind();
                    m_PhysicsManager->m_LinesVertexArray->Unbind();
                }

                // Triangles
                const rp3d::uint nbTriangles = renderer->getNbTriangles();
                if(nbTriangles > 0)
                {
                    const uint32_t size = nbTriangles * sizeof(rp3d::DebugRenderer::DebugTriangle);
                    m_PhysicsManager->m_TriangleVertexArray->Bind();
                    m_PhysicsManager->m_TriangleVertexBuffer->SetData(size, renderer->getTrianglesArray(), DrawType::STREAM, TypeMode::DRAW);
                    m_PhysicsManager->m_TriangleVertexArray->SetIndexSize(nbTriangles * 3);

                    VertexBufferLayout layout = m_PhysicsManager->m_TriangleVertexBuffer->GetLayout();
                    layout.SetStride(sizeof(rp3d::Vector3) + sizeof(rp3d::uint32));
                    auto& elements = layout.GetElements();
                    elements.at(1).Offset = sizeof(rp3d::Vector3);
                    m_PhysicsManager->m_TriangleVertexBuffer->SetLayout(layout);
                    m_PhysicsManager->m_TriangleVertexBuffer->Unbind();
                    m_PhysicsManager->m_TriangleVertexArray->Unbind();
                }
            }
        }
    }
#pragma endregion 

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

    
 /***************************************/

    
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



}