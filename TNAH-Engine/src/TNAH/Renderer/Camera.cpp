#include <tnahpch.h>
#include "Camera.h"

namespace tnah {

	Camera::Camera(const glm::mat4& projectionMatrix)
		: m_ProjectionMatrix(projectionMatrix)
	{
	}


	Camera* Camera::MainCamera = new Camera();

	void Camera::SetMainCamera(Camera& other)
	{
		MainCamera = &other;
	}

	Camera* Camera::Main()
	{
		return MainCamera;
	}
	
}