#pragma once

#include "TNAH/Physics/PhysicsEngine.h"
#include "TNAH/Renderer/Mesh.h"
#include "ComponentIdentification.h"

namespace tnah 
{
	class GameObject;

	struct RigidBodyComponent 
	{
		Ref<Physics::Rigidbody> Body = nullptr;


	};

}
