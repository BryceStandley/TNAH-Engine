#pragma once
#include "TNAH/Core/Core.h"
#include "ImGuiLayer.h"

namespace tnah {

	/**
	 * \file DebugLayer.h
	 * \author Bryce Standley
	 * \brief This layer allows the user to add debug information to the application and display it on the screen
	 * \date  July 2021
	 */
	class TNAH_API DebugLayer : public ImGuiLayer
	{
	public:
		DebugLayer();

		void OnUpdate() override;

	};


}
