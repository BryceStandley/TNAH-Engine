#pragma once
#define MAX_BONE_INFLUENCE 4

#include "TNAH/Core/Core.h"
#include "TNAH/Core/Timestep.h"
#include "TNAH/Renderer/VertexArray.h"
#include "TNAH/Renderer/RenderingBuffers.h"
#include "TNAH/Renderer/Shader.h"
#include "TNAH/Renderer/Material.h"
#include "TNAH/Renderer/Animation.h"
#include "TNAH/Renderer/Submesh.h"

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

#include "TNAH/Core/AABB.h"
#include "TNAH/Core/AABB.h"
#pragma warning(pop)

namespace tnah {

    struct Node
    {
        /** @brief Transform of the node*/
        glm::mat4 Transform = {};

        /** @brief Name of the node*/
        std::string Name = "";

        /** @brief Vector of children within the node*/
        std::vector<Node> NodeChildren = {};

        /** @brief Total children of the node*/
        uint32_t TotalNodeChildren = 0;
    };
    
    struct Bone
    {
        /** @brief Offset of the bone from the parent*/
        glm::mat4 Offset = glm::mat4(1.0f);

        /** @brief Transform of the bone */
        glm::mat4 Transform = glm::mat4(1.0f);
    };
    

    class Model : public RefCounted
    {
    public:
        
        /**
        * @fn static Ref<Model> Model::Create();
        *
        * @brief Creates and returns a empty Ref to a Model.
        *
        * @author Bryce Standley
        * @date 15/09/2021
        *
        * @return Ref of type Model with empty data.
        */
        static Ref<Model> Create();

        /**
        * @fn static Ref<Model> Model::Create();
        *
        * @brief Creates a Model from file and returns a Ref to it.
        *
        * @author Bryce Standley
        * @date 15/09/2021
        *
        * @param filePath The file path on disc of the model to create.
        *
        * @return Ref of type Model with loaded model data from disc.
        *
        * @note File path should be relative to the application or an absolute path to the model file.
        */
        static Ref<Model> Create(const std::string& filePath);

        /**
         * @fn Model::Model() = default;
         *
         * @brief Default constructor for empty model
         *
         * @author Bryce Standley
         * @date 15/09/2021
         */
        Model() = default;

        /**
        * @fn Model::Model(const std::string& filePath);
        *
        * @brief Default constructor with a file path of the model to load.
        *
        * @author Bryce Standley
        * @date 15/09/2021
        *
        * @param filePath The file path of the model to load. 
        */
        Model(const std::string& filePath);
        
        /**
        * @fn Animation* Model::GetAnimation(const std::string& animationName);
        *
        * @brief Gets the animation by name
        *
        * @author Bryce Standley
        * @date 15/09/2021
        *
        * @param animationName The name of the animation to get. 
        */
        Animation* GetAnimation(const std::string& animationName);

        /**
        * @fn uint32_t Model::GetTotalBones();
        *
        * @brief Gets the total bones within the model.
        *
        * @author Bryce Standley
        * @date 15/09/2021
        *
        * @return Total Bones within the model. 
        */
        uint32_t GetTotalBones() const { return static_cast<uint32_t>(m_Bones.size()); }

        /**
        * @fn Node& Model::GetRootNode() { return m_RootNode; }
        *
        * @brief Gets the root node of the model.
        *
        * @author Bryce Standley
        * @date 15/09/2021
        *
        * @return Root Node of the model.
        */
        Node& GetRootNode() { return m_RootNode; }

        /**
        * @fn std::map<std::string, uint32_t>& Model::GetBoneMap() { return m_BoneMap; }
        *
        * @brief Gets the bone map of name and ID's within the model.
        *
        * @author Bryce Standley
        * @date 15/09/2021
        *
        * @return std::map reference of bone name and ID's within the model.
        */
        std::map<std::string, uint32_t>& GetBoneMap() { return m_BoneMap; }

        /**
        * @fn  std::vector<Bone>& Model::GetBones() { return m_Bones; }
        *
        * @brief Gets a vector of bones within the model.
        *
        * @author Bryce Standley
        * @date 15/09/2021
        *
        * @return std::vector reference of bones within the model.
        */
        std::vector<Bone>& GetBones() { return m_Bones; }

        /**
        * @fn glm::mat4 Model::GetGlobalInverseTransform() const { return m_GlobalInverseTransform; }
        *
        * @brief Gets the inverse of the global transform of the model.
        *
        * @author Bryce Standley
        * @date 15/09/2021
        *
        * @return Mat4 inverse of the global transform.
        */
        glm::mat4 GetGlobalInverseTransform() const { return m_GlobalInverseTransform; }
    
    private:
//TODO: Update doxy for these private functions
    	
    	/**
    	* @fn glm::mat4 Model::GetGlobalInverseTransform() const { return m_GlobalInverseTransform; }
    	*
    	* @brief Gets the inverse of the global transform of the model.
    	*
    	* @author Bryce Standley
    	* @date 15/09/2021
    	*
    	* @return Mat4 inverse of the global transform.
    	*/
        void LoadModel(const std::string& filePath);

    	/**
    	* @fn glm::mat4 Model::GetGlobalInverseTransform() const { return m_GlobalInverseTransform; }
    	*
    	* @brief Gets the inverse of the global transform of the model.
    	*
    	* @author Bryce Standley
    	* @date 15/09/2021
    	*
    	* @return Mat4 inverse of the global transform.
    	*/
		static Submesh ProcessSubmesh(aiMesh* mesh, const aiScene* scene, glm::mat4 nodeTransformation);
    	
    	/**
    	* @fn glm::mat4 Model::GetGlobalInverseTransform() const { return m_GlobalInverseTransform; }
    	*
    	* @brief Gets the inverse of the global transform of the model.
    	*
    	* @author Bryce Standley
    	* @date 15/09/2021
    	*
    	* @return Mat4 inverse of the global transform.
    	*/
    	void ProcessNode(aiNode* node, const aiScene* scene, glm::mat4 nodeTransformation);

    	/**
    	* @fn glm::mat4 Model::GetGlobalInverseTransform() const { return m_GlobalInverseTransform; }
    	*
    	* @brief Gets the inverse of the global transform of the model.
    	*
    	* @author Bryce Standley
    	* @date 15/09/2021
    	*
    	* @return Mat4 inverse of the global transform.
    	*/
        void ProcessBones(uint32_t meshIndex, const aiMesh* mesh);

    	/**
    	* @fn glm::mat4 Model::GetGlobalInverseTransform() const { return m_GlobalInverseTransform; }
    	*
    	* @brief Gets the inverse of the global transform of the model.
    	*
    	* @author Bryce Standley
    	* @date 15/09/2021
    	*
    	* @return Mat4 inverse of the global transform.
    	*/
		static std::vector<Ref<Material>> ProcessMaterials(const aiScene* scene, aiMesh* mesh);

    	/**
    	* @fn glm::mat4 Model::GetGlobalInverseTransform() const { return m_GlobalInverseTransform; }
    	*
    	* @brief Gets the inverse of the global transform of the model.
    	*
    	* @author Bryce Standley
    	* @date 15/09/2021
    	*
    	* @return Mat4 inverse of the global transform.
    	*/
    	aiNode* FindRootNode(aiNode* node, aiMesh* mesh) const;

    	/**
    	* @fn glm::mat4 Model::GetGlobalInverseTransform() const { return m_GlobalInverseTransform; }
    	*
    	* @brief Gets the inverse of the global transform of the model.
    	*
    	* @author Bryce Standley
    	* @date 15/09/2021
    	*
    	* @return Mat4 inverse of the global transform.
    	*/
    	void LoadAnimationNodes(aiNode* node, aiMesh* mesh);

    	/**
    	* @fn glm::mat4 Model::GetGlobalInverseTransform() const { return m_GlobalInverseTransform; }
    	*
    	* @brief Gets the inverse of the global transform of the model.
    	*
    	* @author Bryce Standley
    	* @date 15/09/2021
    	*
    	* @return Mat4 inverse of the global transform.
    	*/
		static Node LoadNodeHierarchy(aiNode* rootNode);

    	/**
    	* @fn glm::mat4 Model::GetGlobalInverseTransform() const { return m_GlobalInverseTransform; }
    	*
    	* @brief Gets the inverse of the global transform of the model.
    	*
    	* @author Bryce Standley
    	* @date 15/09/2021
    	*
    	* @return Mat4 inverse of the global transform.
    	*/
    	void LoadAnimations(const aiScene* scene);
    	

    	
#pragma region HelperFunctions
        static glm::mat4 Mat4FromAssimpMat4(const aiMatrix4x4& matrix);
        static glm::vec3 Vec3FromAssimpVec3(const aiVector3D& vector);
        static glm::vec2 Vec2FromAssimpVec3(const aiVector3D& vector);
    	static glm::quat QuatFromAssimpQuat(const aiQuaternion& quaternion);
        static uint32_t TotalTexturesFromAssimpMaterial(const aiMaterial* material);
        static bool AssimpMaterialIsPBR(const aiMaterial* material);
        static std::vector<Ref<Texture2D>> GetTextureFromAssimpMaterial(
            const aiScene* scene, const aiMaterial* material, const aiTextureType& textureType);
        static Ref<Texture2D> CreateBaseColorTexture(const aiMaterial* material);
        static std::string GetTextureNameFromTextureType(const aiTextureType& textureType);
        static void DumpMaterialProperties(const aiMaterial* material);
#pragma endregion 
    
    private:
    	
    	/** @brief Resource information about the model on disc*/
    	Resource m_Resource;

    	/** @brief Flag for if the model is animated or not. True if animated, false if not.*/
    	bool m_IsAnimated = false;
    	
        /** @brief Inverse of the models global transform*/
        glm::mat4 m_GlobalInverseTransform = {};

        /** @brief Vector of submeshes within the model*/
        std::vector<Submesh> m_Submeshes = {};

        /** @brief Vector of bones within the model*/
        std::vector<Bone> m_Bones = {};

        /** @brief Map of bone information within the model*/
        std::map<std::string, uint32_t> m_BoneMap = {};

        /** @brief Root node of the model*/
        Node m_RootNode = {};

        /** @brief Vector of animations within the model*/
        std::vector<Animation> m_Animations = {};

    	/** @brief Root node of the animation structure*/
    	Node m_RootAnimationNode = {};

    	/** @brief Total bones in the model*/
    	uint32_t m_TotalBones = 0;
    	
        friend class EditorUI;
        friend class Serializer;
    };

    


}

