#pragma once

namespace tnah
{
    struct RigidBodyValues
    {
        RigidBodyValues()
        {
            
        }
        RigidBodyValues(unsigned int i)
        {
            unique_id = i;
        }
        unsigned int unique_id = NULL;
    };
    
    class RigidBody : public RefCounted
    {
    public:
        RigidBody();
        RigidBody(unsigned int id) : m_Rb(id) {}
        //Not const because we are wrapping the rigidbody values within this class, we want easy access and changing of these values
        //It is wrapped because we it needs to be derived from refCounted to be used as a reference instead of a standard pointer
        RigidBodyValues GetRb() {return m_Rb;}
    private:
        RigidBodyValues m_Rb;
    };
}
