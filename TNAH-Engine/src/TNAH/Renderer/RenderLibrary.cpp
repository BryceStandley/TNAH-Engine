#include "tnahpch.h"
#include "RenderLibrary.h"

namespace tnah{
    
    bool RenderLibrary::InitializeLibrary()
    {
        m_MeshShader = Shader::Create("Resources/shaders/default/mesh/TNAH_mesh_PBR.glsl");
        m_SkyboxShader = Shader::Create("Resources/shaders/default/skybox/TNAH_skybox_PBR.glsl");
        m_TerrainShader = Shader::Create("Resources/shaders/default/terrain/TNAH_terrain_PBR.glsl");
        m_PhysicsShader = Shader::Create("Resources/shaders/default/physics/TNAH_physics.glsl");

        if(!m_MeshShader || !m_TerrainShader || !m_SkyboxShader || !m_PhysicsShader)
        {
            TNAH_CORE_ERROR("Render library failed to load provided shaders!");
            return false;
        }

        return true;
    }

    bool RenderLibrary::InitializeLibrary(const std::string& meshShaderPath, const std::string& terrainShaderPath,
                                          const std::string& skyboxShaderPath, const std::string& physicsShaderPath)
    {
        m_MeshShader = Shader::Create(meshShaderPath);
        m_SkyboxShader = Shader::Create(skyboxShaderPath);
        m_TerrainShader = Shader::Create(terrainShaderPath);
        m_PhysicsShader = Shader::Create(physicsShaderPath);

        if(!m_MeshShader || !m_TerrainShader || !m_SkyboxShader || !m_PhysicsShader)
        {
            TNAH_CORE_ERROR("Render library failed to load provided shaders!");
            return false;
        }

        return true;
    }

    bool RenderLibrary::InitializeLibrary(const Ref<Shader>& meshShader, const Ref<Shader>& terrainShader,
                                          const Ref<Shader>& skyboxShader, const Ref<Shader>& physicsShader)
    {
        m_MeshShader = meshShader;
        m_TerrainShader = terrainShader;
        m_SkyboxShader = skyboxShader;
        m_PhysicsShader = physicsShader;

        if(!m_MeshShader || !m_TerrainShader || !m_SkyboxShader || !m_PhysicsShader)
        {
            TNAH_CORE_ERROR("Render library failed to copy provided shaders!");
            return false;
        }

        return true;
    }

    Ref<Shader> RenderLibrary::GetShader(const LibraryShader shaderType)
    {
        switch (shaderType)
        {
        case LibraryShader::Mesh:
            return m_MeshShader;
        case LibraryShader::Terrain:
            return m_TerrainShader;
        case LibraryShader::Skybox:
            return m_SkyboxShader;
        case LibraryShader::Physics:
            return m_PhysicsShader;
        default: return nullptr;
        }
    }

    std::unordered_map<std::string, Ref<Shader>> RenderLibrary::GetAllShaders()
    {
        std::unordered_map<std::string, Ref<Shader>> map;
        map["mesh"] = m_MeshShader;
        map["terrain"] = m_TerrainShader;
        map["skybox"] = m_SkyboxShader;
        map["physics"] = m_PhysicsShader;
        
        return map;
    }

    void RenderLibrary::SetShader(const LibraryShader shaderType, const Ref<Shader>& shaderToSet)
    {
        switch (shaderType)
        {
        case LibraryShader::Mesh:
            m_MeshShader = shaderToSet;
        case LibraryShader::Terrain:
            m_TerrainShader = shaderToSet;
        case LibraryShader::Skybox:
            m_SkyboxShader = shaderToSet;
        case LibraryShader::Physics:
            m_PhysicsShader = shaderToSet;
        default: TNAH_CORE_WARN("Library shader type doesn't exist!"); break;
        }
    }

    void RenderLibrary::SetShader(const LibraryShader shaderType, const std::string& shaderPath)
    {
        switch (shaderType)
        {
        case LibraryShader::Mesh:
            m_MeshShader = Shader::Create(shaderPath);
        case LibraryShader::Terrain:
            m_TerrainShader = Shader::Create(shaderPath);
        case LibraryShader::Skybox:
            m_SkyboxShader = Shader::Create(shaderPath);
        case LibraryShader::Physics:
            m_PhysicsShader = Shader::Create(shaderPath);
        default: TNAH_CORE_WARN("Library shader type doesn't exist!"); break;
        }
    }

    void RenderLibrary::SetShader(const LibraryShader shaderType, const std::string& vertexShaderPath,
                                  const std::string& fragmentShaderPath)
    {
        switch (shaderType)
        {
        case LibraryShader::Mesh:
            m_MeshShader = Shader::Create(vertexShaderPath, fragmentShaderPath);
        case LibraryShader::Terrain:
            m_TerrainShader = Shader::Create(vertexShaderPath, fragmentShaderPath);
        case LibraryShader::Skybox:
            m_SkyboxShader = Shader::Create(vertexShaderPath, fragmentShaderPath);
        case LibraryShader::Physics:
            m_PhysicsShader = Shader::Create(vertexShaderPath, fragmentShaderPath);
        default: TNAH_CORE_WARN("Library shader type doesn't exist!"); break;
        }
    }

    void RenderLibrary::SetShader(const LibraryShader shaderType, const char* shaderPath)
    {
        switch (shaderType)
        {
        case LibraryShader::Mesh:
            m_MeshShader = Shader::Create(shaderPath);
        case LibraryShader::Terrain:
            m_TerrainShader = Shader::Create(shaderPath);
        case LibraryShader::Skybox:
            m_SkyboxShader = Shader::Create(shaderPath);
        case LibraryShader::Physics:
            m_PhysicsShader = Shader::Create(shaderPath);
        default: TNAH_CORE_WARN("Library shader type doesn't exist!"); break;
        }
    }

    void RenderLibrary::SetShader(const LibraryShader shaderType, const char* vertexShaderPath,
                                  const char* fragmentShaderPath)
    {
        switch (shaderType)
        {
        case LibraryShader::Mesh:
            m_MeshShader = Shader::Create(vertexShaderPath, fragmentShaderPath);
        case LibraryShader::Terrain:
            m_TerrainShader = Shader::Create(vertexShaderPath, fragmentShaderPath);
        case LibraryShader::Skybox:
            m_SkyboxShader = Shader::Create(vertexShaderPath, fragmentShaderPath);
        case LibraryShader::Physics:
            m_PhysicsShader = Shader::Create(vertexShaderPath, fragmentShaderPath);
        default: TNAH_CORE_WARN("Library shader type doesn't exist!"); break;
        }
    }

    bool RenderLibrary::ClearLibrary()
    {
        m_MeshShader.Reset();
        m_TerrainShader.Reset();
        m_SkyboxShader.Reset();
        m_PhysicsShader.Reset();

        if(m_MeshShader || m_TerrainShader || m_SkyboxShader || m_PhysicsShader)
        {
            TNAH_CORE_ERROR("Render library failed to clear!");
            return false;
        }

        return true;
    }
}