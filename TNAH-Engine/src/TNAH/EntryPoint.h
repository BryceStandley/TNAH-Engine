#pragma once

#ifdef TNAH_PLATFORM_WINDOWS

	extern tnah::Application* tnah::CreateApplication();

	int main(int argc, char** argv)
	{
		tnah::Log::Init();
		TNAH_CORE_WARN("Core Log Initialized!");
		TNAH_INFO("Application Log Initialized!");

		auto app = tnah::CreateApplication();
		app->Run();
		delete app;
	}

#endif
