#pragma once

#include <glm/glm.hpp>

namespace tnah {

	class SceneCamera
	{
	public:
		SceneCamera(float left, float right, float bottom, float top);

		const glm::vec3& GetPosition() const { return m_Position; }
		inline void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }

		const float GetRotation() const { return m_Rotation; }
		inline void SetRotation(const float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

		const glm::mat4& GetProjectionMatrix() const { return m_Projection; }
		inline void SetProjection(const glm::mat4& projection) { m_Projection = projection; }

		const glm::mat4& GetViewMatrix() const { return m_View; }
		inline void SetView(const glm::mat4& view) { m_View = view; }

		const glm::mat4& GetViewProjection() const { return m_ViewProjection; }
		
		


	private:
		void RecalculateViewMatrix();
	private:
		glm::mat4 m_Projection;
		glm::mat4 m_View;
		glm::mat4 m_ViewProjection;


		glm::vec3 m_Position;
		float m_Rotation = 0.0f;
	};

}