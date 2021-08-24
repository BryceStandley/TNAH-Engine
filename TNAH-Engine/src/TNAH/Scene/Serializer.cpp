#include "tnahpch.h"
#include "Serializer.h"

#include "GameObject.h"
#include "Components/Components.h"
#include "Scene.h"
#include "Components/SkyboxComponent.h"

namespace tnah {
    uint32_t m_CurrentTab = 0;
    
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
            TNAH_CORE_ASSERT(false, "Scene file failed to opem");
        }
        return false;
    }

    std::string Serializer::GenerateGlobalSettings(Scene* scene)
    {
        
        auto sceneCam = scene->GetMainCameraGameObject();
        auto sceneLight = scene->GetSceneLightGameObject();
        std::stringstream ss;

        ss << GenerateTagOpen("global", 1);
        m_CurrentTab++;
        if(scene->m_IsEditorScene)
        {
            auto editorCam = scene->GetEditorCameraGameObject();
            ss << GenerateTagOpen("editorView", 2);
            ss << GenerateTagEntry(editorCam->GetComponent<TagComponent>(), 3);
            ss << GenerateTransform(editorCam->GetComponent<TransformComponent>(), 3);
            ss << GenerateCamera(editorCam->GetComponent<EditorCameraComponent>(), 3);
            ss << GenerateTagClose("editorView", 2);
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
        for(auto& go : objects)
        {
            ss << GenerateTagOpen("gameObject", 1);
            auto& g = go.second;
            if(g.HasComponent<TagComponent>())
                ss << GenerateTagEntry(g.GetComponent<TagComponent>(), 2);
            if(g.HasComponent<TransformComponent>())
                ss << GenerateTransform(g.GetComponent<TransformComponent>(), 2);
            if(g.HasComponent<CameraComponent>())
                ss << GenerateCamera(g.GetComponent<CameraComponent>(), 2);
            if(g.HasComponent<TerrainComponent>())
                ss << GenerateTerrain(g.GetComponent<TerrainComponent>(), 2);
            if(g.HasComponent<MeshComponent>())
                ss << GenerateMesh(g.GetComponent<MeshComponent>(), 2);
            if(g.HasComponent<LightComponent>())
                ss << GenerateLight(g.GetComponent<LightComponent>(), 2);
            if(g.HasComponent<SkyboxComponent>())
                ss << GenerateSkybox(g.GetComponent<SkyboxComponent>(), 2);
            ss << GenerateTagClose("gameObject", 1);
        }
        
        return ss.str();
    }

    std::string Serializer::GenerateTagOpen(const std::string& tagType, const uint32_t& totalTabs)
    {
        std::string tabs = "";
        for(int i = 0; i <= totalTabs; i++)
            tabs += "\t"; 
        return tabs +"<" + tagType + ">\n";
    }

    std::string Serializer::GenerateTagClose(const std::string& tagType, const uint32_t& totalTabs)
    {
        std::string tabs = "";
        for(int i = 0; i <= totalTabs; i++)
            tabs += "\t"; 
        return tabs + "</" + tagType + ">\n";
    }

    std::string Serializer::GenerateTagOpen(const char tagType, const uint32_t& totalTabs)
    {
        std::string tabs = "";
        for(int i = 0; i <= totalTabs; i++)
            tabs += "\t"; 
        std::string s = tabs + "<";
        s += tagType;
        s += ">\n";
        return  s;
    }

    std::string Serializer::GenerateTagClose(const char tagType, const uint32_t& totalTabs)
    {
        std::string tabs = "";
        for(int i = 0; i <= totalTabs; i++)
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
        for(int i = 0; i <= totalTabs +2; i++)
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
        for(int i = 0; i <= totalTabs +2; i++)
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
        for(int i = 0; i <= totalTabs +2; i++)
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
        for(int i = 0; i <= totalTabs +2; i++)
            tabs += "\t";
        
        std::stringstream ss;
        ss << GenerateTagOpen(tagType, totalTabs);
        ss << GenerateTagOpen("value", totalTabs + 1);
        ss << tabs +value + "\n";
        ss << GenerateTagClose("value", totalTabs+ 1);
        ss << GenerateTagClose(tagType, totalTabs);
        return ss.str();
    }
}
