#include "tnahpch.h"
#include "SceneCamera.h"

#include <glm/gtc/matrix_transform.hpp>

#include "TNAH/Scene/Components/Components.h"

namespace tnah {

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



	void SceneCamera::OnUpdate(TransformComponent& transform)
	{
		OnCameraChange(transform);
	}

	void SceneCamera::OnCameraChange(TransformComponent& transform)
	{
		m_ProjectionMatrix = glm::perspective(glm::radians(60.0f), 1280.0f / 720.0f, 0.1f, 1000.0f);
		m_ViewMatrix = glm::lookAt(transform.Position, transform.Position + transform.Forward, glm::vec3(0, 1, 0));
		m_ViewProjection = m_ProjectionMatrix * m_ViewMatrix;
	}

}