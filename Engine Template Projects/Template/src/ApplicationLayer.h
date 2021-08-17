#pragma once
#include <TNAH.h>

class ApplicationLayer : public tnah::Layer
{
public:
	ApplicationLayer();

	void OnUpdate(tnah::Timestep deltaTime) override;
	void OnFixedUpdate(tnah::PhysicsTimestep ps) override;
	void OnImGuiRender() override;
	void OnEvent(tnah::Event& event) override;

private:
	//Put any layer specific objects here
	tnah::Scene* m_ActiveScene;
	tnah::GameObject* m_CameraObject;

	//Demo objects
	float m_Colors[3] = { 0.0f, 0.0f, 0.0f };
};

