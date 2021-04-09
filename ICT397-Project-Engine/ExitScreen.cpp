#include "ExitScreen.h"

void ExitScreen::Init(std::string name, Renderer * r)
{
    Shader s = Shader("./res/shader/modelV.glsl", "./res/shader/modelF.glsl");
    shader = s;

    Model m(name, r);
    exitModel = m;

    shader.use();
    shader.setInt("texture", 0);
}

void ExitScreen::Render(Renderer* r, View lens)
{
    {
        r->SetShader(shader, lens);
        for (int i = 0; i < exitModel.meshes.size(); i++)
        {
            glm::mat4 m = glm::mat4(1.0f);
            m = glm::translate(m, lens.GetPosition()); // translate it too the position on the screen we want it
            m = glm::scale(m, glm::vec3(2, 2, 2));	// it's a bit too big for our scene, so scale it down

            m = glm::rotate(m, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            m = glm::rotate(m, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

            m = glm::rotate(m, glm::radians(lens.GetRotation().x * -1), glm::vec3(1.0f, 0.0f, 0.0f));
            m = glm::rotate(m, glm::radians(lens.GetRotation().y), glm::vec3(0.0f, 1.0f, 0.0f));
            m = glm::rotate(m, glm::radians(lens.GetRotation().z), glm::vec3(0.0f, 0.0f, 1.0f));
            r->RenderModel(shader, m * exitModel.meshes[i].transform, exitModel.meshes[i]);
        }
    }
}

