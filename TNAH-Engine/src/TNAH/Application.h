#pragma once

#include "TNAH/Core/Core.h"
#include "TNAH/Window.h"
//#include "Engine.h"

namespace tnah
{
	class TNAH_API Application
	{
	public:
		Application();
		virtual ~Application();


		virtual void Run();

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	Application* CreateApplication();
}

