#include <iostream>
#include <GLFW/glfw3.h>

/*Test includes and defines to be removed*/
#include <cmath>
#include <chrono>
#include <thread>
#include <string>

#include "GameManager.h"
#include "Singleton.h"
#include "OpenGL.h"
#include "GlewInput.h"
#include "GlewWindow.h"

#define PI 3.14159265358

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        std::cout << "GLFW Closing!" << std::endl;
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

int main(void)
{
    Window* win;
    GlewWindow a;
    a.Init("ICT397 Game Engine", 480, 640);
    win = &a;

    GLclampf red = 0.0f;
    GLclampf green = 0.0f;
    GLclampf blue = 0.0f;
    GLclampf alpha = 1.0f;
    float x = -1.0f;

    while (1)
    {
        red = (sin(x) + 1) / 2.0;
        green = (sin(x + 1) + 1) / 2.0;
        blue = (sin(x + 2) + 1) / 2.0;
        x += 0.1;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        glClearColor(red, green, blue, alpha);

        if (a.GameInput())
            break;

        glClear(GL_COLOR_BUFFER_BIT);

        a.Buffer();

        glfwPollEvents();
    }

    return 0;
}