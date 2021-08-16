#pragma once

#define STBI_FAILURE_USERMSG
#include "stb_image.h"
#include <string>

#include "TNAH/Core/Core.h"

namespace tnah {

	enum class ImageFormat
	{
		None = 0,
		RED32F,
		RGB,
		RGBA,
		RGBA16F,
		RGBA32F,
		RG16F,
		RG32F,

		SRGB,

		DEPTH32F,
		DEPTH24STENCIL8,

		// Defaults
		Depth = DEPTH24STENCIL8,
	};

	enum class ImageUsage
	{
		None = 0,
		Texture,
		Attachment,
		Storage
	};

	enum class TextureWrap
	{
		None = 0,
		Clamp,
		Repeat
	};

	enum class TextureFilter
	{
		None = 0,
		Linear,
		Nearest
	};

	enum class TextureType
	{
		None = 0,
		Texture2D,
		TextureCube
	};

	struct TextureProperties
	{
		TextureWrap SamplerWrap = TextureWrap::Repeat;
		TextureFilter SamplerFilter = TextureFilter::Linear;
		bool GenerateMips = true;
		bool SRGB = false;
		bool Storage = false;
	};

	struct ImageSpecification
	{
		ImageFormat Format = ImageFormat::RGBA;
		ImageUsage Usage = ImageUsage::Texture;
		uint32_t Width = 1;
		uint32_t Height = 1;
		uint32_t Mips = 1;
		uint32_t Layers = 1;
		bool Deinterleaved = false;

		std::string DebugName;
	};

	
	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const { return m_Width; }
		virtual uint32_t GetHeight() const { return m_Height; }
		virtual bool IsLoaded() const { return m_Loaded; }
		virtual std::string GetPath() const { return m_Path; }
		virtual std::string GetName() const { return m_Name; }
		virtual unsigned char* GetImageData() const { return m_ImageData; }

		bool m_Loaded = false;
		std::string m_Path = "";
		std::string m_Name = "";
		uint32_t m_Width = 0, m_Height = 0;
		int m_Channels = 0, m_InternalFormat = 0, m_DataFormat = 0;
		unsigned char* m_ImageData = nullptr;
		TextureProperties m_Properties = TextureProperties();
	};

	class Texture2D : public Texture
	{
	public:
		static Texture2D* Create(ImageFormat format, uint32_t width, uint32_t height, const void* data, TextureProperties properties);

		/**
		 * @brief Loads image to memory. NOTE this does NOT load a API specific texture and pass it to the GPU
		 */
		static Texture2D* Load(const std::string& filePath);
		
		static Texture2D* Create(uint32_t width, uint32_t height);
		static Texture2D* Create(const std::string& path, const std::string& textureName = "", bool loadFromMemory = false, void* assimpTexture = nullptr);

		virtual uint32_t GetRendererID() const { return m_RendererID; }
		virtual uint32_t GetTextureSlot() const { return m_Slot; }
		virtual void SetData(void* data, uint32_t size) = 0;
		virtual void Bind(uint32_t slot) const = 0;
		virtual void Bind() const = 0;

		uint32_t m_RendererID;
		uint32_t m_Slot;
		
	};

}