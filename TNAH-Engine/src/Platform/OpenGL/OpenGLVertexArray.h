#pragma once

#include "TNAH/Renderer/VertexArray.h"

namespace tnah {

	class OpenGLVertexArray : public VertexArray
	{
	public:

		/**********************************************************************************************//**
		 * @fn	OpenGLVertexArray::OpenGLVertexArray();
		 *
		 * @brief	Default constructor, gens the VAO and binds it
		 *
		 * @author	Bryce Standley
		 * @date	28/07/2021
		 **************************************************************************************************/

		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }

	private:
		uint32_t m_VAOID;
		uint32_t m_VertexBufferIndex = 0;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
	};

}
