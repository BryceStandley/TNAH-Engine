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