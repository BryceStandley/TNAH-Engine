#pragma once
#include "Layer.h"
#include "TNAH/Events/ApplicationEvent.h"
#include "TNAH/Events/KeyEvent.h"
#include "TNAH/Events/MouseEvent.h"

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
		virtual void OnAttach() override;

		/**
		 * \fn OnDetach
		* \author Bryce Standley
		* \date   July 2021
		*/
		virtual void OnDetach() override;

		/**
		 * \fn OnBegin
		* \author Bryce Standley
		* \date   July 2021
		* \brief Called at the start of a ImGui Frame
		*/
		void Begin();

		/**
		 * \fn OnEnd
		* \author Bryce Standley
		* \date   July 2021
		* \brief Called at the end of a ImGui Frame
		*/
		void End();

		/**
		 * \fn OnEvent
		* \author Bryce Standley
		* \date   July 2021
		* \param event
		*/
		virtual void OnEvent(Event& event) override;

		void SetDarkThemeColors();

	private:
		bool m_BlockEvents = true;
		float m_Time = 0.0f;

	};



}
