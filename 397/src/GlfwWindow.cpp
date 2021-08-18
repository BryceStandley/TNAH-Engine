#include "tnahpch.h"
#include "GlfwWindow.h"
#include "Enemy.h"

namespace tnah {
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

        TNAH_CORE_INFO("GLFW Started!");
        SettingsManager::GetInstance()->windowSize = glm::vec2(w, h);

        glm::vec3 l((256 * 12) / 2.0, 100.0f, (256 * 12) / 2.0);
        lightPos = l;
        Camera c((52.0f * 12) / 2, 4.0f, (52.0f * 12) / 2, 0.0f, 1.0f, 0.0f, 90.0f, -37.0f);
        camera = c;

        /* Make the window's context current */
        glfwMakeContextCurrent(gameWindow);

        ///locks the cursor to the window
        glfwSetInputMode(gameWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        Debugger::GetInstance()->windowRef = gameWindow;
        SettingsManager::GetInstance()->windowRef = gameWindow;


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
        MainMenuGUI* mainMenuGui = MainMenuGUI::GetInstance();
        if (!mainMenuGui->displayMainMenu)
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
                if (Debugger::GetInstance()->drawDebugPanel)
                {
                    camera.disabled = true;
                    glfwSetInputMode(gameWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                }
                else
                {
                    camera.disabled = false;
                    glfwSetInputMode(gameWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                }
            }
        }

        if (!mainMenuGui->mainMenuClosed)
        {
            if (mainMenuGui->displayMainMenu || mainMenuGui->displaySettings || mainMenuGui->displayDifficulty || mainMenuGui->displayControls)
            {
                camera.disabled = true;
                glfwSetInputMode(gameWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }
            else if (!mainMenuGui->displayMainMenu)
            {
                glfwSetInputMode(gameWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                camera.disabled = false;
                mainMenuGui->mainMenuClosed = true;
            }
        }
        else if (mainMenuGui->displayDeathScreen)
        {
            camera.disabled = true;
            glfwSetInputMode(gameWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }


        if ((glfwGetKey(gameWindow, gameInput.pause) == GLFW_PRESS) && canPressPauseButton && !mainMenuGui->displaySettings && !mainMenuGui->displayMainMenu && !mainMenuGui->displayControls && !mainMenuGui->displayDeathScreen)
        {
            canPressPauseButton = false;
            mainMenuGui->canDisplayPauseMenu = !mainMenuGui->canDisplayPauseMenu;

            if (mainMenuGui->canDisplayPauseMenu)
            {
                mainMenuGui->DisplayPauseMenu();
                camera.disabled = true;
                Debugger::GetInstance()->drawDebugPanel = false;
                glfwSetInputMode(gameWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }
            else if (!mainMenuGui->canDisplayPauseMenu)
            {
                mainMenuGui->HideMenus();
                glfwSetInputMode(gameWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                camera.disabled = false;

            }

        }

        if (glfwGetKey(gameWindow, gameInput.pause) == GLFW_RELEASE)
        {
            canPressPauseButton = true;
        }

        if (mainMenuGui->quitClicked)
        {
            //the quit button was pressed in the pause menu, we should quit the application
            glfwSetWindowShouldClose(gameWindow, true);
        }

        if (!exitDisplay && !mainMenuGui->endScreenButtonClicked)
        {

            if (!mainMenuGui->displayingAMenu)
            {
                float speed = singleton<Manager>::getInstance().speed;

                if (glfwGetKey(gameWindow, gameInput.forward) == GLFW_PRESS)
                {
                    fwdUp = false;
                    isPlayerMoving = true;
                    camera.ProcessKeyboard(FORWARD, deltaTime * speed);
                }
                if (glfwGetKey(gameWindow, gameInput.back) == GLFW_PRESS)
                {
                    dwnUp = false;
                    isPlayerMoving = true;
                    camera.ProcessKeyboard(BACKWARD, deltaTime * speed);
                }
                if (glfwGetKey(gameWindow, gameInput.left) == GLFW_PRESS)
                {
                    lftUp = false;
                    isPlayerMoving = true;
                    camera.ProcessKeyboard(LEFT, deltaTime * speed);
                }
                if (glfwGetKey(gameWindow, gameInput.right) == GLFW_PRESS)
                {
                    rhtUp = false;
                    isPlayerMoving = true;
                    camera.ProcessKeyboard(RIGHT, deltaTime * speed);
                }

                if (glfwGetKey(gameWindow, gameInput.forward) == GLFW_RELEASE && !fwdUp)
                {
                    fwdUp = true;
                    if (!dwnUp || !lftUp || !rhtUp)
                    {
                        isPlayerMoving = true;
                    }
                    else
                    {
                        isPlayerMoving = false;
                    }
                }
                if (glfwGetKey(gameWindow, gameInput.back) == GLFW_RELEASE && !dwnUp)
                {
                    dwnUp = true;
                    if (!fwdUp || !lftUp || !rhtUp)
                    {
                        isPlayerMoving = true;
                    }
                    else
                    {
                        isPlayerMoving = false;
                    }
                }
                if (glfwGetKey(gameWindow, gameInput.left) == GLFW_RELEASE && !lftUp)
                {
                    lftUp = true;
                    if (!dwnUp || !fwdUp || !rhtUp)
                    {
                        isPlayerMoving = true;
                    }
                    else
                    {
                        isPlayerMoving = false;
                    }
                }
                if (glfwGetKey(gameWindow, gameInput.right) == GLFW_RELEASE && !rhtUp)
                {
                    rhtUp = true;
                    if (!dwnUp || !lftUp || !fwdUp)
                    {
                        isPlayerMoving = true;
                    }
                    else
                    {
                        isPlayerMoving = false;
                    }
                }




                if (wireDisplay) { glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); }
                else { glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); }



                if ((glfwGetMouseButton(gameWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS &&
                    !mainMenuGui->displayingAMenu && !Debugger::GetInstance()->drawDebugPanel)) {
                    fireWeapon = true;
                }

                if (glfwGetMouseButton(gameWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
                    fireWeapon = false;
                }
            }
        }
        else
        {
            if ((glfwGetMouseButton(gameWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS))
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

    void GlfwWindow::ToggleFullScreen(bool change)
    {
        glfwSetWindowMonitor(gameWindow, change ? glfwGetPrimaryMonitor() : NULL, 0, 0, windowSize.x, windowSize.y, GLFW_DONT_CARE);
    }
}