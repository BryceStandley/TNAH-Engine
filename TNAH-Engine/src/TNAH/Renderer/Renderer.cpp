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
		std::vector<Ref<Texture2D>> LoadedTextures;
		std::vector<Ref<Shader>> LoadedShaders;
		std::vector<Ref<Model>> LoadedModels;
	};

	static RendererData* s_Data = nullptr;

	void Renderer::Init()
	{
		s_Data = new RendererData();
		RenderCommand::Init();

		s_Data->WhiteTexture.reset(Texture2D::Create("Resources/textures/default/default_white.jpg"));
		s_Data->BlackTexture.reset(Texture2D::Create("Resources/textures/default/default_black.jpg"));
		s_Data->MissingTexture.reset(Texture2D::Create("Resources/textures/default/default_missing.jpg"));
		if(s_Data->WhiteTexture != nullptr) s_Data->LoadedTextures.push_back(s_Data->WhiteTexture);
		if(s_Data->BlackTexture != nullptr) s_Data->LoadedTextures.push_back(s_Data->BlackTexture);
		if(s_Data->MissingTexture != nullptr) s_Data->LoadedTextures.push_back(s_Data->MissingTexture);
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
				material->GetShader()->SetInt("u_Light[" +std::to_string(totalLights) +"].type", info.type);
				material->GetShader()->SetVec3("u_Light[" +std::to_string(totalLights) +"].position", info.position);
				material->GetShader()->SetVec3("u_Light[" +std::to_string(totalLights) +"].direction", info.direction);
			
				material->GetShader()->SetVec3("u_Light[" +std::to_string(totalLights) +"].ambient", info.ambient);
				material->GetShader()->SetVec3("u_Light[" +std::to_string(totalLights) +"].diffuse", info.diffuse);
				material->GetShader()->SetVec3("u_Light[" +std::to_string(totalLights) +"].specular", info.specular);
				material->GetShader()->SetVec3("u_Light[" +std::to_string(totalLights) +"].color", info.color);
				material->GetShader()->SetFloat("u_Light[" +std::to_string(totalLights) +"].intensity", info.intensity);
			
				material->GetShader()->SetFloat("u_Light[" +std::to_string(totalLights) +"].constant", info.constant);
				material->GetShader()->SetFloat("u_Light[" +std::to_string(totalLights) +"].linear", info.linear);
				material->GetShader()->SetFloat("u_Light[" +std::to_string(totalLights) +"].quadratic", info.quadratic);
				material->GetShader()->SetFloat("u_Light[" +std::to_string(totalLights) +"]cutoff", info.cutoff);
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

	std::vector<Ref<Texture2D>> Renderer::GetLoadedTextures()
	{
		return s_Data->LoadedTextures;
	}

	std::vector<Ref<Shader>> Renderer::GetLoadedShaders()
	{
		return s_Data->LoadedShaders;
	}

	void Renderer::RegisterTexture(Ref<Texture2D>& texture)
	{
		s_Data->LoadedTextures.push_back(texture);
	}

	void Renderer::RegisterShader(Ref<Shader>& shader)
	{
		s_Data->LoadedShaders.push_back(shader);
	}

	std::vector<Ref<Model>> Renderer::GetLoadedModels()
	{
		return s_Data->LoadedModels;
	}

	void Renderer::RegisterModel(Ref<Model>& model)
	{
		s_Data->LoadedModels.push_back(model);
	}

}
