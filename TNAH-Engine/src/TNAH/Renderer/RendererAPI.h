#pragma once
#include <TNAH/Core/Core.h>
#include "TNAH/Renderer/VertexArray.h"

namespace tnah {

	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1
		};
	public:
		virtual ~RendererAPI() = default;

		virtual void Init() = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const uint32_t indexCount = 0) = 0;

		virtual void BindVAO(const uint32_t VAO) = 0;
		virtual void BindVBO(const uint32_t VBO) = 0;
		virtual void BindIBO(const uint32_t IBO) = 0;

		static API GetAPI() { return s_API; }
		static Scope<RendererAPI> Create();
	private:
		static API s_API;
	};

}

