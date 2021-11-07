#pragma once

#include <TNAH.h>

/**
 * @class	ICT398Application
 *
 * @brief	A ICT398Application application
 *
 * @author	Dylan Blereau
 * @date	6/09/2021
 */

class ICT398Application : public tnah::Application
{
public:

		/**
		 * @fn	ICT398Application::ICT398Application();
		 *
		 * @brief	Constructor that creates a new Application called Testbed and pushes a test layer onto the layerstack
		 *
		 * @author	Dylan Blereau
		 * @date	6/09/2021
		 */

	ICT398Application();

		/**
		 * @fn	ICT398Application::~ICT398Application();
		 *
		 * @brief	Destructor for Testbed
		 *
		 * @author	Dylan Blereau
		 * @date	6/09/2021
		 */

	~ICT398Application();

		/**
		 * @fn	void ICT398Application::OnEvent(tnah::Event& e) override;
		 *
		 * @brief	Executes the 'event' action
		 *
		 * @author	Dylan Blereau
		 * @date	6/09/2021
		 *
		 * @param [in,out]	e	A tnah::Event to process.
		 */

	void OnEvent(tnah::Event& e) override;

};

	/**
	 * @fn	inline tnah::Application* tnah::CreateApplication()
	 *
	 * @brief This is required to make a new application with our set layers inside this project.
	 *  this is a single project and only uses engine classes and doesn't have access to all engine
	 *  specific functions like raw OpenGL calls, thats a job for the engine to handle internally.
	 *
	 * @author	Dylan Blereau
	 * @date	6/09/2021
	 *
	 * @returns	the new application.
	 */

inline tnah::Application* tnah::CreateApplication()
{
	return new ICT398Application();
}


