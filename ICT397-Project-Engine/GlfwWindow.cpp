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
    Camera c(50.0f, 2.5f, 50.0f, 0.0f, 1.0f, 0.0f, 90.0f, -37.0f);
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

bool GlfwWindow::GameInput(float deltaTime)
{
    if (glfwGetKey(gameWindow, gameInput.exit) == GLFW_PRESS)
        return false;

    if (glfwGetKey(gameWindow, gameInput.foward) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(gameWindow, gameInput.back) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(gameWindow, gameInput.left) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(gameWindow, gameInput.right) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(gameWindow, GLFW_KEY_P) == GLFW_PRESS)//P to reset camera to new position
        camera.Position = glm::vec3(100, 0, 0);
    if (glfwGetKey(gameWindow, gameInput.wireOn) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (glfwGetKey(gameWindow, gameInput.wireOff) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    return true;
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
    lens.SetProjection(glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f));
    lens.SetView(camera.GetViewMatrix());

    // world transformation
    lens.SetModel(glm::mat4(1.0f));

    lens.SetModel(glm::mat4(1.0f));
    lens.SetModel(glm::translate(lens.GetModel(), lightPos));
    lens.SetModel(glm::scale(lens.GetModel(), glm::vec3(0.2f))); // a smaller cube
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
    shader.setMat4("projection", lens.GetProjection());
}

void GlfwWindow::SetShader(Shader shader)
{
    shader.use();
    shader.setMat4("projection", lens.GetProjection());
    shader.setMat4("view", lens.GetView());
    shader.setMat4("model", lens.GetModel());
}

void GlfwWindow::Restart()
{
    glPrimitiveRestartIndex(0xFFFFFFFFU);
    glEnable(GL_PRIMITIVE_RESTART);
}

void GlfwWindow::MouseMove()
{
    double xpos, ypos;
    glfwGetCursorPos(gameWindow, &xpos, &ypos);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void GlfwWindow::Update()
{
    gametime.UpdateTime(glfwGetTime());
    Clear();
    Projection();
    Restart();
    lens.SetSkyview(camera.GetViewMatrix());
    lens.SetPosition(camera.Position);
}