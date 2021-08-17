#include <TNAH.h>
#include "MainLayer.h"

class Testbed : public tnah::Application
{
public:
	//Create a new Application called Editor and push a test layer onto the layerstack
	Testbed()
		:tnah::Application("TNAH Testbed Application")
	{
		GetWindow().SetCursorDisabled(m_CursorDisabled);
		GetWindow().SetVSync(m_VSync);
		PushLayer(new MainLayer());
	}


	~Testbed()
	{
	}
	
	void OnEvent(tnah::Event& e) override
	{
		//Close the application on press of Escape
		tnah::Application::OnEvent(e);
		if (e.GetEventType() == tnah::EventType::KeyPressed)
		{
			auto k = (tnah::KeyPressedEvent&)e;
			if (k.GetKeyCode() == tnah::Key::Escape)
			{
				tnah::WindowCloseEvent c = tnah::WindowCloseEvent();
				tnah::Application::OnEvent(c);
			}
			//Toggle the Cursor on or off
			if (k.GetKeyCode() == tnah::Key::D1)
			{
				m_CursorDisabled = !m_CursorDisabled;
				GetWindow().SetCursorDisabled(m_CursorDisabled);
			}
			//Toggle Wireframe on or off
			if (k.GetKeyCode() == tnah::Key::D2)
			{
				m_WireframeEnabled = !m_WireframeEnabled;
				tnah::RenderCommand::SetWireframe(m_WireframeEnabled);
			}

			//Toggle Fullscreen
			if (k.GetKeyCode() == tnah::Key::D3)
			{
				m_Fullscreen = !m_Fullscreen;
				GetWindow().ToggleFullScreen(m_Fullscreen);
			}

			//Toggle VSync
			if (k.GetKeyCode() == tnah::Key::D4)
			{
				m_VSync = !m_VSync;
				GetWindow().SetVSync(m_VSync);
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
	}

	bool m_CursorDisabled = false;
	bool m_WireframeEnabled = false;
	bool m_Fullscreen = false;
	bool m_VSync = false;

	friend class TestLayer;
};


//This is required to make a new application with our set layers inside this project.
// this is a single project and only uses engine classes and doesn't have access to all engine specific
// functions like raw OpenGL calls, thats a job for the engine to handle internally.
tnah::Application* tnah::CreateApplication()
{
	return new Testbed();
}


