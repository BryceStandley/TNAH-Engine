#pragma once

#include "PhysicsCollision.h"
#include "TNAH/Physics/PhysicsTimestep.h"

#include <queue>

namespace tnah {
	namespace Physics {
		
		class CollisionDetectionEngine : public RefCounted
		{
		public:
			static Ref<CollisionDetectionEngine> Create();
			
			CollisionDetectionEngine();
			
			void FixedUpdate(rp3d::PhysicsWorld* physicsWorld, PhysicsTimestep physTime);

			std::queue<PhysicsCollision>& GetCurrentCollisions() { return m_CurrentCollisions; }

			void RegisterCollision(PhysicsCollision collision) { m_CurrentCollisions.push(collision); }

		private:

			std::queue<PhysicsCollision> m_CurrentCollisions;
		};
		
	}
}
