#pragma once
#include "TNAH/Core/Window.h"
#include "TNAH/Events/ApplicationEvent.h"
#include "TNAH/Events/MouseEvent.h"
#include "TNAH/Events/KeyEvent.h"

#include "Platform/OpenGL/OpenGLGraphicsContext.h"


#include <GLFW/glfw3.h>

namespace tnah {

	class WinWindow : public Window
	{
	public:
		WinWindow(const WindowProps& props);
		virtual ~WinWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		// Window attributes
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		inline void* GetNativeWindow() const override { return m_Window; }

		inline virtual void SetCursorDisabled(bool disable) override
		{
			if(disable)
				glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			else
				glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}

	virtual void ToggleFullScreen(const bool& enabled) override;
	inline bool IsFullscreen() const override {return m_Data.Fullscreen;}
	virtual void SetScreenResolution(const uint32_t& width, const uint32_t& height) override;
	
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window;
		GraphicsContext* m_Context;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;
			bool Fullscreen;
			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};





}
