#include <iostream>
#include <GL/glew.h>
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
#include "Shader.h"
#include "VertexBuffer.h"

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
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK){ return 1; }
    float triangle_vertices[] = {
        0.5f,  0.5f,  0.0f,     //1
        0.5f, -0.5f,  0.0f,     //2
        -0.5f, -0.5f,  0.0f,    //3
        0.5f,  0.5f,  0.0f,     //1
        -0.5f, -0.5f,  0.0f,    //3
        -0.5f, 0.5f,  0.0f,     //4
        0.5f,  0.5f,  0.0f,    //1
        0.7f,  0.5f,  0.5F,    //5
        0.7f,  -0.5f,  0.5f   //6
    };

    float triangle_vertices2[] = {
        0.5f, -0.5f,  0.0f,     //2
        0.7f,  -0.5f,  0.5f,   //6
        0.5f,  0.5f,  0.0f     //1
    };

    Shader shad("Simple.vert", "Simple.frag");
    if (!shad.Works())
    {
        return 1;
    }
    Shader shad2("Simple.vert", "Simple2.frag");
    if (!shad2.Works())
    {
        return 1;
    }
    VertexBuffer tri(triangle_vertices, (sizeof(triangle_vertices) / sizeof(*triangle_vertices)));
    VertexBuffer tri2(triangle_vertices2, 9);

    GLclampf red = 0.0f;
    GLclampf green = 0.0f;
    GLclampf blue = 0.0f;
    GLclampf alpha = 1.0f;
    float x = -1.0f;
    bool wire = false;
    std::cout << "TV: " << (sizeof(triangle_vertices) / sizeof(*triangle_vertices)) << std::endl;
    while (1)
    {
        //red = (sin(x) + 1) / 2.0;
        //green = (sin(x + 1) + 1) / 2.0;
        //blue = (sin(x + 2) + 1) / 2.0;
        //x += 0.1;
        //std::this_thread::sleep_for(std::chrono::milliseconds(10));

        //glClearColor(red, green, blue, alpha);

        if (a.GameInput())
        {
            if (wire)
                wire = false;
            else if(!wire)
                wire = true;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shad.Start();
        tri.Render();
        shad2.Start();
        tri2.Render();
        a.Buffer();

        if (wire)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        //normal rendering
        else if (!wire)
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


        glfwPollEvents();
    }

    return 0;
}