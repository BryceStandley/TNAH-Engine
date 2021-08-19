#pragma once
#include "Scene.h"

namespace tnah
{
    class Serializer
    {
    private:
        static bool SerializeScene(Scene* scene, const std::string& filePath);
        static std::string GenerateGlobalSettings(Scene* scene);
        static std::string GenerateSceneSettings(Scene* scene);
        
        static std::string GenerateTagOpen(const std::string& tagType);
        static std::string GenerateTagClose(const std::string& tagType);
        static std::string GenerateTagOpen(const char tagType);
        static std::string GenerateTagClose(const char tagType);
        static std::string GenerateTransform(const TransformComponent& transform);
        static std::string GenerateCamera(const SceneCamera& camera);
        static std::string GenerateTerrain(const TerrainComponent& terrain);
        static std::string GenerateMesh(const MeshComponent& mesh);
        static std::string GenerateLight(const LightComponent& light);
        static std::string GenerateVec3(const glm::vec3& value);
        static std::string GenerateVec4(const glm::vec4& value);
        static std::string GenerateVec3Entry(const std::string& tagType, const glm::vec3& value);
        static std::string GenerateVec4Entry(const std::string& tagType, const glm::vec4& value);
        static std::string GenerateDirectoryEntry(const std::string& path);
        static std::string GenerateValueEntry(const std::string& tagType, const float& value);
        static std::string GenerateValueEntry(const std::string& tagType, const int& value);
        static std::string GenerateValueEntry(const std::string& tagType, const bool& value);
        static std::string GenerateTagEntry(const TagComponent& tag);
        static std::string GenerateValueEntry(const std::string& tagType, const std::string& value);

        friend class EditorLayer;
        friend class Editor;
    };
}