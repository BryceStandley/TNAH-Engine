#pragma once

#include "TNAH/Core/Core.h"

#include "TNAH/Core/Window.h"
#include "TNAH/Events/ApplicationEvent.h"
#include "TNAH/Layers/LayerStack.h"
#include "TNAH/Layers/UI.h"


#include "Timestep.h"

#include "TNAH/Layers/ImGuiLayer.h"
#include "TNAH/Renderer/Shader.h"
#include "TNAH/Renderer/Renderer.h"

#include "TNAH/Scene/SceneCamera.h"

#include "TNAH/Physics/PhysicsTimestep.h"

/**
 * @fn	int main(int argc, char** argv);
 *
 * @brief	Main entry-point for this application
 *
 * @author	Dylan Blereau
 * @date	7/09/2021
 *
 * @param 	argc	The number of command-line arguments provided.
 * @param 	argv	An array of command-line argument strings.
 *
 * @returns	Exit-code for the process - 0 for success, else an error code.
 */

int main(int argc, char** argv);

namespace tnah
{
	class Scene;
#define BIND_EVENT_FN(x) std::bind(&tnah::Application::x, this, std::placeholders::_1)
	class Application
	{
	public:
		Application(const std::string& name = "TNAH App");
		virtual ~Application();


		virtual void Run();

		virtual void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		void Close();

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

		static std::pair<std::string, int> OpenFileFromBrowser();
		static std::pair<std::string, int> OpenAudioFromBrowser();
		static std::pair<std::string, int> OpenMeshFromBrowser();
		static std::pair<std::string, int> SaveFileAs(const char* fileName);

		bool CheckEditor() const { return m_IsEditor; }
		void SetEditorMode(const bool& isEditor) { m_IsEditor = isEditor; }
		
		virtual bool& GetCursorToggleStatus() = 0;
		virtual bool& GetWireframeToggleStatus() = 0;
		virtual bool& GetFullscreenToggleStatus() = 0;
		virtual bool& GetVSyncToggleStatus() = 0;
	
	private:

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
		bool OnMonitorResolutionChange(MonitorResolutionChangeEvent& e);

		
		
		Scope<Window> m_Window;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack = LayerStack();
		float m_DeltaTime = 0.0f;
		ImGuiLayer* m_ImGuiLayer;
		bool m_IsEditor = false;

		
		
		static Application* s_Instance;

		friend int ::main(int argc, char** argv);


	};

	Application* CreateApplication();
}

