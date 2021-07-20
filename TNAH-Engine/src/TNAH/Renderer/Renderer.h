#pragma once

#include "RenderCommand.h"
#include "SceneCamera.h"
#include "Shader.h"

namespace tnah {

	class Renderer
	{
	public:
		static void BeginScene(SceneCamera& camera);
		static void EndScene();

		static void Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjection;
		};

		static SceneData* m_SceneData;
	};


}