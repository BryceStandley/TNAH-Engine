#include <tnahpch.h>
#include "PhysicsComponents.h"
#include "TNAH/Scene/GameObject.h"

namespace tnah
{

#pragma region Rigidbody


    RigidBodyComponent::RigidBodyComponent()
    {
        if(Physics::PhysicsEngine::IsActive())
        {
            Body = Physics::RigidBody::Create({});
        }
    }

    RigidBodyComponent::RigidBodyComponent(GameObject& gameObject, const Physics::BodyType& type)
    {
        if(Physics::PhysicsEngine::IsActive())
        {
            Body = Physics::PhysicsEngine::CreateRigidbody(gameObject);
            Body->SetType(type);
            Body->GetCollisionBody()->setUserData(&gameObject);
        }
    }

    void RigidBodyComponent::OnUpdate(TransformComponent& transform)
    {
        Body->OnUpdate(transform);
    }
    

    void RigidBodyComponent::ApplyForce(const glm::vec3& direction, const glm::vec3& force)
    {
        if(Physics::PhysicsEngine::IsActive() && Body)
        {
            Body->AddForce(direction * force);
        }
    }

    void RigidBodyComponent::ApplyTorque(const glm::vec3& direction,const glm::vec3& torque)
    {
        if(Physics::PhysicsEngine::IsActive() && Body)
        {
            Body->AddForce(direction * torque);
        }
    }

    Ref<Physics::Collider> RigidBodyComponent::AddCollider(const glm::vec3& boxSize)
    {
        if(Physics::PhysicsEngine::IsActive() && Body)
        {
            return Physics::PhysicsEngine::CreateBoxCollider(Body, boxSize * 0.5f);
        }
        return nullptr;
    }

    Ref<Physics::Collider> RigidBodyComponent::AddCollider(const float& sphereRadius)
    {
        if(Physics::PhysicsEngine::IsActive() && Body)
        {
            return Physics::PhysicsEngine::CreateSphereCollider(Body, sphereRadius);
        }
        return nullptr;
    }

    Ref<Physics::Collider> RigidBodyComponent::AddCollider(const float& capsuleRadius, const float& capsuleHeight)
    {
        if(Physics::PhysicsEngine::IsActive() && Body)
        {
            return Physics::PhysicsEngine::CreateCapsuleCollider(Body, capsuleRadius, capsuleHeight);
        }
        return nullptr;
    }
#pragma endregion
 
}
