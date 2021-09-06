#pragma once
#pragma warning(push, 0)
#include <reactphysics3d/reactphysics3d.h>
#include "TNAH/Physics/PhysicsTimestep.h"
#include "TNAH/Scene/Components/Components.h"
#pragma warning(pop)
/*
namespace tnah
{
    class PhysicsCollision
    {
    public:
        PhysicsCollision();
        ~PhysicsCollision();
        bool Initialise(rp3d::EventListener * collisionEventListener);
        void onFixedUpdate(PhysicsTimestep timestep);
        void Destroy();
        rp3d::CollisionBody * CreateCollisionBody(TransformComponent transformValues);
        void DestoryCollisionBody(rp3d::CollisionBody * body);
    private:
        rp3d::PhysicsCommon m_Common;
        rp3d::PhysicsWorld * m_World;
        bool m_Active;
    };
    
    class Physics
    {
    public:
        static bool Initialise(rp3d::EventListener * collisionEventListener);
        static void onFixedUpdate(PhysicsTimestep timestep);
        static void Destory();
        static rp3d::CollisionBody * CreateCollisionBody(const TransformComponent transformValues);
        static void DestoryCollisionBody(rp3d::CollisionBody * body);

    private:
        static PhysicsCollision * m_CollisionSystem;
    };

    static rp3d::Vector3 ConvertGlmVec3ToRP3DVec3(glm::vec3 values)
    {
        return rp3d::Vector3(values.x, values.y, values.z);
    }

    static rp3d::Quaternion ConvertGlmQuatToRP3DQuat(glm::quat values)
    {
        return rp3d::Quaternion(values.x, values.y, values.z, values.w);
    }

    static rp3d::Transform ConvertTransformComponentToRP3DTransform(TransformComponent transformValues)
    {
        return rp3d::Transform(ConvertGlmVec3ToRP3DVec3(transformValues.Position), ConvertGlmQuatToRP3DQuat(glm::quat(transformValues.Rotation)));
    }
}
*/
