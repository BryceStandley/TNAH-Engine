#pragma once
#include "TNAH/Renderer/Light.h"

namespace tnah {
    class PointLight : public Light
    {
    public:
        PointLight();
        virtual ~PointLight() {}

        glm::vec3& GetDirection()  override { return GetPosition(); }
        glm::vec3& GetAmbient()  override { return GetPosition(); }
        glm::vec3& GetDiffuse()  override { return GetPosition(); }
        glm::vec3& GetSpecular()  override { return GetPosition(); }
        
        float& GetConstant()  override { return m_Constant; }
        float& GetLinear()  override { return m_Linear; }
        float& GetQuadratic()  override { return m_Quadratic; }
        float& GetCutOff()  override { return m_CutOff; }

    private:
        float m_Constant;
        float m_Linear;
        float m_Quadratic;
        float m_CutOff;
    
    };
}
