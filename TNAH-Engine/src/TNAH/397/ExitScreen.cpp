#include "tnahpch.h"
#include "ExitScreen.h"

void ExitScreen::Init(std::string name, Renderer * r)
{
    tnah::Shader s = Shader("./res/shader/modelV.glsl", "./res/shader/modelF.glsl");
    shader = s;

    Model m(name, r, false);
    exitModel = m;

    shader.use();
    shader.setInt("texture", 0);
}

void ExitScreen::Render(Renderer* r, View lens)
{
    glm::vec3 rot = lens.GetRotation();
    rot.x *= -1;
    lens.SetRotation(rot);
    exitModel.Render(lens, shader, lens.GetPosition(), lens.GetRotation(), 2, true, 0, 0, r, false);
}

