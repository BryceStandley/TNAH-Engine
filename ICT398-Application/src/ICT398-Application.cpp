#include "ICT398-Application.h"
#include "MainLayer.h"

	ICT398Application::ICT398Application()
		:tnah::Application("ICT398 Milestone 1 - TNAH-Engine")
	{
		tnah::Application::Get().GetWindow().SetCursorDisabled(false);
		tnah::Application::Get().GetWindow().SetVSync(false);
		PushLayer(new MainLayer());
	}


	ICT398Application::~ICT398Application()
	{
	}
	
	void ICT398Application::OnEvent(tnah::Event& e)
	{
		
		if(e.GetEventType() == tnah::EventType::WindowClose)
		{
			tnah::WindowCloseEvent c = tnah::WindowCloseEvent();
			tnah::Application::OnEvent(c);
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







