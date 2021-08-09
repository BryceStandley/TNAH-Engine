#include "tnahpch.h"
#include "Application.h"

#include <GLFW/glfw3.h>

namespace tnah
{


	Application* Application::s_Instance = nullptr;

	Application::Application(const std::string& name)
	{
		TNAH_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = Window::Create(WindowProps(name));
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		

		Renderer::Init();

		if(m_ImGuiLayer == nullptr)
		{
			m_ImGuiLayer = new ImGuiLayer();
			PushOverlay(m_ImGuiLayer);
		}
	}

	Application::~Application()
	{
	}


	void Application::Run()
	{
		PhysicsTimestep physicsTimestep(60.0f);

		while (m_Running)
		{
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_DeltaTime;
			m_DeltaTime = time;

			physicsTimestep.AddFrameTime(timestep);

			if (!m_Minimized)
			{
				for (Layer* layer : m_LayerStack)
				{
					while (physicsTimestep.FixedUpdateCheck())
					{
						layer->OnFixedUpdate(physicsTimestep);
						physicsTimestep.Update();
					}

					layer->OnUpdate(timestep);
				}
			}

			m_ImGuiLayer->Begin();
			{
				for (Layer* layer : m_LayerStack)
					layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();


			m_Window->OnUpdate();
		}
	}

	bool Application::OnMonitorResolutionChange(MonitorResolutionChangeEvent& e)
	{
		const uint32_t width = e.GetWidth();
		const uint32_t height = e.GetHeight();
		GetWindow().SetScreenResolution(width, height);
		return true;
	}
	
	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		const uint32_t width = e.GetWidth(), height = e.GetHeight();
		if (width == 0 || height == 0)
		{
			m_Minimized = true;
			return false;
		}

		RenderCommand::SetViewport(0, 0, width, height);
		m_Minimized = false;
		return false;
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<MonitorResolutionChangeEvent>(BIND_EVENT_FN(OnMonitorResolutionChange));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}
	
	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}
}
