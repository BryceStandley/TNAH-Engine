#include "tnahpch.h"
/*#include "Physics.h"

namespace tnah
{
    PhysicsCollision * Physics::m_CollisionSystem = new PhysicsCollision();

    bool Physics::Initialise(rp3d::EventListener* collisionEventListener)
    {
        return m_CollisionSystem->Initialise(collisionEventListener);
    }

    rp3d::CollisionBody* Physics::CreateCollisionBody(const TransformComponent transformValues)
    {
        return m_CollisionSystem->CreateCollisionBody(transformValues);
    }

    void Physics::DestoryCollisionBody(rp3d::CollisionBody* body)
    {
        m_CollisionSystem->DestoryCollisionBody(body);
    }

    void Physics::onFixedUpdate(PhysicsTimestep timestep)
    {
        m_CollisionSystem->onFixedUpdate(timestep);
    }

    void Physics::Destory()
    {
        m_CollisionSystem->Destroy();
    }
    
    PhysicsCollision::PhysicsCollision()
    {
        m_Active = false;
    }

    PhysicsCollision::~PhysicsCollision()
    {
        Destroy();
    }

    void PhysicsCollision::Destroy()
    {
        m_Common.destroyPhysicsWorld(m_World);
        m_Active = false;
    }

    void PhysicsCollision::DestoryCollisionBody(rp3d::CollisionBody* body)
    {
        m_World->destroyCollisionBody(body);
    }

    rp3d::CollisionBody* PhysicsCollision::CreateCollisionBody(const TransformComponent transformValues)
    {
        if(m_Active)
            return m_World->createCollisionBody(ConvertTransformComponentToRP3DTransform(transformValues));

        return nullptr;
    }
    
    bool PhysicsCollision::Initialise(rp3d::EventListener * collisionEventListener)
    {
        m_World = m_Common.createPhysicsWorld();
        if(m_World == nullptr || collisionEventListener == nullptr)
            return false;
        
        m_World->setEventListener(collisionEventListener);
        m_Active = true;
        return true;
    }

    void PhysicsCollision::onFixedUpdate(PhysicsTimestep timestep)
    {
        
    }


}*/