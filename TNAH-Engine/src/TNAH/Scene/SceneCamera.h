#pragma once

#include "TNAH/Renderer/Camera.h"
#include "TNAH/Core/Timestep.h"

namespace tnah {

	class SceneCamera : public Camera
	{
	public:
		enum class ProjectionType { Perspective = 0, Orthographic = 1 };
		enum class CameraMovement { Forward = 0, Backward = 1, Left = 2, Right = 3, Still = 4};
	public:
		SceneCamera(const glm::vec3& position);
		void SetPerspective(float verticalFOV, float nearClip = 0.01f, float farClip = 1000.0f);
		void SetOrthographic(float size, float nearClip = -1.0f, float farClip = 1.0f);
		void SetViewportSize(uint32_t width, uint32_t height);

		void SetPerspectiveVerticalFOV(float verticalFov) { m_PerspectiveFOV = glm::radians(verticalFov); }
		float GetPerspectiveVerticalFOV() const { return glm::degrees(m_PerspectiveFOV); }
		void SetPerspectiveNearClip(float nearClip) { m_PerspectiveNear = nearClip; }
		float GetPerspectiveNearClip() const { return m_PerspectiveNear; }
		void SetPerspectiveFarClip(float farClip) { m_PerspectiveFar = farClip; }
		float GetPerspectiveFarClip() const { return m_PerspectiveFar; }

		void SetOrthographicSize(float size) { m_OrthographicSize = size; }
		float GetOrthographicSize() const { return m_OrthographicSize; }
		void SetOrthographicNearClip(float nearClip) { m_OrthographicNear = nearClip; }
		float GetOrthographicNearClip() const { return m_OrthographicNear; }
		void SetOrthographicFarClip(float farClip) { m_OrthographicFar = farClip; }
		float GetOrthographicFarClip() const { return m_OrthographicFar; }

		void SetProjectionType(ProjectionType type) { m_ProjectionType = type; }
		ProjectionType GetProjectionType() const { return m_ProjectionType; }
		inline void SetMouseSensitivity(const float sensitivity) { m_MouseSensitivity = sensitivity; }
		inline void SetMovementSpeed(const float speed) { m_MovementSpeed = speed; }
		inline void SetCameraRefPosition(const glm::vec3& position) { m_Position = position; }


		std::unordered_map<std::string, glm::vec3> OnUpdate(Timestep deltaTime, CameraMovement directionOfMovement);
		void OnMouseMovement(float x, float y, bool constrainPitch = true);
		void OnCameraChange();
		
	private:
		ProjectionType m_ProjectionType = ProjectionType::Perspective;


		float m_PerspectiveFOV = glm::radians(45.0f);
		float m_PerspectiveNear = 0.1f, m_PerspectiveFar = 100000.0f;

		float m_OrthographicSize = 10.0f;
		float m_OrthographicNear = -1.0f, m_OrthographicFar = 1.0f;

		float m_Yaw = -45.0f, m_Pitch = 0.0f;
		float m_LastMouseX = 0.0f, m_LastMouseY = 0.0f;
		bool m_firstInput = true;
		bool m_Disabled = false;
		float m_MouseSensitivity = 0.1f;
		float m_MovementSpeed = 2.5f;
		glm::vec3 m_Position;

		std::unordered_map<std::string, glm::vec3> m_Vectors;


	};
	;

}