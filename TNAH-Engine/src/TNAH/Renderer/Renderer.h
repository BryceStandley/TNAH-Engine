#pragma once

#include "TNAH/Renderer/RenderCommand.h"

#include "TNAH/Temp/tempCamera.h"

#include "TNAH/Scene/SceneCamera.h"
#include "TNAH/Renderer/Shader.h"

namespace tnah {

	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginScene(SceneCamera& camera);
		static void BeginScene(TempCamera& camera);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader, const uint32_t VAO, const uint32_t VBO, const uint32_t IBO, const uint32_t indexSize, const glm::mat4& transform = glm::mat4(1.0f));

		static void BindVertexArray(const uint32_t VAO);
		static void BindVertexBuffer(const uint32_t VBO);
		static void BindIndexBuffer(const uint32_t IBO);


		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static Scope<SceneData> s_SceneData;
	};
}
