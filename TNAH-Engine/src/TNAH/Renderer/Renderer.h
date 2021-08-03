#pragma once

#include "TNAH/Renderer/RenderCommand.h"

#include "TNAH/Scene/SceneCamera.h"
#include "TNAH/Renderer/Shader.h"
#include "Texture.h"

namespace tnah {

	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginScene(SceneCamera& camera);
		static void EndScene();

		static void Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f));
		static void SubmitTerrain(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const std::vector<Ref<Texture2D>>& textures, const glm::mat4& transform = glm::mat4(1.0f), const glm::mat3& lightingInformation = glm::mat3(1.0f));


		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjection;
		};

		static SceneData* s_SceneData;
	};
}
