#pragma once

#include <string>

#include <glm/glm.hpp>

namespace tnah {
	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind();
		void Unbind();


		void UniformMat4(const glm::mat4& matrix,const std::string& uniformName);

		void UniformVec(const glm::vec2& vec, const std::string& uniformName);
		void UniformVec(const glm::vec3& vec, const std::string& uniformName);
		void UniformVec(const glm::vec4& vec, const std::string& uniformName);
		
		void UniformBool(const bool& value, const std::string& uniformName);
		void UniformInt(const int& value, const std::string& uniformName);
		void UniformFloat(const float& value, const std::string& uniformName);
		void UniformUnsigned(const unsigned int& value, const std::string& uniformName);

	private:

		/**********************************************************************************************//**
		 * @fn	bool Shader::CheckUniform(const std::string& uniformName);
		 *
		 * @brief	Checks if the uniform is present inside the currently bound program 
		 *
		 * @author	Bryce Standley
		 * @date	20/07/2021
		 *
		 * @param 	uniformName	Name of the uniform.
		 *
		 * @returns	True if it succeeds, false if it fails.
		 **************************************************************************************************/

		bool CheckUniform(const std::string& uniformName);


	private:
		uint32_t m_RendererID;
		bool m_Bound = false;
	};
}

