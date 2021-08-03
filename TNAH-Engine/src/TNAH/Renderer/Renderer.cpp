#include "tnahpch.h"
#include "Renderer.h"

#include "Texture.h"
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

	void Renderer::BeginScene(SceneCamera& camera)
	{
		s_SceneData->ViewProjection = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform)
	{
		shader->Bind();
		shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjection);
		shader->SetMat4("u_Transform", transform);


		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

	void Renderer::SubmitTerrain(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const std::vector<Ref<Texture2D>>& textures, const glm::mat4& transform, const glm::mat3& lightingInformation)
	{


		
		shader->Bind();
		shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjection);
		shader->SetMat4("u_Transform", transform);

		glm::vec3 lightPosition = lightingInformation[0];
		glm::vec3 cameraPosition = lightingInformation[1];
		glm::vec3 lightColor = lightingInformation[2];
		shader->SetVec3("u_LightPosition", lightPosition);
		shader->SetVec3("u_CameraPosition", cameraPosition);
		shader->SetVec3("u_LightColor", lightColor);
		
		uint32_t slot = 0;
		for(auto t : textures)
		{
			t->Bind(slot);
			slot++;
		}

		shader->SetInt("u_DirtTexture", 0);
		shader->SetInt("u_GrassTexture", 1);
		shader->SetInt("u_RockTexture", 2);
		shader->SetInt("u_SnowTexture", 3);
		shader->SetInt("u_DetailTexture", 4);
		
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}