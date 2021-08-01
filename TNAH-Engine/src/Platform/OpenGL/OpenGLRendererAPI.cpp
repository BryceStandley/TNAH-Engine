#include "tnahpch.h"
#include "OpenGLRendererAPI.h"
#include "TNAH/Renderer/VertexArray.h"

#include <glad/glad.h>

namespace tnah {


	void OpenGLRendererAPI::Init()
	{

		//glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glPrimitiveRestartIndex(0xFFFFFFFFU);
		glEnable(GL_PRIMITIVE_RESTART);

		glEnable(GL_DEPTH_TEST);
	}

	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray> vertexArray)
	{
		
		vertexArray->Bind();
		uint32_t count = vertexArray->m_IndicesSize;

		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);
		glActiveTexture(GL_TEXTURE0);
	}


	void OpenGLRendererAPI::BindVAO(const uint32_t VAO)
	{
		glBindVertexArray(VAO);
	}

	void OpenGLRendererAPI::BindVBO(const uint32_t VBO)
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
	}

	void OpenGLRendererAPI::BindIBO(const uint32_t IBO)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	}

}