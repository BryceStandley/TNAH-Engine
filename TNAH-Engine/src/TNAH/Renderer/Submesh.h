#pragma once
#define MAX_BONE_INFLUENCE 4

#include "TNAH/Core/Core.h"
#include "TNAH/Core/Timestep.h"
#include "TNAH/Renderer/VertexArray.h"
#include "TNAH/Renderer/RenderingBuffers.h"
#include "TNAH/Renderer/Shader.h"
#include "TNAH/Renderer/Material.h"
#include "Animation.h"

#pragma warning(push, 0)
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include<glm/gtx/matrix_decompose.hpp>

#include "TNAH/Core/AABB.h"


#pragma warning(pop)

//Forward Decs
struct aiNode;
struct aiAnimation;
struct aiNodeAnim;
struct aiScene;
namespace Assimp {
    class Importer;
}

namespace tnah {

    struct Index
    {
        uint32_t V1, V2, V3;
    };
    
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

    struct BoneInfo
    {
        glm::mat4 BoneOffset;
        glm::mat4 FinalTransform;
    };

    struct VertexBoneData
    {
        uint32_t IDs[4];
        float Weights[4];

        VertexBoneData()
        {
            memset(IDs, 0, sizeof(IDs));
            memset(Weights, 0, sizeof(Weights));
        };

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
            
            TNAH_CORE_ASSERT(false, "Too many bones!");
        }
    };

    struct ModelMaterialTexture
    {
        Ref<Texture2D> Texture;
        std::string TexturePath;

        ModelMaterialTexture(Ref<Texture2D> texture, const std::string& path)
            :Texture(texture), TexturePath(path)
        {}
    };

    struct ModelMaterialShader
    {
        Ref<Shader> Shader;
        std::string VertexShaderPath;
        std::string FragmentShaderPath;

        ModelMaterialShader(Ref<tnah::Shader> shader, const std::string& vertex, const std::string& fragment)
            :Shader(shader), VertexShaderPath(vertex), FragmentShaderPath(fragment)
        {}
    };

    class Submesh  {
    public:
        Submesh();

        Ref<VertexArray> GetVertexArray() const {return m_VertexArray;}
        Ref<VertexBuffer> GetVertexBuffer() const {return m_VertexBuffer;}
        Ref<IndexBuffer> GetIndexBuffer() const {return m_IndexBuffer;}
        Ref<Material> GetMaterials() const {return m_Material;}
    private:
        // Submesh data
        std::vector<Vertex> m_Vertices;
        std::vector<Index> m_Indices;
        uint32_t m_BaseVertex;
        uint32_t m_BaseIndex;
        
        uint32_t m_MaterialIndex;
        uint32_t m_VertexCount;
        uint32_t m_IndexCount;

        AABB m_BoundingBox;
        
        // Animation
        std::vector<AnimatedVertex> m_AnimatedVertices;
        bool m_IsAnimated = false;
        float m_TimeMultiplier = 1.0f;
        bool m_AnimationPlaying = true;


        glm::mat4 m_Transform{1.0f};
        std::string m_NodeName, m_MeshName;
        
        
        Ref<VertexArray> m_VertexArray;
        Ref<VertexBuffer> m_VertexBuffer;
        Ref<IndexBuffer> m_IndexBuffer;
        VertexBufferLayout m_VertexBufferLayout;
        
        friend class EditorUI;
        friend class Model;
    };

    

    class Model : public RefCounted
    {
    public:
        static Ref<Model> Create(const std::string& filePath);
        Model();
        Model(const std::string& filePath);

        Ref<VertexBuffer> GetVertexBuffer() { return m_VertexBuffer; }
        Ref<IndexBuffer> GetIndexBuffer() { return m_IndexBuffer; }
        const VertexBufferLayout& GetVertexBufferLayout() const { return m_VertexBufferLayout; }

        auto& GetAnimation() { return m_Animation; }
        
        std::vector<Submesh> GetMeshes() const { return m_Submeshes; }
        uint32_t GetNumberOfMeshes() const { return static_cast<uint32_t>(m_Submeshes.size()); }
        
        auto& GetBoneInfoMap() { return m_BoneInfoMap; }
        uint32_t& GetBoneCount() { return m_BoneCount; }
    private:
        void BoneTransform(float time);
        void ReadNodeHierarchy(float AnimationTime, const aiNode* pNode, const glm::mat4& ParentTransform);
        void TraverseNodes(aiNode* node, const glm::mat4& parentTransform = glm::mat4(1.0f), uint32_t level = 0);

        const aiNodeAnim* FindNodeAnim(const aiAnimation* animation, const std::string& nodeName);
        uint32_t FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim);
        uint32_t FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim);
        uint32_t FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim);
        glm::vec3 InterpolateTranslation(float animationTime, const aiNodeAnim* nodeAnim);
        glm::quat InterpolateRotation(float animationTime, const aiNodeAnim* nodeAnim);
        glm::vec3 InterpolateScale(float animationTime, const aiNodeAnim* nodeAnim);
    
    private:
        
        std::vector<Submesh> m_Submeshes;
        Resource m_Resource;
        
        Scope<Assimp::Importer> m_Importer;
        const aiScene* m_Scene;
        glm::mat4 m_InverseTransform;

        AABB m_BoundingBox;
        

        // TODO: Make all submeshes push their data into a single VAO/VBO to reduce render calls and improve performance
        // TODO: These are just here so they exist but are NOT USED currently
        Ref<VertexArray> m_VertexArray;
        Ref<VertexBuffer> m_VertexBuffer;
        Ref<IndexBuffer> m_IndexBuffer;
        VertexBufferLayout m_VertexBufferLayout;

        /**
         * Material form the model as a whole
         */
        std::vector<Ref<Material>> m_Materials;
        
        bool m_IsAnimated = false;
        std::vector<BoneInfo> m_BoneInfo;
        uint32_t m_BoneCount = 0;
        std::unordered_map<std::string, uint32_t> m_BoneMapping;
        std::unordered_map<aiNode*, std::vector<uint32_t>> m_NodeMap;
        std::vector<glm::mat4> m_BoneTransforms;


        bool ProcessModelSubmeshes(const aiScene* scene);
        
        
        void SetVertexBoneDataToDefault(Vertex& vertex);
        void SetVertexBoneData(Vertex& vertex, int boneID, float weight);
        void ExtractBoneWeightForVertices(std::vector<Vertex>& vertices, aiMesh* mesh, const aiScene* scene);
        void LoadModel(const std::string& filePath);
        void ProcessNode(aiNode* node, const aiScene* scene);
        Submesh ProcessMesh(aiMesh* mesh, const aiScene* scene, bool animated);
        std::vector<Ref<Texture2D>> LoadMaterialTextures(const aiScene* scene, aiMaterial* material, aiTextureType type, const std::string& typeName);
        friend class EditorUI;
        friend class Serializer;
    };

}

