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

		float GetExposure() const { return m_Exposure; }
		float& GetExposure() { return m_Exposure; }

		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjection; }
		static Camera* Main;
	protected:
		
		static void SetMainCamera(Camera& other);
		static Camera* MainCamera;
		glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);
		float m_Exposure = 0.8f;
		glm::mat4 m_InvertTransformViewMatrix = glm::mat4(1.0f);
		glm::mat4 m_ViewMatrix = glm::mat4(1.0f);

		glm::mat4 m_ViewProjection = m_ProjectionMatrix * m_ViewMatrix;

		friend class Scene;
	};

	



}
