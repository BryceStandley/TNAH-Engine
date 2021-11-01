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
                physicsManager->PhysicsWorld->getDebugRenderer().setIsDebugItemDisplayed(rp3d::DebugRenderer::DebugItem::COLLIDER_BROADPHASE_AABB, false);
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

    void PhysicsEngine::Collisions()
    {
        while(!physicsManager->CollisionDetectionEngine->GetCurrentCollisions().empty())
        {
            auto& collision =  physicsManager->CollisionDetectionEngine->GetCurrentCollisions().front();
            while(!collision.GetCollisionData().empty())
            {
                PhysicsCollision::CollisionData& collisionCallback = collision.GetCollisionData().front();

                //Rigidbodies
                Ref<RigidBody> rigidbodyOne = collisionCallback.GetRigidBodies().first;
                Ref<RigidBody> rigidbodyTwo = collisionCallback.GetRigidBodies().second;

                //Velocities One
                glm::vec3 linearVelocityOne = rigidbodyOne->GetLinearVelocity();
                glm::vec3 angularVelocityOne = rigidbodyOne->GetAngularVelocity();

                //Velocities Two
                glm::vec3 linearVelocityTwo = rigidbodyTwo->GetLinearVelocity();
                glm::vec3 angularVelocityTwo = rigidbodyTwo->GetAngularVelocity();

                //Contact points
                glm::vec3 contactPointOne = collisionCallback.GetContactPositions().first;
                glm::vec3 contactPointTwo = collisionCallback.GetContactPositions().second;

                //Contact normals
                glm::vec3 contactNormal = collisionCallback.GetContactNormal();

                //Rigidbody contacts
                glm::vec3 rigidbodyContactOne = contactPointOne - rigidbodyOne->bodyMass.WorldCentreOfMass;
                glm::vec3 rigidbodyContactTwo = contactPointTwo - rigidbodyTwo->bodyMass.WorldCentreOfMass;

                //Difference in velocity
                glm::vec3 velocityDifference = linearVelocityOne - linearVelocityTwo;

                //Normals cross rigidbody contacts
                glm::vec rigidbodyCrossOne = glm::cross(rigidbodyContactOne, contactNormal);
                glm::vec3 rigidbodyCrossTwo = glm::cross(rigidbodyContactTwo, contactNormal);

                //Numerator (top part of the equation for frictionless collision)
                constexpr float restitution = -1.4;
                float velocityDifferenceContact = glm::dot(contactNormal, velocityDifference);
                float angularCrossOne = glm::dot(angularVelocityOne, rigidbodyCrossOne);
                float angularCrossTwo = glm::dot(angularVelocityTwo, rigidbodyCrossTwo);
                float numerator = restitution * (velocityDifferenceContact + angularCrossOne - angularCrossTwo);

                //Denominator (bottom part of equation)
                float inverseMass = rigidbodyOne->GetBodyMass().InverseMass + rigidbodyTwo->GetBodyMass().InverseMass;
                float inertiaDot = glm::dot((rigidbodyCrossOne * rigidbodyOne->GetInertiaTensor().WorldInverseInertiaTensor * rigidbodyCrossOne),
                                            (rigidbodyCrossTwo * rigidbodyTwo->GetInertiaTensor().WorldInverseInertiaTensor * rigidbodyCrossTwo));
                float denominator = inverseMass + inertiaDot;

                //Big Equation Value
                float lambda = (numerator / denominator);

                //Big Equation * contact normal
                glm::vec3 impulse = lambda * contactNormal;
                
                linearVelocityOne += impulse * rigidbodyOne->GetBodyMass().InverseMass;
                angularVelocityOne += lambda * rigidbodyOne->GetInertiaTensor().WorldInverseInertiaTensor * rigidbodyCrossOne;
                rigidbodyOne->linearVelocity.Velocity = linearVelocityOne;
                rigidbodyOne->angularVelocity.Velocity = angularVelocityOne;
                
                linearVelocityTwo -= impulse * rigidbodyTwo->GetBodyMass().InverseMass;
                angularVelocityTwo -=  lambda * rigidbodyTwo->GetInertiaTensor().WorldInverseInertiaTensor * rigidbodyCrossTwo;
                rigidbodyTwo->linearVelocity.Velocity = linearVelocityTwo;
                rigidbodyTwo->angularVelocity.Velocity = angularVelocityTwo;

                //Penetration, this is done as it sits within the other body otherwise
                TransformComponent& transformTwo = collisionCallback.GetGameObjects().second->Transform();
                TransformComponent& transformOne = collisionCallback.GetGameObjects().first->Transform();
                transformOne.Position += contactNormal * ((collisionCallback.GetPenetration() / 2.0f) * -1);
                transformTwo.Position -= contactNormal * ((collisionCallback.GetPenetration() / 2.0f) * -1);
                
                collision.GetCollisionData().pop();
            }
            physicsManager->CollisionDetectionEngine->GetCurrentCollisions().pop();
        }
    }

    void PhysicsEngine::Velocities(const float& deltaTime, RigidBodyComponent& rb, TransformComponent& transform)
    {
        
            rb.Body->linearVelocity.Velocity += deltaTime * rb.Body->GetBodyMass().InverseMass * rb.Body->Force.Forces;
        
            rb.Body->angularVelocity.Velocity += deltaTime * rb.Body->GetInertiaTensor().WorldInverseInertiaTensor * rb.Body->Torque.Torques;

    }

    void PhysicsEngine::Positions(const float& deltaTime, RigidBodyComponent& rb, TransformComponent& transform)
    {
        transform.Position += rb.Body->linearVelocity.Velocity * deltaTime;
        rb.Body->centralPosition = transform.Position;
                
        rb.Body->Orientation += glm::quat(0.0, rb.Body->angularVelocity) * deltaTime;
        rb.Body->Orientation = glm::normalize(rb.Body->Orientation);
        
        transform.Position += rb.Body->linearVelocity.Velocity * deltaTime;
        rb.Body->centralPosition = transform.Position;
    }

    void PhysicsEngine::ForcesAndTorques(RigidBodyComponent& rb, TransformComponent& transform)
    {
            rb.Body->Force.Forces = {0.0f, 0.0f, 0.0f};
            rb.Body->Torque.Torques = {0.0f, 0.0f, 0.0f};
    }

    void PhysicsEngine::InertiaTensors(RigidBodyComponent& rb, TransformComponent& transform)
    {
            glm::mat3 rot = glm::mat3_cast(rb.Body->Orientation);
            rb.Body->InertiaTensor.WorldInverseInertiaTensor[0][0] = rot[0][0] * rb.Body->InertiaTensor.LocalInverseInertiaTensor.x;
            rb.Body->InertiaTensor.WorldInverseInertiaTensor[0][1] = rot[1][0] * rb.Body->InertiaTensor.LocalInverseInertiaTensor.x;
            rb.Body->InertiaTensor.WorldInverseInertiaTensor[0][2] = rot[2][0] * rb.Body->InertiaTensor.LocalInverseInertiaTensor.x;
	
            rb.Body->InertiaTensor.WorldInverseInertiaTensor[1][0] = rot[0][1] * rb.Body->InertiaTensor.LocalInverseInertiaTensor.y;
            rb.Body->InertiaTensor.WorldInverseInertiaTensor[1][1] = rot[1][1] * rb.Body->InertiaTensor.LocalInverseInertiaTensor.y;
            rb.Body->InertiaTensor.WorldInverseInertiaTensor[1][2] = rot[2][1] * rb.Body->InertiaTensor.LocalInverseInertiaTensor.y;
	
            rb.Body->InertiaTensor.WorldInverseInertiaTensor[2][0] = rot[0][2] * rb.Body->InertiaTensor.LocalInverseInertiaTensor.z;
            rb.Body->InertiaTensor.WorldInverseInertiaTensor[2][1] = rot[1][2] * rb.Body->InertiaTensor.LocalInverseInertiaTensor.z;
            rb.Body->InertiaTensor.WorldInverseInertiaTensor[2][2] = rot[2][2] * rb.Body->InertiaTensor.LocalInverseInertiaTensor.z;

            rb.Body->InertiaTensor.WorldInverseInertiaTensor = rot * rb.Body->InertiaTensor.WorldInverseInertiaTensor;
    }

    void PhysicsEngine::UpdateRbs(RigidBodyComponent& rb, TransformComponent& transform)
    {
            rb.Body->OnUpdate(transform);

            rp3d::Transform t = rb.Body->CollisionBody->getTransform();
            t.setPosition(Math::ToRp3dVec3(rb.Body->centralPosition));
                t.setOrientation(Math::ToRp3dQuat(rb.Body->Orientation));
                rb.Body->CollisionBody->setTransform(t);
        transform.Rotation = glm::eulerAngles(rb.Body->Orientation);
        transform.QuatRotation = rb.Body->Orientation;

            for(std::pair<const unsigned, Ref<Collider>>& c : rb.Body->Colliders)
            {
                Ref<Collider> col = c.second;
                col->SetPosition(transform.Position + col->GetColliderPosition());
                col->SetOrientation(rb.Body->Orientation + col->GetColliderOrientation());
            }
    }

  

    void  PhysicsEngine::OnFixedUpdate(float deltaTime, entt::registry& componentRegistry)
    {
        if(IsActive())
        {
            physicsManager->OnFixedUpdate(deltaTime);
            
            Collisions();

            entt::basic_view<entt::entity, entt::exclude_t<>, TransformComponent, RigidBodyComponent> view = componentRegistry.view<TransformComponent, RigidBodyComponent>();
            
            for(entt::entity entity : view)
            {
                RigidBodyComponent& rb = view.get<RigidBodyComponent>(entity);
                TransformComponent& transform = view.get<TransformComponent>(entity);
                
                Velocities(deltaTime, rb, transform);

                Positions(deltaTime, rb, transform);

                UpdateRbs(rb, transform);

                ForcesAndTorques(rb, transform);
                InertiaTensors(rb, transform);
            }
        }
    }

    void  PhysicsEngine::OnUpdate()
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

    void PhysicsManager::OnFixedUpdate(float deltaTime) const
    {
        CollisionDetectionEngine->FixedUpdate(PhysicsWorld, deltaTime);
    }
#pragma endregion 



}
