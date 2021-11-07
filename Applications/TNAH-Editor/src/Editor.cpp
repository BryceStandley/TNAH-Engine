#include "Editor.h"
#include "EditorLayer.h"


namespace tnah {

		Editor::Editor()
			:tnah::Application("TNAH Editor")
		{
			GetWindow().SetVSync(false);
			SetEditorMode(true);
			PushLayer(new EditorLayer());
		}


		Editor::~Editor()
		{
		}

		void Editor::OnEvent(tnah::Event& e)
		{
			tnah::Application::OnEvent(e);
		}



}


//This is required to make a new application with our set layers inside this project.
// this is a single project and only uses engine classes and doesn't have access to all engine specific
// functions like raw OpenGL calls, thats a job for the engine to handle internally.
tnah::Application* tnah::CreateApplication()
{
	return new Editor();
}


