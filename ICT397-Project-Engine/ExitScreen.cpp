#include "ExitScreen.h"

void ExitScreen::Init()
{
    Shader s = Shader("./res/shader/exitScreenV.glsl", "./res/shader/exitScreenF.glsl");
    shader = s;
    tex = textureLoader.loadTexture("./res/images/exitScreen.png");
    vertexData.emplace_back(glm::vec3(-1.0f,1.0f,0));//Vertex
    vertexData.emplace_back(glm::vec3(0.0f,1.0f,0));//Texture

    vertexData.emplace_back(glm::vec3(1.0f,1.0f,0));
    vertexData.emplace_back(glm::vec3(1.0f,1.0,0));

    vertexData.emplace_back(glm::vec3(1.0f,-1.0f,0));
    vertexData.emplace_back(glm::vec3(1.0f,0.0,0));

    vertexData.emplace_back(glm::vec3(-1.0f,-1.0,0));
    vertexData.emplace_back(glm::vec3(0.0f,0.0,0));

    indicesData.emplace_back(0);
    indicesData.emplace_back(1);
    indicesData.emplace_back(3);
    indicesData.emplace_back(1);
    indicesData.emplace_back(2);
    indicesData.emplace_back(3);

    shader.use();
    shader.setInt("texture", 0);
}

