#include "tnahpch.h"
#include "SceneCamera.h"
#include "TNAH/Core/Math.h"
#include <glm/gtc/matrix_transform.hpp>

#include "TNAH/Scene/Components/Components.h"

namespace tnah {


	SceneCamera::SceneCamera(const glm::mat4& transform)
		: Camera()
	{
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
			m_ProjectionMatrix = glm::perspective(glm::radians(m_PerspectiveFOV), (float)width / (float)height, m_PerspectiveNear, m_PerspectiveFar);
			break;
		case ProjectionType::Orthographic:
			float aspect = (float)width / (float)height;
			float width = m_OrthographicSize * aspect;
			float height = m_OrthographicSize;
			m_ProjectionMatrix = glm::ortho(-width * 0.5f, width * 0.5f, -height * 0.5f, height * 0.5f);
			break;
		}
	}


	void SceneCamera::OnUpdate(TransformComponent& transform)
	{
		OnCameraChange(transform);
	}

	void SceneCamera::OnCameraChange(TransformComponent& transform)
	{

		//m_ViewMatrix = glm::inverse(m_Transform);
		m_ViewMatrix = glm::lookAt(transform.Position, transform.Forward + transform.Forward, transform.Up);
		m_ProjectionMatrix = glm::perspective(glm::radians(m_PerspectiveFOV), 1280.0f / 720.0f, 0.1f, 100.0f);
		
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
	}

}