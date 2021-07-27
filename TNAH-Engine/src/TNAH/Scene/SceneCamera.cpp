#include "tnahpch.h"
#include "SceneCamera.h"
#include "TNAH/Core/Math.h"
#include <glm/gtc/matrix_transform.hpp>

namespace tnah {


	SceneCamera::SceneCamera(const glm::vec3& position)
		: Camera(), m_Position(position)
	{
		OnCameraChange();
	}

	void SceneCamera::SetPerspective(float verticalFOV, float nearClip, float farClip)
	{
		m_ProjectionType = ProjectionType::Perspective;
		m_PerspectiveFOV = verticalFOV;
		m_PerspectiveNear = nearClip;
		m_PerspectiveFar = farClip;
	}

	void SceneCamera::SetOrthographic(float size, float nearClip, float farClip)
	{
		m_ProjectionType = ProjectionType::Orthographic;
		m_OrthographicSize = size;
		m_OrthographicNear = nearClip;
		m_OrthographicFar = farClip;
	}

	void SceneCamera::SetViewportSize(uint32_t width, uint32_t height)
	{
		switch (m_ProjectionType)
		{
		case ProjectionType::Perspective:
			m_ProjectionMatrix = glm::perspective(m_PerspectiveFOV, (float)width / (float)height, m_PerspectiveNear, m_PerspectiveFar);
			break;
		case ProjectionType::Orthographic:
			float aspect = (float)width / (float)height;
			float width = m_OrthographicSize * aspect;
			float height = m_OrthographicSize;
			m_ProjectionMatrix = glm::ortho(-width * 0.5f, width * 0.5f, -height * 0.5f, height * 0.5f);
			break;
		}
	}


	std::unordered_map<std::string, glm::vec3> SceneCamera::OnUpdate(Timestep deltaTime, CameraMovement directionOfMovement)
	{
		
		if (m_Disabled) return m_Vectors;
		float velocity = m_MovementSpeed * deltaTime.GetSeconds() * 5;
		if (directionOfMovement == CameraMovement::Forward)
		{
			m_Position += m_Vectors["forward"] * velocity;
		}
		if (directionOfMovement == CameraMovement::Backward)
		{
			m_Position -= m_Vectors["forward"] * velocity;
		}
		if (directionOfMovement == CameraMovement::Left)
		{
			m_Position -= m_Vectors["right"] * velocity;
		}
		if (directionOfMovement == CameraMovement::Right)
		{
			m_Position += m_Vectors["right"] * velocity;
		}
		if (directionOfMovement == CameraMovement::Still)
		{
			// the camera didnt move, just return the current position vectors
			m_Vectors["position"] = m_Position;
			return m_Vectors;
		}

		m_Vectors["position"] = m_Position;
		return m_Vectors;

	}

	void SceneCamera::OnCameraChange()
	{
		glm::vec3 forward = glm::vec3(0.0f);
		glm::vec3 right = glm::vec3(0.0f);
		glm::vec3 up = glm::vec3(0.0f);
		forward.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		forward.y = sin(glm::radians(m_Pitch));
		forward.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		forward = glm::normalize(forward);
		right = glm::normalize(glm::cross(forward, glm::vec3(0, 1, 0)));
		up = glm::normalize(glm::cross(right, forward));
		m_Vectors["forward"] = forward;
		m_Vectors["right"] = right;
		m_Vectors["up"] = up;

		m_ViewMatrix = glm::lookAt(m_Vectors["position"], m_Vectors["position"] + m_Vectors["forward"], m_Vectors["up"]);
	}

	void SceneCamera::OnMouseMovement(float x, float y, bool constrainPitch)
	{
		if (m_Disabled) return;

		if (m_firstInput)
		{
			m_LastMouseX = x;
			m_LastMouseY = y;
			m_firstInput = false;
		}

		float offsetX = x - m_LastMouseX;
		float offsetY = m_LastMouseY - y;
		m_LastMouseX = x;
		m_LastMouseY = y;


		offsetX *= m_MouseSensitivity;
		offsetY *= m_MouseSensitivity;
		m_Yaw += offsetX;
		m_Pitch += offsetY;

		

		if (constrainPitch)
		{
			if (m_Pitch > 89.0f)
				m_Pitch = 89.0f;
			if (m_Pitch < -89.0f)
				m_Pitch = -89.0f;
		}
		OnCameraChange();
	}

}