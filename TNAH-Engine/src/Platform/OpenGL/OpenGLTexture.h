#pragma once

#include "TNAH/Renderer/Texture.h"

#include <glad/glad.h>

namespace tnah {

	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(ImageFormat format, uint32_t width, uint32_t height, const void* data, TextureProperties properties);
		OpenGLTexture2D(uint32_t width, uint32_t height);
		OpenGLTexture2D(const std::string& path, const std::string& textureName = "", bool loadFromMemory = false, void* assimpTexture = nullptr);
		~OpenGLTexture2D() override;

		unsigned char* LoadFromMemory(const std::string& path, void* assimpTexture = nullptr);

		uint32_t GetWidth() const override { return m_Width;  }
		uint32_t GetHeight() const override { return m_Height; }
		uint32_t GetRendererID() const override { return m_RendererID; }
		
		void SetData(void* data, uint32_t size) override;

		void Bind(uint32_t slot) const override;
		void Bind() const override;
		
		ktxTexture* GetKtxData() const override { return nullptr; }
		unsigned char* GetImageData() const override { return nullptr; }
		void Free() override {}
		void Free(void* data) override {}
	};

	class OpenGLTexture3D : public Texture3D
	{
	public:
		OpenGLTexture3D(const std::vector<std::string>& paths, const std::string& textureName = "");
		OpenGLTexture3D(const Texture3DProperties& properties, const std::string& textureName = "");
		~OpenGLTexture3D() override;

		uint32_t GetWidth() const override { return m_Width;  }
		uint32_t GetHeight() const override { return m_Height; }
		uint32_t GetRendererID() const override { return m_RendererID; }
		
		void SetData(void* data, uint32_t size) override;

		void Bind(uint32_t slot) const override;
		void Bind() const override;
		ktxTexture* GetKtxData() const override { return nullptr; }
		unsigned char* GetImageData() const override { return nullptr; }
	};

}
