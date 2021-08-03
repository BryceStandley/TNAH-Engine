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

		inline static void SetWireframe(const bool& enable)
		{
			s_RendererAPI->SetWireframe(enable);
		}


	private:
		static RendererAPI* s_RendererAPI;
	};

}

