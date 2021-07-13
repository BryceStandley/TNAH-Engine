#pragma once

#include "TNAH/Core/Core.h"
#include "TNAH/Core/Window.h"
#include "TNAH/Events/ApplicationEvent.h"
#include "TNAH/Events/MouseEvent.h"
#include "TNAH/Events/KeyEvent.h"
#include "Layers/LayerStack.h"

namespace tnah
{
	class TNAH_API Application
	{
	public:
		Application();
		virtual ~Application();


		virtual void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;

		static Application* s_Instance;
	};

	Application* CreateApplication();
}

