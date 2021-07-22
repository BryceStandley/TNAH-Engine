#pragma once

#include "RenderCommand.h"
#include "TNAH/Scene/Components/Components.h"
#include "Shader.h"

namespace tnah {

	class Renderer
	{
	public:
		//static void BeginScene(CameraComponent& camera);
		static void BeginScene(SceneCamera& camera, glm::mat4& transform);
		static void EndScene();

		static void Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const TransformComponent& transform = TransformComponent(glm::vec3(1.0f)));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjection;
		};

		static SceneData* m_SceneData;
	};


}