#include "Editor.h"
#include "EditorLayer.h"


namespace tnah {

		Editor::Editor()
			:tnah::Application("TNAH Editor")
		{
			GetWindow().SetVSync(m_VSync);
			SetEditorMode(true);
			PushLayer(new EditorLayer());
		}


		Editor::~Editor()
		{
		}

		void Editor::OnEvent(tnah::Event& e)
		{
			//Close the application on press of Escape
			Application::OnEvent(e);
			if (e.GetEventType() == EventType::KeyPressed)
			{
				auto k = (KeyPressedEvent&)e;

				//Toggle Wireframe on or off
				if (k.GetKeyCode() == tnah::Key::D2)
				{
					m_WireframeEnabled = !m_WireframeEnabled;
					RenderCommand::SetWireframe(m_WireframeEnabled);
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



}


//This is required to make a new application with our set layers inside this project.
// this is a single project and only uses engine classes and doesn't have access to all engine specific
// functions like raw OpenGL calls, thats a job for the engine to handle internally.
tnah::Application* tnah::CreateApplication()
{
	return new Editor();
}


