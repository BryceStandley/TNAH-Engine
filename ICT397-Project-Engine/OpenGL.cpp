#include "OpenGL.h"
#include <thread>

void OpenGL::Render()
{

}

bool OpenGL::Init()
{
	if (!glfwInit())
		return false;
	else
	{
		window = glfwCreateWindow(640, 480, "ICT397 Project", NULL, NULL);
		if (!window)
		{
			glfwTerminate();
			return false;
		}
		std::cout << "GLFW Started!" << std::endl;
		glfwMakeContextCurrent(window);
		return true;
	}
}
void OpenGL::Update()
{
    /* Render here */

    /*Small Background Colour changer for GLFW test*/
    /*Remove below to clear Test from file*/
    red = (sin(x) + 1) / 2.0;
    green = (sin(x + 1) + 1) / 2.0;
    blue = (sin(x + 2) + 1) / 2.0;
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
void OpenGL::Terminate()
{
	glfwTerminate();
}
