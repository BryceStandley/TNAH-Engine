#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/*Test includes and defines to be removed*/
#include <cmath>
#include <chrono>
#include <thread>
#include <string>
#include <vector>

#include "GameManager.h"
#include "Singleton.h"
#include "OpenGL.h"
#include "GlewInput.h"
#include "GlewWindow.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "Terrain.h"
#include "glm/glm.hpp"

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
    Terrain h;
    h.LoadHeightFeild("height128.raw", 128);
    a.Init("ICT397 Game Engine", 1000, 1000);
    win = &a;
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK){ return 1; }

    Shader shad("Simple.vert", "Simple.frag");
    if (!shad.Works())
    {
        return 1;
    }

    bool wire = false;

    std::vector<glm::vec3> thingo;
    std::vector<int> grid;
    int num = 0;
    for (int z = 0; z < h.size-1; z++)
    {
        for (int x = 0; x < h.size; x++) {

            glm::vec3 g;
            g.x = (float)x * h.sX; 
            g.y = h.getHeight(x, z);
            g.z = (float)z * h.sZ;
            thingo.push_back(g);
            grid.push_back(z * h.size + (x + 1));
            grid.push_back(z * h.size + (x + 1) + h.size);
            if (x == h.size && z != h.size - 1)
            {
                grid.push_back(z * h.size + 2 * h.size);
                grid.push_back((z + 1) * h.size + 1);
            }
        }
    }

    VertexBuffer terrain(thingo, grid);

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
        //shad.Start();
        //tri.Render();
        //shad2.Start();
        //tri2.Render();
        terrain.Render();
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