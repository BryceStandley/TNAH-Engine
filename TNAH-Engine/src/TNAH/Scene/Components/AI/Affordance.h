#pragma once
#include "Actions.h"
#include <unordered_map>
namespace tnah
{
    class Affordance
    {
    public:
        Affordance(std::string t = "");
        ~Affordance();

        float GetActionValue(Actions action);
        void SetActionValues(Actions action, float value);
        std::string GetTag() const {return tag;}
    private:
        std::string tag;
        std::unordered_map<Actions, float> objectsActions;
    };
}
