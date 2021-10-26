#pragma once
#include <queue>
#include <reactphysics3d/reactphysics3d.h>

#include "Rigidbody.h"


namespace tnah {

	class GameObject;
	
	namespace Physics {

		class PhysicsCollision
		{
		public:

			class CollisionData
			{
			public:
				glm::vec3 GetContactPoint() const { return m_ContactPoint; }
				glm::vec3 GetContactNormal() const { return m_ContactNormal; }
				float GetPenetration() const { return m_PenetrationDepth; }
				

				std::pair<glm::vec3, glm::vec3> GetContactPositions() { return {m_Body1ContactPosition, m_Body2ContactPosition}; }

				std::pair<GameObject*, GameObject*> GetGameObjects() { return {m_Body1GameObject, m_Body2GameObject}; }

				std::pair<Ref<RigidBody>, Ref<RigidBody>> GetRigidBodies() { return {m_Body1RigidBody, m_Body2RigidBody}; }
			
			private:
				

				glm::vec3 m_ContactPoint = {0,0,0};
				glm::vec3 m_ContactNormal = {0,0,0};
			
				glm::vec3 m_Body1ContactPosition = {0,0,0};
				glm::vec3 m_Body2ContactPosition = {0,0,0};

				float m_PenetrationDepth = 0.0f;

				GameObject* m_Body1GameObject = nullptr;
				GameObject* m_Body2GameObject = nullptr;

				Ref<RigidBody> m_Body1RigidBody = nullptr;
				Ref<RigidBody> m_Body2RigidBody = nullptr;

				friend class PhysicsCollision;
			};
			
			
			PhysicsCollision();
			
			PhysicsCollision(rp3d::CollisionCallback::ContactPair contactPair);

			uint32_t GetTotalContactPoints() const { return m_TotalContactPoints; }
			
			std::queue<CollisionData>& GetCollisionData() { return m_CollisionData; }
 
		private:

			uint32_t m_TotalContactPoints = 0;
			
			/**
			 * @var m_CollisionData
			 *
			 * @brief A queue holding data about a collision.
			 */
			std::queue<CollisionData> m_CollisionData;
			
		};
	}
}