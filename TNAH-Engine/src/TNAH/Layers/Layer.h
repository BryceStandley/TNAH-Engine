#pragma once
#include "TNAH/Core/Core.h"
#include "TNAH/Events/Event.h"
#include "TNAH/Core/Timestep.h"
#include "TNAH/Physics/PhysicsTimestep.h"

namespace tnah {

	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnFixedUpdate(PhysicsTimestep ps) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}

