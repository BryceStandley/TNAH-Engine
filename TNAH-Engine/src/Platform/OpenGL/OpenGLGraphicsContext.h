#pragma once

#include "TNAH/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace tnah {

	class OpenGLGraphicsContext : public GraphicsContext
	{
	public:
		OpenGLGraphicsContext(GLFWwindow* window);

		void Init() override;
		void SwapBuffers() override;
	private:
		GLFWwindow* m_Window;
	};


}
