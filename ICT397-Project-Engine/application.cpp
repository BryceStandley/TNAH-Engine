#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/*Test includes and defines to be removed*/
#include <cmath>
#include <chrono>
#include <thread>
#include <string>
#include <vector>

#include "Engine.h"
#include "GameManager.h"
#include "OpenGL.h"
#include "GlewInput.h"
#include "GlewWindow.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "Terrain.h"
#include "glm/glm.hpp"

#define PI 3.14159265358

int main(void)
{
    Engine e;
    e.Run();

    return 0;
}