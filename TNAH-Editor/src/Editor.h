#pragma once

#include <TNAH.h>

namespace tnah {

		/**
		 * @class	Editor
		 *
		 * @brief	An Editor class that inherits from the base class Application
		 *
		 * @author	Dylan Blereau
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
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 */

		Editor();

			/**
			 * @fn	Editor::~Editor();
			 *
			 * @brief	Destructor
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 */

		~Editor();

			/**
			 * @fn	void Editor::OnEvent(tnah::Event& e) override;
			 *
			 * @brief	Executes the 'event' action
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 *
			 * @param [in,out]	e	A tnah::Event to process.
			 */

		void OnEvent(tnah::Event& e) override;
	};




}