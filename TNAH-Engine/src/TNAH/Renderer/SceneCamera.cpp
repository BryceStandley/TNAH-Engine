#include "tnahpch.h"
#include "SceneCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace tnah {

	SceneCamera::SceneCamera(float left, float right, float bottom, float top)
		: m_Projection(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_View(1.0f), m_Position({0,0,0})
	{
		m_ViewProjection = m_Projection * m_View;
	}

	void SceneCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), { 0,0,1 });

		m_View = glm::inverse(transform);

		//Must be Projection * view not view * projection
		m_ViewProjection = m_Projection * m_View;
	}

}