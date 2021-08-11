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

    Light* Light::CreateDirectional()
    {
        auto light = new DirectionLight();
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

    Light* Light::CreatePoint(const float& constant, const float& linear, const float& quadratic)
    {
        auto light = new PointLight(constant, linear, quadratic);
        light->SetType(LightType::Point);
        light->UpdateShaderLightInfo(glm::vec3(0.0f));
        return light;
    }

    Light* Light::CreateSpot(const float& cutoff)
    {
        auto light = new SpotLight(cutoff);
        light->SetType(LightType::Spot);
        light->UpdateShaderLightInfo(glm::vec3(0.0f));
        return light;
    }

    void Light::UpdateShaderLightInfo(const glm::vec3& cameraPosition)
    {
        m_ShaderLightInformation.cameraPosition = cameraPosition;
        m_ShaderLightInformation.color = GetColor();
        m_ShaderLightInformation.intensity = GetIntensity();
        m_ShaderLightInformation.type = (int)GetType();

        CheckDistance(GetDistance());
        
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
            m_ShaderLightInformation.ambient = GetAmbient();
            m_ShaderLightInformation.diffuse = GetDiffuse();
            m_ShaderLightInformation.specular = GetSpecular();
            m_ShaderLightInformation.constant = GetConstant();
            m_ShaderLightInformation.linear = GetLinear();
            m_ShaderLightInformation.quadratic = GetQuadratic();
            m_ShaderLightInformation.cutoff = glm::cos(GetCutOff());
            break;
        default:
            break;
        }
    }

    void Light::CheckDistance(int distance)
    {
        switch(distance)
        {
            case 10:
                SetLinear(0.7f);
                SetQuadratic(1.8f);
                break;
            case 15:
                SetLinear(0.35f);
                SetQuadratic(0.44f);
                break;
            case 20:
                SetLinear(0.22f);
                SetQuadratic(0.2f);
                break;
            case 50:
                SetLinear(0.9f);
                SetQuadratic(0.032f);
                break;
            case 100:
                SetLinear(0.045f);
                SetQuadratic(0.0075f);
                break;
            case 200:
                SetLinear(0.022f);
                SetQuadratic(0.0019f);
                break;
            default:
                break;
            
        }
        
    }


}
