#pragma once

#define STBI_FAILURE_USERMSG
#include "stb_image.h"
#include <string>
#pragma warning(push, 0)
#include <ktx.h>
#pragma warning(pop)

#include "TNAH/Core/Core.h"
#include "TNAH/Core/FileStructures.h"
#include "TNAH/Core/Ref.h"

namespace tnah {

	enum class ImageLoadFormat
	{
		KTX, STB
	};
	
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
		Texture3D
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

	class Texture3DProperties
	{
	public:
		Texture3DProperties() = default;
		Texture3DProperties(Resource front,Resource back, Resource left, Resource right, Resource top, Resource bottom)
			:Front(front), Back(back), Left(left), Right(right), Top(top), Bottom(bottom) {}
		Texture3DProperties(Resource cubemap)
			:Cubemap(cubemap)
		{
			if(Cubemap.Type.Type == RType::Image && Cubemap.FileName.Extension.find("ktx") != std::string::npos)
			{
				IsKtx = true;
			}
		}
		
		Resource Cubemap;
		bool IsKtx = false;
		Resource Front;
		Resource Back;
		Resource Left;
		Resource Right;
		Resource Top;
		Resource Bottom;
	};

	enum class CubemapImageFormat
	{
		Column, Row, Vertical, Horizontal
	};
	
	struct CubemapInformation
	{
		uint32_t CubeSize = 1;
		CubemapImageFormat Format = CubemapImageFormat::Column;
	};


	
	class Texture : public RefCounted
	{
	public:
		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const { return m_Width; }
		virtual uint32_t GetHeight() const { return m_Height; }
		virtual bool IsLoaded() const { return m_Loaded; }
		virtual std::string GetPath() const { return m_TextureResource.RelativeDirectory; }
		virtual std::string GetName() const { return m_TextureResource.FileName.FileName; }
		virtual ImageLoadFormat GetLoadFormat() const { return m_LoadFormat; }

		/**
		 * @brief Returns a KTX Texture or nullptr if invalid
		 */
		virtual ktxTexture* GetKtxData() const = 0;

		/**
		 * @brief Returns a unsigned char of image data or nullptr if invalid
		 */
		virtual unsigned char* GetImageData() const = 0;

		Resource m_TextureResource;
		
		bool m_Loaded = false;
		uint32_t m_Width = 0, m_Height = 0;
		uint32_t m_Channels = 0, m_InternalFormat = 0, m_DataFormat = 0;
		void* m_ImageData = nullptr;
		ImageLoadFormat m_LoadFormat = ImageLoadFormat::STB;
		TextureProperties m_Properties = TextureProperties();
		CubemapInformation m_CubemapInformation = CubemapInformation();
	};
	
	class Texture2D : public Texture
	{
	public:
		
		static Ref<Texture2D> Create(ImageFormat format, uint32_t width, uint32_t height, const void* data, TextureProperties properties);

		/**
		 * @brief Loads a image to memory
		 * @warning Image must be cleared by the user with tnah::Texture2D::Free()
		 * @param filePath absolute or relative file path to image
		 * @param  flipOnLoad Flips the image on load (STB ONLY)
		 * @param isCubemap Tells the loader the provided image is a cubemap (KTX ONLY}
		 */
		static Ref<Texture2D> LoadImageToMemory(const std::string& filePath, const bool& flipOnLoad = false, const bool& isCubemap = false);
		
		
		
		static Ref<Texture2D> Create(uint32_t width, uint32_t height);
		static Ref<Texture2D> Create(const std::string& path, const std::string& textureName = "", bool loadFromMemory = false, void* assimpTexture = nullptr);

		virtual void Free() = 0;
		virtual void Free(void* data) = 0;
		virtual uint32_t GetRendererID() const { return m_RendererID; }
		virtual uint32_t GetTextureSlot() const { return m_Slot; }
		virtual void SetData(void* data, uint32_t size) = 0;
		virtual void Bind(uint32_t slot) const = 0;
		virtual void Bind() const = 0;

		uint32_t m_RendererID;
		uint32_t m_Slot;
	private:
		static Ref<Texture2D> LoadKTXImage(const std::string& filePath, const bool& isKtx2 = false);
		static std::string KtxErrorReason(const int& ktxError);
		static Ref<Texture2D> LoadSTBiImage(const std::string& filePath, const bool& flipOnLoad = false);
		static CubemapInformation FindCubemapInfo(Ref<Texture2D> texture);
	};

	class Texture3D : public Texture
	{
	public:
		static Ref<Texture3D> Create(const std::vector<std::string>& paths, const std::string& textureName = "");
		static Ref<Texture3D> Create(const Texture3DProperties& properties, const std::string& textureName = "Cubemap");
		
		virtual uint32_t GetRendererID() const { return m_RendererID; }
		virtual uint32_t GetTextureSlot() const { return m_Slot; }
		virtual void SetData(void* data, uint32_t size) = 0;
		virtual void Bind(uint32_t slot) const = 0;
		virtual void Bind() const = 0;

		uint32_t m_RendererID;
		uint32_t m_Slot;
		
	};

}
