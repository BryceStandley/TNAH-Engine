#pragma once

#include "TNAH/core/Core.h"

#include "TNAH/Renderer/Shader.h"
#include "TNAH/Renderer/Texture.h"


namespace tnah
{
	/**
	 * @struct	MaterialProperties
	 *
	 * @brief	A material properties struct.
	 *
	 * @author	Dylan Blereau
	 * @date	12/09/2021
	 */

	struct MaterialProperties
	{
		glm::vec3 AlbedoColor = glm::vec3(0.8f);
		float Emission = 0.0f;
		float Roughness = 0.0f;
        
        /** @brief	The shininess */
		float Shininess = 80.0f;

		/** @brief	The metalness */
		float Metalness = 0.0f;

		/**
		 * @fn	MaterialProperties() = default;
		 *
		 * @brief	Defaulted constructor
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 */

		MaterialProperties() = default;

		/**
		 * @fn	MaterialProperties(float shine, float metal)
		 *
		 * @brief	Constructor
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 *
		 * @param 	shine	The shine.
		 * @param 	metal	The metal.
		 */

		MaterialProperties(float shine, float metal)
			:Shininess(shine), Metalness(metal) {}

		MaterialProperties(const glm::vec3& albedoColor, const float& emission, const float& roughness, const float& shininess, const float& metalness)
			:AlbedoColor(albedoColor), Emission(emission), Roughness(roughness), Shininess(shininess), Metalness(metalness) {}
	};
	
	
	class Material : public RefCounted
	{
	public:

		/**
		 * @fn	static Ref<Material> Material::Create(const Ref<Shader>& shader);
		 *
		 * @brief	Creates a new material
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 *
		 * @param 	shader	The shader.
		 *
		 * @returns	A pointer to the material
		 */

		static Ref<Material> Create(const Ref<Shader>& shader);

		/**
		 * @fn	static Ref<Material> Material::Create(const Ref<Shader>& shader, const MaterialProperties& properties);
		 *
		 * @brief	Creates a new material
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 *
		 * @param 	shader	  	The shader.
		 * @param 	properties	The properties.
		 *
		 * @returns	A pointer to the material
		 */

		static Ref<Material> Create(const Ref<Shader>& shader, const MaterialProperties& properties);

		/**
		 * @fn	static Ref<Material> Material::Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
		 *
		 * @brief	Creates a new material
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 *
		 * @param 	vertexShaderPath  	Full pathname of the vertex shader file.
		 * @param 	fragmentShaderPath	Full pathname of the fragment shader file.
		 *
		 * @returns	A pointer to the material
		 */

		static Ref<Material> Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

		/**
		 * @fn	static Ref<Material> Material::Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const MaterialProperties& properties);
		 *
		 * @brief	Creates a new material
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 *
		 * @param 	vertexShaderPath  	Full pathname of the vertex shader file.
		 * @param 	fragmentShaderPath	Full pathname of the fragment shader file.
		 * @param 	properties		  	The properties.
		 *
		 * @returns	A pointer to the material
		 */

		static Ref<Material> Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const MaterialProperties& properties);

		/**
		 * @fn	static Ref<Material> Material::Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const float& shininess, const float& metalness);
		 *
		 * @brief	Creates a new material
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 *
		 * @param 	vertexShaderPath  	Full pathname of the vertex shader file.
		 * @param 	fragmentShaderPath	Full pathname of the fragment shader file.
		 * @param 	shininess		  	The shininess.
		 * @param 	metalness		  	The metalness.
		 *
		 * @returns	A pointer to the material
		 */

		static Ref<Material> Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const float& shininess, const float& metalness);

		/**
		 * @fn	void Material::SetTextures(std::vector<Ref<Texture2D>> textures);
		 *
		 * @brief	Sets the textures
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 *
		 * @param 	textures	The textures.
		 */

		void SetTextures(std::vector<Ref<Texture2D>> textures);
		
        // TODO: DOXY Here
        void InsertTextures(std::vector<Ref<Texture2D>> textures, uint32_t startIndex);
		void InsertTexture(Ref<Texture2D> texture, uint32_t index);
		void AddTexture(Ref<Texture2D> texture, const uint32_t& index = 0);
		void AddTextures(std::vector<Ref<Texture2D>> textures);
		void ResizeTextureStorage(const uint32_t& size) { m_Textures.resize(size); }
		void SetShader(const Ref<Shader> shader) { m_Shader = shader; }
        

		/**
		 * @fn	virtual void Material::BindTextures();
		 *
		 * @brief	Bind textures
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 */

		virtual void BindTextures();

		/**
		 * @fn	virtual void Material::BindShader();
		 *
		 * @brief	Bind shader
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 */

		virtual void BindShader();

		/**
		 * @fn	virtual void Material::UnBindShader();
		 *
		 * @brief	Unbind shader
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 */

		virtual void UnBindShader();

		/**
		 * @fn	virtual Ref<Shader> Material::GetShader() const
		 *
		 * @brief	Gets the shader
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 *
		 * @returns	The shader.
		 */

		virtual Ref<Shader> GetShader() const { return m_Shader; }

		/**
		 * @fn	std::vector<Ref<Texture2D>> Material::GetTextures() const
		 *
		 * @brief	Gets the textures
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 *
		 * @returns	The textures.
		 */

		std::vector<Ref<Texture2D>> GetTextures() const { return m_Textures; }

		/**
		 * @fn	virtual MaterialProperties& Material::GetProperties()
		 *
		 * @brief	Gets the properties
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 *
		 * @returns	The properties.
		 */

		virtual MaterialProperties& GetProperties() { return m_Properties; }
		virtual void SetProperties(const MaterialProperties& properties) { m_Properties = properties; }

		/**
		 * @fn	virtual Material::~Material();
		 *
		 * @brief	Destructor
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 */

		virtual ~Material();

		/**
		 * @fn	Material::Material();
		 *
		 * @brief	Default constructor
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 */

		Material();


		void Set(const std::string& materialUniform, uint32_t value);
		void Set(const std::string& materialUniform, int value);
		void Set(const std::string& materialUniform, float value);
		void Set(const std::string& materialUniform, bool value);
		void Set(const std::string& materialUniform, glm::vec2 value);
		void Set(const std::string& materialUniform, glm::vec3 value);
		void Set(const std::string& materialUniform, glm::vec4 value);
		void Set(const std::string& materialUniform, glm::mat4 value, bool transpose = false);
		void Set(const std::string& materialUniform, glm::mat3 value);
	



		/**
		 * @fn	Material::Material(const Ref<Shader>& shader);
		 *
		 * @brief	Constructor
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 *
		 * @param 	shader	The shader.
		 */

		Material(const Ref<Shader>& shader);

		/**
		 * @fn	Material::Material(const Ref<Shader>& shader, const MaterialProperties& properties);
		 *
		 * @brief	Constructor
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 *
		 * @param 	shader	  	The shader.
		 * @param 	properties	The properties.
		 */

		Material(const Ref<Shader>& shader, const MaterialProperties& properties);

		/**
		 * @fn	Material::Material(const MaterialProperties& properties);
		 *
		 * @brief	Constructor
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 *
		 * @param 	properties	The properties.
		 */

		Material(const MaterialProperties& properties);

		/**
		 * @fn	Material::Material(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
		 *
		 * @brief	Constructor
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 *
		 * @param 	vertexShaderPath  	Full pathname of the vertex shader file.
		 * @param 	fragmentShaderPath	Full pathname of the fragment shader file.
		 */

		Material(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

		/**
		 * @fn	Material::Material(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const MaterialProperties& properties);
		 *
		 * @brief	Constructor
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 *
		 * @param 	vertexShaderPath  	Full pathname of the vertex shader file.
		 * @param 	fragmentShaderPath	Full pathname of the fragment shader file.
		 * @param 	properties		  	The properties.
		 */

		Material(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const MaterialProperties& properties);

		/**
		 * @fn	Material::Material(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const float& shininess, const float& metalness);
		 *
		 * @brief	Constructor
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 *
		 * @param 	vertexShaderPath  	Full pathname of the vertex shader file.
		 * @param 	fragmentShaderPath	Full pathname of the fragment shader file.
		 * @param 	shininess		  	The shininess.
		 * @param 	metalness		  	The metalness.
		 */

		Material(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const float& shininess, const float& metalness);
	
	protected:

		/** @brief	The shader */
		Ref<Shader> m_Shader;

		/** @brief	The properties */
		MaterialProperties m_Properties;
	
	private:

		/** @brief	The textures */
		std::vector<Ref<Texture2D>> m_Textures;

		friend class EditorUI;
		
	};

	/**
	 * @class	SkyboxMaterial
	 *
	 * @brief	A skybox material class that inherits from the material class
	 *
	 * @author	Dylan Blereau
	 * @date	12/09/2021
	 */

	class SkyboxMaterial : public Material
	{
	public:

		/**
		 * @fn	static Ref<SkyboxMaterial> SkyboxMaterial::Create(const Ref<Shader>& shader);
		 *
		 * @brief	Creates a new Skybox Material
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 *
		 * @param 	shader	The shader.
		 *
		 * @returns	A pointer to the material
		 */

		static Ref<SkyboxMaterial> Create(const Ref<Shader>& shader);

		/**
		 * @fn	static Ref<SkyboxMaterial> SkyboxMaterial::Create(const Ref<Shader>& shader, const Texture3DProperties& cubemapProperties);
		 *
		 * @brief	Creates a new Skybox Material
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 *
		 * @param 	shader			 	The shader.
		 * @param 	cubemapProperties	The cubemap properties.
		 *
		 * @returns	A pointer to the material
		 */

		static Ref<SkyboxMaterial> Create(const Ref<Shader>& shader, const Texture3DProperties& cubemapProperties);

		/**
		 * @fn	static Ref<SkyboxMaterial> SkyboxMaterial::Create(const Ref<Shader>& shader, const MaterialProperties& properties);
		 *
		 * @brief	Creates a new Skybox Material
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 *
		 * @param 	shader	  	The shader.
		 * @param 	properties	The properties.
		 *
		 * @returns	A pointer to the material
		 */

		static Ref<SkyboxMaterial> Create(const Ref<Shader>& shader, const MaterialProperties& properties);

		/**
		 * @fn	static Ref<SkyboxMaterial> SkyboxMaterial::Create(const Ref<Shader>& shader, const MaterialProperties& properties, const Texture3DProperties& cubemapProperties);
		 *
		 * @brief	Creates a new Skybox Material
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 *
		 * @param 	shader			 	The shader.
		 * @param 	properties		 	The properties.
		 * @param 	cubemapProperties	The cubemap properties.
		 *
		 * @returns	A pointer to the material
		 */

		static Ref<SkyboxMaterial> Create(const Ref<Shader>& shader, const MaterialProperties& properties, const Texture3DProperties& cubemapProperties);

		/**
		 * @fn	static Ref<SkyboxMaterial> SkyboxMaterial::Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
		 *
		 * @brief	Creates a new Skybox Material
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 *
		 * @param 	vertexShaderPath  	Full pathname of the vertex shader file.
		 * @param 	fragmentShaderPath	Full pathname of the fragment shader file.
		 *
		 * @returns	A pointer to the material
		 */

		static Ref<SkyboxMaterial> Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

		/**
		 * @fn	static Ref<SkyboxMaterial> SkyboxMaterial::Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const MaterialProperties& properties);
		 *
		 * @brief	Creates a new Skybox Material
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 *
		 * @param 	vertexShaderPath  	Full pathname of the vertex shader file.
		 * @param 	fragmentShaderPath	Full pathname of the fragment shader file.
		 * @param 	properties		  	The properties.
		 *
		 * @returns	A pointer to the material
		 */

		static Ref<SkyboxMaterial> Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const MaterialProperties& properties);

		/**
		 * @fn	static Ref<SkyboxMaterial> SkyboxMaterial::Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const MaterialProperties& properties, const Texture3DProperties& cubemapProperties);
		 *
		 * @brief	Creates a new Skybox Material
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 *
		 * @param 	vertexShaderPath  	Full pathname of the vertex shader file.
		 * @param 	fragmentShaderPath	Full pathname of the fragment shader file.
		 * @param 	properties		  	The properties.
		 * @param 	cubemapProperties 	The cubemap properties.
		 *
		 * @returns	A pointer to the material
		 */

		static Ref<SkyboxMaterial> Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const MaterialProperties& properties, const Texture3DProperties& cubemapProperties);

		/**
		 * @fn	static Ref<SkyboxMaterial> SkyboxMaterial::Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const float& shininess, const float& metalness);
		 *
		 * @brief	Creates a new Skybox Material
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 *
		 * @param 	vertexShaderPath  	Full pathname of the vertex shader file.
		 * @param 	fragmentShaderPath	Full pathname of the fragment shader file.
		 * @param 	shininess		  	The shininess.
		 * @param 	metalness		  	The metalness.
		 *
		 * @returns	A pointer to the material
		 */

		static Ref<SkyboxMaterial> Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const float& shininess, const float& metalness);

		/**
		 * @fn	void SkyboxMaterial::BindTextures() override;
		 *
		 * @brief	Bind textures
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 */

		void BindTextures() override;

		/**
		 * @fn	SkyboxMaterial::SkyboxMaterial(const Ref<Shader>& shader);
		 *
		 * @brief	Constructor
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 *
		 * @param 	shader	The shader.
		 */

		SkyboxMaterial(const Ref<Shader>& shader);

		/**
		 * @fn	SkyboxMaterial::SkyboxMaterial(const Ref<Shader>& shader, const Texture3DProperties& cubemapProperties);
		 *
		 * @brief	Constructor
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 *
		 * @param 	shader			 	The shader.
		 * @param 	cubemapProperties	The cubemap properties.
		 */

		SkyboxMaterial(const Ref<Shader>& shader, const Texture3DProperties& cubemapProperties);

		/**
		 * @fn	SkyboxMaterial::SkyboxMaterial(const Ref<Shader>& shader, const MaterialProperties& properties);
		 *
		 * @brief	Constructor
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 *
		 * @param 	shader	  	The shader.
		 * @param 	properties	The properties.
		 */

		SkyboxMaterial(const Ref<Shader>& shader, const MaterialProperties& properties);

		/**
		 * @fn	SkyboxMaterial::SkyboxMaterial(const Ref<Shader>& shader, const MaterialProperties& properties, const Texture3DProperties& cubemapProperties);
		 *
		 * @brief	Constructor
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 *
		 * @param 	shader			 	The shader.
		 * @param 	properties		 	The properties.
		 * @param 	cubemapProperties	The cubemap properties.
		 */

		SkyboxMaterial(const Ref<Shader>& shader, const MaterialProperties& properties, const Texture3DProperties& cubemapProperties);

		/**
		 * @fn	SkyboxMaterial::SkyboxMaterial(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
		 *
		 * @brief	Constructor
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 *
		 * @param 	vertexShaderPath  	Full pathname of the vertex shader file.
		 * @param 	fragmentShaderPath	Full pathname of the fragment shader file.
		 */

		SkyboxMaterial(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

		/**
		 * @fn	SkyboxMaterial::SkyboxMaterial(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const MaterialProperties& properties);
		 *
		 * @brief	Constructor
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 *
		 * @param 	vertexShaderPath  	Full pathname of the vertex shader file.
		 * @param 	fragmentShaderPath	Full pathname of the fragment shader file.
		 * @param 	properties		  	The properties.
		 */

		SkyboxMaterial(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const MaterialProperties& properties);

		/**
		 * @fn	SkyboxMaterial::SkyboxMaterial(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const MaterialProperties& properties, const Texture3DProperties& cubemapProperties);
		 *
		 * @brief	Constructor
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 *
		 * @param 	vertexShaderPath  	Full pathname of the vertex shader file.
		 * @param 	fragmentShaderPath	Full pathname of the fragment shader file.
		 * @param 	properties		  	The properties.
		 * @param 	cubemapProperties 	The cubemap properties.
		 */

		SkyboxMaterial(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const MaterialProperties& properties, const Texture3DProperties& cubemapProperties);

		/**
		 * @fn	SkyboxMaterial::SkyboxMaterial(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const float& shininess, const float& metalness);
		 *
		 * @brief	Constructor
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 *
		 * @param 	vertexShaderPath  	Full pathname of the vertex shader file.
		 * @param 	fragmentShaderPath	Full pathname of the fragment shader file.
		 * @param 	shininess		  	The shininess.
		 * @param 	metalness		  	The metalness.
		 */

		SkyboxMaterial(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const float& shininess, const float& metalness);

		/**
		 * @fn	Ref<Texture3D> SkyboxMaterial::GetCubemapTextures() const
		 *
		 * @brief	Gets cubemap textures
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 *
		 * @returns	The cubemap textures.
		 */

		Ref<Texture3D> GetCubemapTextures() const { return m_Cubemap; }

		/**
		 * @fn	Texture3DProperties SkyboxMaterial::GetCubemapProperties() const
		 *
		 * @brief	Gets cubemap properties
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 *
		 * @returns	The cubemap properties.
		 */

		Texture3DProperties GetCubemapProperties() const { return m_CubemapProperties; }

		/**
		 * @fn	SkyboxMaterial::~SkyboxMaterial() override;
		 *
		 * @brief	Destructor
		 *
		 * @author	Dylan Blereau
		 * @date	12/09/2021
		 */

		~SkyboxMaterial() override;

	private:
		
		/** @brief	The cubemap properties */
		Texture3DProperties m_CubemapProperties;

		/** @brief	The cubemap */
		Ref<Texture3D> m_Cubemap;
	};

}
