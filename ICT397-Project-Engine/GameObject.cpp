#include "GameObject.h"

glm::mat4 GameObject::GenerateMatFour()
{
    glm::mat4 m = glm::mat4(1.0f);
    m = glm::translate(m, pos); // translate it too the position on the screen we want it
    m = glm::scale(m, glm::vec3(scale, scale, scale));	// it's a bit too big for our scene, so scale it down

    return m;
}

glm::mat4 GameObject::GenerateMatFourForMesh(int i)
{
    return (GenerateMatFour() * model.meshes[i].transform);
}