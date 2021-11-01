#pragma once

#include <TNAH.h>

class DemoApp : public tnah::Application
{
public:
	//Create a new Application called Testbed and push a test layer onto the layerstack
	DemoApp();
	~DemoApp();
	
	void OnEvent(tnah::Event& e) override;
};

//This is required to make a new application with our set layers inside this project.
// this is a single project and only uses engine classes and doesn't have access to all engine specific
// functions like raw OpenGL calls, thats a job for the engine to handle internally.
inline tnah::Application* tnah::CreateApplication()
{
	return new DemoApp();
}


