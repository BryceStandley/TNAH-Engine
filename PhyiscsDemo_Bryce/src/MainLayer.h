#pragma once

#include <TNAH-App.h>

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
	
		void OnAttach() override;
		void OnDetach() override;

	private:

		/** @brief	A pointer to the active scene */
	tnah::Ref<tnah::Scene> m_ActiveScene = nullptr;


		/** @brief	The camera gameObject */
	tnah::GameObject m_Camera;
	

		/** @brief	The skybox gameObject */
	tnah::GameObject m_Skybox;
	

		/** @brief	The camera movement speed */
	float m_CameraMovementSpeed = 20.0f;


		/** @brief	The camera override speed */
	float m_CameraOverrideSpeed = 20.0f;


		/** @brief	(Immutable) the camera default movement speed */
	const float m_CameraDefaultMovementSpeed = 20.0f;


		/** @brief	(Immutable) the maximum camera movement speed */
	const float m_MaxCameraMovementSpeed = 200.0f;

		/** @brief	True to camera movement speed override, false to deny override */
	bool m_CameraMovementSpeedOverride = false;

		/** @brief	The camera mouse sensitivity */
	float m_CameraMouseSensitivity = 0.1f;

		/** @brief	The last mouse x coordinate position */
	float m_LastMouseXPos = 0.0f;

		/** @brief	The last mouse y coordinate position */
	float m_LastMouseYPos = 0.0f;

		/** @brief	True to first mouse input */
	bool m_FirstMouseInput = true;

		/** @brief	True to allow camera movement, false to keep camera movement locked */
	bool m_CameraMovementToggle = false;

		/** @brief	True to allow camera look, false to keep camera look disabled */
	bool m_CameraLookToggle = false;

	/** @brief	True to disable, false to enable the cursor */
	bool m_CursorVisible = false;

	/** @brief	True to enable, false to disable the wireframe */
	bool m_Wireframe = false;

	/** @brief	True to fullscreen */
	bool m_Fullscreen = false;

	/** @brief	True to synchronize */
	bool m_VSync = false;

	tnah::GameObject m_Box1;
	tnah::GameObject m_Box2;
	tnah::GameObject m_Ball;
	tnah::GameObject m_Ground;
	tnah::Ref<tnah::Texture2D> m_Crosshair;
	glm::vec3 m_PhysicsSimStartPosition = {0,0,0};
	

	
	
};

