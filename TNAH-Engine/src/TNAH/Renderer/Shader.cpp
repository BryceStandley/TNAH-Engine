#include "tnahpch.h"
#include "Shader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace tnah {

	Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		// Create an empty vertex shader handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* source = vertexSrc.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			TNAH_CORE_ERROR("{0}", infoLog.data());
			TNAH_CORE_ASSERT(false, "Vertex shader compilation failure!");
			return;
		}

		// Create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = fragmentSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			TNAH_CORE_ERROR("{0}", infoLog.data());
			TNAH_CORE_ASSERT(false, "Fragment shader compilation failure!");
			return;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		m_RendererID = glCreateProgram();
		GLuint program = m_RendererID;

		// Attach our shaders to our program
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			TNAH_CORE_ERROR("{0}", infoLog.data());
			TNAH_CORE_ASSERT(false, "Shader link failure!");
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_RendererID);
	}

	void Shader::Bind()
	{
		glUseProgram(m_RendererID);
		m_Bound = true;
	}

	void Shader::Unbind()
	{
		glUseProgram(0);
		m_Bound = false;
	}

	void Shader::UniformMat4(const glm::mat4& matrix, const std::string& uniformName)
	{
		if (CheckUniform(uniformName))
		{
			glUniformMatrix4fv(glGetUniformLocation(m_RendererID, uniformName.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
		}
	}

	void Shader::UniformVec(const glm::vec2& vec, const std::string& uniformName)
	{
		if (CheckUniform(uniformName))
		{
			glUniform3fv(glGetUniformLocation(m_RendererID, uniformName.c_str()), 1, glm::value_ptr(vec));
		}
	}

	void Shader::UniformVec(const glm::vec3& vec, const std::string& uniformName)
	{
		if (CheckUniform(uniformName))
		{
			glUniform3fv(glGetUniformLocation(m_RendererID, uniformName.c_str()), 1, glm::value_ptr(vec));
		}
	}

	void Shader::UniformVec(const glm::vec4& vec, const std::string& uniformName)
	{
		if (CheckUniform(uniformName))
		{
			glUniform4fv(glGetUniformLocation(m_RendererID, uniformName.c_str()), 1, glm::value_ptr(vec));
		}
	}

	void Shader::UniformBool(const bool& value, const std::string& uniformName)
	{
		if (CheckUniform(uniformName))
		{
			glUniform1i(glGetUniformLocation(m_RendererID, uniformName.c_str()), (int)value);
		}
	}

	void Shader::UniformInt(const int& value, const std::string& uniformName)
	{

		if(CheckUniform(uniformName))
		{
			glUniform1i(glGetUniformLocation(m_RendererID, uniformName.c_str()), value);
		}
	}

	void Shader::UniformFloat(const float& value, const std::string& uniformName)
	{
		if (CheckUniform(uniformName))
		{
			glUniform1f(glGetUniformLocation(m_RendererID, uniformName.c_str()), value);
		}
	}

	void Shader::UniformUnsigned(const unsigned int& value, const std::string& uniformName)
	{
		if (CheckUniform(uniformName))
		{
			glUniform1ui(glGetUniformLocation(m_RendererID, uniformName.c_str()), value);
		}
	}

	bool Shader::CheckUniform(const std::string& uniformName)
	{
		//Always bind the program before checking its uniforms
		if (!m_Bound)
		{
			Bind();
		}

		if (glGetUniformLocation(m_RendererID, uniformName.c_str()) < 0)
		{
			TNAH_CORE_ASSERT(false, "No uniform with that name!");
			return false;
		}
		else
		{
			return true;
		}
	}

}
