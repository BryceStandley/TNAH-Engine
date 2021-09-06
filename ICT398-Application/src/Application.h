#pragma once

#include <TNAH.h>

/**
 * @class	Testbed
 *
 * @brief	A testbed.
 *
 * @author	Plush
 * @date	6/09/2021
 */

class Testbed : public tnah::Application
{
public:

		/**
		 * @fn	Testbed::Testbed();
		 *
		 * @brief	Constructor that creates a new Application called Testbed and pushes a test layer onto the layerstack
		 *
		 * @author	Plush
		 * @date	6/09/2021
		 */

	Testbed();

		/**
		 * @fn	Testbed::~Testbed();
		 *
		 * @brief	Destructor for Testbed
		 *
		 * @author	Plush
		 * @date	6/09/2021
		 */

	~Testbed();

		/**
		 * @fn	void Testbed::OnEvent(tnah::Event& e) override;
		 *
		 * @brief	Executes the 'event' action
		 *
		 * @author	Plush
		 * @date	6/09/2021
		 *
		 * @param [in,out]	e	A tnah::Event to process.
		 */

	void OnEvent(tnah::Event& e) override;

		/**
		 * @fn	bool& Testbed::GetCursorToggleStatus() override
		 *
		 * @brief	Gets cursor toggle status
		 *
		 * @author	Plush
		 * @date	6/09/2021
		 *
		 * @returns	The cursor toggle status.
		 */

	bool& GetCursorToggleStatus() override { return m_CursorDisabled; }

		/**
		 * @fn	bool& Testbed::GetWireframeToggleStatus() override
		 *
		 * @brief	Gets wireframe toggle status
		 *
		 * @author	Plush
		 * @date	6/09/2021
		 *
		 * @returns	The wireframe toggle status.
		 */

	bool& GetWireframeToggleStatus() override  { return m_WireframeEnabled; }

		/**
		 * @fn	bool& Testbed::GetFullscreenToggleStatus() override
		 *
		 * @brief	Gets fullscreen toggle status
		 *
		 * @author	Plush
		 * @date	6/09/2021
		 *
		 * @returns	The fullscreen toggle status.
		 */

	bool& GetFullscreenToggleStatus() override { return m_Fullscreen; }

		/**
		 * @fn	bool& Testbed::GetVSyncToggleStatus() override
		 *
		 * @brief	Gets v synchronize toggle status
		 *
		 * @author	Plush
		 * @date	6/09/2021
		 *
		 * @returns	The v synchronize toggle status.
		 */

	bool& GetVSyncToggleStatus() override { return m_VSync; }

private:

		/** @brief	True to disable, false to enable the cursor */
	bool m_CursorDisabled = false;

		/** @brief	True to enable, false to disable the wireframe */
	bool m_WireframeEnabled = false;

		/** @brief	True to fullscreen */
	bool m_Fullscreen = false;

		/** @brief	True to synchronize */
	bool m_VSync = false;

};

	/**
	 * @fn	inline tnah::Application* tnah::CreateApplication()
	 *
	 * @brief This is required to make a new application with our set layers inside this project.
	 *  this is a single project and only uses engine classes and doesn't have access to all engine
	 *  specific functions like raw OpenGL calls, thats a job for the engine to handle internally.
	 *
	 * @author	Plush
	 * @date	6/09/2021
	 *
	 * @returns	the new application.
	 */

inline tnah::Application* tnah::CreateApplication()
{
	return new Testbed();
}


