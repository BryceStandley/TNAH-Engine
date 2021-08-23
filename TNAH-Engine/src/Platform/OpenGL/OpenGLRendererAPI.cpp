#include "tnahpch.h"
#include "OpenGLRendererAPI.h"
#include "TNAH/Renderer/VertexArray.h"

#include <glad/glad.h>

namespace tnah {


	void OpenGLRendererAPI::Init()
	{
	
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
		
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
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

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRendererAPI::DrawArray(const Ref<VertexArray>& vertexArray)
	{
		glDrawArrays(GL_TRIANGLES, 0, vertexArray->GetIndexBuffer()->GetCount());
	}

	void OpenGLRendererAPI::SetWireframe(const bool& enable)
	{
		if(enable)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}

	bool OpenGLRendererAPI::CheckFullScreen(const int& width, const int& height)
	{
		return false;
	}

	void OpenGLRendererAPI::SetCullMode(const CullMode& mode)
	{
		switch (mode)
		{
			case CullMode::Front:
				glEnable(GL_CULL_FACE);
				glCullFace(GL_FRONT);
				break;
			case CullMode::Back:
				glEnable(GL_CULL_FACE);
				glCullFace(GL_BACK);
				break;
			case CullMode::Front_And_Back:
				glEnable(GL_CULL_FACE);
				glCullFace(GL_FRONT_AND_BACK);
				break;
			case CullMode::Disabled:
				glDisable(GL_CULL_FACE);
				break;
			default:
				glEnable(GL_CULL_FACE);
				glCullFace(GL_FRONT_AND_BACK);
				break;
		}
	}

	void OpenGLRendererAPI::SetDepthMask(const bool& enabled)
	{
		glDepthMask(enabled);
	}

}
