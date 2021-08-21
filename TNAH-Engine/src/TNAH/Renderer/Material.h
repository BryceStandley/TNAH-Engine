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
		void BindTextures();
		void BindShader();
		void UnBindShader();

		Ref<Shader> GetShader() const { return m_Shader; }
		std::vector<Ref<Texture2D>> GetTextures() const { return m_Textures; }
		MaterialProperties& GetProperties() { return m_Properties; }
		

	private:

		Material(const Ref<Shader>& shader);
		Material(const Ref<Shader>& shader, const MaterialProperties& properties);
		Material(const MaterialProperties& properties);
		Material();
		
		Ref<Shader> m_Shader;
		std::vector<Ref<Texture2D>> m_Textures;
		MaterialProperties m_Properties;

		friend class EditorUI;
		
	};

}
