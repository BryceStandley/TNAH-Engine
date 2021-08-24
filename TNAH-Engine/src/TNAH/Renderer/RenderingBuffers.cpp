#include "tnahpch.h"
#include "TNAH/Renderer/RenderingBuffers.h"

#include "TNAH/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"
#include <glm/glm.hpp>

namespace tnah {

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    TNAH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return new OpenGLVertexBuffer(vertices, size);
		}

		TNAH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	VertexBuffer* VertexBuffer::Create(void* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    TNAH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLVertexBuffer(vertices, size);
		}

		TNAH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
	

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    TNAH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return new OpenGLIndexBuffer(indices, size);
		}

		TNAH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(void* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    TNAH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return new OpenGLIndexBuffer(indices, size);
		}

		TNAH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    TNAH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLIndexBuffer(size);
		}

		TNAH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Framebuffer* Framebuffer::Create(const FramebufferSpecification& spec, uint32_t colorAttachments,
		uint32_t depthAttachments)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    TNAH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLFramebuffer(spec, colorAttachments, depthAttachments);
		}

		TNAH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Framebuffer* Framebuffer::Create(const FramebufferSpecification& spec, uint32_t colorAttachments, std::vector<ColorAttachmentSpecs> colorSpecs)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    TNAH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLFramebuffer(spec, colorAttachments, colorSpecs);
		}

		TNAH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Framebuffer* Framebuffer::Create(const FramebufferSpecification& spec, const RenderbufferSpecification& renderSpec)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    TNAH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLFramebuffer(spec, renderSpec);
		}

		TNAH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Renderbuffer* Renderbuffer::Create(const RenderbufferSpecification& renderSpec)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    TNAH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLRenderBuffer(renderSpec);
		}

		TNAH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
