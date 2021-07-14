#pragma once
#include"TNAH/Core/Core.h"
#include "Layer.h"
#include "TNAH/Application.h"
#include "imgui.h"
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

namespace tnah {

	class TNAH_API ImGuiLayer : public Layer
	{
	public:
		/**
		 * \fn ImGuiLayer
		* \author Bryce Standley
		* \date   July 2021
		*/
		ImGuiLayer(std::string name);

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
		 * \fn OnBegin
		* \author Bryce Standley
		* \date   July 2021
		* \brief Called at the start of a ImGui Frame
		*/
		void OnBegin();

		/**
		 * \fn OnUpdate
		* \author Bryce Standley
		* \date   July 2021
		* \brief Virtual function to be implimented by a given ImGui Layer
		* can be used to insert any imgui related items into the render stack for the layer
		* and be rendered as well as linked to its given actions
		*/
		virtual void OnUpdate() {}

		/**
		 * \fn OnEnd
		* \author Bryce Standley
		* \date   July 2021
		* \brief Called at the end of a ImGui Frame
		*/
		void OnEnd();

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

		void SetDarkThemeColors();

		private:
			float m_Time = 0.0f;

	};



}
