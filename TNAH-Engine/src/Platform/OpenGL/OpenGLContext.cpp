#include "tnahpch.h"
#include "Platform/OpenGL/OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace tnah {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		TNAH_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		 

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		TNAH_CORE_ASSERT(status, "Failed to initialize Glad!");

		TNAH_CORE_INFO("OpenGL Info:");
		TNAH_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		TNAH_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		TNAH_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

		TNAH_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "tnah requires at least OpenGL version 4.5!");
	}

	void OpenGLContext::SwapBuffers()
	{
		 

		glfwSwapBuffers(m_WindowHandle);
	}

}
