#include <tnahpch.h>
#include "Submesh.h"

#pragma warning(push, 0)
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include <assimp/DefaultLogger.hpp>
#include <assimp/LogStream.hpp>
#pragma warning(pop)

#include "Renderer.h"

namespace tnah {

    // Helpers
    glm::mat4 Mat4FromAssimpMat4(const aiMatrix4x4& matrix)
    {
        glm::mat4 result;
        //the a,b,c,d in assimp is the row ; the 1,2,3,4 is the column
        result[0][0] = matrix.a1; result[1][0] = matrix.a2; result[2][0] = matrix.a3; result[3][0] = matrix.a4;
        result[0][1] = matrix.b1; result[1][1] = matrix.b2; result[2][1] = matrix.b3; result[3][1] = matrix.b4;
        result[0][2] = matrix.c1; result[1][2] = matrix.c2; result[2][2] = matrix.c3; result[3][2] = matrix.c4;
        result[0][3] = matrix.d1; result[1][3] = matrix.d2; result[2][3] = matrix.d3; result[3][3] = matrix.d4;
        return result;
    }

    struct LogStream : public Assimp::LogStream
    {
        static void Initialize()
        {
            if (Assimp::DefaultLogger::isNullLogger())
            {
                Assimp::DefaultLogger::create("", Assimp::Logger::VERBOSE);
                Assimp::DefaultLogger::get()->attachStream(new LogStream, Assimp::Logger::Err | Assimp::Logger::Warn);
            }
        } 

        void write(const char* message) override
        {
            TNAH_CORE_ERROR("Assimp error: {0}", message);
        }
    };















    
    Submesh::Submesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices, std::vector<Ref<Texture2D>> textures, bool animated)
    {
         m_Vertices = vertices;
        m_Indices = indices;
        m_IsAnimated = animated;

        m_VertexBufferLayout = {
            {ShaderDataType::Float3, "a_Position"},
            {ShaderDataType::Float3, "a_Normal"},
            {ShaderDataType::Float3, "a_Tangent"},
            {ShaderDataType::Float3, "a_Bitangent"},
            {ShaderDataType::Float2, "a_TexCoord"},
            {ShaderDataType::Int4, "a_BoneIds"},
            {ShaderDataType::Float4, "a_Weights"}
        };
        
        m_VertexArray = VertexArray::Create();
        
        m_VertexBuffer = VertexBuffer::Create(&vertices[0], (uint32_t)(sizeof(Vertex) * vertices.size()));

        m_VertexBuffer->SetLayout(m_VertexBufferLayout);
        m_VertexArray->AddVertexBuffer(m_VertexBuffer);

        m_IndexBuffer = IndexBuffer::Create(&indices[0], (uint32_t)indices.size());
        m_VertexArray->SetIndexBuffer(m_IndexBuffer);

        
        std::string defaultVertexShader = "Resources/shaders/default/mesh/mesh_vertex.glsl";
        std::string defaultFragmentShader = "Resources/shaders/default/mesh/mesh_fragment.glsl";
        
        bool skip = false;
        for(auto& shader : Renderer::GetLoadedShaders())
        {
            if(std::strcmp(shader->m_FilePaths.first.data(), defaultVertexShader.c_str()) == 0 && std::strcmp(shader->m_FilePaths.second.data(), defaultFragmentShader.c_str()) == 0)
            {
                //The shaders already been loaded, dont load it again
                m_Material = Material::Create(shader);
                skip = true;
                break;
            }
        }
        if(!skip)
        {
            m_Material = Material::Create(defaultVertexShader, defaultFragmentShader);
            auto s = m_Material->GetShader();
            Renderer::RegisterShader(s);
        }
        
        //bind and set the textures inside the shader uniforms
        uint32_t diffuse = 1;
        uint32_t specular = 1;
        m_Material->BindShader();
        if(textures.empty())
        {
            textures.push_back(Renderer::GetMissingTexture());
            textures.push_back(Renderer::GetBlackTexture());
            m_Material->GetShader()->SetInt("u_Material.texture_diffuse1", Renderer::GetMissingTexture()->GetRendererID());
            m_Material->GetShader()->SetInt("u_Material.texture_specular1", Renderer::GetBlackTexture()->GetRendererID());
            m_Material->SetTextures(textures);
        }
        else
        {
            m_Material->SetTextures(textures);
            bool dif = false;
            bool spec = false;
            for(auto t : textures)
            {
                std::string number;
                std::string name = t->m_TextureResource.CustomName;
                if(name == "texture_diffuse")
                {
                    number = std::to_string(diffuse++);
                    dif = true;
                    //m_Material->GetShader()->SetBool("u_Material.diffuse_bound", true);
                }
                else if(name == "texture_specular")
                {
                    number = std::to_string(specular++);
                    spec = true;
                    //m_Material->GetShader()->SetBool("u_Material.specular_bound", true);
                }
                else
                {
                    m_Material->GetShader()->SetInt("u_Material.texture_diffuse1", Renderer::GetMissingTexture()->GetRendererID());
                    m_Material->GetShader()->SetInt("u_Material.texture_specular1", Renderer::GetBlackTexture()->GetRendererID());
                }

                if(dif && !spec)
                {
                    m_Material->GetShader()->SetInt("u_Material.texture_specular1", Renderer::GetBlackTexture()->GetRendererID());
                }
                
                m_Material->GetShader()->SetInt(("u_Material." + name + number ).c_str(), t->GetRendererID());
            }
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
            aiProcess_ValidateDataStructure;  // Validation

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


    Ref<Model> Model::Create(const std::string& filePath)
    {
        auto model = Ref<Model>::Create();
        bool duplicate = false;
        for(auto& m : Renderer::GetLoadedModels())
        {
            if(std::strcmp(m->m_Resource.RelativeDirectory.data(), filePath.c_str()) == 0)
            {
                // this model has already been loaded, no need to process it again
                model = m;
                duplicate = true;
            }
        }

        if(duplicate) return model;

        //if theres no duplicate model, read in the file as normal and return the new model
        model = Ref<Model>::Create(filePath);
        Renderer::RegisterModel(model);
        return model;
    }

    Model::Model()
    {}

    Model::Model(const std::string& filePath)
    {
        m_Resource = Resource(filePath);
        LoadModel(filePath);
    }

    void Model::TraverseNodes(aiNode* node, const glm::mat4& parentTransform, uint32_t level)
    {
        glm::mat4 transform = parentTransform * Mat4FromAssimpMat4(node->mTransformation);
        m_NodeMap[node].resize(node->mNumMeshes);
        for (uint32_t i = 0; i < node->mNumMeshes; i++)
        {
            uint32_t mesh = node->mMeshes[i];
            auto& submesh = m_Submeshes[mesh];
            submesh.m_NodeName = node->mName.C_Str();
            submesh.m_Transform = transform;
            m_NodeMap[node][i] = mesh;
        }

        // HZ_MESH_LOG("{0} {1}", LevelToSpaces(level), node->mName.C_Str());

        for (uint32_t i = 0; i < node->mNumChildren; i++)
            TraverseNodes(node->mChildren[i], transform, level + 1);
    
    }

    bool Model::ProcessModelSubmeshes(const aiScene* scene)
    {
        uint32_t vertexCount = 0;
        uint32_t indexCount = 0;
        for(uint32_t m = 0; m < scene->mNumMeshes; m++)
        {
            aiMesh* mesh = scene->mMeshes[m];

            Submesh& submesh = m_Submeshes.emplace_back();
            submesh.m_BaseVertex = vertexCount;
            submesh.m_BaseIndex = indexCount;
            submesh.m_MaterialIndex = mesh->mMaterialIndex;
            submesh.m_VertexCount = mesh->mNumVertices;
            submesh.m_IndexCount = mesh->mNumFaces * 3;
            submesh.m_MeshName = mesh->mName.C_Str();

            vertexCount += mesh->mNumVertices;
            indexCount += submesh.m_IndexCount;
            
            TNAH_CORE_ASSERT(mesh->HasPositions(), "A mesh needs positions!");
            TNAH_CORE_ASSERT(mesh->HasNormals(), "A mesh needs normals!");

            if(m_IsAnimated) // Set up animation
            {
                for(size_t i = 0; i < mesh->mNumVertices; i++)
                {
                    AnimatedVertex vertex;
                    vertex.Position = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };
                    vertex.Normal = { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z };
                    if(mesh->HasTangentsAndBitangents())
                    {
                        vertex.Tangent = { mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z };
                        vertex.Bitangents = { mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z };
                    }

                    if (mesh->HasTextureCoords(0))
                    {
                        vertex.Texcoord = { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y };
                    }
                    submesh.m_AnimatedVertices.push_back(vertex);
                }
            }
            else
            {
                auto& aabb = submesh.m_BoundingBox;
                aabb.Min = {FLT_MAX, FLT_MAX, FLT_MAX};
                aabb.Max = { -FLT_MAX, -FLT_MAX, -FLT_MAX };
                for(size_t i = 0; i < mesh->mNumVertices; i++)
                {
                    Vertex vertex;
                    vertex.Position = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };
                    vertex.Normal = { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z };
                    aabb.Min.x = glm::min(vertex.Position.x, aabb.Min.x);
                    aabb.Min.y = glm::min(vertex.Position.y, aabb.Min.y);
                    aabb.Min.z = glm::min(vertex.Position.z, aabb.Min.z);
                    aabb.Max.x = glm::max(vertex.Position.x, aabb.Max.x);
                    aabb.Max.y = glm::max(vertex.Position.y, aabb.Max.y);
                    aabb.Max.z = glm::max(vertex.Position.z, aabb.Max.z);

                    if (mesh->HasTangentsAndBitangents())
                    {
                        vertex.Tangent = { mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z };
                        vertex.Bitangents = { mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z };
                    }

                    if (mesh->HasTextureCoords(0))
                    {
                        vertex.Texcoord = { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y };
                    }

                    submesh.m_Vertices.push_back(vertex);
                }
            }

            for(size_t i = 0; i < mesh->mNumFaces; i++)
            {
                TNAH_CORE_ASSERT(mesh->mFaces[i].mNumIndices == 3, "Mesh needs 3 indices")
                Index index = { mesh->mFaces[i].mIndices[0], mesh->mFaces[i].mIndices[1], mesh->mFaces[i].mIndices[2] };
                submesh.m_Indices.push_back(index);
            }
        }

        TraverseNodes(scene->mRootNode);

        //Bounding Box setup
        for(const auto& submesh : m_Submeshes)
        {
            AABB transformedAABB = submesh.m_BoundingBox;
            glm::vec3 min = glm::vec3(submesh.m_Transform * glm::vec4(transformedAABB.Min, 1.0f));
            glm::vec3 max = glm::vec3(submesh.m_Transform * glm::vec4(transformedAABB.Max, 1.0f));

            m_BoundingBox.Min.x = glm::min(m_BoundingBox.Min.x, min.x);
            m_BoundingBox.Min.y = glm::min(m_BoundingBox.Min.y, min.y);
            m_BoundingBox.Min.z = glm::min(m_BoundingBox.Min.z, min.z);
            m_BoundingBox.Max.x = glm::max(m_BoundingBox.Max.x, max.x);
            m_BoundingBox.Max.y = glm::max(m_BoundingBox.Max.y, max.y);
            m_BoundingBox.Max.z = glm::max(m_BoundingBox.Max.z, max.z);
        }

        // Bones
        if (m_IsAnimated)
        {
            for (size_t m = 0; m < scene->mNumMeshes; m++)
            {
                aiMesh* mesh = scene->mMeshes[m];
                Submesh& submesh = m_Submeshes[m];

                for (size_t i = 0; i < mesh->mNumBones; i++)
                {
                    aiBone* bone = mesh->mBones[i];
                    std::string boneName(bone->mName.data);
                    int boneIndex = 0;

                    if (m_BoneMapping.find(boneName) == m_BoneMapping.end())
                    {
                        // Allocate an index for a new bone
                        boneIndex = m_BoneCount;
                        m_BoneCount++;
                        BoneInfo bi;
                        m_BoneInfo.push_back(bi);
                        m_BoneInfo[boneIndex].BoneOffset = Mat4FromAssimpMat4(bone->mOffsetMatrix);
                        m_BoneMapping[boneName] = boneIndex;
                    }
                    else
                    {
                        TNAH_CORE_WARN("Found existing bone in map");
                        boneIndex = m_BoneMapping[boneName];
                    }

                    for (size_t j = 0; j < bone->mNumWeights; j++)
                    {
                        int VertexID = submesh.m_BaseVertex + bone->mWeights[j].mVertexId;
                        float Weight = bone->mWeights[j].mWeight;
                        submesh.m_AnimatedVertices[VertexID].AddBoneData(boneIndex, Weight);
                    }
                }
            }
        }

        if(scene->HasMaterials())
        {
            m_Materials.resize(scene->mNumMaterials);

            for(uint32_t i = 0; i < scene->mNumMaterials; i++)
            {
                auto aiMaterial = scene->mMaterials[i];
                auto aiMaterialName = aiMaterial->GetName();

                if(Renderer::HasLoadedShader("Resources/shaders/default/mesh/mesh_vertex.glsl", "Resources/shaders/default/mesh/mesh_fragment.glsl") < 0)
                {
                    auto mat = Material::Create("Resources/shaders/default/mesh/mesh_vertex.glsl", "Resources/shaders/default/mesh/mesh_fragment.glsl");
                    
                    m_Materials[i] = mat;
                    aiString aiTexPath;
                    uint32_t textureCount = aiMaterial->GetTextureCount(aiTextureType_DIFFUSE);
                    
                    glm::vec3 albedoColor(0.8f);
                    float emission = 0.0f;
                    aiColor3D aiColor, aiEmission;
                    if (aiMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, aiColor) == AI_SUCCESS)
                        albedoColor = { aiColor.r, aiColor.g, aiColor.b };

                    if (aiMaterial->Get(AI_MATKEY_COLOR_EMISSIVE, aiEmission) == AI_SUCCESS)
                        emission = aiEmission.r;

                    mat->Set("u_MaterialUniforms.AlbedoColor", albedoColor);
                    mat->Set("u_MaterialUniforms.Emission", emission);

                    float shininess, metalness;
                    if (aiMaterial->Get(AI_MATKEY_SHININESS, shininess) != aiReturn_SUCCESS)
                        shininess = 80.0f; // Default value

                    if (aiMaterial->Get(AI_MATKEY_REFLECTIVITY, metalness) != aiReturn_SUCCESS)
                        metalness = 0.0f;

                    float roughness = 1.0f - glm::sqrt(shininess / 100.0f);
                    bool hasAlbedoMap = aiMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &aiTexPath) == AI_SUCCESS;
                    bool fallback = !hasAlbedoMap;
                    if (hasAlbedoMap)
				{
					// TODO: Temp - this should be handled by Hazel's filesystem
					std::filesystem::path path = filename;
					auto parentPath = path.parent_path();
					parentPath /= std::string(aiTexPath.data);
					std::string texturePath = parentPath.string();
					HZ_MESH_LOG("    Albedo map path = {0}", texturePath);
					TextureProperties props;
					props.SRGB = true;
					auto texture = Texture2D::Create(texturePath, props);
					if (texture->Loaded())
					{
						m_Textures[i] = texture;
						mi->Set("u_AlbedoTexture", texture);
						mi->Set("u_MaterialUniforms.AlbedoColor", glm::vec3(1.0f));
					}
					else
					{
						HZ_CORE_ERROR("Could not load texture: {0}", texturePath);
						fallback = true;
					}
				}

				if (fallback)
				{
					HZ_MESH_LOG("    No albedo map");
					mi->Set("u_AlbedoTexture", whiteTexture);
				}

				// Normal maps
				bool hasNormalMap = aiMaterial->GetTexture(aiTextureType_NORMALS, 0, &aiTexPath) == AI_SUCCESS;
				fallback = !hasNormalMap;
				if (hasNormalMap)
				{
					// TODO: Temp - this should be handled by Hazel's filesystem
					std::filesystem::path path = filename;
					auto parentPath = path.parent_path();
					parentPath /= std::string(aiTexPath.data);
					std::string texturePath = parentPath.string();
					HZ_MESH_LOG("    Normal map path = {0}", texturePath);
					auto texture = Texture2D::Create(texturePath);
					if (texture->Loaded())
					{
						m_Textures.push_back(texture);
						mi->Set("u_NormalTexture", texture);
						mi->Set("u_MaterialUniforms.UseNormalMap", true);
					}
					else
					{
						HZ_CORE_ERROR("    Could not load texture: {0}", texturePath);
						fallback = true;
					}
				}

				if (fallback)
				{
					HZ_MESH_LOG("    No normal map");
					mi->Set("u_NormalTexture", whiteTexture);
					mi->Set("u_MaterialUniforms.UseNormalMap", false);
				}

				// Roughness map
				bool hasRoughnessMap = aiMaterial->GetTexture(aiTextureType_SHININESS, 0, &aiTexPath) == AI_SUCCESS;
				fallback = !hasRoughnessMap;
				if (hasRoughnessMap)
				{
					// TODO: Temp - this should be handled by Hazel's filesystem
					std::filesystem::path path = filename;
					auto parentPath = path.parent_path();
					parentPath /= std::string(aiTexPath.data);
					std::string texturePath = parentPath.string();
					HZ_MESH_LOG("    Roughness map path = {0}", texturePath);
					auto texture = Texture2D::Create(texturePath);
					if (texture->Loaded())
					{
						m_Textures.push_back(texture);
						mi->Set("u_RoughnessTexture", texture);
						mi->Set("u_MaterialUniforms.Roughness", 1.0f);
					}
					else
					{
						HZ_CORE_ERROR("    Could not load texture: {0}", texturePath);
						fallback = true;
					}
				}

				if (fallback)
				{
					HZ_MESH_LOG("    No roughness map");
					mi->Set("u_RoughnessTexture", whiteTexture);
					mi->Set("u_MaterialUniforms.Roughness", roughness);
				}

                    bool metalnessTextureFound = false;
                    for (uint32_t p = 0; p < aiMaterial->mNumProperties; p++)
                    {
                        auto prop = aiMaterial->mProperties[p];
                        if (prop->mType == aiPTI_String)
                        {
                            uint32_t strLength = *(uint32_t*)prop->mData;
                            std::string str(prop->mData + 4, strLength);

                            std::string key = prop->mKey.data;
                            if (key == "$raw.ReflectionFactor|file")
                            {
                                // TODO: Temp - this should be handled by Hazel's filesystem
                                std::filesystem::path path = filename;
                                auto parentPath = path.parent_path();
                                parentPath /= str;
                                std::string texturePath = parentPath.string();
                                HZ_MESH_LOG("    Metalness map path = {0}", texturePath);
                                auto texture = Texture2D::Create(texturePath);
                                if (texture->Loaded())
                                {
                                    metalnessTextureFound = true;
                                    m_Textures.push_back(texture);
                                    mi->Set("u_MetalnessTexture", texture);
                                    mi->Set("u_MaterialUniforms.Metalness", 1.0f);
                                }
                                else
                                {
                                    HZ_CORE_ERROR("    Could not load texture: {0}", texturePath);
                                }
                                break;
                            }
                        }
                    }
                    fallback = !metalnessTextureFound;
                    if (fallback)
                    {
                        HZ_MESH_LOG("    No metalness map");
                        mi->Set("u_MetalnessTexture", whiteTexture);
                        mi->Set("u_MaterialUniforms.Metalness", metalness);

                    }
                }
                HZ_MESH_LOG("------------------------");
            }
            else
            {
                auto mi = Material::Create(m_MeshShader, "Hazel-Default");
                mi->Set("u_MaterialUniforms.AlbedoColor", glm::vec3(0.8f));
                mi->Set("u_MaterialUniforms.Emission", 0.0f);
                mi->Set("u_MaterialUniforms.Metalness", 0.0f);
                mi->Set("u_MaterialUniforms.Roughness", 0.8f);
                mi->Set("u_MaterialUniforms.UseNormalMap", false);

                mi->Set("u_AlbedoTexture", whiteTexture);
                mi->Set("u_MetalnessTexture", whiteTexture);
                mi->Set("u_RoughnessTexture", whiteTexture);
                m_Materials.push_back(mi);
            }

		
                if (m_IsAnimated)
                {
                    for(auto& submesh : m_Submeshes)
                    {
                        submesh.m_VertexBuffer = VertexBuffer::Create(submesh.m_AnimatedVertices.data(), (uint32_t)(submesh.m_AnimatedVertices.size() * sizeof(AnimatedVertex)));
                        submesh.m_VertexBufferLayout = {
                            { ShaderDataType::Float3, "a_Position" },
                            { ShaderDataType::Float3, "a_Normal" },
                            { ShaderDataType::Float3, "a_Tangent" },
                            { ShaderDataType::Float3, "a_Bitangent" },
                            { ShaderDataType::Float2, "a_TexCoord" },
                            { ShaderDataType::Int4, "a_BoneIDs" },
                            { ShaderDataType::Float4, "a_BoneWeights" },
                            };
                        m_IndexBuffer = IndexBuffer::Create(submesh.m_Indices.data(), (uint32_t)(m_Indices.size() * sizeof(Index)));
                    }
                }
                else
                {
                    for(auto& submesh : m_Submeshes)
                    {
                        submesh.m_VertexBuffer = VertexBuffer::Create(submesh.m_Vertices.data(), (uint32_t)(submesh.m_Vertices.size() * sizeof(Vertex)));
                        submesh.m_VertexBufferLayout = {
                            { ShaderDataType::Float3, "a_Position" },
                            { ShaderDataType::Float3, "a_Normal" },
                            { ShaderDataType::Float3, "a_Tangent" },
                            { ShaderDataType::Float3, "a_Binormal" },
                            { ShaderDataType::Float2, "a_TexCoord" },
                            };
                        m_IndexBuffer = IndexBuffer::Create(submesh.m_Indices.data(), (uint32_t)(m_Indices.size() * sizeof(Index)));
                    }
                }
            }
        }
        
    }

    

    void Model::SetVertexBoneDataToDefault(Vertex& vertex) 
    {
        for (int i = 0; i < MAX_BONE_INFLUENCE; i++) 
        {
            vertex.IDs[i] = 0;
            vertex.Weights[i] = 0.0f;
        }
    }


    void Model::SetVertexBoneData(Vertex& vertex, int boneID, float weight) 
    {
        for (int i = 0; i < MAX_BONE_INFLUENCE; ++i) 
        {
            vertex.Weights[i] = weight;
            vertex.IDs[i] = boneID;
            
        }
    }

    void Model::ExtractBoneWeightForVertices(std::vector<Vertex>& vertices, aiMesh* mesh, const aiScene* scene) 
    {
        for (uint32_t boneIndex = 0; boneIndex < mesh->mNumBones; ++boneIndex) 
        {
            int boneID = -1;
            std::string boneName = mesh->mBones[boneIndex]->mName.C_Str();

            if (m_BoneInfoMap.find(boneName) == m_BoneInfoMap.end()) 
            {
                
            }
            else 
            {
                boneID = m_BoneInfoMap[boneName].id;
            }
            assert(boneID != -1);
            auto weights = mesh->mBones[boneIndex]->mWeights;
            int numWeights = mesh->mBones[boneIndex]->mNumWeights;

            for (int weightIndex = 0; weightIndex < numWeights; ++weightIndex) 
            {
                int vertexId = weights[weightIndex].mVertexId;
                float weight = weights[weightIndex].mWeight;
                assert(vertexId <= vertices.size());
                SetVertexBoneData(vertices[vertexId], boneID, weight);

            }
        }

    }

    void Model::LoadModel(const std::string& filePath)
    {
        LogStream::Initialize();

        m_Importer = CreateScope<Assimp::Importer>();
        
        const aiScene* scene = m_Importer->ReadFile(filePath, s_MeshImportFlags);
        if(!scene || !scene->HasMeshes())
        {
            TNAH_CORE_ERROR("Error model file: {0}", m_Resource.AbsoluteDirectory);
            return;
        }
        m_Scene = scene;
        m_IsAnimated = scene->mAnimations != nullptr;
        m_InverseTransform = glm::inverse(Mat4FromAssimpMat4(scene->mRootNode->mTransformation));

        m_BoundingBox.Min = {FLT_MAX, FLT_MAX, FLT_MAX};
        m_BoundingBox.Max = { -FLT_MAX, -FLT_MAX, -FLT_MAX };

        m_Submeshes.reserve(scene->mNumMeshes);
        ProcessModelSubmeshes(scene);
    }

    std::vector<Ref<Texture2D>> Model::LoadMaterialTextures(const aiScene* scene, aiMaterial* material, aiTextureType type, const std::string& typeName)
    {
        std::vector<Ref<Texture2D>> textures;
        for(uint32_t i = 0; i < material->GetTextureCount(type); i++)
        {
            aiString str;
            material->Get(AI_MATKEY_TEXTURE(type, 0), str);
            bool skip = false;

            for(uint32_t j = 0; j < Renderer::GetLoadedTextures().size(); j++)
            {
                if(std::strcmp(Renderer::GetLoadedTextures()[j]->m_TextureResource.RelativeDirectory.data(), str.C_Str()) == 0)
                {
                    textures.push_back(Renderer::GetLoadedTextures()[j]);
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
                    tex = (Texture2D::Create(str.C_Str(), typeName,true, aiTex));
                    textures.push_back(tex);
                    //m_LoadedTextures.push_back(MeshTexture(tex, str.data));
                    Renderer::RegisterTexture(tex);
                }
                else
                {
                    tex = (Texture2D::Create(str.data, typeName));
                    textures.push_back(tex);
                    //m_LoadedTextures.push_back(MeshTexture(tex, str.data));
                    Renderer::RegisterTexture(tex);
                }
            }
            
           
        }
        return textures;
    }

    Submesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene, bool animated)
    {
        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;
        std::vector<Ref<Texture2D>> textures;

        for(uint32_t i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex v;

            if(animated)
            {
                SetVertexBoneDataToDefault(v);
            }
            else
            {
                // if the mesh isnt animated, set the id's and weights to 0
                for(uint32_t j = 0; j < 4; j++)
                {
                    v.IDs[j] = 0;
                    v.Weights[j] = 0;
                }
            }

            v.Position = AssimpGLMHelpers::GetGLMVec(mesh->mVertices[i]);
            v.Normal = AssimpGLMHelpers::GetGLMVec(mesh->mNormals[i]);


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
        

        if(animated) ExtractBoneWeightForVertices(vertices, mesh, scene);

        return Submesh(vertices, indices, textures, animated);
    }

    void Model::ProcessNode(aiNode* node, const aiScene* scene)
    {
        if(scene->mNumAnimations > 0)
        {
            m_IsAnimated = true;
            m_Animation = Animation(scene);
        }
        
        for(uint32_t i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            if(m_IsAnimated)
                m_Meshes.push_back(ProcessMesh(mesh, scene, true));
            else
                m_Meshes.push_back(ProcessMesh(mesh, scene, false));
        }

        for(uint32_t i = 0; i < node->mNumChildren; i++)
        {
            ProcessNode(node->mChildren[i], scene);
        }

        if(m_IsAnimated) m_Animation.ReadMissingBones(m_BoneInfoMap, m_BoneCount);
    }
}
