#pragma once

#include "PhysicsLoader.h"

	/**
	 * @class	MainLayer
	 *
	 * @brief	A main layer that inherits from the base Layer class.
	 *
	 * @author	Dylan Blereau
	 * @date	6/09/2021
	 */

class MainLayer : public tnah::Layer
{
public:

		/**
		 * @fn	MainLayer::MainLayer();
		 *
		 * @brief	Default constructor
		 *
		 * @author	Dylan Blereau
		 * @date	6/09/2021
		 */
	MainLayer();

		/**
		 * @fn	void MainLayer::OnUpdate(tnah::Timestep deltaTime) override;
		 *
		 * @brief	Executes the 'update' action
		 *
		 * @author	Dylan Blereau
		 * @date	6/09/2021
		 *
		 * @param 	deltaTime	The delta time.
		 */

	void OnUpdate(tnah::Timestep deltaTime) override;

		/**
		 * @fn	void MainLayer::OnFixedUpdate(tnah::PhysicsTimestep ps) override;
		 *
		 * @brief	Executes the 'fixed update' action
		 *
		 * @author	Dylan Blereau
		 * @date	6/09/2021
		 *
		 * @param 	ps	The ps.
		 */

	void OnFixedUpdate(tnah::Timestep ts, tnah::PhysicsTimestep ps) override;

		/**
		 * @fn	void MainLayer::OnImGuiRender() override;
		 *
		 * @brief	Executes the IMGui render
		 *
		 * @author	Dylan Blereau
		 * @date	6/09/2021
		 */

	void OnImGuiRender() override;

		/**
		 * @fn	void MainLayer::OnEvent(tnah::Event& event) override;
		 *
		 * @brief	Executes the 'event' action, such as a window resize or key input
		 *
		 * @author	Dylan Blereau
		 * @date	6/09/2021
		 *
		 * @param   event	The event.
		 */

	void OnEvent(tnah::Event& event) override;

private:


	tnah::Ref<tnah::Scene> m_ActiveScene = nullptr;
	tnah::GameObject m_Camera;
	tnah::GameObject m_Skybox;
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
	
	bool m_CameraLookToggle = false;
	
	bool m_CursorVisible = false;
	
	bool m_Wireframe = false;
	
	bool m_Fullscreen = false;
	
	bool m_VSync = false;

	tnah::GameObject m_Box1;
	tnah::GameObject m_Box2;
	tnah::GameObject m_Ball;
	std::vector<tnah::GameObject> objects;
	bool m_StartPhysicsSim = false;
	tnah::PhysicsLoader loader;
	glm::vec3 startingPos = {0, 0, 0};
	
};

