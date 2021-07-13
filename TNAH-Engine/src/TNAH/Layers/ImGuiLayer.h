#pragma once
#include"TNAH/Core/Core.h"
#include "Layer.h"
#include "Platform/OpenGL/imguiOpenGLRenderer.h"
#include "TNAH/Application.h"

namespace tnah {

	class TNAH_API ImGuiLayer : public Layer
	{
	public:
		/**
		 * \fn ImGuiLayer
		* \author Bryce Standley
		* \date   July 2021
		*/
		ImGuiLayer();

		/**
		 * \fn ~ImGuiLayer
		* \author Bryce Standley
		* \date   July 2021
		*/
		~ImGuiLayer();

		/**
		 * \fn OnAttach
		* \author Bryce Standley
		* \date   July 2021
		*/
		void OnAttach();

		/**
		 * \fn OnDetach
		* \author Bryce Standley
		* \date   July 2021
		*/
		void OnDetach();

		/**
		 * \fn OnUpdate
		* \author Bryce Standley
		* \date   July 2021
		*/
		void OnUpdate();

		/**
		 * \fn OnEvent
		* \author Bryce Standley
		* \date   July 2021
		* \param event
		*/
		void OnEvent(Event& event);

	private:
		/**
		 * \fn OnMouseButtonPressedEvent
		* \author Bryce Standley
		* \date   July 2021
		* \param e
		* \return bool
		* \brief Event callback for a ImGui Mouse event
		*/
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);

		/**
		 * \fn OnMouseButtonReleasedEvent
		* \author Bryce Standley
		* \date   July 2021
		* \param e
		* \return bool
		* \brief Event callback for a ImGui Mouse event
		*/
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);

		/**
		 * \fn OnMouseScrollEvent
		* \author Bryce Standley
		* \date   July 2021
		* \param e
		* \return bool
		* \brief Event callback for a ImGui Mouse event
		*/
		bool OnMouseScrollEvent(MouseScrolledEvent& e);

		/**
		 * \fn OnMouseMovedEvent
		* \author Bryce Standley
		* \date   July 2021
		* \param e
		* \return bool
		* \brief Event callback for a ImGui Mouse event
		*/
		bool OnMouseMovedEvent(MouseMovedEvent& e);

		/**
		 * \fn OnKeyPressedEvent
		* \author Bryce Standley
		* \date   July 2021
		* \param e
		* \return bool
		* \brief Event callback for a ImGui Key event
		*/
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		
		/**
		 * \fn OnKeyReleasedEvent
		* \author Bryce Standley
		* \date   July 2021
		* \param e
		* \return bool
		* \brief Event callback for a ImGui Key event
		*/
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);

		/**
		 * \fn OnKeyTypedEvent
		* \author Bryce Standley
		* \date   July 2021
		* \param e
		* \return bool
		* \brief Event callback for a ImGui Key event
		*/
		bool OnKeyTypedEvent(KeyTypedEvent& e);

		/**
		 * \fn OnWindowResizeEvent
		* \author Bryce Standley
		* \date   July 2021
		* \param e
		* \return bool
		* \brief Event callback for a ImGui Window Resize event
		*/
		bool OnWindowResizeEvent(WindowResizeEvent& e);

		private:
			float m_Time = 0.0f;

	};



}
