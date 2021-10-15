#pragma once

#include "PhysicsStructures.h"
#include "TNAH/Core/Math.h"
#include <reactphysics3d/reactphysics3d.h>

namespace tnah::Physics {
		
		class Collider : public RefCounted
		{
		public:
			enum class Type
			{
				Box, Sphere, Capsule
			};
			
			Collider();
			Collider(rp3d::CollisionShape* collider, Type type, float mass = 1.0f);

			static Ref<Collider> Create(rp3d::CollisionShape* collider, Type type, float mass = 1.0f);
			
			void SetPosition(const glm::vec3& position) { m_Position = position; }
			void SetOrientation(const glm::quat& orientation) { m_Orientation = orientation; }

			glm::vec3 GetColliderPosition() const { return m_Position; }
			glm::quat GetColliderOrientation() const { return m_Orientation; }
			
			BodyMass GetColliderMass() const { return m_Mass; }
			Type GetType() const { return m_Type; }
			std::pair<Type, rp3d::CollisionShape*> GetCollisionShapePair() { return { m_Type, m_Collider }; }

		private:

			/**
			 * @fn void InitializeBoxMass();
			 *
			 * @brief Sets us the local mass values of the Collider based on the BoxShape.
			 * @author  Bryce Standley
			 */
			void InitializeBoxMass();

			/**
			* @fn void InitializeSphereMass();
			*
			* @brief Sets us the local mass values of the Collider based on the SphereShape.
			* @author  Bryce Standley
			*/
			void InitializeSphereMass();

			/**
			* @fn void InitializeCapsuleMass();
			*
			* @brief Sets us the local mass values of the Collider based on the CapsuleShape.
			* @author  Bryce Standley
			*/
			void InitializeCapsuleMass();

		private:
			/**
			* @var m_Collider
			*
			* @brief The Reactphysics3D CollisionShape. This needs to be reinterpreted into a BoxShape or SphereShape depending on the ColliderType.
			*/
			rp3d::CollisionShape* m_Collider = nullptr;

			/**
			* @var m_Type
			*
			* @brief The type of the Collider. Either Box or Sphere currently.
			*/
			Type m_Type = Type::Box;

			/**
			* @var m_Position
			*
			* @brief The position of the Collider locally to its parent Rigidbody.
			* @note The position should always be at 0,0,0 ie the centre of the Rigidbody.
			* @note However the position should be changed if the object requires multiple colliders with different positions relative to the Rigidbody.
			*/
			glm::vec3 m_Position = {};

			/**
			* @var m_Orientation
			*
			* @brief The orientation of the Collider locally to its parent Rigidbody.
			*/
			glm::quat m_Orientation = {};

			/**
			* @var m_Mass
			*
			* @brief The local BodyMass information for this Collider.
			*/
			BodyMass m_Mass;

			friend class EditorUI;
		};
	
}
