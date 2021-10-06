#pragma once

namespace tnah{

    struct CentreOfMass
    {
        glm::vec3 Position = {};
    };

    struct LinearVelocity
    {
        glm::vec3 Velocity = {};
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
        float Mass = 1.0f;
        float InverseMass = 1.0f;
    };

    struct AngularVelocity
    {
        glm::vec3 Velocity = {};
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