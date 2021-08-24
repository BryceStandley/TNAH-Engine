#pragma once
#include "Scene.h"
#include "Components/SkyboxComponent.h"

namespace tnah
{
    class Serializer
    {
    private:
        
        static bool SerializeScene(Scene* scene, const std::string& filePath);
        static std::string GenerateGlobalSettings(Scene* scene);
        static std::string GenerateSceneSettings(Scene* scene);

        static std::string GenerateTagOpen(const std::string& tagType, const uint32_t& totalTabs = 0);
        static std::string GenerateTagClose(const std::string& tagType, const uint32_t& totalTabs = 0);
        static std::string GenerateTagOpen(const char tagType, const uint32_t& totalTabs = 0);
        static std::string GenerateTagClose(const char tagType, const uint32_t& totalTabs = 0);
        static std::string GenerateTransform(const TransformComponent& transform, const uint32_t& totalTabs = 0);
        static std::string GenerateCamera(const SceneCamera& camera, const uint32_t& totalTabs = 0);
        static std::string GenerateSkybox(const SkyboxComponent& skybox, const uint32_t& totalTabs = 0);
        static std::string GenerateTerrain(const TerrainComponent& terrain, const uint32_t& totalTabs = 0);
        static std::string GenerateMesh(const MeshComponent& mesh, const uint32_t& totalTabs = 0);
        static std::string GenerateLight(const LightComponent& light, const uint32_t& totalTabs = 0);
        static std::string GenerateVec3(const glm::vec3& value, const uint32_t& totalTabs = 0);
        static std::string GenerateVec4(const glm::vec4& value, const uint32_t& totalTabs = 0);
        static std::string GenerateVec3Entry(const std::string& tagType, const glm::vec3& value, const uint32_t& totalTabs = 0);
        static std::string GenerateVec4Entry(const std::string& tagType, const glm::vec4& value, const uint32_t& totalTabs = 0);
        static std::string GenerateDirectoryEntry(const std::string& path, const uint32_t& totalTabs = 0);
        static std::string GenerateValueEntry(const std::string& tagType, const float& value, const uint32_t& totalTabs = 0);
        static std::string GenerateValueEntry(const std::string& tagType, const int& value, const uint32_t& totalTabs = 0);
        static std::string GenerateValueEntry(const std::string& tagType, const bool& value, const uint32_t& totalTabs = 0);
        static std::string GenerateTagEntry(const TagComponent& tag, const uint32_t& totalTabs = 0);
        static std::string GenerateValueEntry(const std::string& tagType, const std::string& value, const uint32_t& totalTabs = 0);

        friend class EditorLayer;
        friend class Editor;
    };
}
