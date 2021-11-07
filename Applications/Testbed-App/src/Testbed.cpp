#include "Testbed.h"
#include "MainLayer.h"

	Testbed::Testbed()
		:tnah::Application("TNAH Testbed Application")
	{
		GetWindow().SetCursorDisabled(false);
		GetWindow().SetVSync(false);
		PushLayer(new MainLayer());
	}


	Testbed::~Testbed()
	{
	}
	
void Testbed::OnEvent(tnah::Event& e)
	{
		//Close the application on press of Escape
		if (e.GetEventType() == tnah::EventType::KeyPressed)
		{
			auto k = (tnah::KeyPressedEvent&)e;
			if (k.GetKeyCode() == tnah::Key::Escape)
			{
				tnah::WindowCloseEvent c = tnah::WindowCloseEvent();
				tnah::Application::OnEvent(c);
			}
		}
		
		//Dispatch an event to the application on window resize
		if (e.GetEventType() == tnah::EventType::WindowResize)
		{
			auto& re = (tnah::WindowResizeEvent&)e;
			tnah::Application::OnEvent(e);
		}

		if(e.GetEventType() == tnah::EventType::MonitorResolutionChange)
		{
			TNAH_CORE_INFO("Application Received resolution change");
		}
		tnah::Application::OnEvent(e);
	}







