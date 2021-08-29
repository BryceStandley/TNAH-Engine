#pragma once

#include "TNAH/Core/Ref.h"
#include "TNAH/Renderer/VertexArray.h"


namespace tnah {

	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		void Bind() const override;
		void Unbind() const override;

		void SetID(const uint32_t& id) override { m_RendererID = id; }
		
		void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;
		void SetIndexSize(const uint32_t& size) override { m_IndexSize = size; }
		
		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }
		uint32_t GetIndexSize() const override { return m_IndexSize; }
	private:
		uint32_t m_RendererID;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
		uint32_t m_IndexSize = 0;
	};


}

