#include "GlfwWindow.h"

void GlfwWindow::Init(std::string title, int h, int w)
{
    /* Create a windowed mode window and its OpenGL context */
    gameWindow = glfwCreateWindow(w, h, title.c_str(), NULL, NULL);
    if (!gameWindow)
    {
        glfwTerminate();
    }

    std::cout << "GLFW Started!" << std::endl;

    glm::vec3 l(0.0, 0.0f, 0.0f);
    lightPos = l;
    Camera c(glm::vec3(0.0f, 10.0f, 50.0f));
    camera = c;

    /* Make the window's context current */
    glfwMakeContextCurrent(gameWindow);
}

void GlfwWindow::Buffer()
{
    glfwSwapBuffers(gameWindow);
    glfwPollEvents();
}

void GlfwWindow::Terminate()
{
    glfwTerminate();
}

bool GlfwWindow::GameInput()
{
    int state = glfwGetKey(gameWindow, GLFW_KEY_W);

    if (state == GLFW_PRESS)
    {
        std::cout << "W pressed in GlewWindow.cpp file" << std::endl;
        return true;
    }


    return false;
}

void GlfwWindow::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GlfwWindow::FrameBuffer()
{
    glfwSetFramebufferSizeCallback(gameWindow, framebufferCallback);
}

//For NOW WE WILL HAVE TERRAIN HERE, WILL BREAK OFF SOON
void GlfwWindow::Projection()
{
    glActiveTexture(GL_TEXTURE0);

    // view/projection transformations
    projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
    view = camera.GetViewMatrix();

    // world transformation
    model = glm::mat4(1.0f);

    model = glm::mat4(1.0f);
    model = glm::translate(model, lightPos);
    model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
}

void GlfwWindow::SetShaderTerrain(Shader shader)
{
    shader.use();
    shader.setInt("texture0", 0);
    shader.setInt("texture1", 1);
    shader.setInt("texture2", 2);
    shader.setInt("texture3", 3);
    shader.setInt("texture4", 4);
}

void GlfwWindow::SetShaderSkybox(Shader shader)
{
    glm::mat4 viewSky = glm::mat4(glm::mat3(camera.GetViewMatrix()));
    shader.use();
    shader.setMat4("view", viewSky);
    shader.setMat4("projection", projection);
}

void GlfwWindow::SetShader(Shader shader)
{
    shader.use();
    shader.setMat4("projection", projection);
    shader.setMat4("view", view);
    shader.setMat4("model", model);
}

void GlfwWindow::Restart()
{
    glPrimitiveRestartIndex(0xFFFFFFFFU);
    glEnable(GL_PRIMITIVE_RESTART);
}