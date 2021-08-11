#pragma once
#include <TNAH/Core/Core.h>
#include <glm/glm.hpp>

#include "Shader.h"

namespace tnah {
    class Light
    {
    public:
        enum class LightType
        {
            Directional = 0,
            Point = 1,
            Spot = 2
        };
        
        struct ShaderLightInformation {
            //shader light type, 0 = Directional, 1 = Point, 2 = Spot, Any other value = disabled lighting in shader
            int type = 0;
            //Camera View
            glm::vec3 cameraPosition = glm::vec3(0.0f);
            //Light position
            glm::vec3 position = glm::vec3(0.0f);
            //directional
            glm::vec3 direction = glm::vec3(0.0f);
            //all lights
            glm::vec3 ambient = glm::vec3(0.0f);
            glm::vec3 diffuse = glm::vec3(0.0f);
            glm::vec3 specular = glm::vec3(0.0f);
            glm::vec3 color = glm::vec3(0.0f);
	        //point
            float constant = 0.0f;
            float linear = 0.0f;
            float quadratic = 0.0f;
            //Spot
            float cutoff = 0.0f;
        };
        

        Light(LightType type) :m_Type(type) {}
        
        static Light* Create(LightType type);
        static Light* CreateDirectional(const glm::vec3& direction = glm::vec3(1.0f), const glm::vec3& ambient = glm::vec3(1.0f),
            const glm::vec3& diffuse = glm::vec3(1.0f),const glm::vec3& specular = glm::vec3(1.0f));
        static Light* CreatePoint();
        static Light* CreateSpot();
        
        virtual void SetColor(const glm::vec4& value) { m_Color = value; }
        virtual void SetIntensity(const float& value) { m_Intensity = value; }
        virtual void SetPosition(const glm::vec3& value) {m_Position = value; }
        virtual void SetType(const LightType& type) { m_Type = type; } 

        virtual glm::vec4& GetColor() { return m_Color; }
        virtual float& GetIntensity() { return m_Intensity; }
        virtual LightType& GetType() { return m_Type; }
        virtual glm::vec3& GetPosition() { return m_Position; }
        ShaderLightInformation& GetShaderInfo() { return m_ShaderLightInformation; }

        virtual glm::vec3& GetDirection() = 0;
        virtual glm::vec3& GetAmbient() = 0;
        virtual glm::vec3& GetDiffuse() = 0;
        virtual glm::vec3& GetSpecular()  = 0;
        virtual float& GetConstant() = 0;
        virtual float& GetLinear() = 0;
        virtual float& GetQuadratic() = 0;
        virtual float& GetCutOff() = 0;
        
        virtual void UpdateShaderLightInfo(const glm::vec3& cameraPosition);
    
    private:
        glm::vec3 m_Position = glm::vec3(0.0f);
        glm::vec4 m_Color = glm::vec4(1.0f);
        float m_Intensity = 1.0f;
        LightType m_Type = LightType::Directional;
        ShaderLightInformation m_ShaderLightInformation = ShaderLightInformation();
    
    };
}
