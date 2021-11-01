#pragma once
#include <reactphysics3d/reactphysics3d.h>

namespace tnah {
    namespace Physics{
    
        struct LinearVelocity
        {
            glm::vec3 Velocity = {};

            operator glm::vec3 () { return Velocity; }
            operator glm::vec3 () const { return Velocity; }

            glm::vec3 operator = (const glm::vec3& value)
            {
                Velocity = value;
                return Velocity;
            }

            glm::vec3 operator * (const float& value)
            {
                Velocity *= value;
                return Velocity;
            }

            glm::vec3 operator *= (const float& value)
            {
                Velocity *= value;
                return Velocity;
            }
            
            glm::vec3 operator / (const float& value)
            {
                Velocity /= value;
                return Velocity;
            }

            glm::vec3 operator + (const glm::vec3& value)
            {
                Velocity += value;
                return Velocity;
            }

            glm::vec3 operator - (const glm::vec3& value)
            {
                Velocity -= value;
                return Velocity;
            }
        };

        struct Force
        {
            glm::vec3 Forces = {};

            glm::vec3 operator = (const glm::vec3& value)
            {
                Forces = value;
                return Forces;
            }

            glm::vec3 operator += (const glm::vec3 value)
            {
                Forces += value;
                return value;
            }
        };

        struct LinearDampening
        {
            float Dampening = 0.0f;

            float operator = (const float& value)
            {
                Dampening = value;
                return Dampening;
            }

            operator float () const
            {
                return Dampening;
            }
        };

        struct BodyMass
        {
            BodyMass()
            { SetMass(); }

            /**
             * @fn void BodyMass::SetMass(float mass = 1.0f);
             *
             * @brief Sets the mass and updates the inverse mass.
             */
            void SetMass(float mass = 1.0f)
            {
                Mass = mass;
                InverseMass = 1.0f / (Mass > 0.0f ? Mass : 1.0f); // cant invert mass if its 0
            }
            
            glm::vec3 LocalCentreOfMass = {0,0,0};
            glm::vec3 WorldCentreOfMass = {0,0,0};
            float Mass = 1.0f;
            float InverseMass = 1.0f;
        };

        struct AngularVelocity
        {
            glm::vec3 Velocity = {};

            operator glm::vec3 () { return Velocity; }
            operator glm::vec3 () const { return Velocity; }

            glm::vec3 operator = (const glm::vec3& value)
            {
                Velocity = value;
                return Velocity;
            }

            glm::vec3 operator * (const float& value)
            {
                Velocity *= value;
                return Velocity;
            }

            glm::vec3 operator *= (const float& value)
            {
                Velocity *= value;
                return Velocity;
            }
            
            glm::vec3 operator / (const float& value)
            {
                Velocity /= value;
                return Velocity;
            }

            glm::vec3 operator + (const glm::vec3& value)
            {
                Velocity += value;
                return Velocity;
            }

            glm::vec3 operator - (const glm::vec3& value)
            {
                Velocity -= value;
                return Velocity;
            }
        };

        struct AngularDampening
        {
            float Dampening = 0.2f;

            float operator = (const float& value)
            {
                Dampening = value;
                return Dampening;
            }

            operator float () const
            {
                return Dampening;
            }
        };

        struct Torque
        {
            glm::vec3 Torques = {};

            glm::vec3 operator = (const glm::vec3& value)
            {
                Torques = value;
                return Torques;
            }

            glm::vec3 operator += (const glm::vec3 value)
            {
                Torques += value;
                return value;
            }
        };

        struct InertiaTensor
        {
            glm::mat3 WorldInertiaTensor = glm::mat3(1.0f);
            glm::mat3 WorldInverseInertiaTensor = glm::inverse(glm::mat3(1.0f));
            glm::vec3 LocalInertiaTensor = {1,1,1};
            glm::vec3 LocalInverseInertiaTensor = {1,1,1};

            glm::vec3 SetLocalInertiaTensor(const glm::vec3 localTensor)
            {
                LocalInertiaTensor = localTensor;
                LocalInverseInertiaTensor = glm::vec3(localTensor.x != 0.0f ? 1.0f / localTensor.x : 0.0f,
                                                        localTensor.y != 0.0f ? 1.0f / localTensor.y : 0.0f,
                                                        localTensor.z != 0.0f ? 1.0f / localTensor.z : 0.0f);
                return LocalInertiaTensor;
            }

            glm::mat3 SetWorldInertiaTensor(const glm::mat3& worldTensor)
            {
                WorldInertiaTensor = worldTensor;
                WorldInverseInertiaTensor = glm::inverse(worldTensor);
                return WorldInertiaTensor;
            }
        };
        
    }
}
