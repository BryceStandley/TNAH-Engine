#include "tnahpch.h"
#include "TNAH/Renderer/Texture.h"

#include <entt.hpp>

#include "TNAH/Renderer/Image.h"

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

	Texture2D* Texture2D::Load(const std::string& filePath)
	{
		auto* texture = new Image();
		texture->m_Path = filePath;
		
		int width, height, channels;
		if(filePath.find(".png") != std::string::npos || filePath.find(".tga") != std::string::npos)
		{
			// .png was found in the file path, flip vertically on load
			stbi_set_flip_vertically_on_load(true);
		}
		else
		{
			stbi_set_flip_vertically_on_load(false);
		}
		
		texture->m_ImageData = stbi_load(filePath.c_str(), &width, &height, &channels, 0);
		if(!texture->m_ImageData)
		{
			TNAH_CORE_ERROR("STBI Error: {0} with file {1}", stbi_failure_reason(), filePath.c_str());
			TNAH_CORE_ASSERT(texture->m_ImageData, "Failed to load image at path: " + filePath);
		}
		
		texture->m_Width = width;
		texture->m_Height = height;
		texture->m_Channels = channels;

		GLenum internalFormat = 0, dataFormat = 0;
		if (channels == 4)
		{
			internalFormat = GL_RGBA;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			internalFormat = GL_RGB;
			dataFormat = GL_RGB;
		}
		else
		{
			internalFormat = GL_RED;
			dataFormat = GL_RED;
		}

		texture->m_InternalFormat = internalFormat;
		texture->m_DataFormat = dataFormat;
		
		
		return texture;
	}

	Texture2D* Texture2D::Create(uint32_t width, uint32_t height)
	{
		Texture2D* t = nullptr;
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    TNAH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  t =  new OpenGLTexture2D(width, height);
		}

		if(t != nullptr)
		{
			Ref<Texture2D> texture; texture.reset(t);
			Renderer::RegisterTexture(texture);
			return t;
		}

		TNAH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Texture2D* Texture2D::Create(const std::string& path, const std::string& textureName, bool loadFromMemory, void* assimpTexture)
	{
		Texture2D* t = nullptr;
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    TNAH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  t = new OpenGLTexture2D(path, textureName, loadFromMemory, assimpTexture);
		}
		if(t != nullptr)
		{
			Ref<Texture2D> texture; texture.reset(t);
			Renderer::RegisterTexture(texture);
			return t;
		}

		TNAH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
