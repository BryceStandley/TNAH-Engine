#pragma once
#include "TNAH/Physics/PhysicsMath.h"
namespace tnah
{
    struct RigidBodyValues
    {
        enum Type
        {
            Dynamic = 0, Kinematic = 1
        };
        
        RigidBodyValues() = default;
        RigidBodyValues(unsigned int id, Type t = Kinematic, glm::vec3 pos = glm::vec3(0), glm::vec3 rot = glm::vec3(0)) : unique_id(id), type(t), position(pos), rotation(glm::quat(rot))  {}
        unsigned int unique_id = NULL;
        Type type = Kinematic;
        Position position;
        Rotation rotation;
        //std::vector<unsigned int> collider_ids;
    };
    
    class RigidBody : public RefCounted
    {
    public:
        
        RigidBody() = default;
        RigidBody(unsigned int id, RigidBodyValues::Type t) : m_Rb(id, t) {}
        
        //Not const because we are wrapping the rigidbody values within this class, we want easy access and changing of these values
        //It is wrapped because we it needs to be derived from refCounted to be used as a reference instead of a standard pointer
        RigidBodyValues GetRigidBody() {return m_Rb;}
    private:
        RigidBodyValues m_Rb;
    };
}
