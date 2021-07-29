#pragma once

#include "TNAH/Renderer/RendererAPI.h"

namespace tnah {

	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Init() override;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const uint32_t indexCount) override;

		virtual void BindVAO(const uint32_t VAO);
		virtual void BindVBO(const uint32_t VBO);
		virtual void BindIBO(const uint32_t IBO);
	};

}
