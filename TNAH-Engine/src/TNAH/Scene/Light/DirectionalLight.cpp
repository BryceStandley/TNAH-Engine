#include <tnahpch.h>
#include "DirectionalLight.h"

namespace tnah {

    DirectionLight::DirectionLight()
        :Light(LightType::Directional)
    {
    }

    DirectionLight::DirectionLight(const glm::vec3& direction, const glm::vec3& ambient, const glm::vec3& diffuse,
        const glm::vec3& specular)
    :Light(LightType::Directional), m_Direction(direction), m_Ambient(ambient), m_Diffuse(diffuse), m_Specular(specular)
    {
    }

}
