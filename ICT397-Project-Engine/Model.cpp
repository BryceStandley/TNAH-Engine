#include "Model.h"

void Model::Draw(Shader& shader, glm::mat4 model)
{
    for (unsigned int i = 0; i < meshes.size(); i++)
    {
        glm::mat4 newModel = model * meshes[i].transform;
        shader.setMat4("model", newModel);
        meshes[i].Draw(shader);
    }
}

    
glm::mat4 Model::to_glm(aiMatrix4x4t<float> m) 
{
    return glm::mat4{ m.a1, m.b1, m.c1, m.d1,  
                m.a2, m.b2, m.c2, m.d2,  
                m.a3, m.b3, m.c3, m.d3,
                m.a4, m.b4, m.c4, m.d4 }; 
}

    
glm::vec3 Model::to_glm(aiVector3t<float> v) {
    return glm::vec3{ v.x, v.y, v.z };
}

    
glm::quat Model::to_glm(aiQuaterniont<float> q) {
    return glm::quat{ q.w, q.x, q.y, q.z };
}

   
void Model::loadModel(std::string const& path)
{
    /// read file via ASSIMP
    directory = path.substr(0, path.find_last_of('/'));
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    /// check for errors
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }
    /// retrieve the directory path of the filepath
    directory = path.substr(0, path.find_last_of('/'));
    std::cout << "Dir: " << directory << ", number of meshes: " << scene->mNumMeshes << std::endl;

    processNode(scene->mRootNode, scene, to_glm(scene->mRootNode->mTransformation));
}


void Model::processNode(aiNode* node, const aiScene* scene, glm::mat4 transform)
{
    // process each mesh located at the current node
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        /// the node object only contains indices to index the actual objects in the scene. 
        /// the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene, transform * to_glm(node->mTransformation)));
    }
    /// after we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene, transform * to_glm(node->mTransformation));
    }
}


Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene, glm::mat4 transform)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<TextureMesh> textures;

    /// walk through each of the mesh's vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;

        /// we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
        glm::vec3 vector;

        /// positions
        if (mesh->HasPositions())
        {
            vector.x = mesh->mVertices[i].x;
            vector.y = mesh->mVertices[i].y;
            vector.z = mesh->mVertices[i].z;
            vertex.Position = vector;
        }

        /// normals
        if (mesh->HasNormals()) {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;
        }
        /// texture coordinates
        if (mesh->mTextureCoords[0])
        {
            glm::vec2 vec;
            /// a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
            /// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);

        if (mesh->HasTangentsAndBitangents())
        {
            /// tangent
            vector.x = mesh->mTangents[i].x;
            vector.y = mesh->mTangents[i].y;
            vector.z = mesh->mTangents[i].z;
            vertex.Tangent = vector;
            /// bitangent
            vector.x = mesh->mBitangents[i].x;
            vector.y = mesh->mBitangents[i].y;
            vector.z = mesh->mBitangents[i].z;
            vertex.Bitangent = vector;
        }
        vertices.push_back(vertex);
    }


    /// now run through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        /// retrieve all indices of the face and store them in the indices vector
        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    /// process materials
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];


    /// 1. diffuse maps
    std::vector<TextureMesh> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    /// 2. specular maps
    std::vector<TextureMesh> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    /// 3. normal maps
    std::vector<TextureMesh> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    /// 4. height maps
    std::vector<TextureMesh> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
    Mesh temp(vertices, indices, textures, transform);
    render->SetupMesh(temp.VAO, temp.VBO, temp.EBO, temp.vertices, temp.indices);

    /// return a mesh object created from the extracted mesh data
    return temp;
}


    
std::vector<TextureMesh> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
    std::vector<TextureMesh> textures;
    int count = mat->GetTextureCount(type);
    std::cout << typeName << " " << count << std::endl;

    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        /// check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
        bool skip = false;
        for (unsigned int j = 0; j < textures_loaded.size(); j++)
        {
            if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
            {
                textures.push_back(textures_loaded[j]);
                skip = true; /// a texture with the same filepath has already been loaded, continue to next one. (optimization)
                break;
            }
        }
        if (!skip)
        {   /// if texture hasn't been loaded already, load it

            TextureMesh texture;
            texture.id = render->TextureFromFile(str.C_Str(), this->directory);

            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            textures_loaded.push_back(texture);  /// store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
        }
    }
    return textures;
}