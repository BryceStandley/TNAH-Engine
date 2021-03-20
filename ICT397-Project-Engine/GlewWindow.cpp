#include "GlewWindow.h"

bool GlewWindow::Init(std::string title, int h, int w)
{
    if (!glfwInit())
        return false;

    /* Create a windowed mode window and its OpenGL context */
    gameWindow = glfwCreateWindow(w, h, title.c_str(), NULL, NULL);
    if (!gameWindow)
    {
        glfwTerminate();
        return false;
    }

    std::cout << "GLFW Started!" << std::endl;

    glm::vec3 l(0.0, 0.0f, 0.0f);
    lightPos = l;
    Camera c(13.2f, 20.6f, -14.1, 0.f, 1.0f, 0.f, 90.9f, -37.f);
    camera = c;

    /* Make the window's context current */
    glfwMakeContextCurrent(gameWindow);
}

void GlewWindow::Buffer()
{
    glfwSwapBuffers(gameWindow);
    glfwPollEvents();
}

void GlewWindow::Terminate()
{
    glfwTerminate();
}

bool GlewWindow::GameInput()
{
    int state = glfwGetKey(gameWindow, GLFW_KEY_W);

    if (state == GLFW_PRESS)
    {
        std::cout << "W pressed in GlewWindow.cpp file" << std::endl;
        return true;
    }


    return false;
}

void GlewWindow::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GlewWindow::FrameBuffer()
{
    glfwSetFramebufferSizeCallback(gameWindow, framebufferCallback);
}

//For NOW WE WILL HAVE TERRAIN HERE, WILL BREAK OFF SOON
void GlewWindow::Projection(Terrain *gameTerrain)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gameTerrain->terrainTextureID);

    // view/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = camera.GetViewMatrix();

    // world transformation
    glm::mat4 model = glm::mat4(1.0f);

    gameTerrain->shader.use();
    gameTerrain->shader.setMat4("projection", projection);
    gameTerrain->shader.setMat4("view", view);
    model = glm::mat4(1.0f);
    model = glm::translate(model, lightPos);
    model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
    gameTerrain->shader.setMat4("model", model);

    glPrimitiveRestartIndex(0xFFFFFFFFU);
    glEnable(GL_PRIMITIVE_RESTART);

    gameTerrain->Render();
}