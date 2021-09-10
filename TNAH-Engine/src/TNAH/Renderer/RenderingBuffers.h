#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "TNAH/Core/Ref.h"

namespace tnah {

	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool,
		UInt
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:    return 4;
			case ShaderDataType::Float2:   return 4 * 2;
			case ShaderDataType::Float3:   return 4 * 3;
			case ShaderDataType::Float4:   return 4 * 4;
			case ShaderDataType::Mat3:     return 4 * 3 * 3;
			case ShaderDataType::Mat4:     return 4 * 4 * 4;
			case ShaderDataType::UInt:		return 4;
			case ShaderDataType::Int:      return 4;
			case ShaderDataType::Int2:     return 4 * 2;
			case ShaderDataType::Int3:     return 4 * 3;
			case ShaderDataType::Int4:     return 4 * 4;
			case ShaderDataType::Bool:     return 1;
			case ShaderDataType::None: break;
		default: break;
		}

		TNAH_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		uint32_t Size;
		size_t Offset;
		bool Normalized;

		BufferElement() = default;

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{
		}

		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
				case ShaderDataType::Float:   return 1;
				case ShaderDataType::Float2:  return 2;
				case ShaderDataType::Float3:  return 3;
				case ShaderDataType::Float4:  return 4;
				case ShaderDataType::Mat3:    return 3; // 3* float3
				case ShaderDataType::Mat4:    return 4; // 4* float4
				case ShaderDataType::UInt:		return 3;
				case ShaderDataType::Int:     return 1;
				case ShaderDataType::Int2:    return 2;
				case ShaderDataType::Int3:    return 3;
				case ShaderDataType::Int4:    return 4;
				case ShaderDataType::Bool:    return 1;
				default: break;
			}

			TNAH_CORE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}
	};

	class VertexBufferLayout
	{
	public:
		VertexBufferLayout() {}

		VertexBufferLayout(std::initializer_list<BufferElement> elements)
			: m_Elements(elements)
		{
			CalculateOffsetsAndStride(m_Elements, m_Stride);
		}

		uint32_t GetStride() const { return m_Stride; }
		const std::vector<BufferElement>& GetElements() const { return m_Elements; }
		std::vector<BufferElement>& GetElements() { return m_Elements; }
		void SetStride(const uint32_t& stride) { m_Stride = stride; }
		
		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
	private:
		static void CalculateOffsetsAndStride(std::vector<BufferElement>& elements, uint32_t& stride)
		{
			size_t offset = 0;
			stride = 0;
			for (auto& element : elements)
			{
				element.Offset = offset;
				offset += element.Size;
				stride += element.Size;
			}
		}
	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;
		friend class VertexBuffer;
	};

	enum class DrawType
	{
		STREAM, STATIC, DYNAMIC
	};

	enum class TypeMode
	{
		DRAW, READ, COPY
	};

	struct BufferDrawMode
	{
		DrawType Type = DrawType::STATIC;
		TypeMode Mode = TypeMode::DRAW;
	};

	class VertexBuffer : public RefCounted
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual void SetData(uint32_t size, const void* data, DrawType type = DrawType::STATIC, TypeMode mode = TypeMode::DRAW) const = 0;

		virtual void CreateLayout(uint32_t location, BufferElement element, uint32_t stride) = 0;
		virtual void DisableLayout(uint32_t location) = 0;
		
		virtual const VertexBufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const VertexBufferLayout& layout) = 0;

		
		static bool CheckIntShaderDataTypes(const BufferElement& element);
		static Ref<VertexBuffer> Create();
		static Ref<VertexBuffer> Create(float* verticies, uint32_t size);
		static Ref<VertexBuffer> Create(void* verticies, uint32_t size);
	};

	enum class IndexBufferDataType
	{
		Byte = 0, Short = 1, Int = 2
	};
	
	// Currently tnah only supports 32-bit index buffers
	class IndexBuffer : public RefCounted
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual int GetDataType() const = 0;
		virtual uint32_t GetCount() const = 0;

		static Ref<IndexBuffer> Create(uint32_t* indices, uint32_t size);
		static Ref<IndexBuffer> Create(void* indices, uint32_t size);

		/*
		 * Creates a empty index buffer with a size
		 */
		static Ref<IndexBuffer> Create(uint32_t size);
	};

	enum class RenderbufferFormat
	{
		Depth16, Depth24, Depth32F,
		Depth24_Stencil8, Depth32F_Stencil8,
		Stencil8
		
	};
	
	struct RenderbufferSpecification
	{
		uint32_t Width = 0; 
		uint32_t Height = 0;
		RenderbufferFormat Format = RenderbufferFormat::Depth24_Stencil8;
		uint32_t Samples = 1;
		bool SwapChainTarget = false;
		bool IsValid = true;

		RenderbufferSpecification() = default;
		RenderbufferSpecification(uint32_t valid)
			:IsValid(false) {}
	};
	
	enum class FramebufferFormat
	{
		SDR, HDR
	};
	
	struct FramebufferSpecification
	{
		uint32_t Width = 0;
		uint32_t Height = 0;
		FramebufferFormat Format = FramebufferFormat::SDR;
		uint32_t Samples = 1;
		bool SwapChainTarget = false;
	};

	struct ColorAttachmentSpecs
	{
		uint32_t Width = 0;
		uint32_t Height = 0;
		FramebufferFormat Format = FramebufferFormat::SDR;

	};

	/**
	 *	Defines the different attachment draw modes.
	 */
	enum class FramebufferDrawMode
	{
		Depth, Color, Stencil, Render
	};
	
	class Framebuffer : public RefCounted
	{
	public:
		virtual ~Framebuffer() = default;
		virtual const FramebufferSpecification& GetSpecification() const = 0;

		virtual void DrawToNext() = 0;
		virtual uint32_t GetColorAttachment() const = 0;
		virtual uint32_t GetColorAttachment(uint32_t attachmentNumber) const = 0;
		virtual uint32_t GetTotalColorAttachments() const = 0;

		virtual uint32_t GetDepthAttachmentID() const = 0;
		virtual uint32_t GetDepthAttachmentID(uint32_t attachmentNumber) const = 0;
		virtual uint32_t GetTotalDepthAttachments() const = 0;

		virtual uint32_t GetRenderBufferID() const = 0;
		virtual void SetRenderbufferSpecification(uint32_t bufferSlot, const RenderbufferSpecification& spec) = 0;
		
		virtual uint32_t GetRendererID() const = 0;
		
		virtual void Bind(uint32_t attachmentSlot = 0) = 0;
		virtual void Unbind() = 0;
		virtual void Rebuild(const FramebufferSpecification& spec) = 0;
		
		static Ref<Framebuffer> Create(const FramebufferSpecification& spec, uint32_t colorAttachments = 1, uint32_t depthAttachments = 1);
		static Ref<Framebuffer> Create(const FramebufferSpecification& spec, uint32_t colorAttachments, std::vector<ColorAttachmentSpecs> colorSpecs);
		static Ref<Framebuffer> Create(const FramebufferSpecification& spec, const RenderbufferSpecification& renderSpec);
		
		virtual void SelectDrawToBuffer(const FramebufferDrawMode& mode = FramebufferDrawMode::Color, uint32_t attachmentNumber = 0) = 0;
		virtual int GetFormatFromSpec(const FramebufferSpecification& spec) = 0;
	};

	class Renderbuffer : public RefCounted
	{
	public:
		virtual ~Renderbuffer() = default;

		virtual uint32_t GetRendererID() const = 0;
		
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void Rebuild(const RenderbufferSpecification& spec) = 0;
		virtual void AttachToFramebuffer() = 0;

		static Ref<Renderbuffer> Create(const RenderbufferSpecification& spec);
		virtual int GetFormatFromSpecification(const RenderbufferSpecification& spec) = 0;
		virtual int GetFramebufferFormatFromSpecification(const RenderbufferSpecification& spec) = 0;
	private:
		

		friend class Framebuffer;
		
	};

}
