#include "tnahpch.h"
#include "TNAH/Renderer/Texture.h"

#include "TNAH/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace tnah {
	Texture2D* Texture2D::Create(ImageFormat format, uint32_t width, uint32_t height, const void* data, TextureProperties properties)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    TNAH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLTexture2D(format, width, height, data, properties);
		}

		TNAH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Texture2D* Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    TNAH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return new OpenGLTexture2D(width, height);
		}

		TNAH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Texture2D* Texture2D::Create(const std::string& path, const std::string& textureName, bool loadFromMemory, void* assimpTexture)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    TNAH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return new OpenGLTexture2D(path, textureName, loadFromMemory, assimpTexture);
		}

		TNAH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}