#include "tnahpch.h"
#include "TnahRigidBody.h"

namespace tnah
{
    TnahRigidBodyComponent::TnahRigidBodyComponent()
    {
        if(Physics::IsActive())
        {
            TransformComponent tt;
            Body = Physics::CreateCollisionBody(tt);
        }
    }
    
    TnahRigidBodyComponent::TnahRigidBodyComponent(const TransformComponent& transform)
    {
        if(Physics::IsActive())
        {
            Body = Physics::CreateCollisionBody(transform);
        }
    }
    
    rp3d::Collider* TnahRigidBodyComponent::AddCollider(rp3d::CollisionShape* collider, const rp3d::Transform &transform)
    {
        if(Physics::IsActive() && Body)
        {
            return Body->addCollider(collider, transform);
        }
    
        return nullptr;
    }
}
