#include <tnahpch.h>
#include "ImGuiLayer.h"

namespace tnah {

	ImGuiLayer::ImGuiLayer(std::string name)
		: Layer(name)
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::OnAttach()
	{
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

		io.Fonts->AddFontFromFileTTF("assets/fonts/opensans/OpenSans-Bold.ttf", 18.0f);
		io.FontDefault = io.Fonts->AddFontFromFileTTF("assets/fonts/opensans/OpenSans-Regular.ttf", 18.0f);

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		SetDarkThemeColors();

		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 330");
	}

	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnBegin()
	{
		ImGuiIO& io = ImGui::GetIO();
		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::OnEnd()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		//Render
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	void ImGuiLayer::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseButtonPressedEvent>(TNAH_BIND_EVENTS_FN(ImGuiLayer::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(TNAH_BIND_EVENTS_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
		dispatcher.Dispatch<MouseMovedEvent>(TNAH_BIND_EVENTS_FN(ImGuiLayer::OnMouseMovedEvent));
		dispatcher.Dispatch<MouseScrolledEvent>(TNAH_BIND_EVENTS_FN(ImGuiLayer::OnMouseScrollEvent));
		dispatcher.Dispatch<KeyPressedEvent>(TNAH_BIND_EVENTS_FN(ImGuiLayer::OnKeyPressedEvent));
		dispatcher.Dispatch<KeyTypedEvent>(TNAH_BIND_EVENTS_FN(ImGuiLayer::OnKeyTypedEvent));
		dispatcher.Dispatch<KeyReleasedEvent>(TNAH_BIND_EVENTS_FN(ImGuiLayer::OnKeyReleasedEvent));
		dispatcher.Dispatch<WindowResizeEvent>(TNAH_BIND_EVENTS_FN(ImGuiLayer::OnWindowResizeEvent));
	}

	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = true;

		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = false;

		return false;
	}

	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.GetX(), e.GetY());

		return false;
	}

	bool ImGuiLayer::OnMouseScrollEvent(MouseScrolledEvent& e)
	{
		ImGuiIO io = ImGui::GetIO();
		io.MouseWheel += e.GetYOffset();
		io.MouseWheelH += e.GetXOffset();

		return false;
	}

	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
	{
		ImGuiIO io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = true;

		return false;
	}

	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
	{
		ImGuiIO io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = false;

		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

		return false;
	}

	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
	{
		ImGuiIO io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = true;
		int keycode = e.GetKeyCode();
		if (keycode > 0 && keycode < 0x10000)
		{
			io.AddInputCharacter((unsigned short)keycode);
		}

		return false;
	}

	bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e)
	{
		ImGuiIO io = ImGui::GetIO();
		io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);

		return false;
	}

	void ImGuiLayer::SetDarkThemeColors()
	{
		auto& colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };

		// Headers
		colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Buttons
		colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Frame BG
		colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Tabs
		colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
		colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
		colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

		// Title
		colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	}

}
