#include "tnahpch.h"
#include "Serializer.h"

#include "GameObject.h"
#include "TNAH/Core/Application.h"

namespace tnah {

    Resource Serializer::s_SceneResource = Resource();
    
    bool Serializer::SerializeScene(Scene* scene, const std::string& filePath)
    {
        std::fstream sceneFile;
        sceneFile.exceptions(std::fstream::failbit | std::fstream::badbit);
        try
        {
            sceneFile.open(filePath.c_str(), std::fstream::out);
            std::stringstream ss;
            ss << GenerateTagOpen("scene", 0);
            ss << GenerateGlobalSettings(scene);

            ss << GenerateSceneSettings(scene);
            
            ss << GenerateTagClose("scene");

            std::string s = ss.str();
            //sceneFile.write(s.c_str(), s.size());
            sceneFile << s << std::endl;
            sceneFile.close();
        }
        catch(std::fstream::failure& e)
        {
            TNAH_CORE_ERROR("{0}", e.what());
            TNAH_CORE_ASSERT(false, "Scene file failed to open");
        }
        return false;
    }

    std::string Serializer::GenerateGlobalSettings(Scene* scene)
    {
        
        auto sceneCam = scene->GetMainCameraGameObject();
        auto sceneLight = scene->GetSceneLightGameObject();
        std::stringstream ss;

        ss << GenerateTagOpen("global", 1);
        if(scene->m_IsEditorScene)
        {
            auto editorCam = scene->GetEditorCameraGameObject();
            ss << GenerateTagOpen("editor", 2);
            ss << GenerateTagEntry(editorCam->GetComponent<TagComponent>(), 3);
            ss << GenerateTransform(editorCam->GetComponent<TransformComponent>(), 3);
            ss << GenerateCamera(editorCam->GetComponent<EditorCameraComponent>(), 3);
            ss << GenerateTagClose("editor", 2);
        }

        ss << GenerateTagOpen("sceneCamera", 2);
        ss << GenerateTagEntry(sceneCam->GetComponent<TagComponent>(), 3);
        ss << GenerateTransform(sceneCam->GetComponent<TransformComponent>(),3 );
        ss << GenerateCamera(sceneCam->GetComponent<CameraComponent>(), 3);
        ss << GenerateTagClose("sceneCamera", 2);

        ss << GenerateTagOpen("sceneLight", 2);
        if(sceneLight->HasComponent<TagComponent>(), 3)
            ss << GenerateTagEntry(sceneLight->GetComponent<TagComponent>(), 3);
        ss << GenerateTransform(sceneLight->GetComponent<TransformComponent>(), 3);
        ss << GenerateLight(sceneLight->GetComponent<LightComponent>(), 3);
        ss << GenerateTagClose("sceneLight", 2);
        
        ss << GenerateTagClose("global", 1);

        return ss.str();
    }

    std::string Serializer::GenerateSceneSettings(Scene* scene)
    {
        auto& objects = scene->GetGameObjectsInScene();
        std::stringstream ss;
        ss << GenerateTagOpen("hierarchy", 1);
        for(auto& go : objects)
        {
            //Skip if the game object is a global game object
            if(go.first == scene->GetMainCameraGameObject()->GetUUID()) continue;
            if(go.first == scene->GetSceneLightGameObject()->GetUUID()) continue;
            if(go.first == scene->GetEditorCameraGameObject()->GetUUID()) continue;
            
            ss << GenerateTagOpen("gameObject", 2);
            auto& g = go.second;
            if(g.HasComponent<TagComponent>())
                ss << GenerateTagEntry(g.GetComponent<TagComponent>(), 3);
            if(g.HasComponent<TransformComponent>())
                ss << GenerateTransform(g.GetComponent<TransformComponent>(), 3);
            if(g.HasComponent<CameraComponent>())
                ss << GenerateCamera(g.GetComponent<CameraComponent>(), 3);
            if(g.HasComponent<TerrainComponent>())
                ss << GenerateTerrain(g.GetComponent<TerrainComponent>(), 3);
            if(g.HasComponent<MeshComponent>())
                ss << GenerateMesh(g.GetComponent<MeshComponent>(), 3);
            if(g.HasComponent<LightComponent>())
                ss << GenerateLight(g.GetComponent<LightComponent>(), 3);
            if(g.HasComponent<SkyboxComponent>())
                ss << GenerateSkybox(g.GetComponent<SkyboxComponent>(), 3);
            ss << GenerateTagClose("gameObject", 2);
        }
        ss << GenerateTagClose("hierarchy", 1);
        
        return ss.str();
    }

    std::string Serializer::GenerateTagOpen(const std::string& tagType, const uint32_t& totalTabs)
    {
        std::string tabs = "";
        for(int i = 0; i < totalTabs; i++)
            tabs += "\t"; 
        return tabs +"<" + tagType + ">\n";
    }

    std::string Serializer::GenerateTagClose(const std::string& tagType, const uint32_t& totalTabs)
    {
        std::string tabs = "";
        for(int i = 0; i < totalTabs; i++)
            tabs += "\t"; 
        return tabs + "</" + tagType + ">\n";
    }

    std::string Serializer::GenerateTagOpen(const char* tagType, const uint32_t& totalTabs)
    {
        std::string tabs = "";
        for(int i = 0; i < totalTabs; i++)
            tabs += "\t"; 
        std::string s = tabs + "<";
        s += tagType;
        s += ">\n";
        return  s;
    }

    std::string Serializer::GenerateTagClose(const char* tagType, const uint32_t& totalTabs)
    {
        std::string tabs = "";
        for(int i = 0; i < totalTabs; i++)
            tabs += "\t"; 
        
        std::string s = tabs +"</";
        s += tagType;
        s += ">\n";
        return  s;
    }

    std::string Serializer::GenerateTransform(const TransformComponent& transform, const uint32_t& totalTabs)
    {
        std::stringstream ss;
        ss << GenerateTagOpen("transform", totalTabs);

        ss << GenerateVec3Entry("position", transform.Position, totalTabs+1);
        ss << GenerateVec3Entry("rotation", transform.Rotation, totalTabs+1);
        ss << GenerateVec3Entry("scale", transform.Scale, totalTabs+1);
        
        ss << GenerateTagClose("transform", totalTabs);
        return ss.str();
    }

    std::string Serializer::GenerateCamera(const SceneCamera& camera, const uint32_t& totalTabs)
    {
        std::stringstream ss;
        ss << GenerateTagOpen("camera", totalTabs);
        if(camera.m_ProjectionType == SceneCamera::ProjectionType::Orthographic)
        {
            ss << GenerateValueEntry("orthographic", true, totalTabs + 1);
            ss << GenerateValueEntry("size", camera.m_OrthographicSize, totalTabs + 1);
            ss << GenerateValueEntry("near", camera.m_OrthographicNear, totalTabs + 1);
            ss << GenerateValueEntry("far", camera.m_OrthographicFar, totalTabs + 1);
        }
        else
        {
            ss << GenerateValueEntry("perspective", true, totalTabs + 1);
            ss << GenerateValueEntry("fov", camera.GetPerspectiveVerticalFOV(), totalTabs + 1);
            ss << GenerateValueEntry("near", camera.m_PerspectiveNear, totalTabs + 1);
            ss << GenerateValueEntry("far", camera.m_PerspectiveFar, totalTabs + 1);
        }
        ss << GenerateTagClose("camera", totalTabs);
        return ss.str();
        
    }

    std::string Serializer::GenerateTerrain(const TerrainComponent& terrain, const uint32_t& totalTabs)
    {
        std::stringstream ss;

        ss << GenerateTagOpen("terrain", totalTabs);
        ss << GenerateDirectoryEntry(terrain.SceneTerrain->m_HeightmapPath, totalTabs + 1);
        ss << GenerateTagClose("terrain", totalTabs);

        return ss.str();
    }

    std::string Serializer::GenerateSkybox(const SkyboxComponent& skybox, const uint32_t& totalTabs)
    {
        std::stringstream ss;

        ss << GenerateTagOpen("skybox", totalTabs);
        const auto textures = skybox.SceneSkybox->GetMaterial()->GetCubemapProperties();
        
        ss << GenerateDirectoryEntry(textures.Front.RelativeDirectory, totalTabs + 1);
        ss << GenerateDirectoryEntry(textures.Back.RelativeDirectory, totalTabs + 1);
        ss << GenerateDirectoryEntry(textures.Top.RelativeDirectory, totalTabs + 1);
        ss << GenerateDirectoryEntry(textures.Bottom.RelativeDirectory, totalTabs + 1);
        ss << GenerateDirectoryEntry(textures.Left.RelativeDirectory, totalTabs + 1);
        ss << GenerateDirectoryEntry(textures.Right.RelativeDirectory, totalTabs + 1);
        
        ss << GenerateTagClose("skybox", totalTabs);

        return ss.str();
    }

    
    std::string Serializer::GenerateMesh(const MeshComponent& mesh, const uint32_t& totalTabs)
    {
        std::stringstream ss;
        ss << GenerateTagOpen("mesh", totalTabs);
        ss << GenerateDirectoryEntry(mesh.Model->m_FilePath, totalTabs + 1);
        ss << GenerateTagClose("mesh", totalTabs);

        return ss.str();
        
    }

    std::string Serializer::GenerateLight(const LightComponent& light, const uint32_t& totalTabs)
    {
        auto l = light.Light;
        std::stringstream ss;

        ss << GenerateTagOpen("light", totalTabs);
        ss << GenerateValueEntry("sceneLight", l->m_IsSceneLight, totalTabs + 1);
        ss << GenerateVec3Entry("direction", l->m_Direction, totalTabs + 1);
        ss << GenerateVec4Entry("color", l->m_Color, totalTabs + 1);
        ss << GenerateValueEntry("intensity", l->m_Intensity, totalTabs + 1);

        ss << GenerateTagClose("light", totalTabs);

        return ss.str();
    }

    std::string tnah::Serializer::GenerateVec3(const glm::vec3& value, const uint32_t& totalTabs)
    {
        std::stringstream ss;
        const char* comp[] = {"x", "y", "z"};
        for(int i = 0; i < 3; i++)
        {
            ss << GenerateValueEntry(comp[i], value[i],totalTabs);
            
        }
        return ss.str();
        
    }

    std::string Serializer::GenerateVec4(const glm::vec4& value, const uint32_t& totalTabs)
    {
        std::stringstream ss;
        const char* comp[] = {"x", "y", "z", "w"};
        for(int i = 0; i < 4; i++)
        {
            ss << GenerateValueEntry(comp[i], value[i],totalTabs);
            
        }
        return ss.str();
        
    }

    std::string Serializer::GenerateVec4Entry(const std::string& tagType, const glm::vec4& value, const uint32_t& totalTabs)
    {
        std::stringstream ss;
        ss << GenerateTagOpen(tagType, totalTabs);
        ss << GenerateVec4(value, totalTabs + 1);
        ss << GenerateTagClose(tagType, totalTabs);
        return ss.str();
    }

    std::string Serializer::GenerateVec3Entry(const std::string& tagType, const glm::vec3& value, const uint32_t& totalTabs)
    {
        std::stringstream ss;
        ss << GenerateTagOpen(tagType, totalTabs);
        ss << GenerateVec3(value, totalTabs + 1);
        ss << GenerateTagClose(tagType, totalTabs);
        return ss.str();
    }

    std::string Serializer::GenerateDirectoryEntry(const std::string& path, const uint32_t& totalTabs)
    {
        std::stringstream ss;

        ss << GenerateTagOpen("directory", totalTabs);
        ss << GenerateValueEntry("path", path, totalTabs+1);
        ss << GenerateTagClose("directory", totalTabs);
        return ss.str();
    }

    std::string Serializer::GenerateTagEntry(const TagComponent& tag, const uint32_t& totalTabs)
    {
        std::stringstream ss;
        ss << GenerateTagOpen("tag", totalTabs);
        ss << GenerateValueEntry("name", tag.Tag, totalTabs + 1);
        ss << GenerateTagClose("tag", totalTabs);
        return ss.str();
    }

    std::string Serializer::GenerateValueEntry(const std::string& tagType, const float& value, const uint32_t& totalTabs)
    {
        std::string tabs = "";
        for(int i = 0; i < totalTabs +2; i++)
            tabs += "\t";
        
        std::stringstream ss;

        ss << GenerateTagOpen(tagType, totalTabs);
        ss << GenerateTagOpen("value", totalTabs + 1);
        ss << tabs + std::to_string(value) + "\n";
        ss << GenerateTagClose("value", totalTabs + 1);
        ss << GenerateTagClose(tagType, totalTabs);
        return ss.str();
    }
    
    std::string Serializer::GenerateValueEntry(const std::string& tagType, const int& value, const uint32_t& totalTabs)
    {
        std::string tabs = "";
        for(int i = 0; i < totalTabs +2; i++)
            tabs += "\t";
        std::stringstream ss;

        ss << GenerateTagOpen(tagType, totalTabs);
        ss << GenerateTagOpen("value", totalTabs+ 1);
        ss << tabs + std::to_string(value) + "\n";
        ss << GenerateTagClose("value", totalTabs + 1);
        ss << GenerateTagClose(tagType, totalTabs);
        return ss.str();
    }
    
    std::string Serializer::GenerateValueEntry(const std::string& tagType, const bool& value, const uint32_t& totalTabs)
    {
        std::string tabs = "";
        for(int i = 0; i < totalTabs +2; i++)
            tabs += "\t";
        std::stringstream ss;

        ss << GenerateTagOpen(tagType, totalTabs);
        ss << GenerateTagOpen("value", totalTabs + 1);
        if(value)
            ss << tabs + "true\n";
        else
            ss << tabs + "false\n";
        ss << GenerateTagClose("value", totalTabs + 1);
        ss << GenerateTagClose(tagType, totalTabs);
        return ss.str();
    }

    std::string Serializer::GenerateValueEntry(const std::string& tagType, const std::string& value, const uint32_t& totalTabs)
    {
        std::string tabs = "";
        for(int i = 0; i < totalTabs +2; i++)
            tabs += "\t";
        
        std::stringstream ss;
        ss << GenerateTagOpen(tagType, totalTabs);
        ss << GenerateTagOpen("value", totalTabs + 1);
        ss << tabs +value + "\n";
        ss << GenerateTagClose("value", totalTabs+ 1);
        ss << GenerateTagClose(tagType, totalTabs);
        return ss.str();
    }

//***********************************************************************************************************************
    //Deserialize scene functions
    
    Scene* Serializer::DeserializeScene(const std::string& filePath)
    {
        std::string result;
        std::ifstream in(filePath, std::ios::in | std::ios::binary);
        if (in)
        {
            in.seekg(0, std::ios::end);
            size_t size = in.tellg();
            if (size != -1)
            {
                result.resize(size);
                in.seekg(0, std::ios::beg);
                in.read(&result[0], size);
                in.close();
            }
            else
            {
                TNAH_CORE_ERROR("Could not read from file '{0}'", filePath);
                return nullptr;
            }
        }
        else
        {
            TNAH_CORE_ERROR("Could not open file '{0}'", filePath);
            return nullptr;
        }

        // the file has been opened and read in to a string, now parse the string like normal finding the required tags
        int currentPos = 0;
        Scene* scene = nullptr;
        s_SceneResource = Resource(filePath);
        
        if(GetGlobalSettingsFromFile(scene, result, currentPos))
        {
           if(GetSceneStructureFromFile(scene, result, currentPos))
           {
               return scene;
           }
            return scene;
        }

        return nullptr;
    }

    bool Serializer::GetGlobalSettingsFromFile(Scene* scene, const std::string& fileContents, int& currentPos)
    {
        //check each level of the global settings to make sure nothing is missing
        // if anything is missing, the file is corrupt, return false
        const auto sceneTags = FindTags("scene", fileContents);
        if(CheckTags(sceneTags))
        {
            const auto global = FindTags("global", fileContents);
            if(CheckTags(global))
            {
                currentPos = global.second; // the current position in the string is the end of the global section
                if(Application::Get().CheckEditor()) // Only create and check editor scene related objects if the application is in editor mode
                {
                    const auto editor = FindTags("editor", fileContents);
                    if(CheckTags(editor))
                    {
                    
                        scene = Scene::CreateNewEditorScene();
                        auto tag = FindTags("tag", fileContents);
                        if(CheckTags(tag))
                        {
                            auto editorCam = scene->GetEditorCameraGameObject();
                            auto tagPos = FindTags("tag", fileContents, editor.first, editor.second);
                            auto transformPos = FindTags("transform", fileContents, editor.first, editor.second);
                            auto cameraPos = FindTags("camera", fileContents, editor.first, editor.second);
                        
                            auto& t = editorCam->GetComponent<TagComponent>();
                            t = GetTagFromFile(fileContents, tagPos);

                            auto& transform = editorCam->GetComponent<TransformComponent>();
                            transform = GetTransformFromFile(fileContents, transformPos);

                            auto& camera = editorCam->GetComponent<EditorCameraComponent>();
                            camera.EditorCamera = GetCameraFromFile(fileContents, cameraPos);
                        }
                    }
                }
                else { scene = Scene::CreateEmptyScene(); }
                auto sceneCam = FindTags("sceneCamera", fileContents);
                if(CheckTags(sceneCam))
                {
                    auto cam = scene->GetMainCameraGameObject();
                    auto tagPos = FindTags("tag", fileContents, sceneCam.first, sceneCam.second);
                    auto transformPos = FindTags("transform", fileContents, sceneCam.first, sceneCam.second);
                    auto cameraPos  = FindTags("camera", fileContents, sceneCam.first, sceneCam.second);

                    auto& tag = cam->GetComponent<TagComponent>();
                    auto& camera = cam->GetComponent<CameraComponent>();
                    auto& transform = cam->GetComponent<TransformComponent>();

                    tag = GetTagFromFile(fileContents, tagPos);
                    camera.Camera = GetCameraFromFile(fileContents, cameraPos);
                    transform = GetTransformFromFile(fileContents, transformPos);
                }
                else GenerateValuesLoadError("Scene Camera");

                auto sceneLight = FindTags("sceneLight", fileContents);
                if(CheckTags(sceneLight))
                {
                    auto light = scene->GetSceneLightGameObject();
                    auto tagPos = FindTags("tag", fileContents, sceneLight.first, sceneLight.second);
                    auto transformPos = FindTags("transform", fileContents, sceneLight.first, sceneLight.second);
                    auto lightPos = FindTags("light", fileContents, sceneLight.first, sceneLight.second);

                    auto& tag = light->GetComponent<TagComponent>();
                    auto& transform = light->GetComponent<TransformComponent>();
                    auto& sLight = light->GetComponent<LightComponent>();

                    tag = GetTagFromFile(fileContents, tagPos);
                    transform = GetTransformFromFile(fileContents, transformPos);
                    sLight.Light = GetLightFromFile(fileContents, lightPos).Light;
                }
                else GenerateValuesLoadError("Scene Light");
                
            }
            else return false;
        }
        else return false;

        return true;
    }

    bool Serializer::GetSceneStructureFromFile(Scene* scene, const std::string& fileContents, int& currentPos)
    {
        
        auto hierarchy = FindTags("hierarchy", fileContents, currentPos);
        int nextGameobjectPos = hierarchy.first;
        if(CheckTags(hierarchy))
        {
            auto go = FindTags("gameObject", fileContents, nextGameobjectPos);
            while(CheckTags(go))
            {
                if(!GetGameObjectFromFile(scene, fileContents, go))
                {
                    GenerateValuesLoadError("GameObject");
                }
                nextGameobjectPos = go.second + strlen("</gameObject>");
                go = FindTags("gameObject", fileContents, nextGameobjectPos);
            }
            return true;
        }
        return false;
    }

    bool Serializer::GetGameObjectFromFile(Scene* scene, const std::string& fileContents,
        std::pair<size_t, size_t> gameObjectTagPositions)
    {
        
        
        auto tagPos = FindTags("tag", fileContents, gameObjectTagPositions.first, gameObjectTagPositions.second);
        auto transformPos = FindTags("transform", fileContents, gameObjectTagPositions.first, gameObjectTagPositions.second);

        if(!CheckTags(tagPos) || !CheckTags(transformPos)) return false;
        
        auto tag = GetTagFromFile(fileContents, tagPos);
        auto object = scene->CreateGameObject(tag.Tag);
        auto& transform = object->GetComponent<TransformComponent>();
        transform = GetTransformFromFile(fileContents, transformPos);
        
        FindAndAddComponentsFromFile(object, fileContents, gameObjectTagPositions);

        return true;
    }

    int Serializer::FindAndAddComponentsFromFile(GameObject* gameObject, const std::string& fileContents,
        std::pair<size_t, size_t> gameObjectTagPositions)
    {
        //Here we just try and find each component in the file and add it to the component if we find a entry for ii
        int added = 0;
        auto cameraPos = FindTags("camera", fileContents, gameObjectTagPositions.first, gameObjectTagPositions.second);
        if(CheckTags(cameraPos))
        {
            gameObject->AddComponent<CameraComponent>(GetCameraFromFile(fileContents, cameraPos));
            added++;
        }

        auto meshPos = FindTags("mesh", fileContents, gameObjectTagPositions.first, gameObjectTagPositions.second);
        if(CheckTags(meshPos))
        {
            gameObject->AddComponent<MeshComponent>(GetMeshFromFile(fileContents, meshPos));
            added++;
        }

        auto playerControllerPos = FindTags("playerController", fileContents, gameObjectTagPositions.first, gameObjectTagPositions.second);
        if(CheckTags(playerControllerPos))
        {
            gameObject->AddComponent<PlayerControllerComponent>(GetPlayerControllerFromFile(fileContents, playerControllerPos));
            added++;
        }

        auto nativePos = FindTags("nativeScript", fileContents, gameObjectTagPositions.first, gameObjectTagPositions.second);
        if(CheckTags(nativePos))
        {
            gameObject->AddComponent<NativeScriptComponent>(GetNativeScriptFromFile(fileContents, nativePos));
            added++;
        }

        auto terrainPos = FindTags("terrain", fileContents, gameObjectTagPositions.first, gameObjectTagPositions.second);
        if(CheckTags(terrainPos))
        {
            gameObject->AddComponent<TerrainComponent>(GetTerrainFromFile(fileContents, terrainPos));
            added++;
        }

        auto lightPos = FindTags("light", fileContents, gameObjectTagPositions.first, gameObjectTagPositions.second);
        if(CheckTags(lightPos))
        {
            gameObject->AddComponent<LightComponent>(GetLightFromFile(fileContents, lightPos));
            added++;
        }

        auto skyboxPos = FindTags("skybox", fileContents, gameObjectTagPositions.first, gameObjectTagPositions.second);
        if(CheckTags(skyboxPos))
        {
            gameObject->AddComponent<SkyboxComponent>(GetSkyboxFromFile(fileContents, skyboxPos));
            added++;
        }

        return added;
    }

    TagComponent Serializer::GetTagFromFile(const std::string& fileContents,
        std::pair<size_t, size_t> componentTagPositions)
    {
        auto tag = GetStringValueFromFile("name", fileContents, componentTagPositions);
        return TagComponent(tag);
    }

    TransformComponent Serializer::GetTransformFromFile(const std::string& fileContents,
        std::pair<size_t, size_t> componentTagPositions)
    {
        auto position = GetVec3FromFile("position", fileContents, componentTagPositions);
        auto rotation = GetVec3FromFile("rotation", fileContents, componentTagPositions);
        auto scale = GetVec3FromFile("scale", fileContents, componentTagPositions);
        return TransformComponent(position, rotation, scale);
    }

    SceneCamera Serializer::GetCameraFromFile(const std::string& fileContents,
        std::pair<size_t, size_t> componentTagPositions)
    {
        //TODO: finish camera
        SceneCamera camera;
        
        return camera;
    }

    SkyboxComponent Serializer::GetSkyboxFromFile(const std::string& fileContents,
                                                  std::pair<size_t, size_t> componentTagPositions)
    {
        //TODO: finish skybox
        return SkyboxComponent();
    }

    TerrainComponent Serializer::GetTerrainFromFile(const std::string& fileContents,
                                                    std::pair<size_t, size_t> componentTagPositions)
    {
        auto heightmap = GetDirectoryFromFile("", fileContents, componentTagPositions);
        return TerrainComponent(heightmap);
    }

    MeshComponent Serializer::GetMeshFromFile(const std::string& fileContents,
        std::pair<size_t, size_t> componentTagPositions)
    {
        auto mesh = GetDirectoryFromFile("", fileContents, componentTagPositions);
        return MeshComponent(mesh);
    }

    PlayerControllerComponent Serializer::GetPlayerControllerFromFile(const std::string& fileContents,
        std::pair<size_t, size_t> componentTagPositions)
    {
        auto forward = GetIntValueFromFile("keyForward", fileContents, componentTagPositions);
        auto backward = GetIntValueFromFile("keyBackward", fileContents, componentTagPositions);
        auto left = GetIntValueFromFile("keyLeft", fileContents, componentTagPositions);
        auto right = GetIntValueFromFile("keyRight", fileContents, componentTagPositions);

        std::pair<int, int> sprint = {
            GetIntValueFromFile("keySprint1", fileContents, componentTagPositions),
            GetIntValueFromFile("keySprint2", fileContents, componentTagPositions)
        };
        
        auto jump = GetIntValueFromFile("keyJump", fileContents, componentTagPositions);
        auto crouch = GetIntValueFromFile("keyCrouch", fileContents, componentTagPositions);

        auto playerHeight = GetFloatValueFromFile("playerHeight", fileContents, componentTagPositions);
        auto movementSpeed = GetFloatValueFromFile("movementSpeed", fileContents, componentTagPositions);
        auto rotationSensitivity = GetFloatValueFromFile("rotationSensitivity", fileContents, componentTagPositions);
        auto sprintSpeed = GetFloatValueFromFile("sprintSpeed", fileContents, componentTagPositions);
        auto crouchSpeed = GetFloatValueFromFile("crouchSpeed", fileContents, componentTagPositions);
        auto crouchHeightMultiplier = GetFloatValueFromFile("crouchHeightMultiplier", fileContents, componentTagPositions);

        auto pc = PlayerControllerComponent();
        pc.Forward = forward;
        pc.Backward = backward;
        pc.Left = left;
        pc.Right = right;
        pc.Sprint = sprint;
        pc.Jump = jump;
        pc.Crouch = crouch;
        pc.PlayerHeight = playerHeight;
        pc.MovementSpeed = movementSpeed;
        pc.RotationSensitivity = rotationSensitivity;
        pc.SprintSpeed = sprintSpeed;
        pc.CrouchSpeed = crouchSpeed;
        pc.CrouchHeightMultiplier = crouchHeightMultiplier;

        return pc;
    }

    NativeScriptComponent Serializer::GetNativeScriptFromFile(const std::string& fileContents,
        std::pair<size_t, size_t> componentTagPositions)
    {
        return NativeScriptComponent();
    }

    LightComponent Serializer::GetLightFromFile(const std::string& fileContents,
        std::pair<size_t, size_t> componentTagPositions)
    {
        auto sceneLight = GetBoolValueFromFile("sceneLight", fileContents, componentTagPositions);
        auto direction = GetVec3FromFile("direction", fileContents, componentTagPositions);
        auto ambient = GetVec3FromFile("ambient", fileContents, componentTagPositions);
        auto diffuse = GetVec3FromFile("diffuse", fileContents, componentTagPositions);
        auto specular = GetVec3FromFile("specular", fileContents, componentTagPositions);
        auto position = GetVec3FromFile("position", fileContents, componentTagPositions);
        auto color = GetVec4FromFile("color", fileContents, componentTagPositions);
        auto distance = GetIntValueFromFile("distance", fileContents, componentTagPositions);
        auto constant = GetFloatValueFromFile("constant", fileContents, componentTagPositions);
        auto linear = GetFloatValueFromFile("linear", fileContents, componentTagPositions);
        auto quadratic = GetFloatValueFromFile("quadratic", fileContents, componentTagPositions);
        auto cutoff = GetFloatValueFromFile("cutoff", fileContents, componentTagPositions);
        auto intensity = GetFloatValueFromFile("intensity", fileContents, componentTagPositions);
        auto type = GetIntValueFromFile("type", fileContents, componentTagPositions);

        LightComponent light;
        switch (type)
        {
            case 0: light = LightComponent(Light::LightType::Directional); break;
            case 1: light = LightComponent(Light::LightType::Point); break;
            case 2: light = LightComponent(Light::LightType::Spot); break;
            default: break;
        }
        light.Light->SetDirection(direction);
        light.Light->SetAmbient(ambient);
        light.Light->SetDiffuse(diffuse);
        light.Light->SetSpecular(specular);
        light.Light->SetPosition(position);
        light.Light->SetColor(color);
        light.Light->SetDistance(distance);
        light.Light->SetConstant(constant);
        light.Light->SetLinear(linear);
        light.Light->SetQuadratic(quadratic);
        light.Light->SetCutOff(cutoff);
        light.Light->SetIntensity(intensity);
        
        return light;
    }

    std::pair<size_t, size_t> Serializer::FindTags(const std::string& tagToFind, const std::string& fileContents, size_t from, size_t to)
    {
        std::string o = "<"; o += tagToFind + ">";
        std::string c = "</"; c += tagToFind + ">";
        if(from == 0 && to == 0)
        {
            auto open = fileContents.find_first_of(o, from);
            auto close = fileContents.find_first_of(c, from);
            return {open, close};
        }

        const auto count = to - from;
        auto open = fileContents.find_first_of(o, from);
        auto close = fileContents.find_first_of(c.c_str(), from, count);
        
        if(CheckTags({open, close}))
            return {open, close};
        return {-1,-1};

        
    }

    bool Serializer::CheckTags(std::pair<size_t, size_t> tags)
    {
        if(tags.first != std::string::npos && tags.second != std::string::npos)
            return true;
        
        return false;
    }


    glm::vec3 Serializer::GetVec3FromFile(const std::string& tagName, const std::string& fileContents,
        std::pair<size_t, size_t> componentTagPositions)
    {
        auto t = FindTags(tagName, fileContents, componentTagPositions.first, componentTagPositions.second);
        if(CheckTags(t))
        {
            glm::vec3 out = glm::vec3(GetVec4FromFile(tagName, fileContents, componentTagPositions));
            return out;
        }

        return glm::vec3(0.0f);
    }

    glm::vec4 Serializer::GetVec4FromFile(const std::string& tagName, const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions)
    {
        auto t = FindTags(tagName, fileContents, componentTagPositions.first, componentTagPositions.second);
        if(CheckTags(t))
        {
            glm::vec4 out;
            out.x = GetFloatValueFromFile("x", fileContents, t);
            out.y = GetFloatValueFromFile("y", fileContents, t);
            out.z = GetFloatValueFromFile("z", fileContents, t);
            out.w = GetFloatValueFromFile("w", fileContents, t);

            return out;
        }
        return glm::vec4(0.0f);
    }

    std::string Serializer::GetDirectoryFromFile(const std::string& tagName, const std::string& fileContents,
                                                 std::pair<size_t, size_t> componentTagPositions)
    {
        return GetStringValueFromFile("path", fileContents, componentTagPositions);
    }

    int Serializer::GetIntValueFromFile(const std::string& tagName, const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions)
    {
        auto t = FindTags(tagName, fileContents, componentTagPositions.first, componentTagPositions.second);
        if(CheckTags(t))
        {
            auto v = FindTags("value", fileContents, t.first, t.second);
            if(CheckTags(v))
            {
                size_t from = v.first + strlen("<value>\n");
                std::string out =  fileContents.substr(from, v.second);
                return std::stoi(out);
            }
        }
        return 0;
    }

    float Serializer::GetFloatValueFromFile(const std::string& tagName, const std::string& fileContents,
                                            std::pair<size_t, size_t> componentTagPositions)
    {
        auto t = FindTags(tagName, fileContents, componentTagPositions.first, componentTagPositions.second);
        if(CheckTags(t))
        {
            auto v = FindTags("value", fileContents, t.first, t.second);
            if(CheckTags(v))
            {
                size_t from = v.first + strlen("<value>\n");
                std::string out =  fileContents.substr(from, v.second);
                return std::stof(out);
            }
        }
        return 0;
    }

    bool Serializer::GetBoolValueFromFile(const std::string& tagName, const std::string& fileContents,
                                          std::pair<size_t, size_t> componentTagPositions)
    {
        auto t = FindTags(tagName, fileContents, componentTagPositions.first, componentTagPositions.second);
        if(CheckTags(t))
        {
            auto v = FindTags("value", fileContents, t.first, t.second);
            if(CheckTags(v))
            {
                size_t from = v.first + strlen("<value>\n");
                std::string out =  fileContents.substr(from, v.second);
                if(out.compare("true") == 0)
                    return true;
                else
                    return false;
            }
        }
        return false;
    }

    std::string Serializer::GetStringValueFromFile(const std::string& tagName, const std::string& fileContents,
                                                   std::pair<size_t, size_t> componentTagPositions)
    {
        auto t = FindTags(tagName, fileContents, componentTagPositions.first, componentTagPositions.second);
        if(CheckTags(t))
        {
            auto v = FindTags("value", fileContents, t.first, t.second);
            if(CheckTags(v))
            {
                size_t from = v.first + strlen("<value>\n");
                return fileContents.substr(from, v.second);
            }
        }
        return "";
    }

    void Serializer::GenerateValuesLoadError(const std::string& tagName)
    {
        std::string error = "Failed to load values for ";
        error += tagName;
        error += " from scene '{0}' at path '{1}'";
        TNAH_WARN(error, s_SceneResource.CustomName, s_SceneResource.AbsoluteDirectory);
        TNAH_WARN("Object defaults loaded");
    }

}
