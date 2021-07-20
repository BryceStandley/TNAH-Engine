#pragma once

#include "TNAH/Renderer/GraphicsContext.h"

class GLFWwindow;

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
