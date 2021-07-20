#include "tnahpch.h"
#include "Renderer.h"

namespace tnah {

	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData();

	void Renderer::BeginScene(SceneCamera& camera)
	{
		m_SceneData->ViewProjection = camera.GetViewProjection();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader)
	{
		shader->Bind();
		shader->UniformMat4(m_SceneData->ViewProjection, "u_ViewProjection");
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}