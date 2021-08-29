#pragma once

#include <string>
#include <glm/glm.hpp>

#include "TNAH/Core/Ref.h"


namespace tnah {

	enum class ShaderUniformType
	{
		None = 0, Bool, Int, UInt, Float, Vec2, Vec3, Vec4, Mat3, Mat4,
		IVec2, IVec3, IVec4
	};

	class ShaderUniform
	{
	public:
		ShaderUniform() = default;
		ShaderUniform(std::string name, ShaderUniformType type, uint32_t size, uint32_t offset);

		const std::string& GetName() const { return m_Name; }
		ShaderUniformType GetType() const { return m_Type; }
		uint32_t GetSize() const { return m_Size; }
		uint32_t GetOffset() const { return m_Offset; }

		static const std::string& UniformTypeToString(ShaderUniformType type);
	private:
		std::string m_Name;
		ShaderUniformType m_Type = ShaderUniformType::None;
		uint32_t m_Size = 0;
		uint32_t m_Offset = 0;
	};

	enum class ShaderDomain
	{
		None = 0, Vertex = 0, Pixel = 1 // unused
	};

	class ShaderResourceDeclaration
	{
	public:
		ShaderResourceDeclaration() = default;
		ShaderResourceDeclaration(const std::string& name, uint32_t resourceRegister, uint32_t count)
			: m_Name(name), m_Register(resourceRegister), m_Count(count) {}
		virtual ~ShaderResourceDeclaration();
		virtual const std::string& GetName() const { return m_Name; }
		virtual uint32_t GetRegister() const { return m_Register; }
		virtual uint32_t GetCount() const { return m_Count; }
	private:
		std::string m_Name;
		uint32_t m_Register = 0;
		uint32_t m_Count = 0;
	};

	typedef std::vector<ShaderResourceDeclaration*> ShaderResourceList;
	
	class Shader : public RefCounted
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual bool IsBound() const = 0;

		virtual void SetBool(const std::string& name, bool value) = 0;
		virtual void SetInt(const std::string& name, int value) = 0;		
		virtual void SetFloat(const std::string& name, float value) = 0;
		virtual void SetVec2(const std::string& name, const glm::vec2& value) = 0;
		virtual void SetVec3(const std::string& name, const glm::vec3& value) = 0;
		virtual void SetVec4(const std::string& name, const glm::vec4& value) = 0;
		virtual void SetMat3(const std::string& name, const glm::mat3& value) = 0;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;

		virtual const std::string& GetName() const = 0;

		static Ref<Shader> Create(const std::string& filePath);
		static Ref<Shader> Create(const std::string& vertexSrc, const std::string& fragmentSrc);
		static Ref<Shader> CheckShaderExists(const std::string& filePath);
		static Ref<Shader> CheckShaderExists(const std::string& vertexSrc, const std::string& fragmentSrc);

		std::pair<std::string, std::string> m_FilePaths;
		std::string m_ShaderName;
		friend class EditorUI;
	};



}

