#pragma once

#include "TNAH/core/Core.h"

#include "TNAH/Renderer/Shader.h"
#include "TNAH/Renderer/Texture.h"


namespace tnah
{
	struct MaterialProperties
	{
		float Shininess = 32.0f;
		float Metalness = 0.0f;

		MaterialProperties() = default;
		MaterialProperties(float shine, float metal)
			:Shininess(shine), Metalness(metal) {}
	};
	
	
	class Material
	{
	public:
		//TODO: ADD Skybox support to materials 
		static Material* Create(const Ref<Shader>& shader);
		static Material* Create(const Ref<Shader>& shader, const MaterialProperties& properties);
		static Material* Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
		static Material* Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const MaterialProperties& properties);
		static Material* Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const float& shininess, const float& metalness);
		void SetTextures(std::vector<Ref<Texture2D>> textures);
		virtual void BindTextures();
		virtual void BindShader();
		virtual void UnBindShader();

		virtual Ref<Shader> GetShader() const { return m_Shader; }
		std::vector<Ref<Texture2D>> GetTextures() const { return m_Textures; }
		virtual MaterialProperties& GetProperties() { return m_Properties; }

		virtual ~Material();
		
	protected:
		Material();
		Material(const Ref<Shader>& shader);
		Material(const Ref<Shader>& shader, const MaterialProperties& properties);
		Material(const MaterialProperties& properties);
		Material(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
		Material(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const MaterialProperties& properties);
		Material(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const float& shininess, const float& metalness);
		
		Ref<Shader> m_Shader;
		MaterialProperties m_Properties;
	
	private:
		std::vector<Ref<Texture2D>> m_Textures;

		friend class EditorUI;
		
	};

	class SkyboxMaterial : public Material
	{
	public:
		static SkyboxMaterial* Create(const Ref<Shader>& shader);
		static SkyboxMaterial* Create(const Ref<Shader>& shader, const Texture3DProperties& cubemapProperties);
		static SkyboxMaterial* Create(const Ref<Shader>& shader, const MaterialProperties& properties);
		static SkyboxMaterial* Create(const Ref<Shader>& shader, const MaterialProperties& properties, const Texture3DProperties& cubemapProperties);
		static SkyboxMaterial* Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
		static SkyboxMaterial* Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const MaterialProperties& properties);
		static SkyboxMaterial* Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const MaterialProperties& properties, const Texture3DProperties& cubemapProperties);
		static SkyboxMaterial* Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const float& shininess, const float& metalness);
		
		void BindTextures() override;

		Ref<Texture3D> GetCubemapTextures() const { return m_Cubemap; }
		Texture3DProperties GetCubemapProperties() const { return m_CubemapProperties; }
		
		~SkyboxMaterial() override;

	protected:
		SkyboxMaterial(const Ref<Shader>& shader);
		SkyboxMaterial(const Ref<Shader>& shader, const Texture3DProperties& cubemapProperties);
		SkyboxMaterial(const Ref<Shader>& shader, const MaterialProperties& properties);
		SkyboxMaterial(const Ref<Shader>& shader, const MaterialProperties& properties, const Texture3DProperties& cubemapProperties);
		SkyboxMaterial(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
		SkyboxMaterial(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const MaterialProperties& properties);
		SkyboxMaterial(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const MaterialProperties& properties, const Texture3DProperties& cubemapProperties);
		SkyboxMaterial(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const float& shininess, const float& metalness);

		Texture3DProperties m_CubemapProperties;
		Ref<Texture3D> m_Cubemap;
	};

}
