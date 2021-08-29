#pragma once
#include <TNAH/Core/Core.h>
#include <glm/glm.hpp>

#include "Shader.h"

namespace tnah {
    class Light : public RefCounted
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
            float intensity = 1.0f;
	        //point
            float constant = 0.0f;
            float linear = 0.0f;
            float quadratic = 0.0f;
            //Spot
            float cutoff = 0.0f;
        };
        

        Light(LightType type) :m_Type(type) {}
        virtual ~Light() = default;
        
        static Ref<Light> Create(LightType type);
        static Ref<Light> CreateDirectional(const glm::vec3& direction, const glm::vec3& ambient,
            const glm::vec3& diffuse, const glm::vec3& specular);
        static Ref<Light> CreateDirectional();
        static Ref<Light> CreatePoint(const float& constant, const float& linear, const float& quadratic);
        static Ref<Light> CreatePoint();
        static Ref<Light> CreateSpot(const float& cutoff);
        static Ref<Light> CreateSpot();
        
        virtual void SetColor(const glm::vec4& value) { m_Color = value; }
        virtual void SetIntensity(const float& value) { m_Intensity = value; }
        virtual void SetPosition(const glm::vec3& value) {m_Position = value; }
        virtual void SetType(const LightType& type) { m_Type = type; } 

        virtual glm::vec4& GetColor() { return m_Color; }
        virtual float& GetIntensity() { return m_Intensity; }
        virtual LightType& GetType() { return m_Type; }
        virtual glm::vec3& GetPosition() { return m_Position; }
        ShaderLightInformation& GetShaderInfo() { return m_ShaderLightInformation; }

        virtual void SetDirection(const glm::vec3& value) { m_Direction = value; }
        virtual void SetDiffuse(const glm::vec3& value) { m_Diffuse = value; }
        virtual void SetAmbient(const glm::vec3& value) { m_Ambient = value; }
        virtual void SetSpecular(const glm::vec3& value) { m_Specular = value; }

        
        virtual glm::vec3& GetDirection() { return m_Direction; }
        virtual glm::vec3& GetAmbient() { return m_Ambient; }
        virtual glm::vec3& GetDiffuse() { return m_Diffuse; }
        virtual glm::vec3& GetSpecular() { return m_Specular;}

        virtual void SetConstant(const float& value) { m_Constant = value; }
        virtual void SetLinear(const float& value) { m_Linear = value; }
        virtual void SetQuadratic(const float& value) { m_Quadratic = value; }
        virtual void SetCutOff(const float& value) { m_CutOff = glm::radians(value); }
        virtual void SetDistance(const int& value) { m_Distance = value; }
        
        virtual float& GetConstant()  { return m_Constant; }
        virtual float& GetLinear() { return m_Linear; }
        virtual float& GetQuadratic() { return m_Quadratic; }
        virtual float GetCutOff() { return glm::degrees(m_CutOff); }
        virtual int& GetDistance() { return m_Distance; }
        
        virtual void UpdateShaderLightInfo(const glm::vec3& cameraPosition);
        virtual void CheckDistance(int distance);
    
    private:
        inline std::string GetTypeAsString()
        {
            switch (m_Type)
            {
                case LightType::Directional:
                    return std::string("Directional");
                case LightType::Point:
                    return std::string("Point");
                case LightType::Spot:
                    return std::string("Spot");
                default:
                    return std::string("Light");
            }
        }
        
        glm::vec3 m_Direction = glm::vec3(-0.2f, -1.0f, -0.3f);
        glm::vec3 m_Ambient = glm::vec3(0.2f, 0.2f, 0.2f);
        glm::vec3 m_Diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
        glm::vec3 m_Specular = glm::vec3(1.0f, 1.0f, 1.0f);
        glm::vec3 m_Position = glm::vec3(0.0f);
        glm::vec4 m_Color = glm::vec4(1.0f);
        int m_Distance = 7;
        float m_Constant = 1.0f;
        float m_Linear = 0.09f;
        float m_Quadratic = 0.032f;
        float m_CutOff = glm::cos(glm::radians(12.5f));
        float m_Intensity = 1.0f;
        LightType m_Type = LightType::Directional;
        ShaderLightInformation m_ShaderLightInformation = ShaderLightInformation();

        bool m_IsSceneLight = false;

        friend class Scene;
        friend class Renderer;
        friend class EditorUI;
        friend class Serializer;
    
    };
}
