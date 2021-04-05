#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include<glm/gtx/matrix_decompose.hpp>
#include "stb_image.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "shader.h"


#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>


#include "Callbacks.h"
#include "OpenGL.h"

    /**
    * @class Model
    * @brief A class that represents a model in its entirety, allowing for multiple meshes and multiple textures if needed. 
    *
    * @author Dylan Blereau
    * @version 01
    * @date 24/03/2021 Dylan Blereau, Started
    *
    **/
class Model
{
public:
        /// model data 
    std::vector<TextureMesh> textures_loaded;
    std::vector<Mesh>    meshes;
    Renderer* render;
    std::string directory;
    bool gammaCorrection;
 

        /// default constructor
    Model(){}

        /**
        * @brief constructor that loads in the model from the given path
        * @param path - represents the model path
        * @param gamma - determines whether or not gamma correction is applied
        */
    Model(std::string const& path, bool gamma = false) : gammaCorrection(gamma)
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
   

        // walk through each of the mesh's vertices
        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            //const bool uvs = mesh->HasTextureCoords(0);
            Vertex vertex;
            glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
            // positions
            if (mesh->HasPositions())
            {
                vector.x = mesh->mVertices[i].x;
                vector.y = mesh->mVertices[i].y;
                vector.z = mesh->mVertices[i].z;
                vertex.Position = vector;
            }

            // normals
            if (mesh->HasNormals()) {
                vector.x = mesh->mNormals[i].x;
                vector.y = mesh->mNormals[i].y;
                vector.z = mesh->mNormals[i].z;
                vertex.Normal = vector;
            }
            // texture coordinates
            if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
            {
                glm::vec2 vec;
                // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
                // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
                vec.x = mesh->mTextureCoords[0][i].x;
                vec.y = mesh->mTextureCoords[0][i].y;
                vertex.TexCoords = vec;
            }
            else
                vertex.TexCoords = glm::vec2(0.0f, 0.0f);

            if (mesh->HasTangentsAndBitangents())
            {
                // tangent
                vector.x = mesh->mTangents[i].x;
                vector.y = mesh->mTangents[i].y;
                vector.z = mesh->mTangents[i].z;
                vertex.Tangent = vector;
                // bitangent
                vector.x = mesh->mBitangents[i].x;
                vector.y = mesh->mBitangents[i].y;
                vector.z = mesh->mBitangents[i].z;
                vertex.Bitangent = vector;
            }
            vertices.push_back(vertex);
        }

        //indices.reserve(mesh->mNumVertices);
        // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            // retrieve all indices of the face and store them in the indices vector
            for (unsigned int j = 0; j < face.mNumIndices; j++)
            {
                indices.push_back(face.mIndices[j]);
            }
        }



        // process materials
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        //textures = GetTextures(material);
        // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
        // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
        // Same applies to other texture as the following list summarizes:
        // diffuse: texture_diffuseN
        // specular: texture_specularN
        // normal: texture_normalN

        // 1. diffuse maps
        std::vector<TextureMesh> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        // 2. specular maps
        std::vector<TextureMesh> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        // 3. normal maps
        std::vector<TextureMesh> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
        // 4. height maps
        std::vector<TextureMesh> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
        Mesh temp(vertices, indices, textures, transform);
        render->SetupMesh(temp.VAO, temp.VBO, temp.EBO, temp.vertices, temp.indices);
        // return a mesh object created from the extracted mesh data
        return temp;
    }

    //vector<Texture> GetTextures(aiMaterial* material)
    //{

    //}


    // checks all material textures of a given type and loads the textures if they're not loaded yet.
    // the required info is returned as a Texture struct.
    std::vector<TextureMesh> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
    {
        std::vector<TextureMesh> textures;
        int count = mat->GetTextureCount(type);
        std::cout << typeName << " " << count << std::endl;

        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
        {
            aiString str;
            mat->GetTexture(type, i, &str);
            // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
            bool skip = false;
            for (unsigned int j = 0; j < textures_loaded.size(); j++)
            {
                if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
                {
                    textures.push_back(textures_loaded[j]);
                    skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
                    break;
                }
            }
            if (!skip)
            {   // if texture hasn't been loaded already, load it

                TextureMesh texture;
                texture.id = render->TextureFromFile(str.C_Str(), this->directory);

                texture.type = typeName;
                texture.path = str.C_Str();
                textures.push_back(texture);
                textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
            }
        }
        return textures;
    }

};