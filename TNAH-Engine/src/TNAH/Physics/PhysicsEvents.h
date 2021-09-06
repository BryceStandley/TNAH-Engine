#pragma once

#pragma warning(push, 0)
#include <reactphysics3d/reactphysics3d.h>
#include <entt.hpp>
#pragma warning(pop)

namespace tnah
{
    class PhysicsEvents : public rp3d::EventListener
    {
    public:
        /**
         * @brief Event callback overriding React. Naming must be the same as React.
         */
        void onContact(const CallbackData& callbackData) override;

        /**
        * @brief Event callback overriding React. Naming must be the same as React.
        */
        void onTrigger(const rp3d::OverlapCallback::CallbackData& callbackData) override;
    private:
        //Maybe Reference to scene pointer
    };
}
