#include "tnahpch.h"
#include "ReactPhysics.h"

namespace tnah
{
    ReactPhysics::~ReactPhysics()
    {
        TNAH_CORE_INFO("Destruction of React Physics Called");
    }

    Ref<RigidBody> ReactPhysics::CreateRigidBody(const TransformComponent& transform)
    {
        m_RigidBody[uniqueIds] = ReactRigidBody(Ref<RigidBody>::Create(uniqueIds), m_PhysicsWorld->createRigidBody(Math::ToRp3dTransform(transform)));
        if(m_RigidBody[uniqueIds].m_RigidBody != nullptr || m_RigidBody[uniqueIds].m_Body != nullptr)
        {
            uniqueIds++;
            return m_RigidBody[uniqueIds].m_RigidBody;
        }

        TNAH_CORE_ASSERT(false, "Did not create a rigidbody - React Physics 3D");
        return nullptr;
    }

    void ReactPhysics::OnFixedUpdate()
    {
        TNAH_CORE_ERROR("Physics OnFixedUpdate not currently supported");
    }

    void ReactPhysics::UpdateRigidBodies()
    {
        TNAH_CORE_ERROR("RigidBody Update not currently supported");
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

}