#include <tnahpch.h>
#include "Light.h"

#include "TNAH/Scene/Light/DirectionalLight.h"
#include "TNAH/Scene/Light/PointLight.h"
#include "TNAH/Scene/Light/SpotLight.h"

namespace tnah {

    Light* Light::Create(LightType type)
    {
        switch(type)
        {
            case LightType::Directional:
                return new DirectionLight();
            case LightType::Point:
                return new PointLight();
            case LightType::Spot:
                return new SpotLight();
            default:
                return new DirectionLight();
        }
    }

    Light* Light::CreateDirectional(const glm::vec3& direction, const glm::vec3& ambient, const glm::vec3& diffuse,
        const glm::vec3& specular)
    {
        auto light = new DirectionLight(direction, ambient, diffuse, specular);
        light->SetType(LightType::Directional);
        light->UpdateShaderLightInfo(glm::vec3(0.0f));
        return light;
    }

    Light* Light::CreatePoint()
    {
        auto light = new PointLight();
        light->SetType(LightType::Point);
        light->UpdateShaderLightInfo(glm::vec3(0.0f));
        return light;
    }

    Light* Light::CreateSpot()
    {
        auto light = new SpotLight();
        light->SetType(LightType::Spot);
        light->UpdateShaderLightInfo(glm::vec3(0.0f));
        return light;
    }

    void Light::UpdateShaderLightInfo(const glm::vec3& cameraPosition)
    {
        m_ShaderLightInformation.cameraPosition = cameraPosition;
        switch(m_Type)
        {
        case LightType::Directional:
            m_ShaderLightInformation.direction = GetDirection();
            m_ShaderLightInformation.ambient = GetAmbient();
            m_ShaderLightInformation.diffuse = GetDiffuse();
            m_ShaderLightInformation.specular = GetSpecular();
            break;
        case LightType::Point:
            m_ShaderLightInformation.position = GetPosition();
            m_ShaderLightInformation.ambient = GetAmbient();
            m_ShaderLightInformation.diffuse = GetDiffuse();
            m_ShaderLightInformation.specular = GetSpecular();
            m_ShaderLightInformation.constant = GetConstant();
            m_ShaderLightInformation.linear = GetLinear();
            m_ShaderLightInformation.quadratic = GetQuadratic();
        case LightType::Spot:
            m_ShaderLightInformation.position = GetPosition();
            m_ShaderLightInformation.direction = GetDirection();
            m_ShaderLightInformation.cutoff = GetCutOff();
            break;
        default:
            break;
        }
    }


}
