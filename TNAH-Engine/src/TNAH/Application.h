#pragma once

#include "Core.h"

namespace tnah
{
	class TNAH_API Application
	{
	public:
		Application();
		virtual ~Application();


		void Run();

	};

	Application* CreateApplication();
}

