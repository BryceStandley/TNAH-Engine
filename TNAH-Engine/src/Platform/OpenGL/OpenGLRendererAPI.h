#pragma once

#include "TNAH/Renderer/RendererAPI.h"

namespace tnah {

	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		void Init() override;
		void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

		void SetClearColor(const glm::vec4& color) override;
		void Clear() override;

		void Disable(const APIEnum& value) override;
		void Enable(const APIEnum& value) override;
		
		void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
		void DrawArray(const Ref<VertexArray>& vertexArray) override;

		void SetWireframe(const bool& enable) override;
		bool CheckFullScreen(const int& width, const int& height) override;
		void SetCullMode(const CullMode& mode) override;
		void SetDepthMask(const bool& enabled) override;
		void SetDepthFunc(const DepthFunc& func) override;
	};

}
