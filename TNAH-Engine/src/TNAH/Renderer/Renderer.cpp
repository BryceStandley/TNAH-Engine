#include "tnahpch.h"
#include "Renderer.h"

#include "Texture.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "TNAH/Core/Math.h"
#include "TNAH/Scene/Components/Components.h"

namespace tnah {

	struct RendererData
	{
		Ref<Texture2D> WhiteTexture;
		Ref<Texture2D> BlackTexture;
		Ref<Texture2D> MissingTexture;
		std::vector<Ref<Texture2D>> LoadedTextures;
		std::vector<Ref<Shader>> LoadedShaders;
		std::vector<Ref<Model>> LoadedModels;
	};

	struct RenderStats
	{
		uint32_t LoadedShaders;
		uint32_t LoadedTextures;
		uint32_t LoadedModels;
		uint32_t DrawCalls;
	};

	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData();
	uint32_t Renderer::s_CurrentTextureSlot = 1;
	static RenderStats* s_RenderStats = new RenderStats();
	static RendererData* s_Data = nullptr;

	uint32_t Renderer::GetDrawCallsPerFrame() { return s_RenderStats->DrawCalls; }
	uint32_t Renderer::GetTotalLoadedTextures() { return s_RenderStats->LoadedTextures; }
	uint32_t Renderer::GetTotalLoadedShaders() { return s_RenderStats->LoadedShaders; }
	uint32_t Renderer::GetTotalLoadedModels() { return s_RenderStats->LoadedModels; }

	int Renderer::HasLoadedShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
	{
		for(auto& shader : s_Data->LoadedShaders)
		{
			auto& paths = shader->m_FilePaths;
			if(paths.first == vertexShaderPath || paths.second == vertexShaderPath)
			{
				if(paths.first == fragmentShaderPath || paths.second == fragmentShaderPath)
				{
					return shader->GetRendererID();
				}
			}
		}
		return -1;
	}

	int Renderer::HasLoadedModel(const std::string& modelPath)
	{
		//ToDo:: Implement
		return 0;
	}

	int Renderer::HasLoadedTexture(const std::string& texturePath)
	{
		//ToDo:: Implement
		return 0;
	}

	void Renderer::IncrementDrawCallsPerFrame() { s_RenderStats->DrawCalls++; }
	void Renderer::IncrementTotalLoadedTextures() { s_RenderStats->LoadedTextures++; }
	void Renderer::IncrementTotalLoadedShaders() { s_RenderStats->LoadedShaders++; }
	void Renderer::IncrementTotalLoadedModels() { s_RenderStats->LoadedModels++; }

	void Renderer::ResetDrawCallsPerFrame() { s_RenderStats->DrawCalls = 0; }
	void Renderer::ResetTotalLoadedTextures() { s_RenderStats->LoadedTextures = 0; }
	void Renderer::ResetTotalLoadedShaders() { s_RenderStats->LoadedShaders = 0; }
	void Renderer::ResetTotalLoadedModels() { s_RenderStats->LoadedModels = 0; }


	void Renderer::Init()
	{
		s_Data = new RendererData();
		RenderCommand::Init();

		s_Data->WhiteTexture = (Texture2D::Create("Resources/textures/default/default_white.jpg"));
		s_Data->BlackTexture = (Texture2D::Create("Resources/textures/default/default_black.jpg"));
		s_Data->MissingTexture = (Texture2D::Create("Resources/textures/default/default_missing.jpg"));

		if (s_Data->WhiteTexture != nullptr)  RegisterTexture(s_Data->WhiteTexture);
		if (s_Data->BlackTexture != nullptr) RegisterTexture(s_Data->BlackTexture);
		if (s_Data->MissingTexture != nullptr) RegisterTexture(s_Data->MissingTexture);
		
	}

	

	void Renderer::Shutdown()
	{
		//Resetting all the loaded objects to shutdown
		for (auto t : s_Data->LoadedTextures)
		{
			t.Reset();
		}

		for (auto s : s_Data->LoadedShaders)
		{
			s.Reset();
		}

		for (auto m : s_Data->LoadedModels)
		{
			m.Reset();
		}

		delete[] s_Data;
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{

	}

	void Renderer::BeginScene(SceneCamera& camera)
	{
		s_SceneData->View = camera.GetViewMatrix();
		s_SceneData->Projection = camera.GetProjectionMatrix();
		s_SceneData->ViewProjection = camera.GetViewProjectionMatrix();
		ResetDrawCallsPerFrame();
	}

	void Renderer::BeginScene(SceneCamera& camera, TransformComponent& cameraTransform)
	{
		s_SceneData->View = camera.GetViewMatrix();
		s_SceneData->Projection = camera.GetProjectionMatrix();
		s_SceneData->ViewProjection = camera.GetViewProjectionMatrix();
		s_SceneData->CameraTransform = cameraTransform;
		ResetDrawCallsPerFrame();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::SetShaderLightInfo(Ref<Material> material, std::vector<Ref<Light>> lights)
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


	void Renderer::Submit(Ref<VertexArray> vertexArray, Ref<Shader> shader, const glm::mat4& transform)
	{
		shader->Bind();
		shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjection);
		shader->SetMat4("u_Transform", transform);


		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
		IncrementDrawCallsPerFrame();
	}

	void Renderer::SubmitTerrain(Ref<VertexArray> vertexArray, Ref<Material> material,
			std::vector<Ref<Light>> sceneLights, const glm::mat4& transform)
	{
		material->BindShader();
		material->GetShader()->SetMat4("u_ViewProjection", s_SceneData->ViewProjection);
		material->GetShader()->SetMat4("u_Transform", transform);

		SetShaderLightInfo(material, sceneLights);

		material->BindTextures();
		
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
		IncrementDrawCallsPerFrame();
	}

	void Renderer::SubmitMesh(Ref<Model> model, std::vector<Ref<Light>> sceneLights, const glm::mat4& transform)
	{
		SetCullMode(CullMode::Back);

		for(auto material : model->GetMaterials())
		{
			material->BindShader();
			if(model->IsAnimated())
			{
				for(uint32_t i = 0; i < model->GetBoneTransforms().size(); i++)
				{
					if(i > 100) break; // No more than 100 transforms in the shader
					material->Set("u_BoneTransform[" +std::to_string(i) + "]", model->GetBoneTransforms()[i], true);
				}
			}
			material->Set("u_ViewProjectionMatrix", s_SceneData->ViewProjection);
			material->Set("u_ViewMatrix", s_SceneData->View);
			material->Set("u_CameraPosition", s_SceneData->CameraTransform.Position);
			material->Set("u_Transform", transform);
		}

		model->GetVertexArray()->Bind();
		for(uint32_t i = 0; i < model->GetSubmeshes().size(); i++)
		{
			
			auto& submesh = model->GetSubmeshes()[i];
			const uint32_t matIndex = submesh.MaterialIndex;
			if(model->GetMaterials()[matIndex])
			{
				model->GetMaterials()[i]->BindTextures();
			}
			RenderCommand::DrawElements(submesh.IndexCount, submesh.BaseIndex, submesh.BaseVertex);
			IncrementDrawCallsPerFrame();
		}

#if 0
		for(auto& submesh : model->GetSubmeshes())
		{
			auto material = model->GetMaterials()[submesh.MaterialIndex].As<Material>();
			material->BindShader();
			material->GetShader()->SetMat4("u_ViewProjectionMatrix", s_SceneData->ViewProjection);
			material->GetShader()->SetMat4("u_ViewMatrix", s_SceneData->View);
			auto transformUniform = transform * submesh.Transform;
			material->GetShader()->SetMat4("u_Transform", transform);
			SetShaderLightInfo(material, sceneLights);
			material->BindTextures();

			if(model->IsAnimated())
			{
				for(size_t i = 0; i < model->GetBoneTransforms().size(); i++)
				{
					std::string uniformName = std::string("u_BoneTransforms[") + std::to_string(i) + std::string("]");
					material->Set(uniformName, model->GetBoneTransforms()[i]);
				}
			}

			
		}
		model->GetVertexArray()->Bind();
		RenderCommand::DrawIndexed(model->GetVertexArray());
#endif
		
		SetCullMode(CullMode::Front);		
	}

	void Renderer::SubmitSkybox(Ref<VertexArray> vertexArray, Ref<SkyboxMaterial> material)
	{
		RenderCommand::SetDepthFunc(RendererAPI::DepthFunc::Lequal);
		
		RenderCommand::SetDepthMask(false);
		
		SetCullMode(CullMode::Back);
		material->BindShader();

		const glm::mat4 view = glm::mat4(glm::mat3(s_SceneData->View));
		
		material->GetShader()->SetMat4("u_ViewProjection", s_SceneData->ViewProjection);
		material->GetShader()->SetVec3("u_CameraPosition", s_SceneData->CameraTransform.Position);
		
		material->BindTextures();
		
		vertexArray->Bind();
		
		RenderCommand::DrawArray(vertexArray);
		RenderCommand::SetDepthFunc(RendererAPI::DepthFunc::Less);
		RenderCommand::SetDepthMask(true);
		SetCullMode(CullMode::Front);
		IncrementDrawCallsPerFrame();
	}

	void Renderer::SetCullMode(const CullMode& mode)
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

	void Renderer::RegisterTexture(Ref<Texture2D> texture)
	{
		s_Data->LoadedTextures.push_back(texture);
		IncrementTotalLoadedTextures();
	}

	void Renderer::RegisterShader(Ref<Shader> shader)
	{
		s_Data->LoadedShaders.push_back(shader);
		IncrementTotalLoadedShaders();
	}

	std::vector<Ref<Model>> Renderer::GetLoadedModels()
	{
		return s_Data->LoadedModels;
	}

	void Renderer::RegisterModel(Ref<Model> model)
	{
		s_Data->LoadedModels.push_back(model);
		IncrementTotalLoadedModels();
	}


}
