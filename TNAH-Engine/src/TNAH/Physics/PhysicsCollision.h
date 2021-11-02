#pragma once
#include <queue>
#include <reactphysics3d/reactphysics3d.h>

#include "Rigidbody.h"


namespace tnah {

	class GameObject;
	
	namespace Physics {
		
			struct CollisionData
			{
				glm::vec3 contactPoint = {0,0,0};
				glm::vec3 contactNormal = {0,0,0};
			
				glm::vec3 body1ContactPosition = {0,0,0};
				glm::vec3 body2ContactPosition = {0,0,0};

				float penetrationDepth = 0.0f;

				GameObject* body1GameObject = nullptr;
				GameObject* body2GameObject = nullptr;

				Ref<RigidBody> body1RigidBody = nullptr;
				Ref<RigidBody> body2RigidBody = nullptr;
			};
		;
	}
}