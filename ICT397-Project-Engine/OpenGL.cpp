#include "OpenGL.h"
#include <thread>

void OpenGL::Render()
{

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

	int state = glfwGetKey(window, GLFW_KEY_E);

	if (state == GLFW_PRESS)
	{
		std::cout << "E pressed" << std::endl;
	}
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
