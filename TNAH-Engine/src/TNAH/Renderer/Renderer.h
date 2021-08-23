#pragma once

#include "TNAH/Renderer/RenderCommand.h"

#include "TNAH/Scene/SceneCamera.h"
#include "TNAH/Renderer/Material.h"
#include "Light.h"
#include "Mesh.h"
#include "Texture.h"

namespace tnah {
	
	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginScene(SceneCamera& camera);
		static void EndScene();
		static void IncrementTextureSlot() { s_CurrentTextureSlot++; }
		static uint32_t GetCurrentTextureSlot() { return s_CurrentTextureSlot; }
		static uint32_t GetAndIncrementTextureSlot() { s_CurrentTextureSlot++; return s_CurrentTextureSlot - 1; }

		static void SetCullMode(const CullMode mode);

		static void SetShaderLightInfo(const Ref<Material>& material, std::vector<Ref<Light>> lights);

		static void Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f));
		static void SubmitTerrain(const Ref<VertexArray>& vertexArray, const Ref<Material>& material, std::vector<Ref<Light>> sceneLights, const glm::mat4& transform = glm::mat4(1.0f));
		static void SubmitMesh(const Ref<VertexArray>& vertexArray, const Ref<Material>& material, std::vector<Ref<Light>> sceneLights, const glm::mat4& transform = glm::mat4(1.0f));
		
		static void SubmitSkybox(const Ref<VertexArray>& vertexArray, const Ref<SkyboxMaterial>& material);
		
		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
		static Ref<Texture2D> GetWhiteTexture();
		static Ref<Texture2D> GetBlackTexture();
		static Ref<Texture2D> GetMissingTexture();
		static std::vector<Ref<Texture2D>> GetLoadedTextures();
		static std::vector<Ref<Shader>> GetLoadedShaders();
		static void RegisterTexture(Ref<Texture2D>& texture);
		static void RegisterShader(Ref<Shader>& shader);

		static std::vector<Ref<Model>> GetLoadedModels();
		static void RegisterModel(Ref<Model>& model);

		//RenderStats
		static uint32_t GetDrawCallsPerFrame();
		static uint32_t GetTotalLoadedTextures();
		static uint32_t GetTotalLoadedShaders();
		static uint32_t GetTotalLoadedModels();


	
	private:

		static void IncrementDrawCallsPerFrame();
		static void IncrementTotalLoadedTextures();
		static void IncrementTotalLoadedShaders();
		static void IncrementTotalLoadedModels();

		static void ResetDrawCallsPerFrame();
		static void ResetTotalLoadedTextures();
		static void ResetTotalLoadedShaders();
		static void ResetTotalLoadedModels();

		struct SceneData
		{
			glm::mat4 View;
			glm::mat4 Projection;
			glm::mat4 ViewProjection;
		};



		static uint32_t s_CurrentTextureSlot;
		static SceneData* s_SceneData;
		
	};
}
