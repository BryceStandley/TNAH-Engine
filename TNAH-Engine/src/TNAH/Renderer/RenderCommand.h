#pragma once

#include "RendererAPI.h"
namespace tnah {
	
	class RenderCommand
	{
	public:
		inline static void Init()
		{
			s_RendererAPI->Init();
		}

		inline static void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}

		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}

		inline static void DrawIndexed(const Ref<VertexArray> vertexArray)
		{
			s_RendererAPI->DrawIndexed(vertexArray);
		}

		inline static void SetViewport(const uint32_t x, const uint32_t y, const uint32_t width, const uint32_t height)
		{
			s_RendererAPI->SetViewport(x, y, width, height);
		}



		inline static void BindVAO(const uint32_t VAO)
		{
			s_RendererAPI->BindVAO(VAO);
		}

		inline static void BindVBO(const uint32_t VBO)
		{
			s_RendererAPI->BindVBO(VBO);
		}

		inline static void BindIBO(const uint32_t IBO)
		{
			s_RendererAPI->BindIBO(IBO);
		}


	private:
		static RendererAPI* s_RendererAPI;
	};

}

