#include "tnahpch.h"
#include "TNAH/Renderer/Framebuffer.h"

#include "TNAH/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace tnah {
	
	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    TNAH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLFramebuffer>(spec);
		}

		TNAH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}

