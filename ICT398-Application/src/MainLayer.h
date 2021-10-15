#pragma once

#include <TNAH-App.h>

class MainLayer : public tnah::Layer
{
public:
	MainLayer();

	void OnUpdate(tnah::Timestep deltaTime) override;
	void OnFixedUpdate(tnah::Timestep ts,tnah::PhysicsTimestep ps) override;
	void OnImGuiRender() override;
	void OnEvent(tnah::Event& event) override;
	void OnAttach() override;

private:
	tnah::Ref<tnah::Scene> m_ActiveScene = nullptr;
	tnah::GameObject m_Camera;
	tnah::GameObject m_Terrain;
	tnah::GameObject m_SceneLight;
	tnah::GameObject m_Skybox;

	tnah::GameObject m_PointLight;

	tnah::Ref<tnah::Texture2D> m_EndScreenImage;

	float m_LightCutoff = 12.5f;
	float m_CameraMovementSpeed = 5.0f;
	float m_CameraOverrideSpeed = 20.0f;
	const float m_CameraDefaultMovementSpeed = 20.0f;
	const float m_MaxCameraMovementSpeed = 200.0f;
	bool m_CameraMovementSpeedOverride = false;
	float m_CameraMouseSensitivity = 0.1f;
	float m_LastMouseXPos = 0.0f;
	float m_LastMouseYPos = 0.0f;
	bool m_FirstMouseInput = true;
	bool m_CameraMovementToggle = true;
	bool m_CameraLookToggle = true;
	
	/** @brief	false to disable, true to enable the cursor */
	bool m_CursorVisible = true;

	/** @brief	True to enable, false to disable the wireframe */
	bool m_Wireframe = false;

	/** @brief	True to fullscreen */
	bool m_Fullscreen = false;

	/** @brief	True to synchronize */
	bool m_VSync = false;

	/** @brief	True to display the close screen */
	bool m_CloseScreen = false;
	
	rp3d::Vector3 m_Velocity = rp3d::Vector3(10, 0, 10);
};

