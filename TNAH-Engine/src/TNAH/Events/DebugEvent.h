#pragma once
#include "TNAH/Core/Core.h"
#include "TNAH/Events/Event.h"

namespace tnah {

	class DebugEvent : public Event
	{
	public:
		std::pair<std::string, std::string> GetDetails() { return { m_Name, m_Description }; }

		EVENT_CLASS_CATEGORY(EventCategoryDebugCore | EventCategoryDebugApp)
	protected:

		std::string m_Name;
		std::string m_Description;
	};
}
