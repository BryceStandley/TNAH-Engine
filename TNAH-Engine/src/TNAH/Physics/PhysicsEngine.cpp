#include "tnahpch.h"
#include "PhysicsEngine.h"

#include "TNAH/Physics/Rigidbody.h"
#include "TNAH/Scene/GameObject.h"

namespace tnah::Physics
{
    
#pragma region Physics
    
    Ref<PhysicsManager>  PhysicsEngine::m_PhysicsManager = Ref<PhysicsManager>::Create();
    Ref<CollisionDetectionEngine> PhysicsManager::m_CollisionDetectionEngine = CollisionDetectionEngine::Create();
    TransformComponent  PhysicsEngine::m_ColliderTransform = TransformComponent();

#pragma region InitAndHelpers
    Ref<PhysicsManager>  PhysicsEngine::GetManager()
    {
        return m_PhysicsManager;
    }

    bool  PhysicsEngine::IsActive()
    {
        return m_PhysicsManager->m_Active;
    }

    bool  PhysicsEngine::Initialise(rp3d::EventListener* collisionEventListener)
    {
        const bool result = m_PhysicsManager->Initialise(collisionEventListener);
        ToggleColliderRendering();
        return result;
    }

    void  PhysicsEngine::ToggleColliderRendering()
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
            if(m_PhysicsManager->m_ColliderRender)
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

    void PhysicsEngine::ProcessCollisions()
    {
        while(!m_PhysicsManager->m_CollisionDetectionEngine->GetCurrentCollisions().empty())
        {
            //loop over the collisions data and process a response for the collision
            auto& collision =  m_PhysicsManager->m_CollisionDetectionEngine->GetCurrentCollisions().front();
            while(!collision.GetCollisionData().empty())
            {
                auto& item = collision.GetCollisionData().front();

                auto rb1 = item.GetRigidBodies().first;
                auto rb2 = item.GetRigidBodies().second;

                if((rb1->IsSleeping() || rb1->m_BodyType == BodyType::Static) && (rb2->IsSleeping() || rb2->m_BodyType == BodyType::Static))
                {
                    collision.GetCollisionData().pop();
                    continue;
                }
                constexpr float restitution = 0.6f;
		
                auto& t1 = item.GetGameObjects().first->Transform();
                glm::vec3 lv1 = rb1->GetLinearVelocity();
                glm::vec3 av1 = rb1->GetAngularVelocity();
                
                auto& t2 = item.GetGameObjects().second->Transform();
                glm::vec3 lv2 = rb2->GetLinearVelocity();
                glm::vec3 av2 = rb2->GetAngularVelocity();
               

                glm::vec3 cp1 = item.GetContactPositions().first;
                glm::vec3 cp2 = item.GetContactPositions().second;
                glm::vec3 cn = item.GetContactNormal();
		

                glm::vec3 r1 = cp1 - (t1.Position + rb1->GetBodyMass().WorldCentreOfMass);
                glm::vec3 r2 = cp2 - (t2.Position + rb2->GetBodyMass().WorldCentreOfMass);

                if(rb1->GetType() == BodyType::Dynamic && !rb1->IsSleeping())
                {
                    t1.Position += cn * ((item.GetPenetration() / 2.0f) * -1);
                }
                if(rb2->GetType() == BodyType::Dynamic && !rb2->IsSleeping())
                {
                    t2.Position -= cn * ((item.GetPenetration() / 2.0f) * -1);
                }
		
                //Transfer of momentum

                //         -(1 + ε) * (n̂ • (v⁻₁ - v⁻₂) + w⁻₁ • (r₁ x n̂) - w₂ • (r₂ x n̂))
                // __________________________________________________________________________ * n̂
                // (m₁⁻¹ + m₂⁻¹) + ((r₁ x n̂)ᵀ J₁⁻¹ * (r₁ x n̂) + (r₂ x n̂)ᵀ * J₂⁻¹ * (r₂ x n̂)

                //  -(1 + ε)
                auto restitution_multiplier = -(1.0f + restitution);

                // (v⁻₁ - v⁻₂)
                auto relative_velocity = lv1 - lv2;

                //(r₁ x n̂)
                auto r1xn = glm::cross(r1, cn);

                //(r₂ x n̂)
                auto r2xn = glm::cross(r2, cn);

                // (m₁⁻¹ + m₂⁻¹)
                auto total_inverse_mass = rb1->GetBodyMass().InverseMass + rb2->GetBodyMass().InverseMass;

                //-(1 + ε) * (n̂ • (v⁻₁ - v⁻₂) + w⁻₁ • (r₁ x n̂) - w₂ • (r₂ x n̂))
                auto numerator = restitution_multiplier * (glm::dot(cn, relative_velocity) + glm::dot(av1, r1xn) - glm::dot(av2, r2xn));

                // (m₁⁻¹ + m₂⁻¹) + ((r₁ x n̂)ᵀ * J₁⁻¹ * (r₁ x n̂) + (r₂ x n̂)ᵀ * J₂⁻¹ * (r₂ x n̂)
                float denominator = total_inverse_mass + (glm::dot(r1xn, rb1->GetInertiaTensor().WorldInverseInertiaTensor * r1xn) + glm::dot(r2xn, rb2->GetInertiaTensor().WorldInverseInertiaTensor * r2xn));

                //         -(1 + ε) * (n̂ • (v⁻₁ - v⁻₂) + w⁻₁ • (r₁ x n̂) - w₂ • (r₂ x n̂))
                // __________________________________________________________________________ * n̂
                // (m₁⁻¹ + m₂⁻¹) + ((r₁ x n̂)ᵀ * J₁⁻¹ * (r₁ x n̂) + (r₂ x n̂)ᵀ * J₂⁻¹ * (r₂ x n̂)

                //Transfer of momentum
                auto lambda = (numerator / denominator);

                //linear impulse
                auto linear_impulse = lambda * cn;

                
                

                if (lambda < 0)
                {
                    // v⁺₁ = v⁻₁
                    //lv1 += linear_impulse * rb1.Body->GetBodyMass().InverseMass;
                    lv1 += linear_impulse * rb1->GetBodyMass().InverseMass;
                    // v⁺₂ = v⁻₂
                    lv2 -= linear_impulse * rb2->GetBodyMass().InverseMass;

                    av1 = av1 + (lambda * rb1->GetInertiaTensor().WorldInverseInertiaTensor) * r1xn;
                    av2 = av2 -  (lambda * rb2->GetInertiaTensor().WorldInverseInertiaTensor) * r2xn;
                }
		
		
                if(rb1->GetType() == BodyType::Dynamic && !rb1->IsSleeping()) 
                {
                    rb1->m_LinearVelocity.Velocity = lv1;
                    rb1->m_AngularVelocity.Velocity = av1;
                }
                if(rb2->GetType() == BodyType::Dynamic && !rb2->IsSleeping())
                {
                    rb2->m_LinearVelocity.Velocity = lv2;
                    rb2->m_AngularVelocity.Velocity = av2;
                }
                collision.GetCollisionData().pop();
            }
            m_PhysicsManager->m_CollisionDetectionEngine->GetCurrentCollisions().pop();
        }
    }

    void PhysicsEngine::ProcessRigidbodyVelocities(const Timestep& deltaTime, TransformComponent& transform, Ref<RigidBody> rb)
    {
        for(auto r : m_PhysicsManager->m_Rigidbodies)
        {
            auto rigidbody = r.second;
            
            if(rigidbody->GetType() == BodyType::Dynamic && !rigidbody->IsSleeping())
            {
                const auto linear = rigidbody->m_LinearVelocity.Velocity;
                const auto angular = rigidbody->m_AngularVelocity.Velocity;
            
                rigidbody->m_ConstrainedLinearVelocity.Velocity = linear + deltaTime.GetSeconds() * rigidbody->GetBodyMass().InverseMass *
                                                                    rigidbody->m_LinearRotationLock * rigidbody->m_Force.Forces;
            
                rigidbody->m_ConstrainedAngularVelocity.Velocity = angular + deltaTime.GetSeconds() * rigidbody->m_AngularRotationLock *
                                                                    rigidbody->GetInertiaTensor().WorldInverseInertiaTensor * rigidbody->m_Torque.Torques;
            }

            if(m_PhysicsManager->GetGravityState() && rigidbody->GetType() == BodyType::Dynamic && !rigidbody->IsSleeping() && !rigidbody->IgnoreGravity())
            {
                rigidbody->m_ConstrainedLinearVelocity.Velocity += deltaTime.GetSeconds() * rigidbody->GetBodyMass().InverseMass *
                                                                    rigidbody->m_LinearRotationLock * rigidbody->GetBodyMass().Mass * m_PhysicsManager->GetGravity();
            }

            auto lDamp = glm::pow(1.0f - rigidbody->m_LinearDampening.Dampening, deltaTime.GetSeconds());
            auto aDamp = glm::pow(1.0f - rigidbody->m_AngularDampening.Dampening, deltaTime.GetSeconds());
            rigidbody->m_ConstrainedLinearVelocity.Velocity *= lDamp;
            rigidbody->m_ConstrainedAngularVelocity.Velocity *= aDamp;
        }
        
    }

    void PhysicsEngine::ProcessRigidbodyPositions(const Timestep& deltaTime,TransformComponent& transform, Ref<RigidBody> rigidbody)
    {
#if 0
        for(auto r : m_PhysicsManager->m_Rigidbodies)
        {
            auto rigidbody = r.second;
            auto transform = rigidbody->m_Transform;
            if(rigidbody->GetType() == BodyType::Dynamic)
            {
                transform->Position += rigidbody->m_ConstrainedLinearVelocity.Velocity * deltaTime.GetSeconds();

                glm::quat rot = glm::quat(transform->Rotation);
                
               rot += glm::quat(rigidbody->m_ConstrainedAngularVelocity.Velocity) * rot * 0.5f * deltaTime.GetSeconds();

                rp3d::Transform t;
                t.setPosition(Math::ToRp3dVec3(transform->Position));
                t.setOrientation(Math::ToRp3dQuat(rot));

                transform->Rotation = glm::eulerAngles(rot);
                rigidbody->m_CollisionBody->setTransform(t);
            }
        }
#endif

        transform.Position += rigidbody->m_ConstrainedLinearVelocity.Velocity * deltaTime.GetSeconds();

        glm::quat rot = glm::quat(transform.Rotation);
                
        rot += glm::quat(rigidbody->m_ConstrainedAngularVelocity.Velocity) * rot * 0.5f * deltaTime.GetSeconds();

        rp3d::Transform t;
        t.setPosition(Math::ToRp3dVec3(transform.Position));
        t.setOrientation(Math::ToRp3dQuat(rot));

        transform.Rotation = glm::eulerAngles(rot);
        rigidbody->m_CollisionBody->setTransform(t);
        
    }

    void PhysicsEngine::ResetRigidbodyForcesAndTorques(Ref<RigidBody> rb)
    {
        for(auto r : m_PhysicsManager->m_Rigidbodies)
        {
            
        }
        auto rigidbody = rb;
        rigidbody->m_Force.Forces = {0.0f, 0.0f, 0.0f};
        rigidbody->m_Torque.Torques = {0.0f, 0.0f, 0.0f};
    }

    void PhysicsEngine::UpdateInertiaTensor()
    {
        for(auto r : m_PhysicsManager->m_Rigidbodies)
        {
            auto m_InertiaTensor = r.second->m_InertiaTensor;
            glm::mat3 rot = glm::mat3_cast(glm::quat(r.second->m_Transform->Rotation));
            m_InertiaTensor.WorldInverseInertiaTensor[0][0] = rot[0][0] * m_InertiaTensor.LocalInverseInertiaTensor.x;
            m_InertiaTensor.WorldInverseInertiaTensor[0][1] = rot[1][0] * m_InertiaTensor.LocalInverseInertiaTensor.x;
            m_InertiaTensor.WorldInverseInertiaTensor[0][2] = rot[2][0] * m_InertiaTensor.LocalInverseInertiaTensor.x;
		
            m_InertiaTensor.WorldInverseInertiaTensor[1][0] = rot[0][1] * m_InertiaTensor.LocalInverseInertiaTensor.y;
            m_InertiaTensor.WorldInverseInertiaTensor[1][1] = rot[1][1] * m_InertiaTensor.LocalInverseInertiaTensor.y;
            m_InertiaTensor.WorldInverseInertiaTensor[1][2] = rot[2][1] * m_InertiaTensor.LocalInverseInertiaTensor.y;
		
            m_InertiaTensor.WorldInverseInertiaTensor[2][0] = rot[0][2] * m_InertiaTensor.LocalInverseInertiaTensor.z;
            m_InertiaTensor.WorldInverseInertiaTensor[2][1] = rot[1][2] * m_InertiaTensor.LocalInverseInertiaTensor.z;
            m_InertiaTensor.WorldInverseInertiaTensor[2][2] = rot[2][2] * m_InertiaTensor.LocalInverseInertiaTensor.z;

            m_InertiaTensor.WorldInverseInertiaTensor = rot * m_InertiaTensor.WorldInverseInertiaTensor;
            r.second->m_InertiaTensor = m_InertiaTensor;
        }
    }

    void PhysicsEngine::UpdateBodies()
    {
        for(auto r : m_PhysicsManager->m_Rigidbodies)
        {
            auto rigidbody = r.second;
            rigidbody->m_LinearVelocity.Velocity = rigidbody->m_ConstrainedLinearVelocity.Velocity;
            rigidbody->m_AngularVelocity.Velocity = rigidbody->m_ConstrainedAngularVelocity.Velocity;

            //m_CollisionBody->setTransform(Math::ToRp3dTransform(transform));
		
            auto position = rigidbody->m_Transform->Position;

            for(auto& col : rigidbody->m_Colliders)
            {
                col.second->SetPosition(position * col.second->GetColliderPosition());
                col.second->SetOrientation(glm::quat(rigidbody->m_Transform->Rotation) * col.second->GetColliderOrientation());
            }
        }
    }

    void  PhysicsEngine::OnFixedUpdate(Timestep deltaTime, PhysicsTimestep timestep, entt::registry& componentRegistry)
    {
        if(IsActive())
        {
            m_PhysicsManager->OnFixedUpdate(timestep);
            auto view = componentRegistry.view<TransformComponent, RigidBodyComponent>();
            for(auto entity : view)
            {
                auto& rb = view.get<RigidBodyComponent>(entity);
                auto& transform = view.get<TransformComponent>(entity);

                rb.Body->RecalculateWorldInertiaTensor(transform);
                //UpdateInertiaTensor();
                
                ProcessRigidbodyVelocities(deltaTime, transform, rb.Body);

                ProcessCollisions();
                
                ProcessRigidbodyPositions(deltaTime, transform, rb.Body);
                
                rb.OnUpdate(transform);
                //UpdateBodies();
                
                //TODO Add a update to make bodies sleep here
                
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
    
    bool&  PhysicsEngine::GetColliderRendererHandle()
    {
        return m_PhysicsManager->m_ColliderRender;
    }

    TransformComponent  PhysicsEngine::GetColliderRendererTransform()
    {
        if(m_PhysicsManager->m_Active)
        {
            return m_ColliderTransform;
        }
        
        return TransformComponent();

    }

    rp3d::DebugRenderer*  PhysicsEngine::GetColliderRenderer()
    {
        if(m_PhysicsManager->m_Active)
        {
            return &m_PhysicsManager->m_PhysicsWorld->getDebugRenderer();
        }
        return nullptr;
    }

    void  PhysicsEngine::EnableLogging()
    {
        if(IsActive())
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
        triangles.first = m_PhysicsManager->m_TriangleVertexArray;
        triangles.second = m_PhysicsManager->m_TriangleVertexBuffer;

        return {lines, triangles};
    }

    Ref<Shader>  PhysicsEngine::GetColliderShader()
    {
        return m_PhysicsManager->m_Shader;
    }

    void  PhysicsEngine::UpdateColliderRenderer()
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

#pragma region RigidbodyAndColliders

    void PhysicsEngine::DestroyRigidbody(Ref<RigidBody> rigidbody)
    {
        if(m_PhysicsManager->m_Active)
        {
            m_PhysicsManager->DestroyRigidBody(rigidbody->GetCollisionBody());
            m_PhysicsManager->m_Rigidbodies[rigidbody->GetID()] = nullptr;
        }
    }

    Ref<RigidBody>  PhysicsEngine::CreateRigidbody(GameObject& gameObject)
    {
        if(m_PhysicsManager->m_Active)
        {
            auto& transform = gameObject.Transform();
            auto rb = RigidBody::Create(&gameObject.Transform(), {});
            rp3d::Transform reactTransform;
            reactTransform.setPosition(Math::ToRp3dVec3(transform.Position));
            reactTransform.setOrientation(Math::ToRp3dQuat(glm::quat(transform.Rotation)));
            rb->SetCollisionBody(m_PhysicsManager->m_PhysicsWorld->createCollisionBody(reactTransform));
            rb->SetID(m_PhysicsManager->m_TotalRigidbodies); // This returns a ID that's the index of the RB. Starting at 0
            m_PhysicsManager->m_Rigidbodies[rb->GetID()] = rb; 
            m_PhysicsManager->m_TotalRigidbodies++;
            
            return rb;
        }
        return nullptr;
    }

    Ref<Collider>  PhysicsEngine::CreateBoxCollider(Ref<RigidBody> rigidbody, const glm::vec3& boxExtents)
    {
        if(m_PhysicsManager->m_Active)
        {
            auto shape =  m_PhysicsManager->m_PhysicsCommon.createBoxShape(Math::ToRp3dVec3(boxExtents));
            auto col = Collider::Create(shape, Collider::Type::Box);
            col->m_ID = m_PhysicsManager->m_TotalColliders;
            m_PhysicsManager->m_Colliders[col->m_ID] = col;
            m_PhysicsManager->m_TotalColliders++;
            rigidbody->AddCollider(col);
            rigidbody->m_CollisionBody->addCollider(shape, rp3d::Transform::identity());
            return col;
        }
        return nullptr;
    }

    Ref<Collider>  PhysicsEngine::CreateSphereCollider(Ref<RigidBody> rigidbody, const float& radius)
    {
        if(m_PhysicsManager->m_Active)
        {
            auto shape = m_PhysicsManager->m_PhysicsCommon.createSphereShape(radius);

            auto col = Collider::Create(shape, Collider::Type::Sphere);
            rigidbody->AddCollider(col);
            col->m_ID = m_PhysicsManager->m_TotalColliders;
            m_PhysicsManager->m_Colliders[col->m_ID] = col;
            m_PhysicsManager->m_TotalColliders++;
            rigidbody->m_CollisionBody->addCollider(shape, rp3d::Transform::identity());
            return col;
        }
        return nullptr;
    }

    Ref<Collider>  PhysicsEngine::CreateCapsuleCollider(Ref<RigidBody> rigidbody, const float& radius, const float& height)
    {
        if(m_PhysicsManager->m_Active)
        {
            auto shape =  m_PhysicsManager->m_PhysicsCommon.createCapsuleShape(radius, height);

            auto col = Collider::Create(shape, Collider::Type::Capsule);
            rigidbody->AddCollider(col);
            col->m_ID = m_PhysicsManager->m_TotalColliders;
            m_PhysicsManager->m_Colliders[col->m_ID] = col;
            m_PhysicsManager->m_TotalColliders++;
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

    void PhysicsManager::DestroyRigidBody(rp3d::CollisionBody* collisionBody) const
    {
        if(m_PhysicsWorld)
        {
            m_PhysicsWorld->destroyCollisionBody(collisionBody);
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
        //m_PhysicsWorld->update(timestep.GetSimulationSpeed());
        m_CollisionDetectionEngine->FixedUpdate(m_PhysicsWorld, timestep);
    }
#pragma endregion 



}
