#include <iostream>
#include <GLFW/glfw3.h>

/*Test includes and defines to be removed*/
#include <cmath>
#include <chrono>
#include <thread>

#include "GameManager.h"
#include "Singleton.h"
#include "OpenGL.h"

#define PI 3.14159265358

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        std::cout << "GLFW Closing!" << std::endl;
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}




/**
* Basic setup for defult GLFW Window
*/
int main(void)
{
    GameManager* gameManager = Singleton<GameManager>::getInstance();
    OpenGL render;
    gameManager->gameRenderer = &render;

    if (!gameManager->gameRenderer->Init())
    {
        return -1;
    }


    //glfwSetKeyCallback(window, key_callback);

    /* Make the window's context current */

    /* Loop until the user closes the window */
    while (1)
    {
        gameManager->gameRenderer->Update();
    }
    
    return 0;
}