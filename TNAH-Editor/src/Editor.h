#pragma once

#include <TNAH.h>

namespace tnah {

	class Editor : public tnah::Application
	{
	public:
		//Create a new Application called Editor and push a test layer onto the layerstack
		Editor();


		~Editor();

		void OnEvent(tnah::Event& e) override;

		bool m_WireframeEnabled = false;
		bool m_Fullscreen = false;
		bool m_VSync = false;
	};




}