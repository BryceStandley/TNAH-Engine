#pragma once

#include "TNAH/Core/Core.h"

#include "TNAH/Core/Window.h"
#include "TNAH/Events/ApplicationEvent.h"
#include "Layers/LayerStack.h"

#include "TNAH/Core/Timestep.h"

#include "Layers/ImGuiLayer.h"
#include "TNAH/Renderer/Shader.h"
#include "TNAH/Renderer/Renderer.h"

#include "TNAH/Scene/SceneCamera.h"


int main(int argc, char** argv);

namespace tnah
{
	class Application
	{
	public:
		Application(const std::string& name = "TNAH App");
		virtual ~Application();


		virtual void Run();

		virtual void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }


	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		Scope<Window> m_Window;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack = LayerStack();
		ImGuiLayer* m_ImGuiLayer;
		float m_DeltaTime = 0.0f;

		

		static Application* s_Instance;
		friend int ::main(int argc, char** argv);

		
	};

	Application* CreateApplication();
}

