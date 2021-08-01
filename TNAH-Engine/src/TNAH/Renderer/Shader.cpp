#include "tnahpch.h"
#include "TNAH/Renderer/Shader.h"

#include "TNAH/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace tnah {

	Shader* Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    TNAH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLShader(filepath);
		}

		TNAH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    TNAH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		TNAH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}


}