#pragma once
#include "Actions.h"
#include <unordered_map>
namespace tnah
{
    class Affordance
    {
    public:
        Affordance(std::string t = "");
        
        Affordance(const Affordance &copy)
        {
            tag = copy.GetTag();
            objectsActions = GetActions();
        }
        
        ~Affordance();
        
        float editorValue = 0;
        std::string recent = "";
        float GetActionValue(Actions action);
        void SetActionValues(Actions action, float value);
        std::string GetTag() const {return tag;}
        static std::string GetActionString(Actions action);
        std::unordered_map<Actions, float> GetActions() {return objectsActions;};
    private:
        std::string tag;
        std::unordered_map<Actions, float> objectsActions;
        inline static std::string s_SearchString = "Affordance";
        /** @brief	Type identifiers for the component */
        inline static ComponentTypes s_Types = {
            {ComponentVariations::ConcaveMeshCollider},
{{ComponentCategory::Physics}}
        };
        friend class EditorUI;
    };
}
