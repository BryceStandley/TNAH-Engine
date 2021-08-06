#pragma once

#include <string>
#include <glm/glm.hpp>


namespace tnah {

	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() {}
		virtual void Unbind() {}

		virtual void SetBool(const std::string& name, bool value) = 0;
		virtual void SetInt(const std::string& name, int value) = 0;		
		virtual void SetFloat(const std::string& name, float value) = 0;
		virtual void SetVec2(const std::string& name, const glm::vec2& value) = 0;
		virtual void SetVec3(const std::string& name, const glm::vec3& value) = 0;
		virtual void SetVec4(const std::string& name, const glm::vec4& value) = 0;
		virtual void SetMat3(const std::string& name, const glm::mat3& value) = 0;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;

		virtual const std::string& GetName() const = 0;

		static Shader* Create(const std::string& filePath);
		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
	};



}
