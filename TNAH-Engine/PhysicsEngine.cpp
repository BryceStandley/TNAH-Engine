#include "tnahpch.h"
#include "TNAH/Physics/PhysicsEngine.h"

#include "TNAH/Physics/Rigidbody.h"
#include "TNAH/Scene/GameObject.h"

namespace tnah::Physics
{

#pragma region Physics

    Ref<PhysicsManager>  PhysicsEngine::m_PhysicsManager = Ref<PhysicsManager>::Create();
    TransformComponent PhysicsEngine::m_ColliderTransform = TransformComponent();


#pragma region InitAndHelpers
    Ref<PhysicsManager>  PhysicsEngine::GetManager()
    {
        return m_PhysicsManager;
    }

    bool  PhysicsEngine::IsActive()
    {
        return m_PhysicsManager->m_Active;
    }

    bool  PhysicsEngine::Init(rp3d::EventListener* collisionEventListener)
    {
        const bool result = m_PhysicsManager->Initialise(collisionEventListener);
        ToggleColliderRendering();
        return result;
    }

    void  PhysicsEngine::ToggleColliderRendering()
    {
        if (m_PhysicsManager->m_Active)
        {
            m_PhysicsManager->m_ColliderRender = !m_PhysicsManager->m_ColliderRender;
            if (m_PhysicsManager->m_ColliderRendererInit)
            {
                m_PhysicsManager->m_PhysicsWorld->setIsDebugRenderingEnabled(m_PhysicsManager->m_ColliderRender);
            }
            else
            {
                m_ColliderTransform.Scale = glm::vec3(1.0f);
                m_PhysicsManager->CreateColliderRenderer();
                m_PhysicsManager->m_PhysicsWorld->setIsDebugRenderingEnabled(m_PhysicsManager->m_ColliderRender);
            }
            if (m_PhysicsManager->m_ColliderRender)
            {
                m_PhysicsManager->m_PhysicsWorld->getDebugRenderer().setIsDebugItemDisplayed(rp3d::DebugRenderer::DebugItem::COLLISION_SHAPE, true);
                m_PhysicsManager->m_PhysicsWorld->getDebugRenderer().setIsDebugItemDisplayed(rp3d::DebugRenderer::DebugItem::COLLIDER_AABB, true);
                m_PhysicsManager->m_PhysicsWorld->getDebugRenderer().setIsDebugItemDisplayed(rp3d::DebugRenderer::DebugItem::CONTACT_POINT, true);
                m_PhysicsManager->m_PhysicsWorld->getDebugRenderer().setIsDebugItemDisplayed(rp3d::DebugRenderer::DebugItem::CONTACT_NORMAL, true);
                m_PhysicsManager->m_PhysicsWorld->getDebugRenderer().setIsDebugItemDisplayed(rp3d::DebugRenderer::DebugItem::COLLIDER_BROADPHASE_AABB, true);
            }
            else
            {
                m_PhysicsManager->m_PhysicsWorld->getDebugRenderer().setIsDebugItemDisplayed(rp3d::DebugRenderer::DebugItem::COLLISION_SHAPE, false);
                m_PhysicsManager->m_PhysicsWorld->getDebugRenderer().setIsDebugItemDisplayed(rp3d::DebugRenderer::DebugItem::COLLIDER_AABB, false);
                m_PhysicsManager->m_PhysicsWorld->getDebugRenderer().setIsDebugItemDisplayed(rp3d::DebugRenderer::DebugItem::CONTACT_POINT, false);
                m_PhysicsManager->m_PhysicsWorld->getDebugRenderer().setIsDebugItemDisplayed(rp3d::DebugRenderer::DebugItem::CONTACT_NORMAL, false);
                m_PhysicsManager->m_PhysicsWorld->getDebugRenderer().setIsDebugItemDisplayed(rp3d::DebugRenderer::DebugItem::COLLIDER_BROADPHASE_AABB, false);
            }

        }
    }

    void  PhysicsEngine::PhysicsLoggerInit()
    {
        m_PhysicsManager->m_PhysicsLogger = m_PhysicsManager->m_PhysicsCommon.createDefaultLogger();
        const rp3d::uint logLevel = static_cast<rp3d::uint>(rp3d::Logger::Level::Warning) | static_cast<rp3d::uint>(rp3d::Logger::Level::Error) | static_cast<rp3d::uint>(rp3d::Logger::Level::Information);
        m_PhysicsManager->m_PhysicsLogger->addFileDestination("rp3d_log.html", logLevel, rp3d::DefaultLogger::Format::HTML);
        m_PhysicsManager->m_PhysicsCommon.setLogger(m_PhysicsManager->m_PhysicsLogger);
    }

    void PhysicsEngine::ProcessRigidbodyVelocities(const Timestep& deltaTime, TransformComponent& transform, Ref<Rigidbody> rigidbody)
    {
        if (rigidbody->GetBodyType() == BodyType::Dynamic && !rigidbody->Sleeping())
        {
            rigidbody->m_LinearVelocity.Velocity += deltaTime.GetSeconds() * (rigidbody->GetBodyMass().InverseMass * rigidbody->m_Force.Forces);
            rigidbody->m_AngularVelocity.Velocity += deltaTime.GetSeconds() * (rigidbody->GetInertiaTensor().InvesrseTensor * rigidbody->m_Torque.Torques);
        }

        if (m_PhysicsManager->GetGravityState() && rigidbody->GetBodyType() != BodyType::Static && !rigidbody->Sleeping() && !rigidbody->IgnoreGravity())
        {
            rigidbody->m_LinearVelocity.Velocity += deltaTime.GetSeconds() * rigidbody->GetBodyMass().InverseMass * rigidbody->GetBodyMass().Mass * m_PhysicsManager->GetGravity();
        }

        auto lDamp = glm::pow(1.0f - rigidbody->m_LinearDampening.Dampening, deltaTime.GetSeconds());
        auto aDamp = glm::pow(1.0f - rigidbody->m_angularDampening.Dampening, deltaTime.GetSeconds());
        rigidbody->m_LinearVelocity.Velocity *= lDamp;
        rigidbody->m_AngularVelocity.Velocity *= aDamp;

    }

    void PhysicsEngine::ProcessRigidbodyPositions(const Timestep& deltaTime, TransformComponent& transform, Ref<Rigidbody> rigidbody)
    {
        if (rigidbody->GetBodyType() == BodyType::Dynamic)
        {
            transform.Position += rigidbody->m_LinearVelocity.Velocity * deltaTime.GetSeconds();

            transform.Rotation = transform.Rotation + rigidbody->m_AngularVelocity.Velocity * transform.Rotation * 0.5f * deltaTime.GetSeconds();

            rigidbody->m_CollisionBody->setTransform(Math::ToRp3dTransform(transform));
        }
    }

    void PhysicsEngine::ResetRigidbodyForcesAndTorques(Ref<Rigidbody> rigidbody)
    {
        rigidbody->m_Force.Forces = { 0.0f, 0.0f, 0.0f };
        rigidbody->m_Torque.Torques = { 0.0f, 0.0f, 0.0f };
    }

    void  PhysicsEngine::OnFixedUpdate(Timestep deltaTime, PhysicsTimestep timestep, entt::registry& componentRegistry)
    {
        if (IsActive())
        {
            m_PhysicsManager->OnFixedUpdate(timestep);
            auto view = componentRegistry.view<TransformComponent, RigidBodyComponent>();
            for (auto entity : view)
            {
                auto& rb = view.get<RigidBodyComponent>(entity);
                auto& transform = view.get<TransformComponent>(entity);

                rb.OnUpdate(transform);

                ProcessRigidbodyVelocities(deltaTime, transform, rb.Body);
                ProcessRigidbodyPositions(deltaTime, transform, rb.Body);

                ResetRigidbodyForcesAndTorques(rb.Body);


            }
        }
    }

    void  PhysicsEngine::OnUpdate(Timestep timestep)
    {
        UpdateColliderRenderer();
    }

    void  PhysicsEngine::Destroy()
    {
        m_PhysicsManager->Destroy();
    }

#pragma endregion 

#pragma region ColliderRenderer

    bool& PhysicsEngine::GetColliderRendererHandle()
    {
        return m_PhysicsManager->m_ColliderRender;
    }

    TransformComponent  PhysicsEngine::GetColliderRendererTransform()
    {
        if (m_PhysicsManager->m_Active)
        {
            return m_ColliderTransform;
        }

        return TransformComponent();

    }

    rp3d::DebugRenderer* PhysicsEngine::GetColliderRenderer()
    {
        if (m_PhysicsManager->m_Active)
        {
            return &m_PhysicsManager->m_PhysicsWorld->getDebugRenderer();
        }
        return nullptr;
    }

    void  PhysicsEngine::EnableLogging()
    {
        if (IsActive())
        {
            m_PhysicsManager->m_Logging = true;
            PhysicsLoggerInit();
        }
    }

    bool  PhysicsEngine::IsColliderRenderingEnabled()
    {
        return m_PhysicsManager->m_ColliderRender;
    }

    std::pair<std::pair<Ref<VertexArray>, Ref<VertexBuffer>>, std::pair<Ref<VertexArray>, Ref<VertexBuffer>>>  PhysicsEngine::
        GetColliderRenderObjects()
    {
        std::pair<Ref<VertexArray>, Ref<VertexBuffer>> lines;
        lines.first = m_PhysicsManager->m_LinesVertexArray;
        lines.second = m_PhysicsManager->m_LinesVertexBuffer;

        std::pair<Ref<VertexArray>, Ref<VertexBuffer>> triangles;
        triangles.first = m_PhysicsManager->m_TraingleVertexArray;
        triangles.second = m_PhysicsManager->m_TriangleVertexBuffer;

        return { lines, triangles };
    }

    Ref<Shader>  PhysicsEngine::GetColliderShader()
    {
        return m_PhysicsManager->m_Shader;
    }

    void  PhysicsEngine::UpdateColliderRenderer()
    {
        if (m_PhysicsManager->m_Active)
        {
            //Check and return if the collider rendering objects haven't been created yet
            // Only check one object, if one is null then they all are
            if (m_PhysicsManager->m_LinesVertexArray == nullptr) return;
            if (!m_PhysicsManager->m_ColliderRendererInit) return;

            //Check and only update if we really want to render the colliders
            if (m_PhysicsManager->m_ColliderRender)
            {
                auto renderer = GetColliderRenderer();
                const rp3d::uint nbLines = renderer->getNbLines();
                if (nbLines > 0)
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
                if (nbTriangles > 0)
                {
                    const uint32_t size = nbTriangles * sizeof(rp3d::DebugRenderer::DebugTriangle);
                    m_PhysicsManager->m_TraingleVertexArray->Bind();
                    m_PhysicsManager->m_TriangleVertexBuffer->SetData(size, renderer->getTrianglesArray(), DrawType::STREAM, TypeMode::DRAW);
                    m_PhysicsManager->m_TraingleVertexArray->SetIndexSize(nbTriangles * 3);

                    VertexBufferLayout layout = m_PhysicsManager->m_TriangleVertexBuffer->GetLayout();
                    layout.SetStride(sizeof(rp3d::Vector3) + sizeof(rp3d::uint32));
                    auto& elements = layout.GetElements();
                    elements.at(1).Offset = sizeof(rp3d::Vector3);
                    m_PhysicsManager->m_TriangleVertexBuffer->SetLayout(layout);
                    m_PhysicsManager->m_TriangleVertexBuffer->Unbind();
                    m_PhysicsManager->m_TraingleVertexArray->Unbind();
                }
            }
        }
    }

#pragma endregion 

#pragma region RigidbodyAndColliders

    void PhysicsEngine::DestroyRigidbody(Ref<Rigidbody> rigidbody)
    {
        if (m_PhysicsManager->m_Active)
        {
            m_PhysicsManager->DestroyRigidBody(rigidbody->GetCollisionBody());
            m_PhysicsManager->m_Rigidbodies[rigidbody->GetID()] = nullptr;
        }
    }

    Ref<Rigidbody>  PhysicsEngine::CreateRigidbody(GameObject& gameObject)
    {
        if (m_PhysicsManager->m_Active)
        {
            auto& transform = gameObject.Transform();
            auto rb = Rigidbody::Create({});
            rp3d::Transform reactTransform;
            reactTransform.setPosition(Math::ToRp3dVec3(transform.Position));
            reactTransform.setOrientation(Math::ToRp3dQuat(glm::quat(transform.Rotation)));
            rb->SetCollisionBody(m_PhysicsManager->m_PhysicsWorld->createCollisionBody(reactTransform));
            rb->SetID(m_PhysicsManager->m_TotalRigidBodies); // This returns a ID that's the index of the RB. Starting at 0
            m_PhysicsManager->m_Rigidbodies[rb->GetID()] = rb;
            m_PhysicsManager->m_TotalRigidBodies++;

            return rb;
        }
        return nullptr;
    }

    Ref<Collider>  PhysicsEngine::CreateBoxCollider(Ref<Rigidbody> rigidbody, const glm::vec3& halfExtents)
    {
        if (m_PhysicsManager->m_Active)
        {
            //Treat 1 unit as 1m.
            //Treat all objects with a density of 1kg/m3
            // IE a cube of 1x1x1 or 1m3 has a mass of 1kg
            constexpr float density = 1000.0f;
            const auto fullExtents = halfExtents * 2.0f;

            //Volume of a cube/box: V = length * width * height
            const auto volume = fullExtents.x * fullExtents.y * fullExtents.z;
            const float mass = density * volume;

            auto shape = m_PhysicsManager->m_PhysicsCommon.createBoxShape(Math::ToRp3dVec3(halfExtents * 2.0f));
            auto col = Collider::Create(shape, Collider::ColliderType::Box, mass);
            rigidbody->AddCollider(col);
            rigidbody->m_CollisionBody->addCollider(shape, rp3d::Transform::identity());
            return col;
        }
        return nullptr;
    }

    Ref<Collider>  PhysicsEngine::CreateSphereCollider(Ref<Rigidbody> rigidbody, const float& radius)
    {
        if (m_PhysicsManager->m_Active)
        {
            //Treat 1 unit as 1m.
            //Treat all objects with a density of 1kg/m3
            // IE a cube of 1x1x1 or 1m3 has a mass of 1kg
            constexpr float density = 1000.0f;

            //Volume of a Sphere: V = (4/3)πr3
            const float volume = (4 / 3) * glm::pi<float>() * glm::pow(radius, 3);
            float mass = density * volume;


            auto shape = m_PhysicsManager->m_PhysicsCommon.createSphereShape(radius);

            auto col = Collider::Create(shape, Collider::ColliderType::Sphere, mass);
            rigidbody->AddCollider(col);
            rigidbody->m_CollisionBody->addCollider(shape, rp3d::Transform::identity());
            return col;
        }
        return nullptr;
    }

    Ref<Collider>  PhysicsEngine::CreateCapsuleCollider(Ref<Rigidbody> rigidbody, const float& radius, const float& height)
    {
        if (m_PhysicsManager->m_Active)
        {
            //Treat 1 unit as 1m.
            //Treat all objects with a density of 1kg/m3
            // IE a cube of 1x1x1 or 1m3 has a mass of 1kg
            constexpr float density = 1000.0f;

            // Volume of a Capsule: V = πr2((4/3)r + a)
            const float volume = glm::pi<float>() * glm::pow(radius, 2) * ((4.0f / 3.0f) * glm::pi<float>() + height);
            const float mass = density * volume;

            auto shape = m_PhysicsManager->m_PhysicsCommon.createCapsuleShape(radius, height);

            auto col = Collider::Create(shape, Collider::ColliderType::Capsule, mass);
            rigidbody->AddCollider(col);
            rigidbody->m_CollisionBody->addCollider(shape, rp3d::Transform::identity());
            return col;
        }

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
        if (m_PhysicsLogger) m_PhysicsCommon.destroyDefaultLogger(m_PhysicsLogger);
        if (m_PhysicsWorld) m_PhysicsCommon.destroyPhysicsWorld(m_PhysicsWorld);
        m_Active = false;
    }

    rp3d::RigidBody* PhysicsManager::CreateRigidBody(const TransformComponent& transform) const
    {
        if (m_Active)
        {
            return m_PhysicsWorld->createRigidBody(Math::ToRp3dTransform(transform));
        }

        return nullptr;
    }

    void PhysicsManager::DestroyRigidBody(rp3d::CollisionBody* collisionBody) const
    {
        if (m_PhysicsWorld)
        {
            m_PhysicsWorld->destroyCollisionBody(collisionBody);
        }
    }

    void PhysicsManager::DestroyCollisionBody(rp3d::CollisionBody* body) const
    {
        if (m_PhysicsWorld)
        {
            m_PhysicsWorld->destroyCollisionBody(body);
        }
    }

    rp3d::CollisionBody* PhysicsManager::CreateCollisionBody(const TransformComponent& transform) const
    {
        if (m_Active)
        {
            return m_PhysicsWorld->createCollisionBody(Math::ToRp3dTransform(transform));
        }

        return nullptr;
    }

    void PhysicsManager::CreateColliderRenderer()
    {
        m_LinesVertexArray = VertexArray::Create();
        m_LinesVertexBuffer = VertexBuffer::Create();


        m_TraingleVertexArray = VertexArray::Create();
        m_TriangleVertexBuffer = VertexBuffer::Create();
        m_ColliderLayout = {
            {ShaderDataType::Float3, "a_Position"},
            {ShaderDataType::UInt, "a_VertexColor"}
        };
        m_LinesVertexBuffer->SetLayout(m_ColliderLayout);
        m_LinesVertexArray->AddVertexBuffer(m_LinesVertexBuffer);

        m_TriangleVertexBuffer->SetLayout(m_ColliderLayout);
        m_TraingleVertexArray->AddVertexBuffer(m_TriangleVertexBuffer);

        m_Shader = Shader::Create("Resources/shaders/default/physics/physics_vertex.glsl", "Resources/shaders/default/physics/physics_fragment.glsl");

        m_ColliderRendererInit = true;
    }



    bool PhysicsManager::Initialise(rp3d::EventListener* collisionEventListener)
    {
        m_PhysicsWorld = m_PhysicsCommon.createPhysicsWorld();
        if (m_PhysicsWorld == nullptr || collisionEventListener == nullptr)
            return false;

        m_PhysicsWorld->setEventListener(collisionEventListener);
        m_Active = true;

        return true;
    }

    void PhysicsManager::OnFixedUpdate(PhysicsTimestep timestep) const
    {
        m_PhysicsWorld->update(timestep.GetSimulationSpeed());
    }
#pragma endregion 



}