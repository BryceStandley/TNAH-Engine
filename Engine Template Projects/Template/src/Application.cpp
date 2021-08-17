#include <TNAH.h>
#include "ApplicationLayer.h"

class App : public tnah::Application
{
public:
	//Create a new Application with a name
	//Set any startup settings for the application like disabling the cursor
	// Create and push a layer to the layerstack
	// Layers are where everything happens for the active scene
	App()
		:tnah::Application("TNAH Application")
	{
		GetWindow().SetCursorDisabled(m_CursorDisabled);
		GetWindow().SetVSync(m_VSync);
		PushLayer(new ApplicationLayer());
	}

	//Destroy anything aditional made within the application before closing
	~App()
	{
	}
	

	void OnEvent(tnah::Event& e) override
	{
		//On Event is called everytime theres an event
		//Here are some examples of key pressed events to toggle
		// window controls or rendering settings at runtime

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
	}

	//Boolans to track the state of the application settings
	// these aren't required but are useful to have and track for toggling
	bool m_CursorDisabled = false;
	bool m_WireframeEnabled = false;
	bool m_Fullscreen = false;
	bool m_VSync = false;
};


//This is required to make a new application with our set layers inside this project.
// this is a single project and only uses engine classes and doesn't have access to all engine specific
// functions like raw OpenGL calls, thats a job for the engine to handle internally.
tnah::Application* tnah::CreateApplication()
{
	//Always return a new tnah::Application derived object
	return new App();
}


