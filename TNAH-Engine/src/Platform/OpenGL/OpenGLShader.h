#pragma once

#include "TNAH/Renderer/Shader.h"

typedef unsigned int GLenum;

namespace tnah {
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		OpenGLShader(const std::string& filePath);
		virtual ~OpenGLShader();

		virtual void Bind() override;
		virtual void Unbind() override;


		void UniformMat4(const glm::mat4& matrix, const std::string& uniformName);

		void UniformVec(const glm::vec2& vec, const std::string& uniformName);
		void UniformVec(const glm::vec3& vec, const std::string& uniformName);
		void UniformVec(const glm::vec4& vec, const std::string& uniformName);

		void UniformBool(const bool& value, const std::string& uniformName);
		void UniformInt(const int& value, const std::string& uniformName);
		void UniformFloat(const float& value, const std::string& uniformName);
		void UniformUnsigned(const unsigned int& value, const std::string& uniformName);

	private:
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& src);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSrc);
		std::string ReadFile(const std::string& filePath);
		bool CheckUniform(const std::string& uniformName);
		inline void SetBound(bool bound) { m_Bound = bound; }


	private:
		uint32_t m_RendererID;
		bool m_Bound = false;
	};
}

