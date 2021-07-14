#include <tnahpch.h>
#include "DebugLayer.h"

namespace tnah {

	DebugLayer::DebugLayer()
		: ImGuiLayer("DebugLayer")
	{
	}

	void DebugLayer::OnUpdate()
	{
		this->OnBegin();

		ImGuiIO io = ImGui::GetIO();

		ImGui::Text("FPS: %.1f", io.Framerate);

		this->OnEnd();
	}
}