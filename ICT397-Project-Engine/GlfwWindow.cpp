#include "GlfwWindow.h"
#include "Enemy.h"

void GlfwWindow::Init(std::string title, int h, int w)
{
    //Store the window size in a vec 2 for gui refrences
    windowSize = glm::vec2(w, h);

    //Set the GLFW Open GL Context to version 3.2
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    gameWindow = glfwCreateWindow(w, h, title.c_str(), NULL, NULL);
    if (!gameWindow)
    {
        glfwTerminate();
    }

    std::cout << "GLFW-WINDOW::INFO::GLFW Started!" << std::endl;

    glm::vec3 l(0.0, 0.0f, 0.0f);
    lightPos = l;
    Camera c(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 90.0f, -37.0f);
    camera = c;

    /* Make the window's context current */
    glfwMakeContextCurrent(gameWindow);

    ///locks the cursor to the window
    glfwSetInputMode(gameWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    Debugger::GetInstance()->windowRef = gameWindow;

    
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

void GlfwWindow::GameInput(float deltaTime)
{
    if ((glfwGetKey(gameWindow, gameInput.exit) == GLFW_PRESS) && canPressExitDisplay)
    {
        canPressExitDisplay = false;
        exitDisplay = !exitDisplay;

        //Making sure the debugger closes on the exit screen display
        Debugger::GetInstance()->drawDebugPanel = false;
    }

    if (glfwGetKey(gameWindow, gameInput.exit) == GLFW_RELEASE)
    {
        canPressExitDisplay = true;
    }

    if ((glfwGetKey(gameWindow, gameInput.toggle) == GLFW_PRESS) && canPressWireDisplay)
    {
        canPressWireDisplay = false;
        wireDisplay = !wireDisplay;
    }

    if (glfwGetKey(gameWindow, gameInput.toggle) == GLFW_RELEASE)
    {
        canPressWireDisplay = true;
    }

    if (glfwGetKey(gameWindow, gameInput.debug) == GLFW_RELEASE)
    {
        canPressDebugDisplay = true;
    }

    if ((glfwGetKey(gameWindow, gameInput.debug) == GLFW_PRESS) && canPressDebugDisplay)
    {
        canPressDebugDisplay = false;
        Debugger::GetInstance()->drawDebugPanel = !Debugger::GetInstance()->drawDebugPanel;
        if(Debugger::GetInstance()->drawDebugPanel)
        {
            glfwSetInputMode(gameWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
        else
        {
            glfwSetInputMode(gameWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }

    }

    if (!exitDisplay)
    {
        float speed = singleton<Manager>::getInstance().speed;

        if (glfwGetKey(gameWindow, gameInput.foward) == GLFW_PRESS)
            camera.ProcessKeyboard(FORWARD, deltaTime * speed);
        if (glfwGetKey(gameWindow, gameInput.back) == GLFW_PRESS)
            camera.ProcessKeyboard(BACKWARD, deltaTime * speed);
        if (glfwGetKey(gameWindow, gameInput.left) == GLFW_PRESS)
            camera.ProcessKeyboard(LEFT, deltaTime * speed);
        if (glfwGetKey(gameWindow, gameInput.right) == GLFW_PRESS)
            camera.ProcessKeyboard(RIGHT, deltaTime * speed);
        if(wireDisplay){glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);}
        else if (!wireDisplay){glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);}

        if ((glfwGetMouseButton(gameWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS))
        {
            fireWeapon = true;
        }

        if (glfwGetMouseButton(gameWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
        {
            fireWeapon = false;
        }
    }
    else
    {
        if (glfwGetMouseButton(gameWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(gameWindow, true);

        }
    }



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

void GlfwWindow::Restart()
{
    glPrimitiveRestartIndex(0xFFFFFFFFU);
    glEnable(GL_PRIMITIVE_RESTART);
}

void GlfwWindow::MouseMove()
{
    //if (!exitDisplay)
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
    lens.SetRotation(glm::vec3(camera.Yaw, camera.Pitch, 0));
    lens.SetForward(camera.Front);
}

bool GlfwWindow::Running()
{
    return glfwWindowShouldClose(gameWindow);
}