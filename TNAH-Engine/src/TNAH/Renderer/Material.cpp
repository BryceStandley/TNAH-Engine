#include "tnahpch.h"
#include "Material.h"

#include "RendererAPI.h"

namespace tnah {


    Material::Material(const Ref<Shader>& shader)
        :m_Shader(shader)
    {
        m_Properties = MaterialProperties();
    }

    Material::Material(const Ref<Shader>& shader, const MaterialProperties& properties)
        :m_Shader(shader), m_Properties(properties)
    {
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
}
