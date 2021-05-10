#include "Debugger.h"


Debugger* Debugger::instance = 0;

Debugger* Debugger::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new Debugger();
    }
    return instance;
}


std::string Debugger::DebugVec3(glm::vec3 a)
{
    std::string b = "X: " + std::to_string(a.x) + " -- Y: " + std::to_string(a.y) + " -- Z: " + std::to_string(a.z);
    return b;
}




