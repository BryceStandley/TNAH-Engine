#pragma once
#include "TNAH/Scene/GameObject.h"

#pragma warning(push, 0)
#include <imgui.h>
#include "imgui_internal.h"
#pragma warning(pop)

namespace tnah {
    class EditorUI
    {
    public:
        static void DrawComponentProperties(GameObject& object);

    private:
        static bool DrawFloatControl(const std::string& label, float& value, float min = 0.0f, float max = 0.0f, bool readOnly = false);
        static bool DrawVec4Control(const std::string& label, glm::vec4& values, bool readOnly = false, float resetValue = 0.0f, float columnWidth = 100.0f);
        static bool DrawVec3Control(const std::string& label, glm::vec3& values, bool readOnly = false, float resetValue = 0.0f, float columnWidth = 100.0f);
        static bool DrawVec2Control(const std::string& label, glm::vec2& values, bool readOnly = false, float resetValue = 0.0f, float columnWidth = 100.0f);
        static bool DrawTextControl(const char* label, std::string& text, bool error = false, bool readOnly = false);
        static bool Draw4ColorControl(const std::string& label, glm::vec4& value, bool readOnly = false,  const glm::vec4& resetValue = {0,0,0,0});
        static bool DrawMaterialProperties(bool empty, Ref<Material> material = nullptr);
        static bool DrawRemoveComponentButton(const std::string& id);
        static bool DrawResetButton(const std::string& id);
        static bool DrawRedButton(const std::string& label);

        /**
         *  Draws the Add component search for a given GameObject.
         *  @return ComponentType - A type of a given component as a enum
         *  @note Not all ComponentTypes can be returned as some are internal types not intended for being added at runtime
         */
        static std::list<ComponentTypes> GetPossibleComponentTypes(std::vector<ComponentTypes> typesHeld);
        static bool DrawAddComponent(GameObject& object, const std::string& searchTerm = "");
        static ComponentTypes FindAndDrawComponentSearchTerm(std::list<ComponentTypes> typesToSearch, const std::string& searchTerm);
        static ComponentTypes DrawComponentList(std::list<ComponentTypes> componentsToDisplay);

        static std::list<ComponentTypes> FindAllComponentsContaining(std::list<ComponentTypes> componentsToSearch, const std::string& term);
        static std::string FindStringFromComponentType(ComponentTypes type);
        static std::string FindComponentTypeCategory(ComponentTypes type);
        static bool AddComponentFromType(GameObject& object, ComponentTypes type);
        
    };



}
