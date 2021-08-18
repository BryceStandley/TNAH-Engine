#pragma once

#include "TNAH/Renderer/Shader.h"
#include <glm/glm.hpp>

// TODO: REMOVE!
typedef unsigned int GLenum;

namespace tnah {

	class  OpenGLShader : public Shader
	{
	public:

		/**
		* @brief A constructor that takes in paths to the shaders and generates them
		* @param vertexPath - represents the path to the vertex shader
		* @param fragmentPath - represents the path to the fragment shader
		* @param geometryPath - represents the path to the geometry shader (Set to null in this case)
		*/
		OpenGLShader(const std::string& shaderFilePath);

		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);

		~OpenGLShader();

		/**
		* @brief Allows you to activate and use the shader
		*/
		void Bind() override;

		//Unbind the shader from the program
		void Unbind() override;

		bool IsBound() const override { return m_Bound; }

		/**
		* @brief Sets a boolean for use in the shader program
		* @param name - represents the name of the variable
		* @param value - represents the variable value
		*/
		virtual void SetBool(const std::string& name, bool value) override;

		/**
		* @brief Sets an integer for use in the shader program
		* @param name - represents the name of the variable
		* @param value - represents the variable value
		*/
		virtual void SetInt(const std::string& name, int value) override;

		/**
		* @brief Sets a float for use in the shader program
		* @param name - represents the name of the variable
		* @param value - represents the variable value
		*/
		virtual void SetFloat(const std::string& name, float value) override;

		/**
		* @brief Sets a vec2 for use in the shader program
		* @param name - represents the name of the variable
		* @param value - represents the variable value
		*/
		virtual void SetVec2(const std::string& name, const glm::vec2& value) override;

		/**
		* @brief Sets a vec3 for use in the shader program
		* @param name - represents the name of the variable
		* @param value - represents the variable value
		*/
		virtual void SetVec3(const std::string& name, const glm::vec3& value) override;


		/**
		* @brief Sets a vec4 for use in the shader program
		* @param name - represents the name of the variable
		* @param value - represents the variable value
		*/
		virtual void SetVec4(const std::string& name, const glm::vec4& value) override;

		/**
		* @brief Sets a mat3 for use in the shader program
		* @param name - represents the name of the variable
		* @param mat - represents the variable value
		*/
		virtual void SetMat3(const std::string& name, const glm::mat3& mat) override;

		/**
		* @brief Sets a mat4 for use in the shader program
		* @param name - represents the name of the variable
		* @param mat - represents the variable value
		*/
		virtual void SetMat4(const std::string& name, const glm::mat4& mat) override;

		inline virtual const std::string& GetName() const override { return m_ShaderName; }
	private:
		std::unordered_map<GLenum, std::pair<std::string, std::string>> PreProcess(const std::string& source, const std::string& shaderFilePath);
		void Compile(const std::unordered_map<GLenum, std::pair<std::string, std::string>>& shaderSources);
		std::string ReadFile(const std::string& filepath);

		std::string PreProcessPaths(const std::string& shaderSorceFilePath);

		uint32_t m_ShaderID;
		
		
		bool m_Bound = false;
	};

	

}
