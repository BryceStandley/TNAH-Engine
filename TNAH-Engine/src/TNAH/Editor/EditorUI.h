#pragma once
#include "TNAH/Scene/GameObject.h"

namespace tnah {
    class EditorUI
    {
    public:
        EditorUI();
        static void DrawComponentProperties(GameObject* object);

    private:
        static bool DrawFloatControl(const std::string& label, float& value, float min = 0.0f, float max = 0.0f, bool readOnly = false);
        static bool DrawVec4Control(const std::string& label, glm::vec4& values, bool readOnly = false, float resetValue = 0.0f, float columnWidth = 100.0f);
        static bool DrawVec3Control(const std::string& label, glm::vec3& values, bool readOnly = false, float resetValue = 0.0f, float columnWidth = 100.0f);
        static bool DrawVec2Control(const std::string& label, glm::vec2& values, bool readOnly = false, float resetValue = 0.0f, float columnWidth = 100.0f);
        static bool DrawTextControl(const std::string& label, std::string& text, const std::string& resetText = "", bool readOnly = false);
        static bool Draw4ColorControl(const std::string& label, glm::vec4& value, bool readOnly = false,  const glm::vec4& resetValue = {0,0,0,0});
        static bool DrawMaterialProperties(Ref<Material> material);
    };



}
