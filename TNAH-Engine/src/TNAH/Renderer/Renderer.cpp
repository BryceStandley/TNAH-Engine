#include "tnahpch.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"
namespace tnah {

	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData();

	void Renderer::Init()
	{

	}

	void Renderer::Shutdown()
	{

	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{

	}

	void Renderer::BeginScene(SceneCamera& camera, glm::mat4& transform)
	{
		glm::mat4 viewPorjection = camera.GetProjectionMatrix() * glm::inverse(transform);

		s_SceneData->ViewProjection = viewPorjection;
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->SetMat4("u_ViewProjection", s_SceneData->ViewProjection);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->SetMat4("u_Transform", transform);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}