#pragma once
#define MAX_BONE_INFLUENCE 4

#include "TNAH/Core/Core.h"
#include "TNAH/Core/Timestep.h"
#include "TNAH/Renderer/VertexArray.h"
#include "TNAH/Renderer/RenderingBuffers.h"
#include "TNAH/Renderer/Shader.h"
#include "TNAH/Renderer/Material.h"

#pragma warning(push, 0)
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include<glm/gtx/matrix_decompose.hpp>

#include "TNAH/Core/AABB.h"


#pragma warning(pop)
#pragma warning(push, 0)
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include <assimp/DefaultLogger.hpp>
#include <assimp/LogStream.hpp>
#pragma warning(pop)

namespace tnah {

    struct Index
    {
        uint32_t V1, V2, V3;
    };
    
    struct Vertex
    {
        glm::vec3 Position = {};
        glm::vec3 Normal = {};
        glm::vec3 Tangent = {};
        glm::vec3 Bitangents = {};
        glm::vec2 Texcoord = {};
    };

    struct AnimatedVertex
    {
        glm::vec3 Position = {};
        glm::vec3 Normal = {};
        glm::vec3 Tangent = {};
        glm::vec3 Bitangents = {};
        glm::vec2 Texcoord = {};

        float IDs[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
        float Weights[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
        
        void AddBoneData(uint32_t BoneID, float Weight)
        {
            for (size_t i = 0; i < 4; i++)
            {
                if (Weights[i] == 0.0f)
                {
                    IDs[i] = (float)BoneID;
                    Weights[i] = Weight;
                    return;
                }
            }
        }
    };

    struct BoneInfo
    {
        glm::mat4 BoneOffset;
        glm::mat4 FinalTransform;
    };

    class Submesh  {
    public:
        uint32_t MaterialIndex;
        uint32_t BaseVertex;
        uint32_t BaseIndex;
        uint32_t VertexCount;
        uint32_t IndexCount;
        
        friend class EditorUI;
        friend class Model;
    };

    class Model : public RefCounted
    {
    public:
        static Ref<Model> Create(const std::string& filePath);
        Model(const std::string& filePath);
        void OnUpdate(const Timestep& ts);

        
        Ref<VertexBuffer> GetVertexBuffer() const { return m_VertexBuffer; }
        Ref<VertexArray> GetVertexArray() const { return m_VertexArray; }
        Ref<IndexBuffer> GetIndexBuffer() const { return m_IndexBuffer; }
        const VertexBufferLayout& GetVertexBufferLayout() const { return m_VertexBufferLayout; }
        std::vector<Ref<Material>> GetMaterials() const { return m_Materials; }
        
        std::vector<Submesh>& GetSubmeshes() { return m_Submeshes; }
        uint32_t GetNumberOfSubmeshes() const { return static_cast<uint32_t>(m_Submeshes.size()); }
        uint32_t& GetBoneCount() { return m_BoneCount; }
        std::vector<glm::mat4>& GetBoneTransforms() { return m_BoneTransforms; }
        bool& IsAnimated() { return m_IsAnimated; }
        bool& GetIsAnimationPlaying() { return m_AnimationPlaying; }
    
    private:
        void LoadModel(const std::string& filePath);

        
        void CreateSubmesh(uint32_t meshIndex, const aiMesh* aMesh);
        void CreateBones(uint32_t meshIndex, const aiMesh* aMesh);
        void CreateMaterials(const aiScene* aScene, const std::string& filePath);
        void CreateRenderInformation();
        
        
        static glm::mat4 Mat4FromAssimpMat4(const aiMatrix4x4& matrix);
        static glm::vec3 Vec3FromAssimpVec3(const aiVector3D& vector);
        static glm::vec2 Vec2FromAssimpVec3(const aiVector3D& vector);

        static uint32_t TotalTexturesFromAssimpMaterial(const aiMaterial* material);
        static bool AssimpMaterialIsPBR(const aiMaterial* material);
        static std::vector<Ref<Texture2D>> GetTextureFromAssimpMaterial(
            const aiScene* scene, const aiMaterial* material, const aiTextureType& textureType);
        static Ref<Texture2D> CreateBaseColorTexture(const aiMaterial* material);
        static std::string GetTextureNameFromTextureType(const aiTextureType& textureType);
        static void DumpMaterialProperties(const aiMaterial* material);

        
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

        std::unique_ptr<Assimp::Importer> m_Importer;
        
        const aiScene* m_Scene;
        glm::mat4 m_InverseTransform;

        AABB m_BoundingBox;

        // Used for rendering, combines all the submesh data into a single batch to render
        Ref<VertexArray> m_VertexArray;
        Ref<VertexBuffer> m_VertexBuffer;
        Ref<IndexBuffer> m_IndexBuffer;
        VertexBufferLayout m_VertexBufferLayout;
        std::vector<Vertex> m_Vertices;
        std::vector<AnimatedVertex> m_AnimatedVertices;
        std::vector<Index> m_Indices;

        /**
         * Materials form the model as a whole
         */
        std::vector<Ref<Material>> m_Materials;
        Ref<Shader> m_Shader;
        
        bool m_IsAnimated = false;
        std::vector<BoneInfo> m_BoneInfo;
        uint32_t m_BoneCount = 0;
        std::unordered_map<std::string, uint32_t> m_BoneMapping;
        std::unordered_map<aiNode*, std::vector<uint32_t>> m_NodeMap;
        std::vector<glm::mat4> m_BoneTransforms;
        float m_AnimationTime = 0.0f;
        float m_WorldTime = 0.0f;
        float m_TimeMultiplier = 1.0f;
        bool m_AnimationPlaying = false;

        void ProcessModelSubmeshes(const aiScene* scene, const std::string& filePath);
        void CombineSubmeshData();
        void SetupRenderingObjects();
        
#if 0
        void SetVertexBoneDataToDefault(Vertex& vertex);
        void SetVertexBoneData(Vertex& vertex, int boneID, float weight);
        void ExtractBoneWeightForVertices(std::vector<Vertex>& vertices, aiMesh* mesh, const aiScene* scene);
        void LoadModel(const std::string& filePath);
        void ProcessNode(aiNode* node, const aiScene* scene);
        Submesh ProcessMesh(aiMesh* mesh, const aiScene* scene, bool animated);
        std::vector<Ref<Texture2D>> LoadMaterialTextures(const aiScene* scene, aiMaterial* material, aiTextureType type, const std::string& typeName);
#endif
        friend class EditorUI;
        friend class Serializer;
    };

    


}

