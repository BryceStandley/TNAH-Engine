#pragma once
#include <glm/glm.hpp>
namespace tnah
{
    struct Position
    {
        Position(glm::vec3 position = glm::vec3(0)) : values(position) {}
        glm::vec3 values;
    };

    struct Rotation
    {
        Rotation(glm::quat rot = glm::quat(1, 0, 0, 0)) : values(rot) {}
        glm::vec3 ValuesAsVec3() {return glm::eulerAngles(values);}
        glm::quat values;
    };
}
