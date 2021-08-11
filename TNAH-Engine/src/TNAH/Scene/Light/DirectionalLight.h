#pragma once
#include "TNAH/Renderer/Light.h"

namespace tnah {
    class DirectionLight : public Light
    {
    public:
        DirectionLight();
        DirectionLight(const glm::vec3& direction, const glm::vec3& ambient,const glm::vec3& diffuse,const glm::vec3& specular);

        virtual ~DirectionLight() {}
        
        glm::vec3& GetDirection()  override { return m_Direction; }
        glm::vec3& GetAmbient()  override { return m_Ambient; }
        glm::vec3& GetDiffuse()  override { return m_Diffuse; }
        glm::vec3& GetSpecular()  override { return m_Specular;}

        float& GetConstant()  override { return GetIntensity(); }
        float& GetLinear()  override { return GetIntensity(); }
        float& GetQuadratic()  override { return GetIntensity(); }
        float& GetCutOff()  override { return GetIntensity(); }
    
    private:
        glm::vec3 m_Direction = glm::vec3(1.0f);
        glm::vec3 m_Ambient = glm::vec3(1.0f);
        glm::vec3 m_Diffuse = glm::vec3(1.0f);
        glm::vec3 m_Specular = glm::vec3(1.0f);
    };
}