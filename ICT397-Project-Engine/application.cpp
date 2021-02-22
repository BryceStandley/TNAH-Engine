#include <iostream>
#include <GLFW/glfw3.h>

/*Test includes and defines to be removed*/
#include <cmath>
#include <chrono>
#include <thread>
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
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "ICT397 Project", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    std::cout << "GLFW Started!" << std::endl;

    glfwSetKeyCallback(window, key_callback);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    GLclampf red = 0.0f;
    GLclampf green = 0.0f;
    GLclampf blue = 0.0f;
    GLclampf alpha = 1.0f;
    float x = -1.0f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */

        /*Small Background Colour changer for GLFW test*/
        /*Remove below to clear Test from file*/
        red = (sin(x) + 1) / 2.0;
        green = (sin(x+1) + 1) / 2.0;
        blue = (sin(x+2) + 1) / 2.0;
        x += 0.1;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        glClearColor(red, green, blue, alpha);
        /*Remove Above to clear test from file*/


        glClear(GL_COLOR_BUFFER_BIT);
        

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}