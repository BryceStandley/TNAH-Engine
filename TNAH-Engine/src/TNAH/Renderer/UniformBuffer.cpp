#include "tnahpch.h"
#include "UniformBuffer.h"
#include "Renderer.h"
#include "RendererAPI.h"
#include "Platform/OpenGL/OpenGLUniformBuffer.h"

namespace tnah {

	Ref<UniformBuffer> UniformBuffer::Create(uint32_t size, uint32_t binding)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:     return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLUniformBuffer>(size, binding);
		}

		TNAH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}


}