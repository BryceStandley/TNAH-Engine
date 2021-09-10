#pragma once

#include "TNAH/core/Core.h"

#include "TNAH/Renderer/Shader.h"
#include "TNAH/Renderer/Texture.h"


namespace tnah
{
	struct MaterialProperties
	{
		glm::vec3 AlbedoColor = glm::vec3(0.8f);
		float Emission = 0.0f;
		float Roughness = 0.0f;
		float Shininess = 80.0f;
		float Metalness = 0.0f;

		MaterialProperties() = default;
		MaterialProperties(float shine, float metal)
			:Shininess(shine), Metalness(metal) {}

		MaterialProperties(const glm::vec3& albedoColor, const float& emission, const float& roughness, const float& shininess, const float& metalness)
			:AlbedoColor(albedoColor), Emission(emission), Roughness(roughness), Shininess(shininess), Metalness(metalness) {}
	};
	
	
	class Material : public RefCounted
	{
	public:
		static Ref<Material> Create(const Ref<Shader>& shader);
		static Ref<Material> Create(const Ref<Shader>& shader, const MaterialProperties& properties);
		static Ref<Material> Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
		static Ref<Material> Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const MaterialProperties& properties);
		static Ref<Material> Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const float& shininess, const float& metalness);
		void SetTextures(std::vector<Ref<Texture2D>> textures);
		void InsertTextures(std::vector<Ref<Texture2D>> textures, uint32_t startIndex);
		void InsertTexture(Ref<Texture2D> texture, uint32_t index);
		void AddTexture(Ref<Texture2D> texture, const uint32_t& index = 0);
		void AddTextures(std::vector<Ref<Texture2D>> textures);
		void ResizeTextureStorage(const uint32_t& size) { m_Textures.resize(size); }
		virtual void BindTextures();
		virtual void BindShader();
		virtual void UnBindShader();

		virtual Ref<Shader> GetShader() const { return m_Shader; }
		std::vector<Ref<Texture2D>> GetTextures() const { return m_Textures; }
		virtual MaterialProperties& GetProperties() { return m_Properties; }
		virtual void SetProperties(const MaterialProperties& properties) { m_Properties = properties; }

		virtual ~Material();

		void Set(const std::string& materialUniform, uint32_t value);
		void Set(const std::string& materialUniform, int value);
		void Set(const std::string& materialUniform, float value);
		void Set(const std::string& materialUniform, bool value);
		void Set(const std::string& materialUniform, glm::vec2 value);
		void Set(const std::string& materialUniform, glm::vec3 value);
		void Set(const std::string& materialUniform, glm::vec4 value);
		void Set(const std::string& materialUniform, glm::mat4 value, bool transpose = false);
		void Set(const std::string& materialUniform, glm::mat3 value);
	
		Material();
		Material(const Ref<Shader>& shader);
		Material(const Ref<Shader>& shader, const MaterialProperties& properties);
		Material(const MaterialProperties& properties);
		Material(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
		Material(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const MaterialProperties& properties);
		Material(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const float& shininess, const float& metalness);
	
	protected:
		Ref<Shader> m_Shader;
		MaterialProperties m_Properties;
	
	private:
		std::vector<Ref<Texture2D>> m_Textures;

		friend class EditorUI;
		
	};

	class SkyboxMaterial : public Material
	{
	public:
		static Ref<SkyboxMaterial> Create(const Ref<Shader>& shader);
		static Ref<SkyboxMaterial> Create(const Ref<Shader>& shader, const Texture3DProperties& cubemapProperties);
		static Ref<SkyboxMaterial> Create(const Ref<Shader>& shader, const MaterialProperties& properties);
		static Ref<SkyboxMaterial> Create(const Ref<Shader>& shader, const MaterialProperties& properties, const Texture3DProperties& cubemapProperties);
		static Ref<SkyboxMaterial> Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
		static Ref<SkyboxMaterial> Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const MaterialProperties& properties);
		static Ref<SkyboxMaterial> Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const MaterialProperties& properties, const Texture3DProperties& cubemapProperties);
		static Ref<SkyboxMaterial> Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const float& shininess, const float& metalness);
		
		void BindTextures() override;

		SkyboxMaterial(const Ref<Shader>& shader);
		SkyboxMaterial(const Ref<Shader>& shader, const Texture3DProperties& cubemapProperties);
		SkyboxMaterial(const Ref<Shader>& shader, const MaterialProperties& properties);
		SkyboxMaterial(const Ref<Shader>& shader, const MaterialProperties& properties, const Texture3DProperties& cubemapProperties);
		SkyboxMaterial(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
		SkyboxMaterial(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const MaterialProperties& properties);
		SkyboxMaterial(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const MaterialProperties& properties, const Texture3DProperties& cubemapProperties);
		SkyboxMaterial(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const float& shininess, const float& metalness);

		Ref<Texture3D> GetCubemapTextures() const { return m_Cubemap; }
		Texture3DProperties GetCubemapProperties() const { return m_CubemapProperties; }
		
		~SkyboxMaterial() override;

	private:
		

		Texture3DProperties m_CubemapProperties;
		Ref<Texture3D> m_Cubemap;
	};

}
