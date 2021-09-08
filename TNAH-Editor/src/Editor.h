#pragma once

#include <TNAH.h>

namespace tnah {

		/**
		 * @class	Editor
		 *
		 * @brief	An Editor class that inherits from the base class Application
		 *
		 * @author	Plush
		 * @date	7/09/2021
		 */

	class Editor : public tnah::Application
	{
	public:

			/**
			 * @fn	Editor::Editor();
			 *
			 * @brief	Constructor that creates a new Application called Editor and push an EditorLayer onto the layerstack
			 *
			 * @author	Plush
			 * @date	7/09/2021
			 */

		Editor();

			/**
			 * @fn	Editor::~Editor();
			 *
			 * @brief	Destructor
			 *
			 * @author	Plush
			 * @date	7/09/2021
			 */

		~Editor();

			/**
			 * @fn	void Editor::OnEvent(tnah::Event& e) override;
			 *
			 * @brief	Executes the 'event' action
			 *
			 * @author	Plush
			 * @date	7/09/2021
			 *
			 * @param [in,out]	e	A tnah::Event to process.
			 */

		void OnEvent(tnah::Event& e) override;

			/**
			 * @fn	bool& Editor::GetCursorToggleStatus() override
			 *
			 * @brief	Gets cursor toggle status
			 *
			 * @author	Plush
			 * @date	7/09/2021
			 *
			 * @returns	The cursor toggle status.
			 */

		bool& GetCursorToggleStatus() override { return m_CursorDisabled; }

			/**
			 * @fn	bool& Editor::GetWireframeToggleStatus() override
			 *
			 * @brief	Gets wireframe toggle status
			 *
			 * @author	Plush
			 * @date	7/09/2021
			 *
			 * @returns	The wireframe toggle status.
			 */

		bool& GetWireframeToggleStatus() override  { return m_WireframeEnabled; }

			/**
			 * @fn	bool& Editor::GetFullscreenToggleStatus() override
			 *
			 * @brief	Gets fullscreen toggle status
			 *
			 * @author	Plush
			 * @date	7/09/2021
			 *
			 * @returns	The fullscreen toggle status.
			 */

		bool& GetFullscreenToggleStatus() override { return m_Fullscreen; }

			/**
			 * @fn	bool& Editor::GetVSyncToggleStatus() override
			 *
			 * @brief	Gets v synchronize toggle status
			 *
			 * @author	Plush
			 * @date	7/09/2021
			 *
			 * @returns	The v synchronize toggle status.
			 */

		bool& GetVSyncToggleStatus() override { return m_VSync; }
		

			/** @brief	True to disable, false to enable the cursor */
		bool m_CursorDisabled = false;

			/** @brief	True to enable, false to disable the wireframe */
		bool m_WireframeEnabled = false;

			/** @brief	True to fullscreen */
		bool m_Fullscreen = false;
			
			/** @brief	True to synchronize */
		bool m_VSync = false;
	};




}