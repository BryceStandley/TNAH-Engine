#pragma once
#include "TNAH/Core/Core.h"
#include "TNAH/Events/Event.h"

namespace tnah {
	/**
	 * \file Layer.h
	 * \author Bryce Standley
	 * \brief Base class of all layers within the engine. Each layer is placed on a stack and updated in order of the layer stack.
	 * \date  July 2021
	 */
	class TNAH_API Layer
	{
	public:
		/**
		 * \fn Layer
		* \author Bryce Standley
		* \date   July 2021
		* \param name
		* \brief Main constructor of the layer
		*/
		Layer(const std::string& name = "Layer");

		/**
		 * \fn ~Layer
		* \author Bryce Standley
		* \date   July 2021
		* \brief Deconstructor of the layer
		*/
		virtual ~Layer();

		/**
		 * \fn OnAttach
		* \author Bryce Standley
		* \date   July 2021
		* \brief Function called when a layer is attached to the layer stack, override per layer implimentation
		*/
		virtual void OnAttach() {}

		/**
		 * \fn OnDetach
		* \author Bryce Standley
		* \date   July 2021
		* \brief Function called when a layer is detached from the layer stack, override per layer implimentation
		*/
		virtual void OnDetach() {}

		/**
		 * \fn OnUpdate
		* \author Bryce Standley
		* \date   July 2021
		* \brief Function called when a layer is updated in the layer stack, override per layer implimentation
		*/
		virtual void OnUpdate() {}

		/**
		 * \fn OnEvent
		* \author Bryce Standley
		* \date   July 2021
		* \param event
		* \brief Function called when a layer receives a event in the layer stack, override per layer implimentation
		*/
		virtual void OnEvent(Event& event) {}

		/**
		 * \fn GetName
		* \author Bryce Standley
		* \date   July 2021
		* \return string - name of the layer
		* \brief Returns a name of the layer
		*/
		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};
}

