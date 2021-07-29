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
		glm::mat4 projection = camera.GetProjectionMatrix();
		glm::mat4 view = camera.GetViewMatrix();

		s_SceneData->ViewProjectionMatrix = projection * view;
	}

	void Renderer::BeginScene(TempCamera& camera)
	{
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)1280 / (float)720, 0.1f, 10000.0f);
		glm::mat4 projectionViewMatrix = projection * camera.GetViewMatrix();


		s_SceneData->ViewProjectionMatrix = projectionViewMatrix;
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const Ref<Shader>& shader, const uint32_t VAO, const uint32_t VBO, const uint32_t IBO, const uint32_t indexSize, const glm::mat4& transform)
	{

		shader->Bind();
		shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		shader->SetMat4("u_Transform", transform);

		BindVertexArray(VAO);
		RenderCommand::DrawIndexed(indexSize);
	}

	void Renderer::BindVertexArray(const uint32_t VAO)
	{
		RenderCommand::BindVAO(VAO);
	}

	void Renderer::BindVertexBuffer(const uint32_t VBO)
	{
		RenderCommand::BindVBO(VBO);
	}

	void Renderer::BindIndexBuffer(const uint32_t IBO)
	{
		RenderCommand::BindIBO(IBO);
	}

}
