#include "tnahpch.h"
#include "PhysicsAPI.h"

namespace tnah
{
    Scope<PhysicsAPI> PhysicsAPI::Create()
    {
        switch(p_Api)
        {
            case PhysicsAPI::API::none: TNAH_CORE_ASSERT(false, "PhysicsAPI::None is currently not supported!"); return nullptr;
            case PhysicsAPI::API::tnah: TNAH_CORE_ASSERT(false, "PhysicsAPI::TNAH-Physics is currently not supported!"); return nullptr;
            case PhysicsAPI::API::react: TNAH_CORE_ASSERT(false, "PhysicsAPI::React Physics 3D is currently not supported!"); return nullptr;
        }

        TNAH_CORE_ASSERT(false, "Unknown PhysicsAPI!");
        return nullptr;
    }

}