#include "tnahpch.h"
#include "Material.h"

#include "RendererAPI.h"

namespace tnah {


    Material::~Material()
    {
    }
    void Material::Set(const std::string& materialUniform, uint32_t value)
    {
        if(!m_Shader->IsBound())
            m_Shader->Bind();
        m_Shader->SetInt(materialUniform, (int)value);
        m_Shader->Unbind();
    }
    
    void Material::Set(const std::string& materialUniform, int value)
    {
        if(!m_Shader->IsBound())
            m_Shader->Bind();
        m_Shader->SetInt(materialUniform, value);
        m_Shader->Unbind();
    }

    void Material::Set(const std::string& materialUniform, float value)
    {
        if(!m_Shader->IsBound())
            m_Shader->Bind();
        m_Shader->SetFloat(materialUniform, value);
        m_Shader->Unbind();
    }

    void Material::Set(const std::string& materialUniform, bool value)
    {
        if(!m_Shader->IsBound())
            m_Shader->Bind();
        m_Shader->SetBool(materialUniform, value);
        m_Shader->Unbind();
    }

    void Material::Set(const std::string& materialUniform, glm::vec2 value)
    {
        if(!m_Shader->IsBound())
            m_Shader->Bind();
        m_Shader->SetVec2(materialUniform, value);
        m_Shader->Unbind();
    }

    void Material::Set(const std::string& materialUniform, glm::vec3 value)
    {
        if(!m_Shader->IsBound())
            m_Shader->Bind();
        m_Shader->SetVec3(materialUniform, value);
        m_Shader->Unbind();
    }

    void Material::Set(const std::string& materialUniform, glm::vec4 value)
    {
        if(!m_Shader->IsBound())
            m_Shader->Bind();
        m_Shader->SetVec4(materialUniform, value);
        m_Shader->Unbind();
    }

    void Material::Set(const std::string& materialUniform, glm::mat4 value, bool transpose)
    {
        if(!m_Shader->IsBound())
            m_Shader->Bind();
        m_Shader->SetMat4(materialUniform, value, transpose);
        m_Shader->Unbind();
    }

    void Material::Set(const std::string& materialUniform, glm::mat3 value)
    {
        if(!m_Shader->IsBound())
            m_Shader->Bind();
        m_Shader->SetMat3(materialUniform, value);
        m_Shader->Unbind();
    }

    Material::Material(const Ref<Shader>& shader)
        :m_Shader(shader)
    {
        m_Properties = MaterialProperties();
    }

    Material::Material(const Ref<Shader>& shader, const MaterialProperties& properties)
        :m_Shader(shader), m_Properties(properties)
    {
    }

    Material::Material(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
    {
        m_Shader = Shader::Create(vertexShaderPath, fragmentShaderPath);
        m_Properties = MaterialProperties();
    }

    Material::Material(const std::string& vertexShaderPath, const std::string& fragmentShaderPath,
        const MaterialProperties& properties)
            :m_Properties(properties)
    {
        m_Shader = Shader::Create(vertexShaderPath, fragmentShaderPath);
    }

    Material::Material(const std::string& vertexShaderPath, const std::string& fragmentShaderPath,
        const float& shininess, const float& metalness)
    {
        m_Shader = Shader::Create(vertexShaderPath, fragmentShaderPath);
        m_Properties = {shininess, metalness};
    }

    Material::Material(const MaterialProperties& properties)
        :m_Properties(properties)
    {
        m_Shader = Shader::Create("Resources/shaders/default/mesh/mesh_vertex.glsl", "Resources/shaders/default/mesh/mesh_fragment.glsl");
    }

    Material::Material()
    {
        m_Shader = Shader::Create("Resources/shaders/default/mesh/mesh_vertex.glsl", "Resources/shaders/default/mesh/mesh_fragment.glsl");
        m_Properties = MaterialProperties();
    }

    

    Ref<Material> Material::Create(const Ref<Shader>& shader)
    {
        MaterialProperties p = MaterialProperties();
        return new Material(shader, p);
    }

    Ref<Material> Material::Create(const Ref<Shader>& shader, const MaterialProperties& properties)
    {
        return Ref<Material>::Create(shader, properties);
    }

    Ref<Material> Material::Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
    {
        Ref<Shader> s = Shader::Create(vertexShaderPath, fragmentShaderPath);
        MaterialProperties p = MaterialProperties();
        return Ref<Material>::Create(s, p);
    }

    Ref<Material> Material::Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath,
                               const MaterialProperties& properties)
    {
        Ref<Shader> s = Shader::Create(vertexShaderPath, fragmentShaderPath);
        return Ref<Material>::Create(s, properties);
        
    }

    Ref<Material> Material::Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath,
        const float& shininess, const float& metalness)
    {
        Ref<Shader> s = Shader::Create(vertexShaderPath, fragmentShaderPath);
        MaterialProperties p  = MaterialProperties(shininess, metalness);
        return Ref<Material>::Create(s, p);
    }

    void Material::SetTextures(std::vector<Ref<Texture2D>> textures)
    {
        m_Textures = textures;
    }

    void Material::InsertTextures(std::vector<Ref<Texture2D>> textures, uint32_t startIndex)
    {
        if(startIndex < 0) return;
        
        for(uint32_t i = 0; i < textures.size(); i++)
        {
            m_Textures[startIndex + i] = textures[i];
        }
    }

    void Material::InsertTexture(Ref<Texture2D> texture, uint32_t index)
    {
        if(index < 0) return;
        m_Textures[index] = texture;
    }

    void Material::AddTexture(Ref<Texture2D> texture, const uint32_t& index)
    {
        if(texture)
        {
            if(m_Shader)
            {
                Set("u_" + texture->GetName() +std::to_string(index), texture->GetRendererID());
            }
            m_Textures.emplace_back(texture);
        }
    }

    void Material::AddTextures(std::vector<Ref<Texture2D>> textures)
    {
        uint32_t index = 0;
        for(auto t : textures)
        {
            AddTexture(t,index);
            index++;
        }
    }

    void Material::BindTextures()
    {
        if(!m_Shader->IsBound())m_Shader->Bind();
        for(auto t : m_Textures)
        {
            t->Bind(t->m_RendererID);
        }
    }

    void Material::BindShader()
    {
        m_Shader->Bind();
    }

    void Material::UnBindShader()
    {
        m_Shader->Unbind();
    }

//***********************************************************************************
    //Skybox Material
    
    Ref<SkyboxMaterial> SkyboxMaterial::Create(const Ref<Shader>& shader)
    {
        return Ref<SkyboxMaterial>::Create(shader);
    }

    Ref<SkyboxMaterial> SkyboxMaterial::Create(const Ref<Shader>& shader, const Texture3DProperties& cubemapProperties)
    {
        return Ref<SkyboxMaterial>::Create(shader, cubemapProperties);
    }

    Ref<SkyboxMaterial> SkyboxMaterial::Create(const Ref<Shader>& shader, const MaterialProperties& properties,
        const Texture3DProperties& cubemapProperties)
    {
        return Ref<SkyboxMaterial>::Create(shader, properties, cubemapProperties);
    }

    Ref<SkyboxMaterial> SkyboxMaterial::Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath,
        const MaterialProperties& properties, const Texture3DProperties& cubemapProperties)
    {
        return Ref<SkyboxMaterial>::Create(vertexShaderPath, fragmentShaderPath, properties, cubemapProperties);
    }

    Ref<SkyboxMaterial> SkyboxMaterial::Create(const Ref<Shader>& shader, const MaterialProperties& properties)
    {
        return Ref<SkyboxMaterial>::Create(shader, properties);
    }

    Ref<SkyboxMaterial> SkyboxMaterial::Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
    {
        return Ref<SkyboxMaterial>::Create(vertexShaderPath, fragmentShaderPath);
    }

    Ref<SkyboxMaterial> SkyboxMaterial::Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath,
        const MaterialProperties& properties)
    {
        return Ref<SkyboxMaterial>::Create(vertexShaderPath, fragmentShaderPath, properties);
    }

    Ref<SkyboxMaterial> SkyboxMaterial::Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath,
        const float& shininess, const float& metalness)
    {
        return Ref<SkyboxMaterial>::Create(vertexShaderPath, fragmentShaderPath, shininess, metalness);
    }

    void SkyboxMaterial::BindTextures() { m_Cubemap->Bind(); }

    SkyboxMaterial::~SkyboxMaterial() {}

    SkyboxMaterial::SkyboxMaterial(const Ref<Shader>& shader, const Texture3DProperties& cubemapProperties)
        :Material(shader), m_CubemapProperties(cubemapProperties)
    {
        m_Cubemap = (Texture3D::Create(m_CubemapProperties));
    }
    
    SkyboxMaterial::SkyboxMaterial(const Ref<Shader>& shader)
        :Material(shader, MaterialProperties())
    {
        m_CubemapProperties = {
            {"Resources/textures/default/skybox/default_front.jpg"},
            {"Resources/textures/default/skybox/default_back.jpg"},
            {"Resources/textures/default/skybox/default_left.jpg"},
            {"Resources/textures/default/skybox/default_right.jpg"},
            {"Resources/textures/default/skybox/default_top.jpg"},
            {"Resources/textures/default/skybox/default_bottom.jpg"}
        };
        m_Cubemap = (Texture3D::Create(m_CubemapProperties));
    }

    SkyboxMaterial::SkyboxMaterial(const Ref<Shader>& shader, const MaterialProperties& properties)
        :Material(shader, properties)
    {
        m_CubemapProperties = {
            {"Resources/textures/default/skybox/default_front.jpg"},
            {"Resources/textures/default/skybox/default_back.jpg"},
            {"Resources/textures/default/skybox/default_left.jpg"},
            {"Resources/textures/default/skybox/default_right.jpg"},
            {"Resources/textures/default/skybox/default_top.jpg"},
            {"Resources/textures/default/skybox/default_bottom.jpg"}
        };
        m_Cubemap = (Texture3D::Create(m_CubemapProperties));
    }

    SkyboxMaterial::SkyboxMaterial(const Ref<Shader>& shader, const MaterialProperties& properties,
        const Texture3DProperties& cubemapProperties)
            :Material(shader, properties), m_CubemapProperties(cubemapProperties)
    {
        m_Cubemap = (Texture3D::Create(m_CubemapProperties));
    }

    SkyboxMaterial::SkyboxMaterial(const std::string& vertexShaderPath, const std::string& fragmentShaderPath,
        const MaterialProperties& properties, const Texture3DProperties& cubemapProperties)
            :Material(vertexShaderPath, fragmentShaderPath, properties), m_CubemapProperties(cubemapProperties)
    {
        m_Cubemap = (Texture3D::Create(m_CubemapProperties));
    }

    SkyboxMaterial::SkyboxMaterial(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
        :Material(vertexShaderPath, fragmentShaderPath)
    {
        m_CubemapProperties = {
            {"Resources/textures/default/skybox/default_front.jpg"},
            {"Resources/textures/default/skybox/default_back.jpg"},
            {"Resources/textures/default/skybox/default_left.jpg"},
            {"Resources/textures/default/skybox/default_right.jpg"},
            {"Resources/textures/default/skybox/default_top.jpg"},
            {"Resources/textures/default/skybox/default_bottom.jpg"}
        };
        m_Cubemap = (Texture3D::Create(m_CubemapProperties));
    }

    SkyboxMaterial::SkyboxMaterial(const std::string& vertexShaderPath, const std::string& fragmentShaderPath,
        const MaterialProperties& properties)
            :Material(vertexShaderPath, fragmentShaderPath, properties)
    {
        m_CubemapProperties = {
            {"Resources/textures/default/skybox/default_front.jpg"},
            {"Resources/textures/default/skybox/default_back.jpg"},
            {"Resources/textures/default/skybox/default_left.jpg"},
            {"Resources/textures/default/skybox/default_right.jpg"},
            {"Resources/textures/default/skybox/default_top.jpg"},
            {"Resources/textures/default/skybox/default_bottom.jpg"}
        };
        m_Cubemap = (Texture3D::Create(m_CubemapProperties));
    }

    SkyboxMaterial::SkyboxMaterial(const std::string& vertexShaderPath, const std::string& fragmentShaderPath,
        const float& shininess, const float& metalness)
            :Material(vertexShaderPath, fragmentShaderPath, shininess, metalness)
    {
        m_CubemapProperties = {
            {"Resources/textures/default/skybox/default_front.jpg"},
            {"Resources/textures/default/skybox/default_back.jpg"},
            {"Resources/textures/default/skybox/default_left.jpg"},
            {"Resources/textures/default/skybox/default_right.jpg"},
            {"Resources/textures/default/skybox/default_top.jpg"},
            {"Resources/textures/default/skybox/default_bottom.jpg"}
        };
        m_Cubemap = (Texture3D::Create(m_CubemapProperties));
    }


}
