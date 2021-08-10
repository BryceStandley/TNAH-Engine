#include "tnahpch.h"
#include "Renderer.h"

#include "Texture.h"
#include "Platform/OpenGL/OpenGLShader.h"
namespace tnah {

	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData();
	uint32_t Renderer::m_CurrentTextureSlot = 0;

	struct RendererData
	{
		Ref<Texture2D> WhiteTexture;
		Ref<Texture2D> BlackTexture;
	};

	static RendererData* s_Data = nullptr;

	void Renderer::Init()
	{
		s_Data = new RendererData();
		RenderCommand::Init();

		s_Data->WhiteTexture.reset(Texture2D::Create("assets/textures/default/default_white.jpg"));
		s_Data->BlackTexture.reset(Texture2D::Create("assets/textures/default/default_black.jpg"));
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

	void Renderer::SubmitTerrain(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader,
		const std::vector<Ref<Texture2D>>& textures, const glm::mat4& transform, const glm::mat3& lightingInformation)
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
		
		for(auto& t : textures)
		{
			t->Bind();
		}
		
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

	void Renderer::SubmitMesh(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader,
		const std::vector<Ref<Texture2D>>& textures, const glm::mat4& transform)
	{
		shader->Bind();
		shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjection);
		shader->SetMat4("u_Transform", transform);
		
		for(auto t : textures)
		{
			t->Bind();
		}
		
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
		
	}

	Ref<Texture2D> Renderer::GetWhiteTexture()
	{
		return s_Data->WhiteTexture;
	}

	Ref<Texture2D> Renderer::GetBlackTexture()
	{
		return s_Data->BlackTexture;
	}
}
