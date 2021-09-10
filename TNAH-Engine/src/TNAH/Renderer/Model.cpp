#include <tnahpch.h>
#include "Model.h"



#include "Renderer.h"

namespace tnah {

    /**
     * @brief Assimp logger for debugging
     */
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

#pragma region ImportFlags
    static const uint32_t s_MeshImportFlags =
            aiProcess_CalcTangentSpace |        // Create binormals/tangents just in case
            aiProcess_Triangulate |             // Make sure we're triangles
            aiProcess_SortByPType |             // Split meshes by primitive type
            aiProcess_GenNormals |              // Make sure we have legit normals
            aiProcess_GenUVCoords |             // Convert UVs if required 
            aiProcess_OptimizeMeshes |          // Batch draws where possible
            aiProcess_JoinIdenticalVertices |          
            aiProcess_ValidateDataStructure;  // Validation
#pragma endregion 

    Ref<Model> Model::Create(const std::string& filePath)
    {
        for(auto& m : Renderer::GetLoadedModels())
        {
            if(std::strcmp(m->m_Resource.RelativeDirectory.data(), filePath.c_str()) == 0)
            {
                // this model has already been loaded, no need to process it again
                return m;
            }
        }

        //if theres no duplicate model, read in the file as normal and return the new model
        Ref<Model> model = Ref<Model>::Create(filePath);
        Renderer::RegisterModel(model);
        return model;
    }

    Model::Model(const std::string& filePath)
    {
        m_Resource = Resource(filePath);
        LoadModel(filePath);
    }

    void Model::LoadModel(const std::string& filePath)
    {
        LogStream::Initialize();
        m_Resource = Resource(filePath);

        m_Importer = std::make_unique<Assimp::Importer>();
        
        m_Scene = m_Importer->ReadFile(filePath, s_MeshImportFlags);
        if(!m_Scene || !m_Scene->HasMeshes())
        {
            TNAH_CORE_ERROR("Error model file: {0}", m_Resource.AbsoluteDirectory);
            return;
        }
        m_IsAnimated = m_Scene->mAnimations != nullptr;

        if(m_IsAnimated)
        {
            //m_Shader = Shader::Create("Resources/shaders/default/mesh/mesh_vertex_anim_pbr.glsl", "Resources/shaders/default/mesh/mesh_fragment_anim_pbr.glsl");
            m_Shader = Shader::Create("Resources/shaders/default/mesh/mesh_anim_vertex.glsl", "Resources/shaders/default/mesh/mesh_anim_fragment.glsl");
        }
        else
        {
            m_Shader = Shader::Create("Resources/shaders/default/mesh/mesh_vertex_static_pbr.glsl", "Resources/shaders/default/mesh/mesh_fragment_static_pbr.glsl");
        }
        
        m_InverseTransform = glm::inverse(Mat4FromAssimpMat4(m_Scene->mRootNode->mTransformation));

        m_BoundingBox.Min = {FLT_MAX, FLT_MAX, FLT_MAX};
        m_BoundingBox.Max = { -FLT_MAX, -FLT_MAX, -FLT_MAX };

        m_Submeshes.resize(m_Scene->mNumMeshes);
        m_Materials.resize(m_Scene->mNumMaterials);
        
        ProcessModelSubmeshes(m_Scene,filePath);
        //CombineSubmeshData();
    }



    void Model::ProcessModelSubmeshes(const aiScene* scene, const std::string& filePath)
    {
        uint32_t vertexCount = 0;
        uint32_t indexCount = 0;

        for(uint32_t i = 0; i < m_Submeshes.size(); i++)
        {
            m_Submeshes[i].MaterialIndex = scene->mMeshes[i]->mMaterialIndex;
            m_Submeshes[i].IndexCount = scene->mMeshes[i]->mNumFaces * 3;
            m_Submeshes[i].BaseVertex = vertexCount;
            m_Submeshes[i].BaseIndex = indexCount;

            vertexCount += scene->mMeshes[i]->mNumVertices;
            indexCount += m_Submeshes[i].IndexCount;
        }

        if(m_IsAnimated)
        {
            m_AnimatedVertices.reserve(vertexCount);
        }
        else
        {
            m_Vertices.reserve(vertexCount);
        }
        m_Indices.reserve(indexCount);

        for(uint32_t i = 0; i < m_Submeshes.size(); i++)
        {
            const aiMesh* aMesh = scene->mMeshes[i];
            CreateSubmesh(i, aMesh);
        }

        CreateMaterials(scene, filePath);

        CreateRenderInformation();
        
#if 0 
        for(uint32_t m = 0; m < scene->mNumMeshes; m++)
        {
            aiMesh* mesh = scene->mMeshes[m];

            Submesh& submesh = m_Submeshes.emplace_back();
            submesh.BaseVertex = vertexCount;
            submesh.BaseIndex = indexCount;
            submesh.MaterialIndex = mesh->mMaterialIndex;
            submesh.VertexCount = mesh->mNumVertices;
            submesh.IndexCount = mesh->mNumFaces * 3;
            submesh.m_MeshName = mesh->mName.C_Str();

            vertexCount += mesh->mNumVertices;
            indexCount += submesh.IndexCount;
            
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
                        vertex.Texcoord = { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y};
                    }
                    //submesh.m_AnimatedVertices.push_back(vertex);
                    m_AnimatedVertices.push_back(vertex);
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

                    //submesh.m_Vertices.push_back(vertex);
                    m_Vertices.push_back(vertex);
                }
            }

            for(size_t i = 0; i < mesh->mNumFaces; i++)
            {
                TNAH_CORE_ASSERT(mesh->mFaces[i].mNumIndices == 3, "Mesh needs 3 indices")
                aiFace face = mesh->mFaces[i];

                Index index = { mesh->mFaces[i].mIndices[0], mesh->mFaces[i].mIndices[1], mesh->mFaces[i].mIndices[2] };
                m_Indices.push_back(index);
                
                /*for(uint32_t j = 0; j < face.mNumIndices; j++)
                {
                    submesh.m_Indices.push_back(face.mIndices[j]);
                    m_Indices.push_back(face.mIndices[j]);
                }*/
            }
        }

        TraverseNodes(scene->mRootNode);

        //Bounding Box setup
        for(const auto& submesh : m_Submeshes)
        {
            AABB transformedAABB = submesh.m_BoundingBox;
            glm::vec3 min = glm::vec3(submesh.Transform * glm::vec4(transformedAABB.Min, 1.0f));
            glm::vec3 max = glm::vec3(submesh.Transform * glm::vec4(transformedAABB.Max, 1.0f));

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
                        //TNAH_CORE_WARN("Found existing bone in map");
                        boneIndex = m_BoneMapping[boneName];
                    }

                    for (size_t j = 0; j < bone->mNumWeights; j++)
                    {
                        int VertexID = submesh.BaseVertex + bone->mWeights[j].mVertexId;
                        float Weight = bone->mWeights[j].mWeight;
                        m_AnimatedVertices[VertexID].AddBoneData(boneIndex, Weight);
                        if(VertexID == 0)
                        {
                            int test = 0;
                        }
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

                auto mat = Material::Create(m_Shader);
                auto properties = MaterialProperties();
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
                properties.AlbedoColor = albedoColor;
                properties.Emission = emission;
                float shininess, metalness;
                if (aiMaterial->Get(AI_MATKEY_SHININESS, shininess) != aiReturn_SUCCESS)
                    shininess = 80.0f; // Default value

                if (aiMaterial->Get(AI_MATKEY_REFLECTIVITY, metalness) != aiReturn_SUCCESS)
                    metalness = 0.0f;

                float roughness = 1.0f - glm::sqrt(shininess / 100.0f);
                properties.Shininess = shininess;
                properties.Metalness = metalness;
                properties.Roughness = roughness;
                bool hasAlbedoMap = aiMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &aiTexPath) == AI_SUCCESS;
                bool fallback = !hasAlbedoMap;
                if (hasAlbedoMap)
                {
                    if(auto t = scene->GetEmbeddedTexture(aiTexPath.C_Str()))
                    {
                        aiTexture* aiTex = const_cast<aiTexture*>(t);
                        auto texture = Texture2D::Create(aiTexPath.C_Str(), "Albedo", true, aiTex);
                        mat->AddTexture(texture);
                        mat->Set("u_AlbedoTexture", texture);
                        mat->Set("u_MaterialUniforms.AlbedoColor", glm::vec3(1.0f));
                        Renderer::RegisterTexture(texture);
                    }
                    else
                    {
                        TNAH_CORE_INFO("    Albedo map path = {0}", aiTexPath.C_Str());
                        auto texture = Texture2D::Create(aiTexPath.C_Str(), "Albedo");
                        if (texture->IsLoaded())
                        {
                            mat->AddTexture(texture);
                            Renderer::RegisterTexture(texture);
                            mat->Set("u_AlbedoTexture", texture->GetRendererID());
                            mat->Set("u_MaterialUniforms.AlbedoColor", glm::vec3(1.0f));
                        }
                        else
                        {
                            TNAH_CORE_ERROR("Could not load texture: {0}", aiTexPath.C_Str());
                            fallback = true;
                        }
                    }
                }

                if (fallback)
                {
                    TNAH_CORE_ERROR("    No albedo map");
                    mat->Set("u_AlbedoTexture", Renderer::GetWhiteTexture()->GetRendererID());
                }
#if 0
                // Normal maps
                bool hasNormalMap = aiMaterial->GetTexture(aiTextureType_NORMALS, 0, &aiTexPath) == AI_SUCCESS;
                fallback = !hasNormalMap;
                if (hasNormalMap)
                {
                    if(auto t = scene->GetEmbeddedTexture(aiTexPath.C_Str()))
                    {
                        aiTexture* aiTex = const_cast<aiTexture*>(t);
                        auto texture = Texture2D::Create(aiTexPath.C_Str(), "Normal", true, aiTex);
                        mat->AddTexture(texture);
                        mat->Set("u_NormalTexture", texture);
                        mat->Set("u_MaterialUniforms.UseNormalMap", true);
                        Renderer::RegisterTexture(texture);
                    }
                    else
                    {
                        TNAH_CORE_INFO("    Normal map path = {0}", aiTexPath.C_Str());
                        auto texture = Texture2D::Create(aiTexPath.C_Str());
                        if (texture->IsLoaded())
                        {
                            mat->AddTexture(texture);
                            Renderer::RegisterTexture(texture);
                            mat->Set("u_NormalTexture", texture);
                            mat->Set("u_MaterialUniforms.UseNormalMap", true);
                        }
                        else
                        {
                            TNAH_CORE_ERROR("    Could not load texture: {0}", aiTexPath.C_Str());
                            fallback = true;
                        }
                    }
                }

                if (fallback)
                {
                    TNAH_CORE_ERROR("    No normal map");
                    mat->Set("u_NormalTexture", Renderer::GetWhiteTexture()->m_RendererID);
                    mat->Set("u_MaterialUniforms.UseNormalMap", false);
                }

                // Roughness map
                bool hasRoughnessMap = aiMaterial->GetTexture(aiTextureType_SHININESS, 0, &aiTexPath) == AI_SUCCESS;
                fallback = !hasRoughnessMap;
                if (hasRoughnessMap)
                {
                    if(auto t = scene->GetEmbeddedTexture(aiTexPath.C_Str()))
                    {
                        aiTexture* aiTex = const_cast<aiTexture*>(t);
                        auto texture = Texture2D::Create(aiTexPath.C_Str(), "Roughness", true, aiTex);
                        mat->AddTexture(texture);
                        mat->Set("u_RoughnessTexture", texture);
                        mat->Set("u_MaterialUniforms.Roughness", 1.0f);
                        Renderer::RegisterTexture(texture);
                    }
                    else
                    {
                        TNAH_CORE_INFO("    Roughness map path = {0}", aiTexPath.C_Str());
                        auto texture = Texture2D::Create(aiTexPath.C_Str(), "Roughness");
                        if (texture->IsLoaded())
                        {
                            mat->AddTexture(texture);
                            Renderer::RegisterTexture(texture);
                            mat->Set("u_RoughnessTexture", texture);
                            mat->Set("u_MaterialUniforms.Roughness", 1.0f);
                        }
                        else
                        {
                            TNAH_CORE_ERROR("    Could not load texture: {0}", aiTexPath.C_Str());
                            fallback = true;
                        }
                    }
                }

                if (fallback)
                {
                    TNAH_CORE_ERROR("    No roughness map");
                    mat->Set("u_RoughnessTexture", Renderer::GetWhiteTexture()->GetRendererID());
                    mat->Set("u_MaterialUniforms.Roughness", roughness);
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
                            std::filesystem::path path = m_Resource.RelativeDirectory;
                            auto parentPath = path.parent_path();
                            parentPath /= str;
                            std::string texturePath = parentPath.string();
                            if(auto t = scene->GetEmbeddedTexture(texturePath.c_str()))
                            {
                                aiTexture* aiTex = const_cast<aiTexture*>(t);
                                auto texture = Texture2D::Create(texturePath.c_str(), "Metalness", true, aiTex);
                                mat->AddTexture(texture);
                                mat->Set("u_MetalnessTexture", texture);
                                mat->Set("u_MaterialUniforms.Metalness", 1.0f);
                                Renderer::RegisterTexture(texture);
                            }
                            else
                            {
                                TNAH_CORE_INFO("    Metalness map path = {0}", texturePath);
                                auto texture = Texture2D::Create(texturePath);
                                if (texture->IsLoaded())
                                {
                                    metalnessTextureFound = true;
                                    mat->AddTexture(texture);
                                    Renderer::RegisterTexture(texture);
                                    mat->Set("u_MetalnessTexture", texture);
                                    mat->Set("u_MaterialUniforms.Metalness", 1.0f);
                                }
                                else
                                {
                                    TNAH_CORE_ERROR("    Could not load texture: {0}", texturePath);
                                }
                            }
                            break;
                        }
                    }
                }
                fallback = !metalnessTextureFound;
                if (fallback)
                {
                    TNAH_CORE_ERROR("    No metalness map");
                    mat->Set("u_MetalnessTexture", Renderer::GetWhiteTexture()->GetRendererID());
                    mat->Set("u_MaterialUniforms.Metalness", metalness);

                }
#endif
                mat->SetProperties(properties);
            }
        }
        else
        {
            auto mat = Material::Create(m_Shader);
            auto properties = MaterialProperties({0.8f,0.8f,0.8f}, 0.0f, 0.8f, 0.0f, 0.0f);
            mat->Set("u_MaterialUniforms.AlbedoColor", {0.8f,0.8f,0.8f});
            mat->Set("u_MaterialUniforms.Emission", 0.0f);
            mat->Set("u_MaterialUniforms.Metalness", 0.0f);
            mat->Set("u_MaterialUniforms.Roughness", 0.8f);
            mat->Set("u_MaterialUniforms.UseNormalMap", false);

            mat->Set("u_AlbedoTexture", Renderer::GetWhiteTexture()->GetRendererID());
            mat->Set("u_MetalnessTexture", Renderer::GetWhiteTexture()->GetRendererID());
            mat->Set("u_RoughnessTexture", Renderer::GetWhiteTexture()->GetRendererID());
            mat->SetProperties(properties);
            m_Materials.push_back(mat);
        }

        if (m_IsAnimated)
        {
            m_VertexArray = VertexArray::Create();
            m_VertexBuffer = VertexBuffer::Create(m_AnimatedVertices.data(), (uint32_t)(m_AnimatedVertices.size() * sizeof(AnimatedVertex)));
            m_VertexBufferLayout = {
             { ShaderDataType::Float3, "a_Position" },
             { ShaderDataType::Float3, "a_Normal" },
             { ShaderDataType::Float3, "a_Tangent" },
             { ShaderDataType::Float3, "a_Bitangent" },
             { ShaderDataType::Float2, "a_TexCoord" },
             { ShaderDataType::Int4, "a_BoneIDs" },
             { ShaderDataType::Float4, "a_BoneWeights" }
             };
            m_VertexBuffer->SetLayout(m_VertexBufferLayout);
            m_VertexArray->AddVertexBuffer(m_VertexBuffer);
        }
        else
        {
            m_VertexArray = VertexArray::Create();
            m_VertexBuffer = VertexBuffer::Create(m_Vertices.data(), (uint32_t)(m_Vertices.size() * sizeof(Vertex)));
            m_VertexBufferLayout = {
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float3, "a_Normal" },
            { ShaderDataType::Float3, "a_Tangent" },
            { ShaderDataType::Float3, "a_Binormal" },
            { ShaderDataType::Float2, "a_TexCoord" }
            };
            m_VertexBuffer->SetLayout(m_VertexBufferLayout);
            m_VertexArray->AddVertexBuffer(m_VertexBuffer);
        }
        m_IndexBuffer = IndexBuffer::Create(m_Indices.data(), (uint32_t)(m_Indices.size() * sizeof(Index)));
#endif
    }

    void Model::CreateSubmesh(uint32_t meshIndex, const aiMesh* aMesh)
    {
        const aiVector3D zero(0.0f, 0.0f, 0.0f);

        for(uint32_t i = 0; i < aMesh->mNumVertices; i++)
        {
            const aiVector3D position = (aMesh->mVertices[i]);
            const aiVector3D normal = (aMesh->mNormals[i]);
            const aiVector3D texCoord = aMesh->HasTextureCoords(0) ? (aMesh->mTextureCoords[0][i]) : zero;
            const aiVector3D tangent = aMesh->HasTangentsAndBitangents() ? (aMesh->mTangents[i]) : zero;
            const aiVector3D bitangent = aMesh->HasTangentsAndBitangents() ? (aMesh->mBitangents[i]) : zero;

            if(m_IsAnimated)
            {
                AnimatedVertex vertex;
                vertex.Position = Vec3FromAssimpVec3(position);
                vertex.Normal = Vec3FromAssimpVec3(normal);
                vertex.Texcoord = Vec2FromAssimpVec3(texCoord);
                vertex.Tangent = Vec3FromAssimpVec3(tangent);
                vertex.Bitangents = Vec3FromAssimpVec3(bitangent);
                m_AnimatedVertices.push_back(vertex);
            }
            else
            {
                Vertex vertex;
                vertex.Position = Vec3FromAssimpVec3(position);
                vertex.Normal = Vec3FromAssimpVec3(normal);
                vertex.Texcoord = Vec2FromAssimpVec3(texCoord);
                vertex.Tangent = Vec3FromAssimpVec3(tangent);
                vertex.Bitangents = Vec3FromAssimpVec3(bitangent);
                m_Vertices.push_back(vertex);
            }
        }

        if(m_IsAnimated) CreateBones(meshIndex, aMesh);

        for(uint32_t i = 0; i < aMesh->mNumFaces; i++)
        {
            const aiFace& face = aMesh->mFaces[i];
            TNAH_CORE_ASSERT(face.mNumIndices == 3, "A mesh face must have 3 verticies");
            m_Indices.push_back({face.mIndices[0], face.mIndices[1], face.mIndices[2]});
        }
    }

    void Model::CreateBones(uint32_t meshIndex, const aiMesh* aMesh)
    {
        for(uint32_t i = 0; i < aMesh->mNumBones; i++)
        {
            uint32_t boneIndex = 0;
            std::string boneName(aMesh->mBones[i]->mName.data);

            if(m_BoneMapping.find(boneName) == m_BoneMapping.end())
            {
                boneIndex = m_BoneCount;
                m_BoneCount++;
                BoneInfo bi;
                m_BoneInfo.push_back(bi);
                m_BoneInfo[boneIndex].BoneOffset = Mat4FromAssimpMat4(aMesh->mBones[i]->mOffsetMatrix);
                m_BoneMapping[boneName] = boneIndex;
            }
            else
            {
                boneIndex = m_BoneMapping[boneName];
            }

            for(uint32_t j = 0; j < aMesh->mBones[i]->mNumWeights; j++)
            {
                //m_Submeshes[meshIndex].BaseVertex + 
                int vertexID = aMesh->mBones[i]->mWeights[j].mVertexId;
                float weight = aMesh->mBones[i]->mWeights[j].mWeight;
                m_AnimatedVertices[vertexID].AddBoneData(boneIndex, weight);
            }
        }
    }

    void Model::CreateMaterials(const aiScene* aScene, const std::string& filePath)
    {
        if(m_IsAnimated)
        {
            m_Shader = Shader::Create("Resources/shaders/default/mesh/mesh_anim_vertex.glsl","Resources/shaders/default/mesh/mesh_anim_fragment.glsl");
        }
        else
        {
            m_Shader = Shader::Create("Resources/shaders/default/mesh/mesh_vertex.glsl","Resources/shaders/default/mesh/mesh_fragment.glsl");
        }
        
        for(uint32_t i = 0; i < aScene->mNumMaterials; i++)
        {
            const aiMaterial* aMaterial = aScene->mMaterials[i];
            
            m_Materials[i] = Material::Create(m_Shader);
            auto totalTextures = TotalTexturesFromAssimpMaterial(aMaterial);
            m_Materials[i]->ResizeTextureStorage(totalTextures);
            uint32_t texturesSet = 0;
            
            //DumpMaterialProperties(aMaterial);
            
            if(AssimpMaterialIsPBR(aMaterial))
            {
                //TODO: Load PBR textures
                auto diffuse = GetTextureFromAssimpMaterial(aScene, aMaterial, aiTextureType_DIFFUSE);
                if(!diffuse.empty()) m_Materials[i]->InsertTextures(diffuse, 0);
                texturesSet += (uint32_t)diffuse.size();

                auto normals = GetTextureFromAssimpMaterial(aScene, aMaterial, aiTextureType_NORMALS);
                if(!normals.empty()) m_Materials[i]->InsertTextures(normals, texturesSet);
                texturesSet += (uint32_t)normals.size();

                auto roughness = GetTextureFromAssimpMaterial(aScene, aMaterial, aiTextureType_SHININESS);
                if(!roughness.empty()) m_Materials[i]->InsertTextures(roughness, texturesSet);
                texturesSet += (uint32_t)roughness.size();

                auto metalness = GetTextureFromAssimpMaterial(aScene, aMaterial, aiTextureType_METALNESS);
                if(!metalness.empty()) m_Materials[i]->InsertTextures(metalness, texturesSet);
            }
            else
            {
                auto diffuse = GetTextureFromAssimpMaterial(aScene, aMaterial, aiTextureType_DIFFUSE);
                if(!diffuse.empty()) m_Materials[i]->AddTextures(diffuse);

                auto specular = GetTextureFromAssimpMaterial(aScene, aMaterial, aiTextureType_SPECULAR);
                if(!specular.empty()) m_Materials[i]->AddTextures(specular);
            }

            if(m_Materials[i]->GetTextures().empty())
            {
                //No textures were loaded, create a texture using the base color
                m_Materials[i]->AddTexture(CreateBaseColorTexture(aMaterial));
            }
        
        }
    }

    void Model::CreateRenderInformation()
    {
        if (m_IsAnimated)
        {
            m_VertexArray = VertexArray::Create();
            m_VertexBuffer = VertexBuffer::Create(m_AnimatedVertices.data(), (uint32_t)(m_AnimatedVertices.size() * sizeof(AnimatedVertex)));
            m_VertexBufferLayout = {
                { ShaderDataType::Float3, "a_Position" },
                { ShaderDataType::Float3, "a_Normal" },
                { ShaderDataType::Float3, "a_Tangent" },
                { ShaderDataType::Float3, "a_Bitangent" },
                { ShaderDataType::Float2, "a_TexCoord" },
                { ShaderDataType::Float4, "a_BoneIDs" },
                { ShaderDataType::Float4, "a_BoneWeights" }
            };
            m_VertexBuffer->SetLayout(m_VertexBufferLayout);
            m_VertexArray->AddVertexBuffer(m_VertexBuffer);
        }
        else
        {
            m_VertexArray = VertexArray::Create();
            m_VertexBuffer = VertexBuffer::Create(m_Vertices.data(), (uint32_t)(m_Vertices.size() * sizeof(Vertex)));
            m_VertexBufferLayout = {
                { ShaderDataType::Float3, "a_Position" },
                { ShaderDataType::Float3, "a_Normal" },
                { ShaderDataType::Float3, "a_Tangent" },
                { ShaderDataType::Float3, "a_Binormal" },
                { ShaderDataType::Float2, "a_TexCoord" }
            };
            m_VertexBuffer->SetLayout(m_VertexBufferLayout);
            m_VertexArray->AddVertexBuffer(m_VertexBuffer);
        }
        m_IndexBuffer = IndexBuffer::Create(m_Indices.data(), (uint32_t)(m_Indices.size() * 3));
        m_VertexArray->SetIndexBuffer(m_IndexBuffer);
    }

    void Model::DumpMaterialProperties(const aiMaterial* material)
    {
        for(uint32_t p = 0; p < material->mNumProperties; p++)
        {
            auto prop = material->mProperties[p];
            TNAH_CORE_INFO("\nMaterial Property:");
            TNAH_CORE_INFO("Name = {0}", prop->mKey.data);
            
            float data = *(float*)prop->mData;
            TNAH_CORE_INFO("Value = {0}", data);
            switch (prop->mSemantic)
            {
            case aiTextureType_NONE:
                TNAH_CORE_INFO("  Semantic = aiTextureType_NONE");
                break;
            case aiTextureType_DIFFUSE:
                TNAH_CORE_INFO("  Semantic = aiTextureType_DIFFUSE");
                break;
            case aiTextureType_SPECULAR:
                TNAH_CORE_INFO("  Semantic = aiTextureType_SPECULAR");
                break;
            case aiTextureType_AMBIENT:
                TNAH_CORE_INFO("  Semantic = aiTextureType_AMBIENT");
                break;
            case aiTextureType_EMISSIVE:
                TNAH_CORE_INFO("  Semantic = aiTextureType_EMISSIVE");
                break;
            case aiTextureType_HEIGHT:
                TNAH_CORE_INFO("  Semantic = aiTextureType_HEIGHT");
                break;
            case aiTextureType_NORMALS:
                TNAH_CORE_INFO("  Semantic = aiTextureType_NORMALS");
                break;
            case aiTextureType_SHININESS:
                TNAH_CORE_INFO("  Semantic = aiTextureType_SHININESS");
                break;
            case aiTextureType_OPACITY:
                TNAH_CORE_INFO("  Semantic = aiTextureType_OPACITY");
                break;
            case aiTextureType_DISPLACEMENT:
                TNAH_CORE_INFO("  Semantic = aiTextureType_DISPLACEMENT");
                break;
            case aiTextureType_LIGHTMAP:
                TNAH_CORE_INFO("  Semantic = aiTextureType_LIGHTMAP");
                break;
            case aiTextureType_REFLECTION:
                TNAH_CORE_INFO("  Semantic = aiTextureType_REFLECTION");
                break;
            case aiTextureType_BASE_COLOR:
                TNAH_CORE_INFO("  Semantic = aiTextureType_BASE_COLOR");
                break;
            case aiTextureType_NORMAL_CAMERA:
                TNAH_CORE_INFO("  Semantic = aiTextureType_NORMAL_CAMERA");
                break;
            case aiTextureType_EMISSION_COLOR:
                TNAH_CORE_INFO("  Semantic = aiTextureType_EMISSION_COLOR");
                break;
            case aiTextureType_METALNESS:
                TNAH_CORE_INFO("  Semantic = aiTextureType_METALNESS");
                break;
            case aiTextureType_DIFFUSE_ROUGHNESS:
                TNAH_CORE_INFO("  Semantic = aiTextureType_DIFFUSE_ROUGHNESS");
                break;
            case aiTextureType_AMBIENT_OCCLUSION:
                TNAH_CORE_INFO("  Semantic = aiTextureType_AMBIENT_OCCLUSION");
                break;
            case aiTextureType_UNKNOWN:
                TNAH_CORE_INFO("  Semantic = aiTextureType_UNKNOWN");
                break;

            default: break;
            }
        }
    }

    void Model::CombineSubmeshData()
    {
#if 0
        uint32_t totalVerts = 0;
        uint32_t totalIndices = 0;
        for(auto& submesh : m_Submeshes)
        {
            if(m_IsAnimated)
            {
                totalVerts += (uint32_t)submesh.m_AnimatedVertices.size();
            }
            else
            {
                totalVerts += (uint32_t)submesh.m_Vertices.size();
            }
            totalIndices += (uint32_t)submesh.m_Indices.size();
        }

        if(m_IsAnimated) { m_AnimatedVertices.resize(totalVerts); }
        else { m_Vertices.resize(totalVerts); }
        m_Indices.resize(totalIndices);
        
        for(auto& submesh : m_Submeshes)
        {
            if(m_IsAnimated)
            {
                for(auto& v : submesh.m_AnimatedVertices)
                {
                    m_AnimatedVertices.push_back(v);
                }
                
            }
            else
            {
                for(auto& v : submesh.m_Vertices)
                {
                    m_Vertices.push_back(v);
                }
            }
            
            for(auto& i : submesh.m_Indices)
            {
                m_Indices.push_back(i);
            }
        }
#endif
        SetupRenderingObjects();
    }

    void Model::SetupRenderingObjects()
    {
        if (m_IsAnimated)
        {
            m_VertexArray = VertexArray::Create();
            m_VertexBuffer = VertexBuffer::Create(&m_AnimatedVertices[0], (uint32_t)(m_AnimatedVertices.size() * sizeof(AnimatedVertex)));
            m_VertexBufferLayout = {
                { ShaderDataType::Float3, "a_Position" },
                { ShaderDataType::Float3, "a_Normal" },
                { ShaderDataType::Float3, "a_Tangent" },
                { ShaderDataType::Float3, "a_Bitangent" },
                { ShaderDataType::Float3, "a_TexCoord" },
                { ShaderDataType::Float4, "a_BoneWeights" },
                { ShaderDataType::Int4, "a_BoneIDs" }
                };
            m_VertexBuffer->SetLayout(m_VertexBufferLayout);
            m_VertexArray->AddVertexBuffer(m_VertexBuffer);
            m_IndexBuffer = IndexBuffer::Create(&m_Indices[0], (uint32_t)(m_Indices.size()));
            m_VertexArray->SetIndexBuffer(m_IndexBuffer);
        }
        else
        {
            m_VertexArray = VertexArray::Create();
            m_VertexBuffer = VertexBuffer::Create(&m_Vertices[0], (uint32_t)(m_Vertices.size() * sizeof(AnimatedVertex)));
            m_VertexBufferLayout = {
                { ShaderDataType::Float3, "a_Position" },
                { ShaderDataType::Float3, "a_Normal" },
                { ShaderDataType::Float3, "a_Tangent" },
                { ShaderDataType::Float3, "a_Bitangent" },
                { ShaderDataType::Float3, "a_TexCoord" }
                };
            m_VertexBuffer->SetLayout(m_VertexBufferLayout);
            m_VertexArray->AddVertexBuffer(m_VertexBuffer);
            m_IndexBuffer = IndexBuffer::Create(&m_Indices[0], (uint32_t)(m_Indices.size()));
            m_VertexArray->SetIndexBuffer(m_IndexBuffer);
            
        }
    }

    void Model::OnUpdate(const Timestep& ts)
    {
        if (m_IsAnimated)
        {
            if (m_AnimationPlaying)
            {
                float ticksPerSecond = (float)(m_Scene->mAnimations[0]->mTicksPerSecond != 0 ? m_Scene->mAnimations[0]->mTicksPerSecond : 25.0f);
                m_AnimationTime = ts.GetSeconds() * ticksPerSecond;
                m_AnimationTime = fmod(m_AnimationTime, (float)m_Scene->mAnimations[0]->mDuration);
            }
            
            BoneTransform(m_AnimationTime); 
        }
    }

#pragma region ModelProcessingHelpers
    void Model::TraverseNodes(aiNode* node, const glm::mat4& parentTransform, uint32_t level)
    {
        glm::mat4 transform = parentTransform * Mat4FromAssimpMat4(node->mTransformation);
        m_NodeMap[node].resize(node->mNumMeshes);
        for (uint32_t i = 0; i < node->mNumMeshes; i++)
        {
            uint32_t mesh = node->mMeshes[i];
            auto& submesh = m_Submeshes[mesh];
            //submesh.m_NodeName = node->mName.C_Str();
            //submesh.Transform = transform;
            m_NodeMap[node][i] = mesh;
        }

        for (uint32_t i = 0; i < node->mNumChildren; i++)
            TraverseNodes(node->mChildren[i], transform, level + 1);
    
    }

    uint32_t Model::FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim)
	{
		for (uint32_t i = 0; i < pNodeAnim->mNumPositionKeys - 1; i++)
		{
			if (AnimationTime < (float)pNodeAnim->mPositionKeys[i + 1].mTime)
				return i;
		}

		return 0;
	}

	uint32_t Model::FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim)
	{
		TNAH_CORE_ASSERT(pNodeAnim->mNumRotationKeys > 0);

		for (uint32_t i = 0; i < pNodeAnim->mNumRotationKeys - 1; i++)
		{
			if (AnimationTime < (float)pNodeAnim->mRotationKeys[i + 1].mTime)
				return i;
		}

		return 0;
	}

	uint32_t Model::FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim)
	{
		TNAH_CORE_ASSERT(pNodeAnim->mNumScalingKeys > 0);

		for (uint32_t i = 0; i < pNodeAnim->mNumScalingKeys - 1; i++)
		{
			if (AnimationTime < (float)pNodeAnim->mScalingKeys[i + 1].mTime)
				return i;
		}

		return 0;
	}

	glm::vec3 Model::InterpolateTranslation(float animationTime, const aiNodeAnim* nodeAnim)
	{
		if (nodeAnim->mNumPositionKeys == 1)
		{
			// No interpolation necessary for single value
			auto v = nodeAnim->mPositionKeys[0].mValue;
			return { v.x, v.y, v.z };
		}

		uint32_t PositionIndex = FindPosition(animationTime, nodeAnim);
		uint32_t NextPositionIndex = (PositionIndex + 1);
		TNAH_CORE_ASSERT(NextPositionIndex < nodeAnim->mNumPositionKeys);
		float DeltaTime = (float)(nodeAnim->mPositionKeys[NextPositionIndex].mTime - nodeAnim->mPositionKeys[PositionIndex].mTime);
		float Factor = (animationTime - (float)nodeAnim->mPositionKeys[PositionIndex].mTime) / DeltaTime;
		TNAH_CORE_ASSERT(Factor <= 1.0f, "Factor must be below 1.0f");
		Factor = glm::clamp(Factor, 0.0f, 1.0f);
		const aiVector3D& Start = nodeAnim->mPositionKeys[PositionIndex].mValue;
		const aiVector3D& End = nodeAnim->mPositionKeys[NextPositionIndex].mValue;
		aiVector3D Delta = End - Start;
		auto aiVec = Start + Factor * Delta;
		return { aiVec.x, aiVec.y, aiVec.z };
	}

	glm::quat Model::InterpolateRotation(float animationTime, const aiNodeAnim* nodeAnim)
	{
		if (nodeAnim->mNumRotationKeys == 1)
		{
			// No interpolation necessary for single value
			auto v = nodeAnim->mRotationKeys[0].mValue;
			return glm::quat(v.w, v.x, v.y, v.z);
		}

		uint32_t RotationIndex = FindRotation(animationTime, nodeAnim);
		uint32_t NextRotationIndex = (RotationIndex + 1);
		TNAH_CORE_ASSERT(NextRotationIndex < nodeAnim->mNumRotationKeys);
		float DeltaTime = (float)(nodeAnim->mRotationKeys[NextRotationIndex].mTime - nodeAnim->mRotationKeys[RotationIndex].mTime);
		float Factor = (animationTime - (float)nodeAnim->mRotationKeys[RotationIndex].mTime) / DeltaTime;
		TNAH_CORE_ASSERT(Factor <= 1.0f, "Factor must be below 1.0f");
		Factor = glm::clamp(Factor, 0.0f, 1.0f);
		const aiQuaternion& StartRotationQ = nodeAnim->mRotationKeys[RotationIndex].mValue;
		const aiQuaternion& EndRotationQ = nodeAnim->mRotationKeys[NextRotationIndex].mValue;
		auto q = aiQuaternion();
		aiQuaternion::Interpolate(q, StartRotationQ, EndRotationQ, Factor);
		q = q.Normalize();
		return glm::quat(q.w, q.x, q.y, q.z);
	}

	glm::vec3 Model::InterpolateScale(float animationTime, const aiNodeAnim* nodeAnim)
	{
		if (nodeAnim->mNumScalingKeys == 1)
		{
			// No interpolation necessary for single value
			auto v = nodeAnim->mScalingKeys[0].mValue;
			return { v.x, v.y, v.z };
		}

		uint32_t index = FindScaling(animationTime, nodeAnim);
		uint32_t nextIndex = (index + 1);
		TNAH_CORE_ASSERT(nextIndex < nodeAnim->mNumScalingKeys);
		float deltaTime = (float)(nodeAnim->mScalingKeys[nextIndex].mTime - nodeAnim->mScalingKeys[index].mTime);
		float factor = (animationTime - (float)nodeAnim->mScalingKeys[index].mTime) / deltaTime;
		TNAH_CORE_ASSERT(factor <= 1.0f, "Factor must be below 1.0f");
		factor = glm::clamp(factor, 0.0f, 1.0f);
		const auto& start = nodeAnim->mScalingKeys[index].mValue;
		const auto& end = nodeAnim->mScalingKeys[nextIndex].mValue;
		auto delta = end - start;
		auto aiVec = start + factor * delta;
		return { aiVec.x, aiVec.y, aiVec.z };
	}

	void Model::ReadNodeHierarchy(float AnimationTime, const aiNode* pNode, const glm::mat4& parentTransform)
	{
		std::string name(pNode->mName.data);
		const aiAnimation* animation = m_Scene->mAnimations[0];
		glm::mat4 nodeTransform(Mat4FromAssimpMat4(pNode->mTransformation));
		const aiNodeAnim* nodeAnim = FindNodeAnim(animation, name);

		if (nodeAnim)
		{
			glm::vec3 translation = InterpolateTranslation(AnimationTime, nodeAnim);
			glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(translation.x, translation.y, translation.z));

			glm::quat rotation = InterpolateRotation(AnimationTime, nodeAnim);
			glm::mat4 rotationMatrix = glm::toMat4(rotation);

			glm::vec3 scale = InterpolateScale(AnimationTime, nodeAnim);
			glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(scale.x, scale.y, scale.z));

			nodeTransform = translationMatrix * rotationMatrix * scaleMatrix;
		}

		glm::mat4 transform = parentTransform * nodeTransform;

		if (m_BoneMapping.find(name) != m_BoneMapping.end())
		{
			uint32_t BoneIndex = m_BoneMapping[name];
			m_BoneInfo[BoneIndex].FinalTransform = m_InverseTransform * transform * m_BoneInfo[BoneIndex].BoneOffset;
		}

		for (uint32_t i = 0; i < pNode->mNumChildren; i++)
			ReadNodeHierarchy(AnimationTime, pNode->mChildren[i], transform);
	}

	const aiNodeAnim* Model::FindNodeAnim(const aiAnimation* animation, const std::string& nodeName)
	{
		for (uint32_t i = 0; i < animation->mNumChannels; i++)
		{
			const aiNodeAnim* nodeAnim = animation->mChannels[i];
			if (std::string(nodeAnim->mNodeName.data) == nodeName)
				return nodeAnim;
		}
		return nullptr;
	} 

	void Model::BoneTransform(float time)
	{
		ReadNodeHierarchy(time, m_Scene->mRootNode, glm::mat4(1.0f));
		m_BoneTransforms.resize(m_BoneCount);
		for (size_t i = 0; i < m_BoneCount; i++)
			m_BoneTransforms[i] = m_BoneInfo[i].FinalTransform;
	}


    // Helpers
    glm::mat4 Model::Mat4FromAssimpMat4(const aiMatrix4x4& matrix)
    {
        glm::mat4 result;
        //the a,b,c,d in assimp is the row ; the 1,2,3,4 is the column
        result[0][0] = matrix.a1; result[1][0] = matrix.a2; result[2][0] = matrix.a3; result[3][0] = matrix.a4;
        result[0][1] = matrix.b1; result[1][1] = matrix.b2; result[2][1] = matrix.b3; result[3][1] = matrix.b4;
        result[0][2] = matrix.c1; result[1][2] = matrix.c2; result[2][2] = matrix.c3; result[3][2] = matrix.c4;
        result[0][3] = matrix.d1; result[1][3] = matrix.d2; result[2][3] = matrix.d3; result[3][3] = matrix.d4;
        return result;
    }

    glm::vec3 Model::Vec3FromAssimpVec3(const aiVector3D& vector)
    {
        return glm::vec3(vector.x, vector.y, vector.z);
    }
    
    glm::vec2 Model::Vec2FromAssimpVec3(const aiVector3D& vector)
    {
        return glm::vec2(vector.x, vector.y);
    }

    uint32_t Model::TotalTexturesFromAssimpMaterial(const aiMaterial* material)
    {
        uint32_t textureTotal = 0;
        textureTotal += material->GetTextureCount(aiTextureType_DIFFUSE);
        textureTotal += material->GetTextureCount(aiTextureType_SPECULAR);
        textureTotal += material->GetTextureCount(aiTextureType_AMBIENT);
        textureTotal += material->GetTextureCount(aiTextureType_EMISSIVE);
        textureTotal += material->GetTextureCount(aiTextureType_HEIGHT);
        textureTotal += material->GetTextureCount(aiTextureType_NORMALS);
        textureTotal += material->GetTextureCount(aiTextureType_SHININESS);
        textureTotal += material->GetTextureCount(aiTextureType_OPACITY);
        textureTotal += material->GetTextureCount(aiTextureType_DISPLACEMENT);
        textureTotal += material->GetTextureCount(aiTextureType_LIGHTMAP);
        textureTotal += material->GetTextureCount(aiTextureType_REFLECTION);
        
        //PBR
        textureTotal += material->GetTextureCount(aiTextureType_BASE_COLOR);
        textureTotal += material->GetTextureCount(aiTextureType_NORMAL_CAMERA);
        textureTotal += material->GetTextureCount(aiTextureType_EMISSION_COLOR);
        textureTotal += material->GetTextureCount(aiTextureType_METALNESS);
        textureTotal += material->GetTextureCount(aiTextureType_DIFFUSE_ROUGHNESS);
        textureTotal += material->GetTextureCount(aiTextureType_AMBIENT_OCCLUSION);

        return textureTotal;
    }

    bool Model::AssimpMaterialIsPBR(const aiMaterial* material)
    {
        bool pbr = false;
        if(material->GetTextureCount(aiTextureType_NORMAL_CAMERA) > 0) pbr = true;
        if(material->GetTextureCount(aiTextureType_EMISSION_COLOR) > 0) pbr = true;
        if(material->GetTextureCount(aiTextureType_METALNESS) > 0) pbr = true;
        if(material->GetTextureCount(aiTextureType_DIFFUSE_ROUGHNESS) > 0) pbr = true;
        if(material->GetTextureCount(aiTextureType_AMBIENT_OCCLUSION) > 0) pbr = true;
        if(material->GetTextureCount(aiTextureType_BASE_COLOR) > 0) pbr = true;
        return pbr;
    }

    std::vector<Ref<Texture2D>> Model::GetTextureFromAssimpMaterial(const aiScene* scene,
                                                                    const aiMaterial* material,
                                                                    const aiTextureType& textureType)
    {
        if(const uint32_t tCount = material->GetTextureCount(textureType) > 0)
        {
            std::vector<Ref<Texture2D>> textures;
            textures.resize(tCount);
            for(uint32_t i = 0; i < tCount; i++)
            {
                aiString texturePath;
                if (material->GetTexture(textureType, i, &texturePath) == AI_SUCCESS)
                {
                    if(auto aTexture = scene->GetEmbeddedTexture(texturePath.C_Str()))
                    {
                        if(auto texture = Texture2D::Create(texturePath.C_Str(), GetTextureNameFromTextureType(textureType), true, const_cast<aiTexture*>(aTexture)))
                        {
                            Renderer::RegisterTexture(texture);
                            textures[i] = texture;
                            continue;
                        }
                        textures[i] = Renderer::GetMissingTexture();
                    }
                
                    if(auto texture = Texture2D::Create(texturePath.C_Str(), GetTextureNameFromTextureType(textureType)))
                    {
                        Renderer::RegisterTexture(texture);
                        textures[i] = texture;
                    }
                    textures[i] = Renderer::GetMissingTexture();
                }
            }
            return textures;
        }
        return std::vector<Ref<Texture2D>>(); // return empty vector if no textures were found
    }

    Ref<Texture2D> Model::CreateBaseColorTexture(const aiMaterial* material)
    {
        aiColor3D color(0.0f, 0.0f, 0.0f);
        material->Get(AI_MATKEY_BASE_COLOR, color);

        if(auto texture = Texture2D::Create(ImageFormat::RGB, 1,1, {color.r, color.g, color.b, 1.0f}))
        {
            Renderer::RegisterTexture(texture);
            return texture;
        }
        return nullptr;
    }


    std::string Model::GetTextureNameFromTextureType(const aiTextureType& textureType)
    {
        switch (textureType)
        {
        case aiTextureType_NONE:
            return std::string("NONE");
        case aiTextureType_DIFFUSE:
            return std::string("Diffuse");
        case aiTextureType_SPECULAR:
            return std::string("Specular");
        case aiTextureType_AMBIENT:
            return std::string("Ambient");
        case aiTextureType_EMISSIVE:
            return std::string("Emissive");
        case aiTextureType_HEIGHT:
            return std::string("Height");
        case aiTextureType_NORMALS:
            return std::string("Normals");
        case aiTextureType_SHININESS:
            return std::string("Shininess");
        case aiTextureType_OPACITY:
            return std::string("Opacity");
        case aiTextureType_DISPLACEMENT:
            return std::string("Displacement");
        case aiTextureType_LIGHTMAP:
            return std::string("Lightmap");
        case aiTextureType_REFLECTION:
            return std::string("Reflection");
        case aiTextureType_BASE_COLOR:
            return std::string("Base Color");
        case aiTextureType_NORMAL_CAMERA:
            return std::string("Normal Camera");
        case aiTextureType_EMISSION_COLOR:
            return std::string("Emission Color");
        case aiTextureType_METALNESS:
            return std::string("Metalness");
        case aiTextureType_DIFFUSE_ROUGHNESS:
            return std::string("Roughness");
        case aiTextureType_AMBIENT_OCCLUSION:
            return std::string("Ambient Occlusion");
        case aiTextureType_SHEEN:
            return std::string("Sheen");
        case aiTextureType_CLEARCOAT:
            return std::string("Clear Coat");
        case aiTextureType_TRANSMISSION:
            return std::string("Transmission");
        case aiTextureType_UNKNOWN:
            return std::string("UNKNOWN");
        case _aiTextureType_Force32Bit:
            return std::string("FORCE32Bit");
        default: return std::string("ERROR");
        }
    }

#if 0
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
#endif
#pragma endregion
}
