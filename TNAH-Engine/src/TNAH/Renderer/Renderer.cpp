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
		Ref<Texture2D> MissingTexture;
	};

	static RendererData* s_Data = nullptr;

	void Renderer::Init()
	{
		s_Data = new RendererData();
		RenderCommand::Init();

		s_Data->WhiteTexture.reset(Texture2D::Create("assets/textures/default/default_white.jpg"));
		s_Data->BlackTexture.reset(Texture2D::Create("assets/textures/default/default_black.jpg"));
		s_Data->MissingTexture.reset(Texture2D::Create("assets/textures/default/default_missing.jpg"));
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

		//The camera position is the same regardless of light so just take the first lights camera position value
		auto& l = lights[0]->GetShaderInfo();
		material->GetShader()->SetVec3("u_Global.cameraPosition", l.cameraPosition);

		uint32_t totalLights = 0;
		for(uint32_t i = 0; i < lights.size(); i++)
		{
			if(i > 8)
			{
				TNAH_INFO("The TNAH-Engine only supports 8 lights at once. Using the first 8 in the scene!");
				return;
			}
			
			auto& light = lights[i];
			auto& info = light->GetShaderInfo();
			if(light->m_IsSceneLight)
			{
				material->GetShader()->SetVec3("u_Global.direction", info.direction);
				material->GetShader()->SetVec3("u_Global.ambient", info.ambient);
				material->GetShader()->SetVec3("u_Global.diffuse", info.diffuse);
				material->GetShader()->SetVec3("u_Global.specular", info.specular);
				material->GetShader()->SetVec3("u_Global.color", info.color);
				material->GetShader()->SetFloat("u_Global.intensity", info.intensity);
			}
			else
			{
				material->GetShader()->SetInt("u_Light[" +std::to_string(i-1) +"].type", info.type);
				material->GetShader()->SetVec3("u_Light[" +std::to_string(i-1) +"].position", info.position);
				material->GetShader()->SetVec3("u_Light[" +std::to_string(i-1) +"].direction", info.direction);
			
				material->GetShader()->SetVec3("u_Light[" +std::to_string(i-1) +"].ambient", info.ambient);
				material->GetShader()->SetVec3("u_Light[" +std::to_string(i-1) +"].diffuse", info.diffuse);
				material->GetShader()->SetVec3("u_Light[" +std::to_string(i-1) +"].specular", info.specular);
				material->GetShader()->SetVec3("u_Light[" +std::to_string(i-1) +"].color", info.color);
				material->GetShader()->SetFloat("u_Light[" +std::to_string(i-1) +"].intensity", info.intensity);
			
				material->GetShader()->SetFloat("u_Light[" +std::to_string(i-1) +"].constant", info.constant);
				material->GetShader()->SetFloat("u_Light[" +std::to_string(i-1) +"].linear", info.linear);
				material->GetShader()->SetFloat("u_Light[" +std::to_string(i-1) +"].quadratic", info.quadratic);
				material->GetShader()->SetFloat("u_Light[" +std::to_string(i-1) +"]cutoff", info.cutoff);
				totalLights++;
			}
			
			material->GetShader()->SetFloat("u_Material.shininess", material->GetProperties().Shininess);
			material->GetShader()->SetFloat("u_Material.metalness", material->GetProperties().Metalness);
		}
		material->GetShader()->SetInt("u_Global.totalLights", totalLights);

		///////
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

	Ref<Texture2D> Renderer::GetMissingTexture()
	{
		return s_Data->MissingTexture;
	}
	
}
