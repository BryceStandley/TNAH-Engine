#include "tnahpch.h"
#include "Character.h"

#include "TNAH/Core/Application.h"

namespace tnah{

    void Character::LogAction(std::string text, glm::vec4 colour)
    {
        Application::LogPush(LogText(name + ": " + text, colour));
    }
}
