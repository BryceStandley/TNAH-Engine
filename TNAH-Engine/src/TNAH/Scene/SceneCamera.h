#pragma once

#include "TNAH/Renderer/Camera.h"

namespace tnah {
	struct TransformComponent;
	class SceneCamera : public Camera
	{
	public:
		enum class ProjectionType { Perspective = 0, Orthographic = 1 };
	public:
		void SetPerspective(float verticalFOV, float nearClip = 0.01f, float farClip = 1000.0f);
		void SetOrthographic(float size, float nearClip = -1.0f, float farClip = 1.0f);
		void SetViewportSize(uint32_t width, uint32_t height);
		glm::vec2 GetViewportSize() const {return glm::vec2(m_ViewportWidth, m_ViewportHeight);}
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
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetInvertedTransformViewMatrix() const { return m_InvertTransformViewMatrix; }

		void OnUpdate(TransformComponent& transform);
		void OnCameraChange(TransformComponent& transform);

		glm::quat GetOrientation(TransformComponent& transform);
	private:
		ProjectionType m_ProjectionType = ProjectionType::Perspective;

		uint32_t m_ViewportWidth = 1280;
		uint32_t m_ViewportHeight = 720;
		
		float m_PerspectiveFOV = glm::radians(60.0f);
		float m_PerspectiveNear = 0.1f, m_PerspectiveFar = 10000.0f;

		float m_OrthographicSize = 10.0f;
		float m_OrthographicNear = -1.0f, m_OrthographicFar = 1.0f;

		friend class EditorUI;
		friend class Serializer;
	};
}