#pragma once

#include "TNAH/Renderer/RenderCommand.h"

#include "TNAH/Scene/SceneCamera.h"
#include "TNAH/Scene/Components/Components.h"
#include "TNAH/Renderer/Material.h"
#include "Light.h"
#include "Submesh.h"
#include "Texture.h"

namespace tnah {
	
	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginScene(SceneCamera& camera);
		static void BeginScene(SceneCamera& camera, TransformComponent& cameraTransform);
		static void EndScene();
		static void IncrementTextureSlot() { s_CurrentTextureSlot++; }
		static uint32_t GetCurrentTextureSlot() { return s_CurrentTextureSlot; }
		static uint32_t GetAndIncrementTextureSlot() { s_CurrentTextureSlot++; return s_CurrentTextureSlot - 1; }

		static void SetCullMode(const CullMode& mode);

		static void SetShaderLightInfo(Ref<Material> material, std::vector<Ref<Light>> lights);

		static void Submit(Ref<VertexArray> vertexArray, Ref<Shader> shader, const glm::mat4& transform = glm::mat4(1.0f));
		static void SubmitTerrain(Ref<VertexArray> vertexArray, Ref<Material> material, std::vector<Ref<Light>> sceneLights, const glm::mat4& transform = glm::mat4(1.0f));
		static void SubmitMesh(Ref<VertexArray> vertexArray, Ref<Material> material, std::vector<Ref<Light>> sceneLights, const glm::mat4& transform = glm::mat4(1.0f), const bool& isAnimated = false, const std::vector<glm::mat4>& animTransforms = {glm::mat4(1.0f)});
		
		static void SubmitSkybox(Ref<VertexArray> vertexArray, Ref<SkyboxMaterial> material);
		
		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
		static Ref<Texture2D> GetWhiteTexture();
		static Ref<Texture2D> GetBlackTexture();
		static Ref<Texture2D> GetMissingTexture();
		static std::vector<Ref<Texture2D>> GetLoadedTextures();
		static std::vector<Ref<Shader>> GetLoadedShaders();
		static void RegisterTexture(Ref<Texture2D> texture);
		static void RegisterShader(Ref<Shader> shader);

		static std::vector<Ref<Model>> GetLoadedModels();
		static void RegisterModel(Ref<Model> model);

		//RenderStats
		static uint32_t GetDrawCallsPerFrame();
		static uint32_t GetTotalLoadedTextures();
		static uint32_t GetTotalLoadedShaders();
		static uint32_t GetTotalLoadedModels();


		static int HasLoadedShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
		static int HasLoadedModel(const std::string& modelPath);
		static int HasLoadedTexture(const std::string& texturePath);
	
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
			TransformComponent CameraTransform;
		};



		static uint32_t s_CurrentTextureSlot;
		static SceneData* s_SceneData;
		
	};
}
