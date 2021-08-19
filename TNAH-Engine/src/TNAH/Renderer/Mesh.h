#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include<glm/gtx/matrix_decompose.hpp>

#include "TNAH/Core/Core.h"
#include "TNAH/Core/Timestep.h"
#include "TNAH/Renderer/VertexArray.h"
#include "TNAH/Renderer/RenderingBuffers.h"
#include "TNAH/Renderer/Shader.h"
#include "TNAH/Renderer/Material.h"

#include <Assimp/Importer.hpp>
#include <Assimp/scene.h>
#include <Assimp/postprocess.h>

namespace tnah {
struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec3 Tangent;
    glm::vec3 Bitangents;
    glm::vec2 Texcoord;
};

struct AnimatedVertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec3 Tangent;
    glm::vec3 Bitangents;
    glm::vec2 Texcoord;

    uint32_t IDs[4] = { 0, 0,0, 0 };
    float Weights[4]{ 0.0f, 0.0f, 0.0f, 0.0f };

    void AddBoneData(uint32_t BoneID, float Weight)
    {
        for (size_t i = 0; i < 4; i++)
        {
            if (Weights[i] == 0.0)
            {
                IDs[i] = BoneID;
                Weights[i] = Weight;
                return;
            }
        }

        // TODO: Keep top weights
        TNAH_CORE_WARN("Vertex has more than four bones/weights affecting it, extra data will be discarded (BoneID={0}, Weight={1})", BoneID, Weight);
    }
};

    struct MeshTexture
    {
        Ref<Texture2D> Texture;
        std::string TexturePath;

        MeshTexture(Ref<Texture2D> texture, const std::string& path)
            :Texture(texture), TexturePath(path)
        {}
    };

    struct MeshShader
    {
        Ref<Shader> Shader;
        std::string VertexShaderPath;
        std::string FragmentShaderPath;

        MeshShader(Ref<tnah::Shader> shader, const std::string& vertex, const std::string& fragment)
            :Shader(shader), VertexShaderPath(vertex), FragmentShaderPath(fragment)
        {}
    };

    class Mesh {
    public:


        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Ref<Texture2D>> textures);

        Ref<VertexArray> GetMeshVertexArray() const {return m_Vao;}
        Ref<VertexBuffer> GetMeshVertexBuffer() const {return m_Vbo;}
        Ref<IndexBuffer> GetMeshIndexBuffer() const {return m_Ibo;}
        Ref<Material> GetMeshMaterial() const {return m_Material;}
    private:
        // mesh data
        std::vector<Vertex> m_Vertices;
        std::vector<uint32_t> m_Indices;
        
        Ref<VertexArray> m_Vao;
        Ref<VertexBuffer> m_Vbo;
        Ref<IndexBuffer> m_Ibo;
        Ref<Material> m_Material;
        BufferLayout m_BufferLayout;
        friend class EditorUI;
    };

    class Model
    {
    public:
        static Model* Create(const std::string& filePath);
        
    
        std::vector<Mesh> GetMeshes() const { return m_Meshes; }
        uint32_t GetNumberOfMeshes() const { return static_cast<uint32_t>(m_Meshes.size()); }
    private:
        Model();
        Model(const std::string& filePath);
        std::vector<Mesh> m_Meshes;
        std::string m_Directory;
        std::string m_FilePath;

        glm::mat4 AiToGLM(aiMatrix4x4t<float> m);
        glm::vec3 AiToGLM(aiVector3t<float> v);
        glm::quat AiToGLM(aiQuaterniont<float> q);
        
        void LoadModel(const std::string& filePath);
        void ProcessNode(aiNode* node, const aiScene* scene);
        Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
        std::vector<Ref<Texture2D>> LoadMaterialTextures(const aiScene* scene, aiMaterial* material, aiTextureType type, const std::string& typeName);
        friend class EditorUI;
        friend class Serializer;
    };

}

