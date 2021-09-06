#pragma once

#include <TNAH.h>

class Testbed : public tnah::Application
{
public:
	//Create a new Application called Testbed and push a test layer onto the layerstack
	Testbed();
	~Testbed();
	
	void OnEvent(tnah::Event& e) override;
	bool& GetCursorToggleStatus() override { return m_CursorDisabled; }
	bool& GetWireframeToggleStatus() override  { return m_WireframeEnabled; }
	bool& GetFullscreenToggleStatus() override { return m_Fullscreen; }
	bool& GetVSyncToggleStatus() override { return m_VSync; }
private:
	bool m_CursorDisabled = false;
	bool m_WireframeEnabled = false;
	bool m_Fullscreen = false;
	bool m_VSync = false;

};

//This is required to make a new application with our set layers inside this project.
// this is a single project and only uses engine classes and doesn't have access to all engine specific
// functions like raw OpenGL calls, thats a job for the engine to handle internally.
inline tnah::Application* tnah::CreateApplication()
{
	return new Testbed();
}


