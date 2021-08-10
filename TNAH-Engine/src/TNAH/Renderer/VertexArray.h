#pragma once

#include <memory>
#include "TNAH/Renderer/RenderingBuffers.h"

namespace tnah {

	class VertexArray
	{
	public:
		virtual ~VertexArray() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

		/**********************************************************************************************//**
		 * @fn	static Ref<VertexArray> VertexArray::Create();
		 *
		 * @brief	Creates a new VAO and binds it for use
		 *
		 * @author	Bryce Standley
		 * @date	28/07/2021
		 *
		 * @returns	A Ref&lt;VertexArray&gt;
		 **************************************************************************************************/

		static VertexArray* Create();

		uint32_t m_IndicesSize;
	};

}
