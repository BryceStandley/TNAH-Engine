#pragma once

#include <TNAH-App.h>

class MainLayer : public tnah::Layer
{
public:
	MainLayer();

	void OnUpdate(tnah::Timestep deltaTime) override;
	void OnFixedUpdate(tnah::PhysicsTimestep ps) override;
	void OnImGuiRender() override;
	void OnEvent(tnah::Event& event) override;

private:
	tnah::Scene* m_ActiveScene = nullptr;
	tnah::Ref<tnah::GameObject> m_Camera;
	tnah::GameObject* m_Terrain = nullptr;
	std::vector<tnah::GameObject*> m_MeshObjects;
	tnah::Ref<tnah::GameObject> m_SceneLight;
	tnah::GameObject* m_Skybox = nullptr;

	tnah::GameObject* m_PointLight = nullptr;

	float m_LightCutoff = 12.5f;
	float m_CameraMovementSpeed = 20.0f;
	float m_CameraOverrideSpeed = 20.0f;
	const float m_CameraDefaultMovementSpeed = 20.0f;
	const float m_MaxCameraMovementSpeed = 200.0f;
	bool m_CameraMovementSpeedOverride = false;
	float m_CameraMouseSensitivity = 0.1f;
	float m_LastMouseXPos = 0.0f;
	float m_LastMouseYPos = 0.0f;
	bool m_FirstMouseInput = true;
	bool m_CameraMovementToggle = false;
};

