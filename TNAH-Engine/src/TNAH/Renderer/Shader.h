#pragma once

#include <string>

namespace tnah {
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() {}
		virtual void Unbind() {}


		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
		static Shader* Create(const std::string& filePath);
	private:
		uint32_t m_RendererID;
	};
}

