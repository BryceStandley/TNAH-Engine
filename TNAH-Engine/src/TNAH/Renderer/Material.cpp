#include "tnahpch.h"
#include "Material.h"

#include "RendererAPI.h"

namespace tnah {


    Material::~Material()
    {
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
        m_Shader.reset(Shader::Create(vertexShaderPath, fragmentShaderPath));
        m_Properties = MaterialProperties();
    }

    Material::Material(const std::string& vertexShaderPath, const std::string& fragmentShaderPath,
        const MaterialProperties& properties)
            :m_Properties(properties)
    {
        m_Shader.reset(Shader::Create(vertexShaderPath, fragmentShaderPath));
    }

    Material::Material(const std::string& vertexShaderPath, const std::string& fragmentShaderPath,
        const float& shininess, const float& metalness)
    {
        m_Shader.reset(Shader::Create(vertexShaderPath, fragmentShaderPath));
        m_Properties = {shininess, metalness};
    }

    Material::Material(const MaterialProperties& properties)
        :m_Properties(properties)
    {
           m_Shader.reset(Shader::Create("Resources/shaders/default/mesh/mesh_vertex.glsl", "Resources/shaders/default/mesh/mesh_fragment.glsl"));
    }

    Material::Material()
    {
        m_Shader.reset(Shader::Create("Resources/shaders/default/mesh/mesh_vertex.glsl", "Resources/shaders/default/mesh/mesh_fragment.glsl"));
        m_Properties = MaterialProperties();
    }

    

    Material* Material::Create(const Ref<Shader>& shader)
    {
        MaterialProperties p = MaterialProperties();
        return new Material(shader, p);
    }

    Material* Material::Create(const Ref<Shader>& shader, const MaterialProperties& properties)
    {
        return new Material(shader, properties);
    }

    Material* Material::Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
    {
        Ref<Shader> s;
        s.reset(Shader::Create(vertexShaderPath, fragmentShaderPath));
        MaterialProperties p = MaterialProperties();
        return new Material(s, p);
    }

    Material* Material::Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath,
                               const MaterialProperties& properties)
    {
        Ref<Shader> s;
        s.reset(Shader::Create(vertexShaderPath, fragmentShaderPath));
        return new Material(s, properties);
        
    }

    Material* Material::Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath,
        const float& shininess, const float& metalness)
    {
        Ref<Shader> s;
        s.reset(Shader::Create(vertexShaderPath, fragmentShaderPath));
        MaterialProperties p  = MaterialProperties(shininess, metalness);
        return new Material(s, p);
    }

    void Material::SetTextures(std::vector<Ref<Texture2D>> textures)
    {
        m_Textures = textures;
    }

    void Material::BindTextures()
    {
        if(!m_Shader->IsBound())m_Shader->Bind();
        for(auto t : m_Textures)
        {
            t->Bind(t->m_Slot);
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
    
    SkyboxMaterial* SkyboxMaterial::Create(const Ref<Shader>& shader)
    {
        return new SkyboxMaterial(shader);
    }

    SkyboxMaterial* SkyboxMaterial::Create(const Ref<Shader>& shader, const Texture3DProperties& cubemapProperties)
    {
        return new SkyboxMaterial(shader, cubemapProperties);
    }

    SkyboxMaterial* SkyboxMaterial::Create(const Ref<Shader>& shader, const MaterialProperties& properties,
        const Texture3DProperties& cubemapProperties)
    {
        return new SkyboxMaterial(shader, properties, cubemapProperties);
    }

    SkyboxMaterial* SkyboxMaterial::Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath,
        const MaterialProperties& properties, const Texture3DProperties& cubemapProperties)
    {
        return new SkyboxMaterial(vertexShaderPath, fragmentShaderPath, properties, cubemapProperties);
    }

    SkyboxMaterial* SkyboxMaterial::Create(const Ref<Shader>& shader, const MaterialProperties& properties)
    {
        return new SkyboxMaterial(shader, properties);
    }

    SkyboxMaterial* SkyboxMaterial::Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
    {
        return new SkyboxMaterial(vertexShaderPath, fragmentShaderPath);
    }

    SkyboxMaterial* SkyboxMaterial::Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath,
        const MaterialProperties& properties)
    {
        return new SkyboxMaterial(vertexShaderPath, fragmentShaderPath, properties);
    }

    SkyboxMaterial* SkyboxMaterial::Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath,
        const float& shininess, const float& metalness)
    {
        return new SkyboxMaterial(vertexShaderPath, fragmentShaderPath, shininess, metalness);
    }

    void SkyboxMaterial::BindTextures() { m_Cubemap->Bind(); }

    SkyboxMaterial::~SkyboxMaterial() {}

    SkyboxMaterial::SkyboxMaterial(const Ref<Shader>& shader, const Texture3DProperties& cubemapProperties)
        :Material(shader), m_CubemapProperties(cubemapProperties)
    {
        m_Cubemap.reset(Texture3D::Create(m_CubemapProperties));
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
        m_Cubemap.reset(Texture3D::Create(m_CubemapProperties));
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
        m_Cubemap.reset(Texture3D::Create(m_CubemapProperties));
    }

    SkyboxMaterial::SkyboxMaterial(const Ref<Shader>& shader, const MaterialProperties& properties,
        const Texture3DProperties& cubemapProperties)
            :Material(shader, properties), m_CubemapProperties(cubemapProperties)
    {
        m_Cubemap.reset(Texture3D::Create(m_CubemapProperties));
    }

    SkyboxMaterial::SkyboxMaterial(const std::string& vertexShaderPath, const std::string& fragmentShaderPath,
        const MaterialProperties& properties, const Texture3DProperties& cubemapProperties)
            :Material(vertexShaderPath, fragmentShaderPath, properties), m_CubemapProperties(cubemapProperties)
    {
        m_Cubemap.reset(Texture3D::Create(m_CubemapProperties));
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
        m_Cubemap.reset(Texture3D::Create(m_CubemapProperties));
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
        m_Cubemap.reset(Texture3D::Create(m_CubemapProperties));
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
        m_Cubemap.reset(Texture3D::Create(m_CubemapProperties));
    }


}
