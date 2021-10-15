#include "DemoApp.h"
#include "MainLayer.h"

	DemoApp::DemoApp()
		:tnah::Application("ICT398 Physics - Bryce Standley 33046367")
	{
		GetWindow().SetCursorDisabled(false);
		GetWindow().SetVSync(false);
		PushLayer(new MainLayer());
	}


	DemoApp::~DemoApp()
	{
	}
	
void DemoApp::OnEvent(tnah::Event& e)
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

		tnah::Application::OnEvent(e);
	}







