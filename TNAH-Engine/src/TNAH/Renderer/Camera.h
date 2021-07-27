#pragma once
#include <glm/glm.hpp>

namespace tnah {

	class Camera
	{
	public:
		Camera() = default;
		Camera(const glm::mat4& projectionMatrix);
		virtual ~Camera() = default;

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		void SetProjectionMatrix(const glm::mat4& projectionMatrix) { m_ProjectionMatrix = projectionMatrix; }

		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		void SetViewMatrix(const glm::mat4& viewMatrix) { m_ViewMatrix = viewMatrix; }

		float GetExposure() const { return m_Exposure; }
		float& GetExposure() { return m_Exposure; }
	protected:
		glm::mat4 m_ViewMatrix = glm::mat4(1.0f);
		glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);
		float m_Exposure = 0.8f;
	};



}
