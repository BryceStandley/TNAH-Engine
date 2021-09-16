#pragma once

namespace tnah{

    /**
    * @class RenderLibrary
    *
    * @brief  Holds Renderer library data like default shaders
    *
    * @author Bryce Standley
    * @date 16/09/21
    */
    class RenderLibrary
    {
    public:

        /**
        * @enumclass LibraryShader
        *
        * @brief Used to identify different shaders within the library.
        *
        * @author Bryce Standley
        * @date 16/09/21
        *
        */
        enum class LibraryShader
        {
            Mesh, Terrain, Skybox, Physics
        };

        /**
        * @fn static bool RenderLibrary::InitializeLibrary();
        *
        * @brief Sets up the RenderLibrary with default shaders and data.
        *
        * @author Bryce Standley
        * @date 16/09/21
        *
        */
        static bool InitializeLibrary();

        /**
        * @fn static bool RenderLibrary::InitializeLibrary(const std::string& meshShaderPath, const std::string& terrainShaderPath, const std::string& skyboxShaderPath, const std::string& physicsShaderPath);
        *
        * @brief Sets up the RenderLibrary with user defined shaders to load.
        *
        * @author Bryce Standley
        * @date 16/09/21
        *
        */
        static bool InitializeLibrary(const std::string& meshShaderPath, const std::string& terrainShaderPath,
                                      const std::string& skyboxShaderPath, const std::string& physicsShaderPath);

        /**
        * @fn static bool RenderLibrary::InitializeLibrary(const Ref<Shader>& meshShader, const Ref<Shader>& terrainShader,const Ref<Shader>& skyboxShader, const Ref<Shader>& physicsShader);
        *
        * @brief Sets up the RenderLibrary with pre-loaded shaders.
        *
        * @author Bryce Standley
        * @date 16/09/21
        *
        */
        static bool InitializeLibrary(const Ref<Shader>& meshShader, const Ref<Shader>& terrainShader,
                                      const Ref<Shader>& skyboxShader, const Ref<Shader>& physicsShader);

        /**
        * @fn static bool RenderLibrary::ClearLibrary();
        *
        * @brief Used to clear the library and release any ref's to data.
        *
        * @author Bryce Standley
        * @date 16/09/21
        *
        */
        static bool ClearLibrary();
        
        /**
        * @fn static Ref<Shader> RenderLibrary::GetShader(LibraryShader shaderType);
        *
        * @brief Gets the shader of a given type within the library.
        *
        * @author Bryce Standley
        * @date 16/09/21
        *
        * @param shaderType The type of the shader within the library to set.
        *
        */
        static Ref<Shader> GetShader(LibraryShader shaderType);

        /**
        * @fn static std::unordered_map<std::string, Ref<Shader>> RenderLibrary::GetAllShaders();
        *
        * @brief Gets a unordered map of all shaders with basic names to identify them.
        *
        * @author Bryce Standley
        * @date 16/09/21
        *
        * @return Unordered map of shaders with basic names to describe them.
        *
        * @note Shader names are simple all lower names. eg. "mesh" = Mesh Shader, "terrain" = Terrain Shader, etc...
        *
        */
        static std::unordered_map<std::string, Ref<Shader>> GetAllShaders();

        /**
        * @fn static void RenderLibrary::SetShader(LibraryShader shaderType, const Ref<Shader>& shaderToSet);
        *
        * @brief Sets the shader of a given type.
        *
        * @author Bryce Standley
        * @date 16/09/21
        *
        * @param shaderType The type of the shader within the library to set.
        * @param shaderToSet The shader to set within the library.
        *
        * @note shaderToSet must be preloaded.
        */
        static void SetShader(LibraryShader shaderType, const Ref<Shader>& shaderToSet);

        /**
        * @fn static void RenderLibrary::SetShader(LibraryShader shaderType, const std::string& shaderPath);
        *
        * @brief Sets the shader of a given type.
        *
        * @author Bryce Standley
        * @date 16/09/21
        *
        * @param shaderType The type of the shader within the library to set.
        * @param shaderPath Path of the shader file to load and set.
        *
        */
        static void SetShader(LibraryShader shaderType, const std::string& shaderPath);

        /**
        * @fn static void RenderLibrary::SetShader(LibraryShader shaderType, const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
        *
        * @brief Sets the shader of a given type.
        *
        * @author Bryce Standley
        * @date 16/09/21
        *
        * @param shaderType The type of the shader within the library to set.
        * @param vertexShaderPath Path of the vertex shader file to load.
        * @param fragmentShaderPath Path of the fragment shader file to load.
        *
        */
        static void SetShader(LibraryShader shaderType, const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

        /**
        * @fn static void RenderLibrary::SetShader(LibraryShader shaderType, const char* shaderPath);
        *
        * @brief Sets the shader of a given type.
        *
        * @author Bryce Standley
        * @date 16/09/21
        *
        * @param shaderType The type of the shader within the library to set.
        * @param shaderPath Path of the shader file to load.
        *
        */
        static void SetShader(LibraryShader shaderType, const char* shaderPath);

        /**
        * @fn static void RenderLibrary::SetShader(LibraryShader shaderType, const char* vertexShaderPath,  const char* fragmentShaderPath);
        *
        * @brief Sets the shader of a given type.
        *
        * @author Bryce Standley
        * @date 16/09/21
        *
        * @param shaderType The type of the shader within the library to set.
        * @param vertexShaderPath Path of the vertex shader file to load.
        * @param fragmentShaderPath Path of the fragment shader file to load.
        *
        */
        static void SetShader(LibraryShader shaderType, const char* vertexShaderPath,  const char* fragmentShaderPath);

        

    private:
       
        /** @brief The Library shader for meshes*/
        static Ref<Shader> m_MeshShader;

        /** @brief The Library shader for terrains*/
        static Ref<Shader> m_TerrainShader;

        /** @brief The Library shader for skybox's*/
        static Ref<Shader> m_SkyboxShader;

        /** @brief The Library shader for physics colliders*/
        static Ref<Shader> m_PhysicsShader;

        friend class Renderer;
    };
}
