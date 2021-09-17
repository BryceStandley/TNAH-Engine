#include "tnahpch.h"
#include "ReactPhysics.h"

namespace tnah
{
    void ReactPhysics::Init()
    {
        //TODO: Add values for gravity ect
        m_PhysicsWorld = m_PhysicsCommon.createPhysicsWorld();
    }
    
    ReactPhysics::~ReactPhysics()
    {
        TNAH_CORE_INFO("Destruction of React Physics Called");
    }

    Ref<RigidBody> ReactPhysics::CreateRigidBody(const TransformComponent& transform)
    {
        m_RigidBody[uniqueIds] = ReactRigidBody(Ref<RigidBody>::Create(uniqueIds, RigidBodyValues::Type::Dynamic), m_PhysicsWorld->createRigidBody(Math::ToRp3dTransform(transform)));
        if(m_RigidBody[uniqueIds].m_RigidBody != nullptr || m_RigidBody[uniqueIds].m_Body != nullptr)
        {
            uniqueIds++;
            return m_RigidBody[uniqueIds].m_RigidBody;
        }

        TNAH_CORE_ASSERT(false, "Did not create a rigidbody - React Physics 3D");
        return nullptr;
    }

    void ReactPhysics::OnFixedUpdate(PhysicsTimestep timestep)
    {
        m_PhysicsWorld->getDebugRenderer().setIsDebugItemDisplayed(rp3d::DebugRenderer::DebugItem::COLLISION_SHAPE, true);
        m_PhysicsWorld->getDebugRenderer().setIsDebugItemDisplayed(rp3d::DebugRenderer::DebugItem::COLLIDER_AABB, true);

        //This is the main thing we would need to do ourselves
        m_PhysicsWorld->update(timestep.GetSimulationSpeed());
        
        UpdateRigidBodies();
    }

    void ReactPhysics::UpdateRigidBodies()
    {
        for(auto& event : m_RigidBody)
        {
            //Update all the rigidbody values
            auto& values = event.second;
            auto reactRb = values.m_Body;
            auto rb = values.m_RigidBody;
            glm::vec3 newPos = Math::FromRp3dVec3(reactRb->getTransform().getPosition());
            glm::quat newRot(reactRb->getTransform().getOrientation().w, reactRb->getTransform().getOrientation().x, reactRb->getTransform().getOrientation().y, reactRb->getTransform().getOrientation().z);
            //TODO: Change this, using vec3 for now is okay, but it should be changed completely
            rb->GetRigidBody().position = newPos;
            rb->GetRigidBody().rotation = newRot;
            //More values from it
        }
    }
    
    void ReactPhysics::CreateBoxShape(const glm::vec3& halfValues, Ref<RigidBody> rb)
    {
        TNAH_CORE_ERROR("Collider-Box not currently supported");
    }

    void ReactPhysics::CreateCapsuleShape(const float& radius, const float& height, Ref<RigidBody> rb)
    {
        TNAH_CORE_ERROR("Collider-Capsule not currently supported");
    }

    void ReactPhysics::CreateSphereShape(const float& radius, Ref<RigidBody> rb)
    {
        TNAH_CORE_ERROR("Collider-Sphere not currently supported");
    }

    void ReactPhysics::CreateTerrainCollider(tnah::Terrain* terrain)
    {
        TNAH_CORE_ERROR("Collider-Terrain not currently supported");
    }

    void ReactPhysics::EnableLogging()
    {
        m_Logging = true;
        PhysicsLoggerInit();
    }

    Ref<Shader> ReactPhysics::GetColliderShader()
    {
        return m_Shader;
    }

    bool ReactPhysics::IsColliderRenderingEnabled()
    {
        return m_ColliderRender;
    }

    std::pair<std::pair<Ref<VertexArray>, Ref<VertexBuffer>>, std::pair<Ref<VertexArray>, Ref<VertexBuffer>>> ReactPhysics::GetColliderRenderObjects()
    {
        std::pair<Ref<VertexArray>, Ref<VertexBuffer>> lines;
        lines.first = m_LinesVertexArray;
        lines.second = m_LinesVertexBuffer;

        std::pair<Ref<VertexArray>, Ref<VertexBuffer>> triangles;
        triangles.first = m_TriangleVertexArray;
        triangles.second = m_TriangleVertexBuffer;

        return {lines, triangles};
    }

    void ReactPhysics::CreateColliderRenderer()
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

    void ReactPhysics::TollgeColliderRendering()
    {
        m_ColliderRender = !m_ColliderRender;
        if(m_ColliderRendererInit)
        {
            m_PhysicsWorld->setIsDebugRenderingEnabled(m_ColliderRender);
        }
        else
        {
            m_ColliderTransform.Scale = glm::vec3(1.0f);
            CreateColliderRenderer();
            m_PhysicsWorld->setIsDebugRenderingEnabled(m_ColliderRender);
        }
    }

    void ReactPhysics::UpdateColliderRenderer()
    {
        if(m_LinesVertexArray == nullptr) return;
        if(!m_ColliderRendererInit) return;
        
        const auto& renderer = m_PhysicsWorld->getDebugRenderer();
        const rp3d::uint nbLines = renderer.getNbLines();

        //Lines
        if(nbLines > 0)
        {
            const uint32_t size = nbLines * sizeof(rp3d::DebugRenderer::DebugLine);
            m_LinesVertexArray->Bind();
            m_LinesVertexBuffer->SetData(size, renderer.getLinesArray(), DrawType::STREAM, TypeMode::DRAW);
            m_LinesVertexArray->SetIndexSize(nbLines * 2);

            VertexBufferLayout layout = m_LinesVertexBuffer->GetLayout();
            layout.SetStride(sizeof(rp3d::Vector3) + sizeof(rp3d::uint32));
            auto& elements = layout.GetElements();
            elements.at(1).Offset = sizeof(rp3d::Vector3);
            m_LinesVertexBuffer->SetLayout(layout);
            m_LinesVertexBuffer->Unbind();
            m_LinesVertexArray->Unbind();
        }

        // Triangles
        const rp3d::uint nbTriangles = renderer.getNbTriangles();
        if(nbTriangles > 0)
        {
            const uint32_t size = nbTriangles * sizeof(rp3d::DebugRenderer::DebugTriangle);
            m_TriangleVertexArray->Bind();
            m_TriangleVertexBuffer->SetData(size, renderer.getTrianglesArray(), DrawType::STREAM, TypeMode::DRAW);
            m_TriangleVertexArray->SetIndexSize(nbTriangles * 3);

            VertexBufferLayout layout = m_TriangleVertexBuffer->GetLayout();
            layout.SetStride(sizeof(rp3d::Vector3) + sizeof(rp3d::uint32));
            auto& elements = layout.GetElements();
            elements.at(1).Offset = sizeof(rp3d::Vector3);
            m_TriangleVertexBuffer->SetLayout(layout);
            m_TriangleVertexBuffer->Unbind();
            m_TriangleVertexArray->Unbind();
        }
        
    }

    void ReactPhysics::PhysicsLoggerInit()
    {
        m_PhysicsLogger = m_PhysicsCommon.createDefaultLogger();
        const rp3d::uint logLevel = static_cast<rp3d::uint>(rp3d::Logger::Level::Warning) | static_cast<rp3d::uint>(rp3d::Logger::Level::Error) | static_cast<rp3d::uint>(rp3d::Logger::Level::Information);
        m_PhysicsLogger->addFileDestination("rp3d_log.html", logLevel, rp3d::DefaultLogger::Format::HTML);
        m_PhysicsCommon.setLogger(m_PhysicsLogger);
    }

    void ReactPhysics::Destroy()
    {
        if(m_PhysicsLogger) m_PhysicsCommon.destroyDefaultLogger(m_PhysicsLogger);
        if(m_PhysicsWorld) m_PhysicsCommon.destroyPhysicsWorld(m_PhysicsWorld);
    }

    bool& ReactPhysics::GetColliderRendererHandle()
    {
        return m_ColliderRender;
    }


}