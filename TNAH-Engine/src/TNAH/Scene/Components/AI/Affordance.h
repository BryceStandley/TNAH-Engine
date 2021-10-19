#pragma once
#include "Actions.h"
#include <unordered_map>
namespace tnah
{
    class Affordance
    {
    public:
        Affordance();
        ~Affordance();

        float GetActionValue(Actions action);
        void SetActionValues(Actions action, float value);
    private:
        std::unordered_map<Actions, float> objectsActions;
    };
}
