#pragma once

#include "Core.h"
#include "Engine.h"

namespace tnah
{
	class TNAH_API Application
	{
	public:
		Application();
		virtual ~Application();


		virtual void Run();

	};

	Application* CreateApplication();
}

