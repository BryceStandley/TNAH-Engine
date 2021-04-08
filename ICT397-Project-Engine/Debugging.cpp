#include "Debugging.h"

std::string tnah::Debugging::DebugVec3(glm::vec3 a)
{
    std::string b = "X: " + std::to_string(a.x) + " -- Y: " + std::to_string(a.y) + " -- Z: " + std::to_string(a.z);
    return b;
}
