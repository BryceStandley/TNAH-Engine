#include "tnahpch.h"
#include "TNAH/Renderer/GraphicsContext.h"

#include "TNAH/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace tnah {

	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    TNAH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		TNAH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}