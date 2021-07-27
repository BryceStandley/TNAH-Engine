#include "tnahpch.h"
#include "TNAH/Renderer/Renderer.h"


namespace tnah {

	Scope<Renderer::SceneData> Renderer::s_SceneData = CreateScope<Renderer::SceneData>();

	void Renderer::Init()
	{

		RenderCommand::Init();

	}

	void Renderer::Shutdown()
	{

	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::BeginScene(SceneCamera& camera)
	{
		s_SceneData->ViewProjectionMatrix = camera.GetProjectionMatrix() * camera.GetViewMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
	{

		shader->Bind();
		shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		shader->SetMat4("u_Transform", transform);
		glm::mat4 m = glm::mat4(1.0f);
		m = glm::scale(m, glm::vec3(0.2f));
		shader->SetMat4("u_Model", m);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}
