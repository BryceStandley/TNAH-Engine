#pragma once

#include "TNAH/Renderer/Buffer.h"

namespace tnah {

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(uint32_t size);
		OpenGLVertexBuffer();
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		
		virtual void SetData(const std::vector<glm::vec3>& data, uint32_t size) const override;

		virtual const BufferLayout& GetLayout() const override { return m_Layout; }
		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
	private:
		uint32_t m_VBOID;
		BufferLayout m_Layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(std::vector<uint32_t>& indices, uint32_t count);
		OpenGLIndexBuffer();
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const;
		virtual void Unbind() const;

		virtual void SetData(const std::vector<uint32_t>& data) override;

		virtual uint32_t GetCount() const { return m_Count; }
	private:
		uint32_t m_IBOID;
		uint32_t m_Count;
	};

}