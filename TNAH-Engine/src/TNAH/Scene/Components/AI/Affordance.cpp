#include "tnahpch.h"
#include "Affordance.h"

namespace tnah
{
    Affordance::Affordance(std::string t) : tag(t)
    {
        objectsActions[none] = 1;
    }

    Affordance::~Affordance()
    {
        
    }

    float Affordance::GetActionValue(Actions action)
    {
        float value;
        try
        {
            value = objectsActions[action];
        }
        catch (...)
        {
            objectsActions[action] = 0;
            value = objectsActions[action];
        }

        //TNAH_CORE_INFO("action value {0}", objectsActions[action]);
        return value;
    }

    void Affordance::SetActionValues(Actions action, float value)
    {
        if(action != none)
        {
            if(value > 1)
                value = 1;
            else if(value < 0)
                value = 0;

            objectsActions[action] = value;
        }
    }

    std::string Affordance::GetActionString(Actions action)
    {
        switch(action)
        {
        case abuse:
            return "Abuse";
        case drink:
            return "Drink";
        case greeting:
            return "Greeting";
        case kick:
            return "Kick";
        case pickup:
            return "Pickup";
        case play:
            return "Play";
        case punch:
            return "Punch";
        case sit:
            return "Sit";
        case sleep:
            return "Sleep";
        case none:
        default:
            return "None";
        }
    }
}

