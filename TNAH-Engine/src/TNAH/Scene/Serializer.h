#pragma once
#include "Scene.h"

namespace tnah
{
    class Serializer
    {
    private:  
        static bool SerializeScene(Ref<Scene> scene, const std::string& filePath);
        static std::string GenerateGlobalSettings(Ref<Scene> scene);
        static std::string GenerateSceneSettings(Ref<Scene> scene);


        //Components
        static std::string GenerateTransform(const TransformComponent& transform, const uint32_t& totalTabs = 0);
        static std::string GenerateCamera(const SceneCamera& camera, const uint32_t& totalTabs = 0);
        static std::string GenerateSkybox(const SkyboxComponent& skybox, const uint32_t& totalTabs = 0);
        static std::string GenerateTerrain(const TerrainComponent& terrain, const uint32_t& totalTabs = 0);
        static std::string GenerateMesh(const MeshComponent& mesh, const uint32_t& totalTabs = 0);
        static std::string GenerateLight(const LightComponent& light, const uint32_t& totalTabs = 0);
        
        //Tag creators
        static std::string GenerateTagOpen(const std::string& tagType, const uint32_t& totalTabs = 0);
        static std::string GenerateTagClose(const std::string& tagType, const uint32_t& totalTabs = 0);
        static std::string GenerateTagOpen(const char* tagType, const uint32_t& totalTabs = 0);
        static std::string GenerateTagClose(const char* tagType, const uint32_t& totalTabs = 0);
        
        //Helpers for different data types
        static std::string GenerateVec3(const glm::vec3& value, const uint32_t& totalTabs = 0);
        static std::string GenerateVec4(const glm::vec4& value, const uint32_t& totalTabs = 0);
        static std::string GenerateVec3Entry(const std::string& tagType, const glm::vec3& value, const uint32_t& totalTabs = 0);
        static std::string GenerateVec4Entry(const std::string& tagType, const glm::vec4& value, const uint32_t& totalTabs = 0);
        static std::string GenerateDirectoryEntry(const std::string& tagType, const std::string& path, const uint32_t& totalTabs = 0);
        static std::string GenerateValueEntry(const std::string& tagType, const float& value, const uint32_t& totalTabs = 0);
        static std::string GenerateValueEntry(const std::string& tagType, const int& value, const uint32_t& totalTabs = 0);
        static std::string GenerateValueEntry(const std::string& tagType, const bool& value, const uint32_t& totalTabs = 0);
        static std::string GenerateTagEntry(const TagComponent& tag, const uint32_t& totalTabs = 0);
        static std::string GenerateValueEntry(const std::string& tagType, const std::string& value, const uint32_t& totalTabs = 0);

    private:
        static Ref<Scene> DeserializeScene(const std::string& filePath);

        /**
         * Finds the all data for the scene within <global> </global> tags
         */
        static Ref<Scene> GetGlobalSettingsFromFile(Ref<Scene> scene, const std::string& fileContents, int& currentPos);
        static std::pair<size_t, size_t> FindTags(const std::string& tagToFind, const std::string& fileContents, size_t from = 0, size_t to = 0);
        static bool CheckTags(std::pair<size_t, size_t> tags);
        /**
        * Finds the all data for the scene within <hierarchy> </hierarchy> tags
        */
        static Ref<Scene> GetSceneStructureFromFile(Ref<Scene> scene, const std::string& fileContents, int& currentPos);
        /**
        * Finds the all data for the scene within <gameobject> </gameobject> tags
        */
        static Ref<Scene> GetGameObjectFromFile(Ref<Scene> scene, const std::string& fileContents, std::pair<size_t, size_t> gameObjectTagPositions);
        static int FindAndAddComponentsFromFile(GameObject& gameObject, const std::string& fileContents, std::pair<size_t, size_t> gameObjectTagPositions);

        /**
        * Finds the all data for the scene within <tag> </tag> tags
        */
        static TagComponent GetTagFromFile(const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions);
        
        /**
        * Finds the all data for the scene within <transform> </transform> tags
        */
        static TransformComponent GetTransformFromFile(const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions);

        /**
        * Finds the all data for the scene within <camera> </camera> tags
        */
        static SceneCamera GetCameraFromFile(const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions);

        /**
        * Finds the all data for the scene within <skybox> </skybox> tags
        */
        static SkyboxComponent GetSkyboxFromFile(const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions);

        /**
        * Finds the all data for the scene within <terrain> </terrain> tags
        */
        static TerrainComponent GetTerrainFromFile(const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions);

        /**
        * Finds the all data for the scene within <mesh> </mesh> tags
        */
        static MeshComponent GetMeshFromFile(const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions);

        static PlayerControllerComponent GetPlayerControllerFromFile(const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions);

        static NativeScriptComponent GetNativeScriptFromFile(const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions);
        /**
        * Finds the all data for the scene within <light> </light> tags
        */
        static LightComponent GetLightFromFile(const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions);

        /**
        * Finds values of a vec3 for a component with a given search tag
        */
        static glm::vec3 GetVec3FromFile(const std::string& tagName, const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions);

        /**
        * Finds values of a vec4 for a component with a given search tag
        */
        static glm::vec4 GetVec4FromFile(const std::string& tagName, const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions);

        /**
        * Finds a path from a directory entry between <directory> </directory> tags
        */
        static std::string GetDirectoryFromFile(const std::string& tagName, const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions);

        /**
        * Finds a int value between <value> </value> tags
        */
        static int GetIntValueFromFile(const std::string& tagName, const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions);

        /**
        * Finds a float value between <value> </value> tags
        */
        static float GetFloatValueFromFile(const std::string& tagName, const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions);

        /**
        * Finds a bool value between <value> </value> tags
        */
        static bool GetBoolValueFromFile(const std::string& tagName, const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions);

        static std::string GetStringValueFromFile(const std::string& tagName, const std::string& fileContents, std::pair<size_t, size_t> componentTagPositions);
        
        static void GenerateValuesLoadError(const std::string& tagName);

        static Resource s_SceneResource;
        
        friend class EditorLayer;
        friend class Editor;
    };

    


}
