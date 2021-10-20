#pragma once
#include <reactphysics3d/reactphysics3d.h>

namespace tnah {
    namespace Physics{

        enum class BodyType
        {
            Dynamic, Static
        };
    
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
                InverseMass = 1.0f / Mass;
            }
            
            glm::vec3 CentreOfMass = {};
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

        struct Torque
        {
            glm::vec3 Torques = {};

            glm::vec3 operator = (const glm::vec3& value)
            {
                Torques = value;
                return Torques;
            }
        };

        struct InertiaTensor
        {
            glm::mat3 Tensor = glm::mat3(1.0f);
            glm::mat3 InverseTensor = glm::inverse(glm::mat3(1.0f));
        };
    }
}
