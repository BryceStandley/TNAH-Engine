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
#pragma warning(push, 0) // Stopping any warnings or errors from being included on build from 3rd parties
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
    	* @fn void Model::LoadModel(const std::string& filePath);
    	*
    	* @brief Gets the inverse of the global transform of the model.
    	* @brief Loads a model from a file path
    	*
    	* @author Bryce Standley
    	* @date 15/09/2021
    	*
    	* @return Mat4 inverse of the global transform.
    	* @param filePath The relative or absolute file path of a 3D model.
    	*/
        void LoadModel(const std::string& filePath);

    	/**
    	* @fn glm::mat4 Model::GetGlobalInverseTransform() const { return m_GlobalInverseTransform; }
    	* @fn void Model::ProcessSubmesh(aiMesh* mesh, const aiScene* scene, glm::mat4 nodeTransformation);
    	*
    	* @brief Gets the inverse of the global transform of the model.
    	* @brief Processes a submesh of a 3D model.
    	*
    	* @author Bryce Standley
    	* @date 15/09/2021
    	*
    	* @return Mat4 inverse of the global transform.
    	* @param mesh A Assimp mesh that holds the submesh data
    	* @param scene A Assimp scene that holds the overall 3D model and its scene
    	* @param nodeTransformation The transformation of the submesh and its nodes from the root transform
    	*/
		static Submesh ProcessSubmesh(aiMesh* mesh, const aiScene* scene, glm::mat4 nodeTransformation);
    	
    	/**
    	* @fn glm::mat4 Model::GetGlobalInverseTransform() const { return m_GlobalInverseTransform; }
    	* @fn voil Model::ProcessNode(aiNode* node, const aiScene* scene, glm::mat4 nodeTransformation);
    	*
    	* @brief Gets the inverse of the global transform of the model.
    	* @brief Processes a node of the 3D model
    	*
    	* @author Bryce Standley
    	* @date 15/09/2021
    	*
    	* @return Mat4 inverse of the global transform.
    	* @param node A Assimp node within the imported scene
    	* @param scene A Assimp scene that holds the overall 3D model and its scene
    	* @param nodeTransformation Transform of the parent node to this node
    	* 
    	*/
    	void ProcessNode(aiNode* node, const aiScene* scene, glm::mat4 nodeTransformation);

    	/**
    	* @fn boid Model::ProcessBones(uint32_t meshIndex, const aiMesh* mesh);
    	*
    	* @brief Processes bones of a 3D model if the model has animations.
    	*
    	* @author Bryce Standley
    	* @date 15/09/2021
    	*
    	* @return Mat4 inverse of the global transform.
    	* @param meshIndex A index of which mesh within the models scene to process
    	* @param mesh A Assimp submesh of the model
    	* 
    	*/
        void ProcessBones(uint32_t meshIndex, const aiMesh* mesh);

    	/**
    	* @fn glm::mat4 Model::GetGlobalInverseTransform() const { return m_GlobalInverseTransform; }
    	* @fn std::vector<Ref<Material>> Model::ProcessMaterials(const aiScene* scene, aiMesh* mesh);
    	*
    	* @brief Processes the materials of the 3D model
    	*
    	* @author Bryce Standley
    	* @date 15/09/2021
    	*
    	* @return Mat4 inverse of the global transform.
    	* @param scene A Assimp scene that holds the overall 3D model and its scene
    	* @param mesh A Assimp mesh to process.
    	* 
    	*/
		static std::vector<Ref<Material>> ProcessMaterials(const aiScene* scene, aiMesh* mesh);

    	/**
    	* @fn glm::mat4 Model::GetGlobalInverseTransform() const { return m_GlobalInverseTransform; }
    	* @fn void Model::FindRootNode(aiNode* node, aiMesh* mesh) const;
    	*
    	* @brief Finds the root node of a mesh.
    	*
    	* @author Bryce Standley
    	* @date 15/09/2021
    	*
    	* @return Mat4 inverse of the global transform.
    	* @param node A Assimp node.
    	* @param mesh A Assimp mesh.
    	* 
    	*/
    	aiNode* FindRootNode(aiNode* node, aiMesh* mesh) const;

    	/**
    	* @fn glm::mat4 Model::GetGlobalInverseTransform() const { return m_GlobalInverseTransform; }
    	* @fn void Model::LoadAnimationNodes(aiNode* node, aiMesh* mesh);
    	*
    	* @brief Gets the inverse of the global transform of the model.
    	* @brief Loads the animation nodes of the submesh.
    	*
    	* @author Bryce Standley
    	* @date 15/09/2021
    	*
    	* @return Mat4 inverse of the global transform.
    	* @param node A Assimp node.
    	* @param mesh A Assimp mesh.
    	* 
    	*/
    	void LoadAnimationNodes(aiNode* node, aiMesh* mesh);

    	/**
    	* @fn glm::mat4 Model::GetGlobalInverseTransform() const { return m_GlobalInverseTransform; }
    	* @fn Node Model::LoadNodeHierarchy(aiNode* rootNode);
    	*
    	* @brief Gets the inverse of the global transform of the model.
    	* @brief Loads the Assimp node hierarchy from the root node into a TNAH Node structure.
    	*
    	* @author Bryce Standley
    	* @date 15/09/2021
    	*
    	* @return Mat4 inverse of the global transform.
    	* @returns A Node containing the hierarchical data of all Assimp nodes within the scene.
    	* 
    	*/
		static Node LoadNodeHierarchy(aiNode* rootNode);

    	/**
    	* @fn glm::mat4 Model::GetGlobalInverseTransform() const { return m_GlobalInverseTransform; }
    	* @fn void Model:: LoadAnimations(const aiScene* scene);
    	*
    	* @brief Loads animations from the Assimp model scene.
    	*
    	* @author Bryce Standley
    	* @date 15/09/2021
    	*
    	* @return Mat4 inverse of the global transform.
    	* @param scene A Assimp scene.
    	* 
    	*/
    	void LoadAnimations(const aiScene* scene);
    	

    	/**
    	 * @brief This function is temporary to test and make sure data is being processed correctly before moving to batch rendering.
    	 */
    	void ProcessSubmeshesForRendering();
    	
#pragma region HelperFunctions
		/**
         * \fn uint32_t tnah::Model::TotalTexturesFromAssimpMaterial(const aiMaterial* material)
         * 
         * \brief Gets the total textures within a Assimp material.
         *
         * \author Bryce Standley
         * \date Friday, 17 September 2021
         * 
         * \param material A Assimp material to use
         *
         * \return  a unsigned int of the total textures used.
         *
         */
        static uint32_t TotalTexturesFromAssimpMaterial(const aiMaterial* material);

    	
		/**
         * \fn bool ::tnah::Model::AssimpMaterialIsPBR(const aiMaterial* material)
         * 
         * \brief Checks if a Assimp material is a PBR material or standard material.
         *
         * \author Bryce Standley
         * \date Friday, 17 September 2021
         * 
         * \param material A Assimp material to test.
         *
         * \return  true if material is PBR else false
         *
         */
        static bool AssimpMaterialIsPBR(const aiMaterial* material);

    	
		/**
         * \fn std::vector<tnah::Ref<tnah::Texture2D>> ::tnah::Model::GetTextureFromAssimpMaterial(const aiScene* scene, const aiMaterial* material, const aiTextureType& textureType)
         * 
         * \brief Gets textures from a Assimp material, loads them and returns them.
         *
         * \author Bryce Standley
         * \date Friday, 17 September 2021
         * 
         * \param scene A Assimp Scene
         * \param material A Assimp Material
         * \param textureType a Assimp texture type
         *
         * \return  a vector of Texture2D references
         *
         */
        static std::vector<Ref<Texture2D>> GetTextureFromAssimpMaterial(
            const aiScene* scene, const aiMaterial* material, const aiTextureType& textureType);

    	
		/**
         * \fn tnah::Ref<tnah::Texture2D> ::tnah::Model::CreateBaseColorTexture(const aiMaterial* material)
         * 
         * \brief Creates a default texture using a Assimp materials base color.
         *
         * \author Bryce Standley
         * \date Friday, 17 September 2021
         * 
         * \param material a Assimp material
         *
         * \return  a reference to a Texture2D
         *
         */
        static Ref<Texture2D> CreateBaseColorTexture(const aiMaterial* material);
    	
		/**
         * \fn std::string ::tnah::Model::GetTextureNameFromTextureType(const aiTextureType& textureType)
         * 
         * \brief Gets the a texture name from a Assimp texture type
         *
         * \author Bryce Standley
         * \date Friday, 17 September 2021
         * 
         * \param textureType a Assimp texture type
         *
         * \return  a string of the name
         *
         */
        static std::string GetTextureNameFromTextureType(const aiTextureType& textureType);
    	
		/**
         * \fn void ::tnah::Model::DumpMaterialProperties(const aiMaterial* material)
         * 
         * \brief Dumps the properties of a Assimp material to the console. Useful for debugging models and loading issues.
         *
         * \author Bryce Standley
         * \date Friday, 17 September 2021
         * 
         * \param material a Assimp material
         *
         */
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

    	//Temp variables
    	std::vector<Vertex> m_Vertices;
    	std::vector<uint32_t> m_Indices;
    	Ref<VertexArray> m_VertexArray;
    	Ref<VertexBuffer> m_VertexBuffer;
    	Ref<IndexBuffer> m_IndexBuffer;
    	VertexBufferLayout m_VertexBufferLayout;
    	
        friend class EditorUI;
        friend class Serializer;
    };

}

