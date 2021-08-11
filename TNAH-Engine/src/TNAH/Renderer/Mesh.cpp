#include <tnahpch.h>
#include "Mesh.h"



#include "Renderer.h"

namespace tnah {
    Mesh::Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices, std::vector<Ref<Texture2D>> textures)
    {
        this->m_Vertices = vertices;
        this->m_Indices = indices;
        
        m_BufferLayout = {
            {ShaderDataType::Float3, "a_Position"},
            {ShaderDataType::Float3, "a_Normal"},
            {ShaderDataType::Float3, "a_Tangent"},
            {ShaderDataType::Float3, "a_Bitangents"},
            {ShaderDataType::Float2, "a_TexCoord"}
        };
        m_Vao.reset(VertexArray::Create());
        
        m_Vbo.reset(VertexBuffer::Create(&vertices[0], sizeof(Vertex) * vertices.size()));
        m_Vbo->SetLayout(m_BufferLayout);
        m_Vao->AddVertexBuffer(m_Vbo);

        m_Ibo.reset(IndexBuffer::Create(&indices[0], indices.size()));
        m_Vao->SetIndexBuffer(m_Ibo);

        const std::string defaultVertexShader = "assets/shaders/default/mesh/mesh_vertex.glsl";
        const std::string defaultFragmentShader = "assets/shaders/default/mesh/mesh_fragment.glsl";
        
        bool skip = false;
        for(auto& shader : m_LoadedShaders)
        {
            if(std::strcmp(shader.VertexShaderPath.data(), defaultVertexShader.c_str()) == 0 && std::strcmp(shader.FragmentShaderPath.data(), defaultFragmentShader.c_str()) == 0)
            {
                //The shaders already been loaded, dont load it again
                m_Material.reset(Material::Create(shader.Shader));
                skip = true;
                break;
            }
        }
        if(!skip)
        {
            m_Material.reset(Material::Create(defaultVertexShader, defaultFragmentShader));
            MeshShader s(m_Material->GetShader(), defaultVertexShader, defaultFragmentShader);
            m_LoadedShaders.push_back(s);
        }

        m_Material->SetTextures(textures);
        
        //bind and set the textures inside the shader uniforms
        uint32_t diffuse = 1;
        uint32_t specular = 1;
        m_Material->BindShader();
        for(auto t : textures)
        {
            std::string number;
            std::string name = t->m_Name;
            if(name == "texture_diffuse")
            {
                number = std::to_string(diffuse++);
            }
            else if(name == "texture_specular")
            {
                number = std::to_string(specular++);
            }
            m_Material->GetShader()->SetInt(("u_Material." + name + number).c_str(), t->m_Slot);
        }
        m_Material->UnBindShader();
    }

    static const uint32_t s_MeshImportFlags =
            aiProcess_CalcTangentSpace |        // Create binormals/tangents just in case
            aiProcess_Triangulate |             // Make sure we're triangles
            aiProcess_SortByPType |             // Split meshes by primitive type
            aiProcess_GenNormals |              // Make sure we have legit normals
            aiProcess_GenUVCoords |             // Convert UVs if required 
            aiProcess_OptimizeMeshes |          // Batch draws where possible
            aiProcess_JoinIdenticalVertices |          
            aiProcess_ValidateDataStructure;    // Validation

    glm::mat4 Model::AiToGLM(aiMatrix4x4t<float> m)
    {
        return glm::mat4{ m.a1, m.b1, m.c1, m.d1,
                m.a2, m.b2, m.c2, m.d2,
                m.a3, m.b3, m.c3, m.d3,
                m.a4, m.b4, m.c4, m.d4 };
    }

    glm::vec3 Model::AiToGLM(aiVector3t<float> v)
    {
        return glm::vec3{ v.x, v.y, v.z };
    }

    glm::quat Model::AiToGLM(aiQuaterniont<float> q)
    {
        return glm::quat{ q.w, q.x, q.y, q.z };
    }


    Model* Model::Create(const std::string& filePath)
    {
        return new Model(filePath);
    }

    Model::Model(const std::string& filePath)
    {
        LoadModel(filePath);
    }

    void Model::LoadModel(const std::string& filePath)
    {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(filePath, s_MeshImportFlags);

        if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            TNAH_CORE_ERROR("Error Importing file: {0}    error: {1}", filePath, importer.GetErrorString());
            return;
        }
        m_Directory = filePath.substr(0, filePath.find_last_of('/'));
        ProcessNode(scene->mRootNode, scene);
    }

    std::vector<Ref<Texture2D>> Model::LoadMaterialTextures(const aiScene* scene, aiMaterial* material, aiTextureType type, const std::string& typeName)
    {
        std::vector<Ref<Texture2D>> textures;
        for(uint32_t i = 0; i < material->GetTextureCount(type); i++)
        {
            aiString str;
            material->Get(AI_MATKEY_TEXTURE(type, 0), str);
            bool skip = false;

            for(uint32_t j = 0; j < m_LoadedTextures.size(); j++)
            {
                if(std::strcmp(m_LoadedTextures[j].TexturePath.data(), str.C_Str()) == 0)
                {
                    textures.push_back(m_LoadedTextures[j].Texture);
                    skip = true;
                    break;
                }
            }
            if(!skip)
            {
                Ref<Texture2D> tex;
                
                if(auto t = scene->GetEmbeddedTexture(str.C_Str()))
                {
                    aiTexture* aiTex = const_cast<aiTexture*>(t);
                    //read file from memory
                    tex.reset(Texture2D::Create(str.C_Str(), typeName,true, aiTex));
                    textures.push_back(tex);
                    m_LoadedTextures.push_back(MeshTexture(tex, str.data));
                }
                else
                {
                    tex.reset(Texture2D::Create(str.data, typeName));
                    textures.push_back(tex);
                    m_LoadedTextures.push_back(MeshTexture(tex, str.data));
                }
            }
            
           
        }
        return textures;
    }

    Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
    {
        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;
        std::vector<Ref<Texture2D>> textures;

        for(uint32_t i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex v;
            glm::vec3 vec;
            if(mesh->HasPositions())
            {
                vec.x = mesh->mVertices[i].x;
                vec.y = mesh->mVertices[i].y;
                vec.z = mesh->mVertices[i].z;
                v.Position = vec;
            }

            if(mesh->HasNormals())
            {
                vec.x = mesh->mNormals[i].x;
                vec.y = mesh->mNormals[i].y;
                vec.z = mesh->mNormals[i].z;
                v.Normal = vec;
            }

            if(mesh->HasTangentsAndBitangents())
            {
                vec.x = mesh->mTangents[i].x;
                vec.y = mesh->mTangents[i].y;
                vec.z = mesh->mTangents[i].z;
                v.Tangent = vec;
                vec.x = mesh->mBitangents[i].x;
                vec.y = mesh->mBitangents[i].y;
                vec.z = mesh->mBitangents[i].z;
                v.Bitangents = vec;
            }
            
            if(mesh->mTextureCoords[0])
            {
                glm::vec2 tex;
                tex.x = mesh->mTextureCoords[0][i].x;
                tex.y = mesh->mTextureCoords[0][i].y;
                v.Texcoord = tex;
            }
            else
            {
                v.Texcoord = glm::vec2(0.0f);
            }
            vertices.push_back(v);
        }

        for(uint32_t i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            for(uint32_t j = 0; j < face.mNumIndices; j++)
            {
                indices.push_back(face.mIndices[j]);
            }
        }

        if(mesh->mMaterialIndex >= 0)
        {
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
            // 1. diffuse maps
            std::vector<Ref<Texture2D>> diffuseMaps = LoadMaterialTextures(scene, material, aiTextureType_DIFFUSE, "texture_diffuse");
            textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
            /// 2. specular maps
             std::vector<Ref<Texture2D>> specularMaps = LoadMaterialTextures(scene, material, aiTextureType_SPECULAR, "texture_specular");
            textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
            /// 3. normal maps
            std::vector<Ref<Texture2D>> normalMaps = LoadMaterialTextures(scene, material, aiTextureType_HEIGHT, "texture_normal");
            textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
            /// 4. height maps
            std::vector<Ref<Texture2D>> heightMaps = LoadMaterialTextures(scene, material, aiTextureType_AMBIENT, "texture_height");
            textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
        }


        return Mesh(vertices, indices, textures);
    }

    void Model::ProcessNode(aiNode* node, const aiScene* scene)
    {
        for(uint32_t i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            m_Meshes.push_back(ProcessMesh(mesh, scene));
        }

        for(uint32_t i = 0; i < node->mNumChildren; i++)
        {
            ProcessNode(node->mChildren[i], scene);
        }
    }
}
