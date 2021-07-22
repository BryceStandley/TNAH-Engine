#include "tnahpch.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"
namespace tnah {

	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData();

	/*void Renderer::BeginScene(CameraComponent& camera)
	{
		m_SceneData->ViewProjection = camera.Camera.GetProjectionMatrix();
	}*/

	void Renderer::BeginScene(SceneCamera& camera, glm::mat4& transform)
	{
		glm::mat4 viewPorjection = camera.GetProjectionMatrix() * glm::inverse(transform);


		m_SceneData->ViewProjection = viewPorjection;
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const TransformComponent& transform)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UniformMat4(m_SceneData->ViewProjection, "u_ViewProjection");
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UniformMat4(transform.GetTransform(), "u_Transform");
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}