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
        };

        struct Force
        {
            glm::vec3 Forces = {};
        };

        struct LinearDampening
        {
            float Dampening = 1.0f;
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
        };

        struct AngularDampening
        {
            float Dampening = 1.0f;
        };

        struct Torque
        {
            glm::vec3 Torques = {};
        };

        struct InertiaTensor
        {
            glm::mat3 Tensor = glm::mat3(1.0f);
            glm::mat3 InverseTensor = glm::inverse(glm::mat3(1.0f));
        };
    }
}
