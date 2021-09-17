#include "tnahpch.h"
#include "PhysicsCommand.h"

#include "Platform/React/ReactPhysics.h"

namespace tnah
{
    PhysicsAPI * PhysicsCommand::s_PhysicsAPI = new ReactPhysics;
}
