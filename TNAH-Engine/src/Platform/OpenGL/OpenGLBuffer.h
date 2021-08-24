#pragma once

#include "TNAH/Renderer/RenderingBuffers.h"

namespace tnah {

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		OpenGLVertexBuffer(void* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		void Bind() const override;
		void Unbind() const override;

		const BufferLayout& GetLayout() const override { return m_Layout; }
		void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t count);
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		OpenGLIndexBuffer(void* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		void Bind() const override;
		void Unbind() const override;

		uint32_t GetCount() const override { return m_Count; }
	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};

	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpecification& spec, uint32_t colorAttachments = 1, uint32_t depthAttachments = 1);
		OpenGLFramebuffer(const FramebufferSpecification& spec, uint32_t colorAttachments, std::vector<ColorAttachmentSpecs> colorSpecs);
		OpenGLFramebuffer(const FramebufferSpecification& spec, const RenderbufferSpecification& renderSpec);

		
		virtual ~OpenGLFramebuffer();

		void Bind(uint32_t attachmentSlot = 0) override;
		void Unbind() override;
		void Rebuild(const FramebufferSpecification& spec) override;
		
		const FramebufferSpecification& GetSpecification() const override { return m_Specification; }
		
		void DrawToNext() override;
		
		uint32_t GetRendererID() const override { return m_RendererID; }
		uint32_t GetColorAttachment() const override { return GetColorAttachment(0); }
		uint32_t GetColorAttachment(uint32_t attachmentNumber) const override;
		uint32_t GetTotalColorAttachments() const override { return m_ColorAttachments.size(); }
		
		uint32_t GetDepthAttachmentID() const override { return GetDepthAttachmentID(0); }
		uint32_t GetDepthAttachmentID(uint32_t attachmentNumber) const override;
		uint32_t GetTotalDepthAttachments() const override { return m_DepthAttachments.size(); }

		uint32_t GetRenderBufferID() const override { return m_Renderbuffer->GetRendererID(); }
		void SetRenderbufferSpecification(uint32_t bufferSlot, const RenderbufferSpecification& spec) override;
	
	
		void SelectDrawToBuffer(const FramebufferDrawMode& mode, uint32_t attachmentNumber) override;
		
		int GetFormatFromSpec(const FramebufferSpecification& spec) override;
	private:
		void Invalidate(uint32_t color = 1, uint32_t depth = 1, RenderbufferSpecification renderSpec = {0} );
		
		uint32_t m_RendererID;
		FramebufferSpecification m_Specification;
		
		std::vector<ColorAttachmentSpecs> m_ColorSpecifications;
		std::vector<uint32_t> m_ColorAttachments;
		std::vector<uint32_t> m_DepthAttachments;
		Ref<Renderbuffer> m_Renderbuffer;
		RenderbufferSpecification m_RenderbufferSpecification;

		uint32_t m_ActiveColorAttachment = 0;
		
		
	
	};

	class OpenGLRenderBuffer : public Renderbuffer
	{
	public:
		virtual ~OpenGLRenderBuffer();
		OpenGLRenderBuffer(const RenderbufferSpecification& spec);
		uint32_t GetRendererID() const override { return m_RendererID; }
		void Bind() override;
		void Unbind() override;
		void Rebuild(const RenderbufferSpecification& spec) override;
		void AttachToFramebuffer() override;
		
		int GetFormatFromSpecification(const RenderbufferSpecification& spec) override;
		int GetFramebufferFormatFromSpecification(const RenderbufferSpecification& spec) override;

	private:
		
		
		void Invalidate();
		
	
	private:
		uint32_t m_RendererID;
		RenderbufferSpecification m_Specification;
	};
}