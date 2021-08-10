#include "tnahpch.h"
#include "Platform/OpenGL/OpenGLTexture.h"

#include <stb_image.h>

#include "TNAH/Renderer/Renderer.h"

namespace tnah {
	
	OpenGLTexture2D::OpenGLTexture2D(ImageFormat format, uint32_t width, uint32_t height, const void* data, TextureProperties properties)
		: m_Width(width), m_Height(height), m_Properties(properties)
	{
		TNAH_CORE_WARN("Generating a texture at runtime isn't implimented yet!");
	}

	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
		: m_Width(width), m_Height(height)
	{
		m_InternalFormat = GL_RGBA8;
		m_DataFormat = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
	{
		m_Path = path;
		int width, height, channels;
		if(path.find(".png") != std::string::npos)
		{
			// .png was found in the file path, flip vertically on load
			stbi_set_flip_vertically_on_load(true);
		}
		else
		{
			stbi_set_flip_vertically_on_load(false);
		}

		unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		TNAH_CORE_ASSERT(data, "Failed to load image!");
		
		m_Width = width;
		m_Height = height;

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

		m_InternalFormat = internalFormat;
		m_DataFormat = dataFormat;

		TNAH_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");

		glGenTextures(1, &m_RendererID);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		glTexImage2D(GL_TEXTURE_2D, 0, (int)m_InternalFormat, m_Width, m_Height, 0, m_InternalFormat, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(data);
		m_Loaded = true;
		m_Slot = Renderer::GetAndIncrementTextureSlot();
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::SetData(void* data, uint32_t size)
	{
		uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;
		TNAH_CORE_ASSERT(size == m_Width * m_Height * bpp, "Data must be entire texture!");
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		if(slot < 0) {slot = 0;}
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
	}

	void OpenGLTexture2D::Bind() const
	{
		glActiveTexture(GL_TEXTURE0 + m_Slot);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
	}
}
