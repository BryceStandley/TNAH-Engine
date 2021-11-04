#pragma once
#include <reactphysics3d/reactphysics3d.h>

namespace tnah {
    namespace Physics{
        

        struct Mass
        {
            Mass()
            {
                SetMass();
            }
            
            void SetMass(float mass = 1.0f)
            {
                mass = mass;
                inverseMass = 1.0f / (mass > 0.0f ? mass : 1.0f);
            }
            
            glm::vec3 LocalCentreOfMass = {0,0,0};
            glm::vec3 WorldCentreOfMass = {0,0,0};
            float mass = 1.0f;
            float inverseMass = 1.0f;
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
