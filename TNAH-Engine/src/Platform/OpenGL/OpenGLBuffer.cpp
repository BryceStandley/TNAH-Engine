#include "tnahpch.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>


namespace tnah {

	/////////////////////////////////////////////////////////////////////////////
	// VertexBuffer /////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////

	OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size)
	{
	
		glGenBuffers(1, &m_VBOID);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBOID);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer()
	{
		glGenBuffers(1, &m_VBOID);

	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		 

		glDeleteBuffers(1, &m_VBOID);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		 

		glBindBuffer(GL_ARRAY_BUFFER, m_VBOID);
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		 

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::SetData(const std::vector<glm::vec3>& data, uint32_t size) const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VBOID);
		glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec3), &data[0], GL_STATIC_DRAW);
	}

	/////////////////////////////////////////////////////////////////////////////
	// IndexBuffer //////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////

	OpenGLIndexBuffer::OpenGLIndexBuffer(std::vector<uint32_t>& indices, uint32_t count)
		: m_Count(count)
	{
		 

		glCreateBuffers(1, &m_IBOID);
		
		// GL_ELEMENT_ARRAY_BUFFER is not valid without an actively bound VAO
		// Binding with GL_ARRAY_BUFFER allows the data to be loaded regardless of VAO state. 
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBOID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), &indices[0], GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer()
	{
		glGenBuffers(1, &m_IBOID);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		 

		glDeleteBuffers(1, &m_IBOID);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		 

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBOID);
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		 

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void OpenGLIndexBuffer::SetData(const std::vector<uint32_t>& data)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBOID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(uint32_t), &data[0], GL_STATIC_DRAW);
		m_Count = data.size();
	}

}
