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
		static void IncrementTextureSlot() {m_CurrentTextureSlot++;}
		static uint32_t GetCurrentTextureSlot() {return m_CurrentTextureSlot;}
		static uint32_t GetAndIncrementTextureSlot() {m_CurrentTextureSlot++; return m_CurrentTextureSlot - 1;}

		static void SetCullMode(const CullMode mode);

		static void SetShaderLightInfo(const Ref<Material>& material, std::vector<Ref<Light>> lights);

		static void Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f));
		static void SubmitTerrain(const Ref<VertexArray>& vertexArray, const Ref<Material>& material, std::vector<Ref<Light>> sceneLights, const glm::mat4& transform = glm::mat4(1.0f));
		static void SubmitMesh(const Ref<VertexArray>& vertexArray, const Ref<Material>& material, std::vector<Ref<Light>> sceneLights, const glm::mat4& transform = glm::mat4(1.0f));

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
		
	
	private:
		struct SceneData
		{
			glm::mat4 ViewProjection;
		};

		static uint32_t m_CurrentTextureSlot;
		static SceneData* s_SceneData;
	};
}
