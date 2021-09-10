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

	void OpenGLRendererAPI::Disable(const APIEnum& value)
	{
		switch (value)
		{
		case APIEnum::CullFace: glDisable(GL_CULL_FACE); break;
		case APIEnum::DepthTest: glDisable(GL_DEPTH_TEST); break;
		case APIEnum::DepthMask: glDepthMask(GL_FALSE); break;
		case APIEnum::FrontFace_CW: glFrontFace(GL_CCW); break;
		case APIEnum::FrontFace_CCW: glFrontFace(GL_CW); break;
		case APIEnum::CubeMap: glDisable(GL_TEXTURE_CUBE_MAP);  break;
		default: break;
		}
	}

	void OpenGLRendererAPI::Enable(const APIEnum& value)
	{
		switch (value)
		{
		case APIEnum::CullFace: glEnable(GL_CULL_FACE); break;
		case APIEnum::DepthTest: glEnable(GL_DEPTH_TEST); break;
		case APIEnum::DepthMask: glDepthMask(GL_TRUE); break;
		case APIEnum::FrontFace_CW: glFrontFace(GL_CW); break;
		case APIEnum::FrontFace_CCW: glFrontFace(GL_CCW); break;
		case APIEnum::CubeMap: glEnable(GL_TEXTURE_CUBE_MAP); break;
		default: break;
		}
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRendererAPI::DrawArray(const Ref<VertexArray>& vertexArray)
	{
		glDrawArrays(GL_TRIANGLES, 0, vertexArray->GetIndexSize());
	}

	void OpenGLRendererAPI::SetDepthFunc(const DepthFunc& func)
	{
		switch (func)
		{
		case DepthFunc::Never: glDepthFunc(GL_NEVER); break;
		case DepthFunc::Less: glDepthFunc(GL_LESS); break;
		case DepthFunc::Equal: glDepthFunc(GL_EQUAL); break;
		case DepthFunc::Lequal: glDepthFunc(GL_LEQUAL); break;
		case DepthFunc::Greater: glDepthFunc(GL_GREATER); break;
		case DepthFunc::NotEqual: glDepthFunc(GL_NOTEQUAL); break;
		case DepthFunc::Gequal: glDepthFunc(GL_GEQUAL); break;
		case DepthFunc::Always: glDepthFunc(GL_ALWAYS); break;
		default:  glDepthFunc(GL_LESS); break;
		}
	}

	void OpenGLRendererAPI::DrawElements(const uint32_t& indexCount, const uint32_t& baseIndex, const uint32_t& baseVertex)
	{
		glDrawElementsBaseVertex(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, reinterpret_cast<void*>(sizeof(uint32_t) * baseIndex), baseVertex);
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
