#pragma once
#include "TNAH/Core/Core.h"
#include "TNAH/Core/Input.h"

#include <GLFW/glfw3.h>

namespace tnah {

	class WinInput : public Input
	{

	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;

		virtual bool IsMouseButtonPressedImpl(int button) override;

		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
		virtual std::pair<float, float> GetMousePosImpl() override;
	};
}
