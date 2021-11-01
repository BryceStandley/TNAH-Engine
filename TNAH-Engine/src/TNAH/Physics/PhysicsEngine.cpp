#include "tnahpch.h"
#include "PhysicsEngine.h"

//#include "TNAH/Debug/Debug.h"
#include "TNAH/Physics/Rigidbody.h"
#include "TNAH/Scene/GameObject.h"

namespace tnah::Physics
{
    
#pragma region Physics
    
    Ref<PhysicsManager>  PhysicsEngine::physicsManager = Ref<PhysicsManager>::Create();
    Ref<CollisionDetectionEngine> PhysicsManager::CollisionDetectionEngine = CollisionDetectionEngine::Create();
    TransformComponent  PhysicsEngine::ColliderTransform = TransformComponent();

#pragma region InitAndHelpers
    Ref<PhysicsManager>  PhysicsEngine::GetManager()
    {
        return physicsManager;
    }

    bool  PhysicsEngine::IsActive()
    {
        return physicsManager->Active;
    }

    bool  PhysicsEngine::Initialise(rp3d::EventListener* collisionEventListener)
    {
        const bool result = physicsManager->Initialise(collisionEventListener);
        ToggleColliderRendering();
        return result;
    }

    void  PhysicsEngine::ToggleColliderRendering()
    {
        if(physicsManager->Active)
        {
            physicsManager->ColliderRender = !physicsManager->ColliderRender;
            if(physicsManager->ColliderRendererInit)
            {
                physicsManager->PhysicsWorld->setIsDebugRenderingEnabled(physicsManager->ColliderRender);
            }
            else
            {
                ColliderTransform.Scale = glm::vec3(1.0f);
                physicsManager->CreateColliderRenderer();
                physicsManager->PhysicsWorld->setIsDebugRenderingEnabled(physicsManager->ColliderRender);
            }
            if(physicsManager->ColliderRender)
            {
                physicsManager->PhysicsWorld->getDebugRenderer().setIsDebugItemDisplayed(rp3d::DebugRenderer::DebugItem::COLLISION_SHAPE, true);
                physicsManager->PhysicsWorld->getDebugRenderer().setIsDebugItemDisplayed(rp3d::DebugRenderer::DebugItem::COLLIDER_AABB, true);
                physicsManager->PhysicsWorld->getDebugRenderer().setIsDebugItemDisplayed(rp3d::DebugRenderer::DebugItem::CONTACT_POINT, true);
                physicsManager->PhysicsWorld->getDebugRenderer().setIsDebugItemDisplayed(rp3d::DebugRenderer::DebugItem::CONTACT_NORMAL, true);
                physicsManager->PhysicsWorld->getDebugRenderer().setIsDebugItemDisplayed(rp3d::DebugRenderer::DebugItem::COLLIDER_BROADPHASE_AABB, true);
            }
            else
            {
                physicsManager->PhysicsWorld->getDebugRenderer().setIsDebugItemDisplayed(rp3d::DebugRenderer::DebugItem::COLLISION_SHAPE, false);
                physicsManager->PhysicsWorld->getDebugRenderer().setIsDebugItemDisplayed(rp3d::DebugRenderer::DebugItem::COLLIDER_AABB, false);
                physicsManager->PhysicsWorld->getDebugRenderer().setIsDebugItemDisplayed(rp3d::DebugRenderer::DebugItem::CONTACT_POINT, false);
                physicsManager->PhysicsWorld->getDebugRenderer().setIsDebugItemDisplayed(rp3d::DebugRenderer::DebugItem::CONTACT_NORMAL, false);
                physicsManager->PhysicsWorld->getDebugRenderer().setIsDebugItemDisplayed(rp3d::DebugRenderer::DebugItem::COLLIDER_BROADPHASE_AABB, false);
            }
            
        }
    }

    void  PhysicsEngine::PhysicsLoggerInit()
    {
        physicsManager->PhysicsLogger = physicsManager->PhysicsCommon.createDefaultLogger();
        const rp3d::uint logLevel = static_cast<rp3d::uint>(rp3d::Logger::Level::Warning) | static_cast<rp3d::uint>(rp3d::Logger::Level::Error) | static_cast<rp3d::uint>(rp3d::Logger::Level::Information);
        physicsManager->PhysicsLogger->addFileDestination("rp3d_log.html", logLevel, rp3d::DefaultLogger::Format::HTML);
        physicsManager->PhysicsCommon.setLogger(physicsManager->PhysicsLogger);
    }

    void PhysicsEngine::ProcessCollisions()
    {
        while(!physicsManager->CollisionDetectionEngine->GetCurrentCollisions().empty())
        {
            //loop over the collisions data and process a response for the collision
            auto& collision =  physicsManager->CollisionDetectionEngine->GetCurrentCollisions().front();
            while(!collision.GetCollisionData().empty())
            {
                auto& item = collision.GetCollisionData().front();

                auto rb1 = item.GetRigidBodies().first;
                auto rb2 = item.GetRigidBodies().second;
                
                constexpr float restitution = 0.4f;
		
                auto& t1 = item.GetGameObjects().first->Transform();
                glm::vec3 lv1 = rb1->GetLinearVelocity();
                glm::vec3 av1 = rb1->GetAngularVelocity();
                
                auto& t2 = item.GetGameObjects().second->Transform();
                glm::vec3 lv2 = rb2->GetLinearVelocity();
                glm::vec3 av2 = rb2->GetAngularVelocity();
                
                glm::vec3 cp1 = item.GetContactPositions().first;
                glm::vec3 cp2 = item.GetContactPositions().second;
                glm::vec3 cn = item.GetContactNormal();

                glm::vec3 r1 = cp1 - t1.Position;
                glm::vec3 r2 = cp2 - t2.Position;
                
                t1.Position += cn * ((item.GetPenetration() / 2.0f) * -1);

                t2.Position -= cn * ((item.GetPenetration() / 2.0f) * -1);

                auto restitution_multiplier = -(1.0f + restitution);

                auto relative_velocity = lv1 - lv2;

                auto r1xn = glm::cross(r1, cn);

                auto r2xn = glm::cross(r2, cn);
                
                auto total_inverse_mass = rb1->GetBodyMass().InverseMass + rb2->GetBodyMass().InverseMass;

                auto numerator = restitution_multiplier * (glm::dot(cn, relative_velocity) + glm::dot(av1, r1xn) - glm::dot(av2, r2xn));

                auto denominator = total_inverse_mass + (r1xn * rb1->GetInertiaTensor().WorldInverseInertiaTensor * r1xn) + (r2xn * rb2->GetInertiaTensor().WorldInverseInertiaTensor * r2xn);

                auto lambda = (numerator / denominator);
                
                auto linear_impulse = lambda * cn;
                
                lv1 += linear_impulse * rb1->GetBodyMass().InverseMass;
                av1 += (lambda * rb1->GetInertiaTensor().WorldInverseInertiaTensor * r1xn);
                rb1->linearVelocity.Velocity = lv1;
                rb1->angularVelocity.Velocity = av1;
                

                lv2 -= linear_impulse * rb2->GetBodyMass().InverseMass;
                av2 -=  (lambda * rb2->GetInertiaTensor().WorldInverseInertiaTensor * r2xn);
                rb2->linearVelocity.Velocity = lv2;
                rb2->angularVelocity.Velocity = av2;
                
                collision.GetCollisionData().pop();
            }
            physicsManager->CollisionDetectionEngine->GetCurrentCollisions().pop();
        }
    }

    void PhysicsEngine::ProcessRigidbodyVelocities(const Timestep& deltaTime, entt::registry& componentRegistry)
    {
        auto view = componentRegistry.view<RigidBodyComponent>();
        for(auto e : view)
        {
            auto& rb = view.get<RigidBodyComponent>(e).Body;
        
            rb->linearVelocity.Velocity += deltaTime.GetSeconds() * rb->GetBodyMass().InverseMass *
                                                                     rb->Force.Forces;
        
            rb->angularVelocity.Velocity += deltaTime.GetSeconds() *
                                                                    rb->GetInertiaTensor().WorldInverseInertiaTensor * rb->Torque.Torques;
                
        }
    }

    void PhysicsEngine::ProcessRigidbodyPositions(const Timestep& deltaTime, entt::registry& componentRegistry)
    {
        auto view = componentRegistry.view<TransformComponent, RigidBodyComponent>();
        for(auto e : view)
        {
            auto& rb = view.get<RigidBodyComponent>(e).Body;
            auto& trans = view.get<TransformComponent>(e);
                
                trans.Position += rb->linearVelocity.Velocity * deltaTime.GetSeconds();
                rb->Position = trans.Position;
                
                rb->Orientation += glm::quat(0.0, rb->angularVelocity) * deltaTime.GetSeconds();
                rb->Orientation = glm::normalize(rb->Orientation);
                
                //rb->LinearVelocity = glm::vec3(0, rb->LinearVelocity.Velocity.y, 0);
                trans.Position += rb->linearVelocity.Velocity * deltaTime.GetSeconds();
                rb->Position = trans.Position;
        }
    }

    void PhysicsEngine::ResetRigidbodyForcesAndTorques(entt::registry& componentRegistry)
    {
        auto view = componentRegistry.view<RigidBodyComponent>();
        for(auto e : view)
        {
            auto& rigidbody = view.get<RigidBodyComponent>(e).Body;
            rigidbody->Force.Forces = {0.0f, 0.0f, 0.0f};
            rigidbody->Torque.Torques = {0.0f, 0.0f, 0.0f};
        }
    }

    void PhysicsEngine::UpdateInertiaTensor(entt::registry& componentRegistry)
    {
        auto view = componentRegistry.view<TransformComponent, RigidBodyComponent>();
        for(auto e : view)
        {
            auto& rb = view.get<RigidBodyComponent>(e).Body;
            auto& trans = view.get<TransformComponent>(e);
            glm::mat3 rot = glm::mat3_cast(rb->Orientation);
            rb->InertiaTensor.WorldInverseInertiaTensor[0][0] = rot[0][0] * rb->InertiaTensor.LocalInverseInertiaTensor.x;
            rb->InertiaTensor.WorldInverseInertiaTensor[0][1] = rot[1][0] * rb->InertiaTensor.LocalInverseInertiaTensor.x;
            rb->InertiaTensor.WorldInverseInertiaTensor[0][2] = rot[2][0] * rb->InertiaTensor.LocalInverseInertiaTensor.x;
	
            rb->InertiaTensor.WorldInverseInertiaTensor[1][0] = rot[0][1] * rb->InertiaTensor.LocalInverseInertiaTensor.y;
            rb->InertiaTensor.WorldInverseInertiaTensor[1][1] = rot[1][1] * rb->InertiaTensor.LocalInverseInertiaTensor.y;
            rb->InertiaTensor.WorldInverseInertiaTensor[1][2] = rot[2][1] * rb->InertiaTensor.LocalInverseInertiaTensor.y;
	
            rb->InertiaTensor.WorldInverseInertiaTensor[2][0] = rot[0][2] * rb->InertiaTensor.LocalInverseInertiaTensor.z;
            rb->InertiaTensor.WorldInverseInertiaTensor[2][1] = rot[1][2] * rb->InertiaTensor.LocalInverseInertiaTensor.z;
            rb->InertiaTensor.WorldInverseInertiaTensor[2][2] = rot[2][2] * rb->InertiaTensor.LocalInverseInertiaTensor.z;

            rb->InertiaTensor.WorldInverseInertiaTensor = rot * rb->InertiaTensor.WorldInverseInertiaTensor;
        }
    }

    void PhysicsEngine::UpdateBodies(entt::registry& componentRegistry)
    {
        auto view = componentRegistry.view<TransformComponent, RigidBodyComponent>();
        for(auto e : view)
        {
            auto& rb = view.get<RigidBodyComponent>(e).Body;
            auto& transform = view.get<TransformComponent>(e);
            
            rb->OnUpdate(transform);
            
            rb->linearVelocity.Velocity = rb->linearVelocity.Velocity;
            rb->angularVelocity.Velocity = rb->angularVelocity.Velocity;

            auto t = rb->CollisionBody->getTransform();
            t.setPosition(Math::ToRp3dVec3(rb->Position));
                t.setOrientation(Math::ToRp3dQuat(rb->Orientation));
                rb->CollisionBody->setTransform(t);
                transform.Rotation = glm::eulerAngles(rb->Orientation);
                transform.QuatRotation = rb->Orientation;

            for(auto& c : rb->Colliders)
            {
                auto col = c.second;
                col->SetPosition(transform.Position + col->GetColliderPosition());
                col->SetOrientation(rb->Orientation + col->GetColliderOrientation());
            }
        }
    }

  

    void  PhysicsEngine::OnFixedUpdate(Timestep deltaTime, PhysicsTimestep timestep, entt::registry& componentRegistry)
    {
        if(IsActive())
        {
            auto ts = timestep;
            ts.SetSimulationSpeed(deltaTime.GetSeconds());
            physicsManager->OnFixedUpdate(deltaTime, timestep);

            UpdateInertiaTensor(componentRegistry);
            
            ProcessCollisions();
            
            ProcessRigidbodyVelocities(deltaTime, componentRegistry);

            ProcessRigidbodyPositions(deltaTime, componentRegistry);

            UpdateBodies(componentRegistry);

            ResetRigidbodyForcesAndTorques(componentRegistry);
        }
    }

    void  PhysicsEngine::OnUpdate(Timestep timestep)
    {
        UpdateColliderRenderer();
    }

    void  PhysicsEngine::Destroy()
    {
        physicsManager->Destroy();
    }
    
#pragma endregion 

#pragma region ColliderRenderer
    
    bool&  PhysicsEngine::GetColliderRendererHandle()
    {
        return physicsManager->ColliderRender;
    }

    TransformComponent  PhysicsEngine::GetColliderRendererTransform()
    {
        if(physicsManager->Active)
        {
            return ColliderTransform;
        }
        
        return TransformComponent();

    }

    rp3d::DebugRenderer*  PhysicsEngine::GetColliderRenderer()
    {
        if(physicsManager->Active)
        {
            return &physicsManager->PhysicsWorld->getDebugRenderer();
        }
        return nullptr;
    }

    void  PhysicsEngine::EnableLogging()
    {
        if(IsActive())
        {
            physicsManager->Logging = true;
            PhysicsLoggerInit();
        }
    }

    bool  PhysicsEngine::IsColliderRenderingEnabled()
    {
        return physicsManager->ColliderRender;
    }

    std::pair<std::pair<Ref<VertexArray>, Ref<VertexBuffer>>, std::pair<Ref<VertexArray>, Ref<VertexBuffer>>>  PhysicsEngine::
    GetColliderRenderObjects()
    {
        std::pair<Ref<VertexArray>, Ref<VertexBuffer>> lines;
        lines.first = physicsManager->LinesVertexArray;
        lines.second = physicsManager->LinesVertexBuffer;

        std::pair<Ref<VertexArray>, Ref<VertexBuffer>> triangles;
        triangles.first = physicsManager->TriangleVertexArray;
        triangles.second = physicsManager->TriangleVertexBuffer;

        return {lines, triangles};
    }

    Ref<Shader>  PhysicsEngine::GetColliderShader()
    {
        return physicsManager->Shader;
    }

    void  PhysicsEngine::UpdateColliderRenderer()
    {
        if(physicsManager->Active)
        {
            //Check and return if the collider rendering objects haven't been created yet
            // Only check one object, if one is null then they all are
            if(physicsManager->LinesVertexArray == nullptr) return;
            if(!physicsManager->ColliderRendererInit) return;

            //Check and only update if we really want to render the colliders
            if(physicsManager->ColliderRender)
            {
                auto renderer = GetColliderRenderer();
                const rp3d::uint nbLines = renderer->getNbLines();
                if(nbLines > 0)
                {
                    const uint32_t size = nbLines * sizeof(rp3d::DebugRenderer::DebugLine);
                    physicsManager->LinesVertexArray->Bind();
                    physicsManager->LinesVertexBuffer->SetData(size, renderer->getLinesArray(), DrawType::STREAM, TypeMode::DRAW);
                    physicsManager->LinesVertexArray->SetIndexSize(nbLines * 2);

                    VertexBufferLayout layout = physicsManager->LinesVertexBuffer->GetLayout();
                    layout.SetStride(sizeof(rp3d::Vector3) + sizeof(rp3d::uint32));
                    auto& elements = layout.GetElements();
                    elements.at(1).Offset = sizeof(rp3d::Vector3);
                    physicsManager->LinesVertexBuffer->SetLayout(layout);
                    physicsManager->LinesVertexBuffer->Unbind();
                    physicsManager->LinesVertexArray->Unbind();
                }

                // Triangles
                const rp3d::uint nbTriangles = renderer->getNbTriangles();
                if(nbTriangles > 0)
                {
                    const uint32_t size = nbTriangles * sizeof(rp3d::DebugRenderer::DebugTriangle);
                    physicsManager->TriangleVertexArray->Bind();
                    physicsManager->TriangleVertexBuffer->SetData(size, renderer->getTrianglesArray(), DrawType::STREAM, TypeMode::DRAW);
                    physicsManager->TriangleVertexArray->SetIndexSize(nbTriangles * 3);

                    VertexBufferLayout layout = physicsManager->TriangleVertexBuffer->GetLayout();
                    layout.SetStride(sizeof(rp3d::Vector3) + sizeof(rp3d::uint32));
                    auto& elements = layout.GetElements();
                    elements.at(1).Offset = sizeof(rp3d::Vector3);
                    physicsManager->TriangleVertexBuffer->SetLayout(layout);
                    physicsManager->TriangleVertexBuffer->Unbind();
                    physicsManager->TriangleVertexArray->Unbind();
                }
            }
        }
    }
    
#pragma endregion 

#pragma region RigidbodyAndColliders

    void PhysicsEngine::DestroyRigidbody(Ref<RigidBody> rigidbody)
    {
        if(physicsManager->Active)
        {
            physicsManager->DestroyRigidBody(rigidbody->GetCollisionBody());
            physicsManager->Rigidbodies[rigidbody->GetID()] = nullptr;
        }
    }

    Ref<RigidBody>  PhysicsEngine::CreateRigidbody(GameObject& gameObject)
    {
        if(physicsManager->Active)
        {
            auto& transform = gameObject.Transform();
            auto rb = RigidBody::Create(gameObject.Transform(), {});
            rp3d::Transform reactTransform;
            reactTransform.setPosition(Math::ToRp3dVec3(transform.Position));
            reactTransform.setOrientation(Math::ToRp3dQuat(transform.QuatRotation));
            rb->SetCollisionBody(physicsManager->PhysicsWorld->createCollisionBody(reactTransform));
            rb->SetID(physicsManager->TotalRigidbodies); // This returns a ID that's the index of the RB. Starting at 0
            physicsManager->Rigidbodies[rb->GetID()] = rb; 
            physicsManager->TotalRigidbodies++;
            
            return rb;
        }
        return nullptr;
    }

    Ref<Collider>  PhysicsEngine::CreateBoxCollider(Ref<RigidBody> rigidbody, const glm::vec3& boxExtents)
    {
        if(physicsManager->Active)
        {
            auto shape =  physicsManager->PhysicsCommon.createBoxShape(Math::ToRp3dVec3(boxExtents));
            auto col = Collider::Create(shape, Collider::Type::Box);
            col->ID = physicsManager->TotalColliders;
            physicsManager->Colliders[col->ID] = col;
            physicsManager->TotalColliders++;
            rigidbody->AddCollider(col);
            rigidbody->CollisionBody->addCollider(shape, rp3d::Transform::identity());
            return col;
        }
        return nullptr;
    }

    Ref<Collider>  PhysicsEngine::CreateSphereCollider(Ref<RigidBody> rigidbody, const float& radius)
    {
        if(physicsManager->Active)
        {
            auto shape = physicsManager->PhysicsCommon.createSphereShape(radius);

            auto col = Collider::Create(shape, Collider::Type::Sphere);
            rigidbody->AddCollider(col);
            col->ID = physicsManager->TotalColliders;
            physicsManager->Colliders[col->ID] = col;
            physicsManager->TotalColliders++;
            rigidbody->CollisionBody->addCollider(shape, rp3d::Transform::identity());
            return col;
        }
        return nullptr;
    }

    Ref<Collider>  PhysicsEngine::CreateCapsuleCollider(Ref<RigidBody> rigidbody, const float& radius, const float& height)
    {
        if(physicsManager->Active)
        {
            auto shape =  physicsManager->PhysicsCommon.createCapsuleShape(radius, height);

            auto col = Collider::Create(shape, Collider::Type::Capsule);
            rigidbody->AddCollider(col);
            col->ID = physicsManager->TotalColliders;
            physicsManager->Colliders[col->ID] = col;
            physicsManager->TotalColliders++;
            rigidbody->CollisionBody->addCollider(shape, rp3d::Transform::identity());
            return col;
        }

        return nullptr;
    }
    
#pragma endregion 

#pragma endregion

    
 /***************************************/

    
#pragma region physicsManager
        
    PhysicsManager::PhysicsManager()
    {
    }

    PhysicsManager::~PhysicsManager()
    {
        Destroy();
    }

    void PhysicsManager::Destroy()
    {
        if(PhysicsLogger) PhysicsCommon.destroyDefaultLogger(PhysicsLogger);
        if(PhysicsWorld) PhysicsCommon.destroyPhysicsWorld(PhysicsWorld);
        Active = false;
    }

    rp3d::RigidBody* PhysicsManager::CreateRigidBody(const TransformComponent& transform) const
    {
        if(Active)
        {
            return PhysicsWorld->createRigidBody(Math::ToRp3dTransform(transform));
        }

        return nullptr;
    }

    void PhysicsManager::DestroyRigidBody(rp3d::CollisionBody* collisionBody) const
    {
        if(PhysicsWorld)
        {
            PhysicsWorld->destroyCollisionBody(collisionBody);
        }
    }

    void PhysicsManager::DestroyCollisionBody(rp3d::CollisionBody* body) const
    {
        if(PhysicsWorld)
        {
            PhysicsWorld->destroyCollisionBody(body);
        }
    }
    
    rp3d::CollisionBody* PhysicsManager::CreateCollisionBody(const TransformComponent& transform) const
    {
        if(Active)
        {
            return PhysicsWorld->createCollisionBody(Math::ToRp3dTransform(transform));
        }
        
        return nullptr;
    }

    void PhysicsManager::CreateColliderRenderer()
    {
        LinesVertexArray = VertexArray::Create();
        LinesVertexBuffer = VertexBuffer::Create();


        TriangleVertexArray = VertexArray::Create();
        TriangleVertexBuffer = VertexBuffer::Create();
        ColliderLayout = {
            {ShaderDataType::Float3, "a_Position"},
            {ShaderDataType::UInt, "a_VertexColor"}
        };
        LinesVertexBuffer->SetLayout(ColliderLayout);
        LinesVertexArray->AddVertexBuffer(LinesVertexBuffer);

        TriangleVertexBuffer->SetLayout(ColliderLayout);
        TriangleVertexArray->AddVertexBuffer(TriangleVertexBuffer);
        
        Shader = Shader::Create("Resources/shaders/default/physics/physics_vertex.glsl","Resources/shaders/default/physics/physics_fragment.glsl");

        ColliderRendererInit = true;
    }

    
    
    bool PhysicsManager::Initialise(rp3d::EventListener* collisionEventListener)
    {
        PhysicsWorld = PhysicsCommon.createPhysicsWorld();
        if(PhysicsWorld == nullptr || collisionEventListener == nullptr)
            return false;
        
        PhysicsWorld->setEventListener(collisionEventListener);
        Active = true;
        
        return true;
    }

    void PhysicsManager::OnFixedUpdate(Timestep deltaTime, PhysicsTimestep timestep) const
    {
        //PhysicsWorld->update(timestep.GetSimulationSpeed());
        CollisionDetectionEngine->FixedUpdate(PhysicsWorld, deltaTime.GetSeconds());
    }
#pragma endregion 



}
