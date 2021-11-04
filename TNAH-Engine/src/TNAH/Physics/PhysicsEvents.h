#pragma once

#pragma warning(push, 0)
#include <reactphysics3d/reactphysics3d.h>
#include <entt.hpp>
#pragma warning(pop)

namespace tnah {
	namespace Physics {
		class PhysicsEvents : public rp3d::EventListener
		{
		public:
			void onContact(const CallbackData& callbackData) override;

			void onTrigger(const rp3d::OverlapCallback::CallbackData& callbackData) override;
		};
	}
}
