#include "tnahpch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace tnah {

	static GLenum ShaderTypeFromString(const std::string type)
	{
		if (type == "vertex") return GL_VERTEX_SHADER;
		if (type == "fragment") return GL_FRAGMENT_SHADER;

		TNAH_CORE_ASSERT(false, "Invalid shader type provided!");
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		std::unordered_map<GLenum, std::string> src;
		src[GL_VERTEX_SHADER] = vertexSrc;
		src[GL_FRAGMENT_SHADER] = fragmentSrc;
		Compile(src);
	}

	OpenGLShader::OpenGLShader(const std::string& filePath)
	{
		std::string shaderSrc = ReadFile(filePath);
		auto src = PreProcess(shaderSrc);
		Compile(src);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind()
	{
		glUseProgram(m_RendererID);
		SetBound(true);
	}

	void OpenGLShader::Unbind()
	{
		glUseProgram(0);
		SetBound(false);
	}

	void OpenGLShader::UniformMat4(const glm::mat4& matrix, const std::string& uniformName)
	{
		if (CheckUniform(uniformName))
		{
			glUniformMatrix4fv(glGetUniformLocation(m_RendererID, uniformName.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
		}
	}

	void OpenGLShader::UniformVec(const glm::vec2& vec, const std::string& uniformName)
	{
		if (CheckUniform(uniformName))
		{
			glUniform3fv(glGetUniformLocation(m_RendererID, uniformName.c_str()), 1, glm::value_ptr(vec));
		}
	}

	void OpenGLShader::UniformVec(const glm::vec3& vec, const std::string& uniformName)
	{
		if (CheckUniform(uniformName))
		{
			glUniform3fv(glGetUniformLocation(m_RendererID, uniformName.c_str()), 1, glm::value_ptr(vec));
		}
	}

	void OpenGLShader::UniformVec(const glm::vec4& vec, const std::string& uniformName)
	{
		if (CheckUniform(uniformName))
		{
			glUniform4fv(glGetUniformLocation(m_RendererID, uniformName.c_str()), 1, glm::value_ptr(vec));
		}
	}

	void OpenGLShader::UniformBool(const bool& value, const std::string& uniformName)
	{
		if (CheckUniform(uniformName))
		{
			glUniform1i(glGetUniformLocation(m_RendererID, uniformName.c_str()), (int)value);
		}
	}

	void OpenGLShader::UniformInt(const int& value, const std::string& uniformName)
	{

		if (CheckUniform(uniformName))
		{
			glUniform1i(glGetUniformLocation(m_RendererID, uniformName.c_str()), value);
		}
	}

	void OpenGLShader::UniformFloat(const float& value, const std::string& uniformName)
	{
		if (CheckUniform(uniformName))
		{
			glUniform1f(glGetUniformLocation(m_RendererID, uniformName.c_str()), value);
		}
	}

	void OpenGLShader::UniformUnsigned(const unsigned int& value, const std::string& uniformName)
	{
		if (CheckUniform(uniformName))
		{
			glUniform1ui(glGetUniformLocation(m_RendererID, uniformName.c_str()), value);
		}
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& src)
	{
		std::unordered_map<GLenum, std::string> shaderSrc;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = src.find(typeToken, 0);
		while (pos != std::string::npos)
		{
			size_t eol = src.find_first_of("\r\n", pos);
			TNAH_CORE_ASSERT(eol != std::string::npos, "Syntax Error!");
			size_t begin = pos + typeTokenLength + 1;
			std::string type = src.substr(begin, eol - begin);
			TNAH_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type provided!");

			size_t nextLinePos = src.find_first_not_of("\r\n", eol);
			pos = src.find(typeToken, nextLinePos);

			shaderSrc[ShaderTypeFromString(type)] =
				src.substr(nextLinePos, 
					pos - (nextLinePos == std::string::npos ? src.size() - 1 : nextLinePos));
		}
		return shaderSrc;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSrc)
	{
		GLuint program = glCreateProgram();
		std::vector<GLenum> glShaderIDs(shaderSrc.size());

		for (auto& kv : shaderSrc)
		{
			GLenum type = kv.first;
			const std::string& src = kv.second;


			GLuint shader = glCreateShader(type);

			const GLchar* sourceCStr = src.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);


			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				// We don't need the shader anymore.
				glDeleteShader(shader);

				TNAH_CORE_ERROR("{0}", infoLog.data());
				TNAH_CORE_ASSERT(false, "Shader compilation failure!");
				break;
			}
			glAttachShader(program, shader);
			glShaderIDs.push_back(shader);

		}
		
		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(program);
			
			for (auto id : glShaderIDs)
			{
				glDeleteShader(id);
			}
			
			TNAH_CORE_ERROR("{0}", infoLog.data());
			TNAH_CORE_ASSERT(false, "Shader link failure!");
			return;
		}
		m_RendererID = program;

		for (auto id : glShaderIDs)
		{
			glDetachShader(program, id);
		}

	}

	std::string OpenGLShader::ReadFile(const std::string& filePath)
	{
		std::string result;
		std::ifstream in(filePath, std::ios::in, std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();


		}
		else
		{
			TNAH_CORE_ERROR("Couldn't open shader file at path: {0}", filePath);
		}

		return result;
	}

	bool OpenGLShader::CheckUniform(const std::string& uniformName)
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
