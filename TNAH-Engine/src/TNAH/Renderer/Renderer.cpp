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

	void Renderer::SetShaderLightInfo(const Ref<Material>& material, std::vector<Ref<Light>> lights)
	{
		if(!material->GetShader()->IsBound()) material->BindShader();

		for(auto& l : lights)
		{
			auto info = l->GetShaderInfo();
			material->GetShader()->SetInt("u_Light.type", info.type);
			material->GetShader()->SetVec3("u_Light.cameraPosition", info.cameraPosition);
			material->GetShader()->SetVec3("u_Light.position", info.position);
			material->GetShader()->SetVec3("u_Light.direction", info.direction);
			material->GetShader()->SetVec3("u_Light.ambient", info.ambient);
			material->GetShader()->SetVec3("u_Light.diffuse", info.diffuse);
			material->GetShader()->SetVec3("u_Light.specular", info.specular);
			material->GetShader()->SetVec3("u_Light.color", info.color);
			material->GetShader()->SetFloat("u_Light.intensity", info.intensity);
			material->GetShader()->SetFloat("u_Light.constant", info.constant);
			material->GetShader()->SetFloat("u_Light.linear", info.linear);
			material->GetShader()->SetFloat("u_Light.quadratic", info.quadratic);
			material->GetShader()->SetFloat("u_Light.cutoff", info.cutoff);

			material->GetShader()->SetFloat("u_Material.shininess", material->GetProperties().Shininess);
			material->GetShader()->SetFloat("u_Material.metalness", material->GetProperties().Metalness);
		}
	}


	void Renderer::Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform)
	{
		shader->Bind();
		shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjection);
		shader->SetMat4("u_Transform", transform);


		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

	void Renderer::SubmitTerrain(const Ref<VertexArray>& vertexArray, const Ref<Material>& material,
			std::vector<Ref<Light>> sceneLights, const glm::mat4& transform)
	{
		material->BindShader();
		material->GetShader()->SetMat4("u_ViewProjection", s_SceneData->ViewProjection);
		material->GetShader()->SetMat4("u_Transform", transform);

		SetShaderLightInfo(material, sceneLights);

		material->BindTextures();
		
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

	void Renderer::SubmitMesh(const Ref<VertexArray>& vertexArray, const Ref<Material>& material,
			 std::vector<Ref<Light>> sceneLights, const glm::mat4& transform)
	{
		SetCullMode(CullMode::Back);
		material->BindShader();
		material->GetShader()->SetMat4("u_ViewProjection", s_SceneData->ViewProjection);
		material->GetShader()->SetMat4("u_Transform", transform);

		SetShaderLightInfo(material, sceneLights);
		
		material->BindTextures();
		
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
		SetCullMode(CullMode::Front);
	}

	void Renderer::SetCullMode(const CullMode mode)
	{
		RenderCommand::SetCullMode(mode);
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
