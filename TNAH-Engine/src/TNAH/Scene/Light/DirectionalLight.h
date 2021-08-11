#pragma once
#include "TNAH/Renderer/Light.h"

namespace tnah {
    class DirectionLight : public Light
    {
    public:
        DirectionLight();
        DirectionLight(const glm::vec3& direction, const glm::vec3& ambient,const glm::vec3& diffuse,const glm::vec3& specular);

        virtual ~DirectionLight() {}

        void SetUpLight(const glm::vec3& direction, const glm::vec3& ambient,const glm::vec3& diffuse,const glm::vec3& specular);
    };
}