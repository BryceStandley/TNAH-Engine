#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include<glm/gtx/matrix_decompose.hpp>
#include "stb_image.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "Shader.h"


#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>


#include "Callbacks.h"
#include "OpenGL.h"

#include "Debugger.h"
#include "PhysicsManager.h"

/**
* @class Fbx
* @brief A class that represents a model in its entirety, allowing for multiple meshes and multiple textures if needed.
*
* @author Dylan Blereau
* @version 01
* @date 24/03/2021 Dylan Blereau, Started
* 
* @author Christopher Logan
* @version 02
* @date 25/04/2021 Christopher Logan, Moved to Fbx
*
**/
class Fbx
{
public:
    /// model data 
    std::vector<TextureMesh> textures_loaded;
    std::vector<Mesh> meshes;
    Renderer* render;
    std::string directory;
    bool gammaCorrection;


    /// default constructor
    Fbx() {}

    /**
    * @brief constructor that loads in the model from the given path
    * @param path - represents the model path
    * @param r - pointer to a renderer object
    * @param gamma - determines whether or not gamma correction is applied
    */
    Fbx(std::string const& path, Renderer* r, bool gamma = false) : gammaCorrection(gamma)
    {
        render = r;
        loadModel(path);
    }

    /**
    * @brief draws the model, and thus all it meshes
    * @param shader - represents the models shader object
    * @param model - represents the model matrix
    */
    void Draw(Shader& shader, glm::mat4 model);

    rp3d::BoxShape* collider;


private:

    /**
    * @brief converts a aiMatrix4x4t to a glm::mat4
    * @param m - represents a 4x4 matrix of floats
    * @return glm::mat4
    */
    glm::mat4 to_glm(aiMatrix4x4t<float> m);

    /**
    * @brief converts a aiVector3t to a glm::vec3
    * @param v - represents a vector of 3 floats
    * @return glm::vec3
    */
    glm::vec3 to_glm(aiVector3t<float> v);

    /**
    * @brief converts a aiQuaterniont to a glm::quat
    * @param q - represents a quaternion of 4 floats
    * @return glm::quat
    */
    glm::quat to_glm(aiQuaterniont<float> q);


    /**
    * @brief loads a model via assimp from file and stores the meshes in a vector
    * @param path - represents the path of the model
    */
    void loadModel(std::string const& path);

    /**
    * @brief processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
    * @param node
    * @param scene
    * @param transform
    */
    void processNode(aiNode* node, const aiScene* scene, glm::mat4 transform);

    /**
    * @brief translates the aiMesh object to a mesh object by running through the mesh's properties and storing data in the object
    * @param mesh - represents a pointer to the aiMesh
    * @param scene - represents a pointer to the scene
    * @param transform - represents the transform matrix required to properly set up models
    * @return Mesh
    */
    Mesh processMesh(aiMesh* mesh, const aiScene* scene, glm::mat4 transform);

    /**
    *
    * @brief check all material textures of a given type and loads the texture in if they haven't loaded yet
    * @param mat - represents assimps aiMaterial type
    * @param type - represents assimps aiTextureType
    * @param typeName - represents a string denoting the type of the texture material
    * @return std::vector<TextureMesh>
    */
    std::vector<TextureMesh> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

};

