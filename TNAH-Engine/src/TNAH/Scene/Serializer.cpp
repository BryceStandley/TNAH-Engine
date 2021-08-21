#include "tnahpch.h"
#include "Serializer.h"

#include "GameObject.h"
#include "Components/EditorCamera.h"
#include "Scene.h"

namespace tnah {
    
    bool Serializer::SerializeScene(Scene* scene, const std::string& filePath)
    {
        std::fstream sceneFile;
        sceneFile.exceptions(std::fstream::failbit | std::fstream::badbit);
        try
        {
            sceneFile.open(filePath.c_str(), std::fstream::out);
            std::stringstream ss;
            ss << GenerateTagOpen("scene");
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

        ss << GenerateTagOpen("global");
        if(scene->m_IsEditorScene)
        {
            auto editorCam = scene->GetEditorCameraGameObject();
            ss << GenerateTagOpen("editorView");
            ss << GenerateTagEntry(editorCam->GetComponent<TagComponent>());
            ss << GenerateTransform(editorCam->GetComponent<TransformComponent>());
            ss << GenerateCamera(editorCam->GetComponent<EditorCameraComponent>());
            ss << GenerateTagClose("editorView");
        }

        ss << GenerateTagOpen("sceneCamera");
        ss << GenerateTagEntry(sceneCam->GetComponent<TagComponent>());
        ss << GenerateTransform(sceneCam->GetComponent<TransformComponent>());
        ss << GenerateCamera(sceneCam->GetComponent<CameraComponent>());
        ss << GenerateTagClose("sceneCamera");

        ss << GenerateTagOpen("sceneLight");
        if(sceneLight->HasComponent<TagComponent>())
            ss << GenerateTagEntry(sceneLight->GetComponent<TagComponent>());
        ss << GenerateTransform(sceneLight->GetComponent<TransformComponent>());
        ss << GenerateLight(sceneLight->GetComponent<LightComponent>());
        ss << GenerateTagClose("sceneLight");
        
        ss << GenerateTagClose("global");

        return ss.str();
    }

    std::string Serializer::GenerateSceneSettings(Scene* scene)
    {
        auto& objects = scene->GetGameObjectsInScene();
        std::stringstream ss;
        for(auto& go : objects)
        {
            ss << GenerateTagOpen("gameObject");
            auto& g = go.second;
            if(g.HasComponent<TagComponent>())
                ss << GenerateTagEntry(g.GetComponent<TagComponent>());
            if(g.HasComponent<TransformComponent>())
                ss << GenerateTransform(g.GetComponent<TransformComponent>());
            if(g.HasComponent<CameraComponent>())
                ss << GenerateCamera(g.GetComponent<CameraComponent>());
            if(g.HasComponent<TerrainComponent>())
                ss << GenerateTerrain(g.GetComponent<TerrainComponent>());
            if(g.HasComponent<MeshComponent>())
                ss << GenerateMesh(g.GetComponent<MeshComponent>());
            if(g.HasComponent<LightComponent>())
                ss << GenerateLight(g.GetComponent<LightComponent>());
            ss << GenerateTagClose("gameObject");
        }

        return ss.str();
    }

    std::string Serializer::GenerateTagOpen(const std::string& tagType)
    {
        return "<" + tagType + ">\n";
    }

    std::string Serializer::GenerateTagClose(const std::string& tagType)
    {
        return "</" + tagType + ">\n";
    }

    std::string Serializer::GenerateTagOpen(const char tagType)
    {
        std::string s = "<";
        s += tagType;
        s += ">\n";
        return  s;
    }

    std::string Serializer::GenerateTagClose(const char tagType)
    {
        std::string s = "</";
        s += tagType;
        s += ">\n";
        return  s;
    }

    std::string Serializer::GenerateTransform(const TransformComponent& transform)
    {
        std::stringstream ss;
        ss << GenerateTagOpen("transform");

        ss << GenerateVec3Entry("position", transform.Position);
        ss << GenerateVec3Entry("rotation", transform.Rotation);
        ss << GenerateVec3Entry("scale", transform.Scale);
        
        ss << GenerateTagClose("transform");
        return ss.str();
    }

    std::string Serializer::GenerateCamera(const SceneCamera& camera)
    {
        std::stringstream ss;
        ss << GenerateTagOpen("camera");
        if(camera.m_ProjectionType == SceneCamera::ProjectionType::Orthographic)
        {
            ss << GenerateValueEntry("orthographic", true);
            ss << GenerateValueEntry("size", camera.m_OrthographicSize);
            ss << GenerateValueEntry("near", camera.m_OrthographicNear);
            ss << GenerateValueEntry("far", camera.m_OrthographicFar);
        }
        else
        {
            ss << GenerateValueEntry("perspective", true);
            ss << GenerateValueEntry("fov", camera.GetPerspectiveVerticalFOV());
            ss << GenerateValueEntry("near", camera.m_PerspectiveNear);
            ss << GenerateValueEntry("far", camera.m_PerspectiveFar);
        }
        ss << GenerateTagClose("camera");
        return ss.str();
        
    }

    std::string Serializer::GenerateTerrain(const TerrainComponent& terrain)
    {
        std::stringstream ss;

        ss << GenerateTagOpen("terrain");
        ss << GenerateDirectoryEntry(terrain.SceneTerrain->m_HeightmapPath);
        ss << GenerateTagClose("terrain");

        return ss.str();
    }

    std::string Serializer::GenerateMesh(const MeshComponent& mesh)
    {
        std::stringstream ss;
        ss << GenerateTagOpen("mesh");
        ss << GenerateDirectoryEntry(mesh.Model->m_FilePath);
        ss << GenerateTagClose("mesh");

        return ss.str();
        
    }

    std::string Serializer::GenerateLight(const LightComponent& light)
    {
        auto l = light.Light;
        std::stringstream ss;

        ss << GenerateTagOpen("light");
        ss << GenerateValueEntry("sceneLight", l->m_IsSceneLight);
        ss << GenerateVec3Entry("direction", l->m_Direction);
        ss << GenerateVec4Entry("color", l->m_Color);
        ss << GenerateValueEntry("intensity", l->m_Intensity);

        ss << GenerateTagClose("light");

        return ss.str();
        
        
        
        
    }

    std::string tnah::Serializer::GenerateVec3(const glm::vec3& value)
    {
        std::stringstream ss;
        const char* comp[] = {"x", "y", "z"};
        for(int i = 0; i < 3; i++)
        {
            ss << GenerateTagOpen(comp[i]);
            ss << GenerateTagOpen("value");
            ss << std::to_string(value[i]) + "\n";
            ss << GenerateTagClose("value");
            ss << GenerateTagClose(comp[i]);
            
        }
        return ss.str();
        
    }

    std::string Serializer::GenerateVec4(const glm::vec4& value)
    {
        std::stringstream ss;
        const char* comp[] = {"x", "y", "z", "w"};
        for(int i = 0; i < 4; i++)
        {
            ss << GenerateTagOpen(comp[i]);
            ss << GenerateTagOpen("value");
            ss << std::to_string(value[i]) + "\n";
            ss << GenerateTagClose("value");
            ss << GenerateTagClose(comp[i]);
            
        }
        return ss.str();
        
    }

    std::string Serializer::GenerateVec4Entry(const std::string& tagType, const glm::vec4& value)
    {
        std::stringstream ss;
        ss << GenerateTagOpen(tagType);
        ss << GenerateVec4(value);
        ss << GenerateTagClose(tagType);
        return ss.str();
    }

    std::string Serializer::GenerateVec3Entry(const std::string& tagType, const glm::vec3& value)
    {
        std::stringstream ss;
        ss << GenerateTagOpen(tagType);
        ss << GenerateVec3(value);
        ss << GenerateTagClose(tagType);
        return ss.str();
    }

    std::string Serializer::GenerateDirectoryEntry(const std::string& path)
    {
        std::stringstream ss;

        ss << GenerateTagOpen("path");
        ss << GenerateTagOpen("value");
        ss << path + "\n";
        ss << GenerateTagClose("value");
        ss << GenerateTagClose("path");
        return ss.str();
    }

    std::string Serializer::GenerateValueEntry(const std::string& tagType, const float& value)
    {
        std::stringstream ss;

        ss << GenerateTagOpen(tagType);
        ss << GenerateTagOpen("value");
        ss << std::to_string(value) + "\n";
        ss << GenerateTagClose("value");
        ss << GenerateTagClose(tagType);
        return ss.str();
    }

    std::string Serializer::GenerateValueEntry(const std::string& tagType, const int& value)
    {
        std::stringstream ss;

        ss << GenerateTagOpen(tagType);
        ss << GenerateTagOpen("value");
        ss << std::to_string(value) + "\n";
        ss << GenerateTagClose("value");
        ss << GenerateTagClose(tagType);
        return ss.str();
    }

    std::string Serializer::GenerateValueEntry(const std::string& tagType, const bool& value)
    {
        std::stringstream ss;

        ss << GenerateTagOpen(tagType);
        ss << GenerateTagOpen("value");
        if(value)
            ss << "true\n";
        else
            ss << "false\n";
        ss << GenerateTagClose("value");
        ss << GenerateTagClose(tagType);
        return ss.str();
    }

    std::string Serializer::GenerateTagEntry(const TagComponent& tag)
    {
        std::stringstream ss;
        ss << GenerateTagOpen("tag");
        ss << GenerateValueEntry("name", tag.Tag) + "\n";
        ss << GenerateTagClose("tag");
        return ss.str();
    }

    std::string Serializer::GenerateValueEntry(const std::string& tagType, const std::string& value)
    {
        std::stringstream ss;
        ss << GenerateTagOpen(tagType);
        ss << GenerateTagOpen("value");
        ss << value + "\n";
        ss << GenerateTagClose("value");
        ss << GenerateTagClose(tagType);
        return ss.str();
    }
}
