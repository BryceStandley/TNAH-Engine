#pragma once

#include "PhysicsStructures.h"
#include "TNAH/Core/Math.h"
#include <reactphysics3d/reactphysics3d.h>

#include "TNAH/Core/AABB.h"
#include "TNAH/Core/AABB.h"

namespace tnah::Physics {
		
		class Collider : public RefCounted
		{
		public:
			enum class Type
			{
				Box, Sphere, Capsule
			};
			
			Collider();
			Collider(rp3d::CollisionShape* collider, Type type);

			static Ref<Collider> Create(rp3d::CollisionShape* collider, Type type);
			
			void SetPosition(const glm::vec3& position) { m_LocalPosition = position; }
			void SetOrientation(const glm::quat& orientation) { m_LocalOrientation = orientation; }

			glm::vec3 GetColliderPosition() const { return m_LocalPosition; }
			glm::quat GetColliderOrientation() const { return m_LocalOrientation; }
			
			BodyMass& GetColliderMass() { return m_Mass; }
			Type GetType() const { return m_Type; }
			std::pair<Type, rp3d::CollisionShape*> GetCollisionShapePair() { return { m_Type, m_Collider }; }

			glm::vec3 GetLocalColliderInertiaTensor();

			float GetVolume() { return m_Volume; }
			void SetVolume(const float value) { m_Volume = value; }
			
			float GetDensity() { return m_Density; }
			void SetDensity(const float value) { m_Density = value; }

		private:

			/**
			 * @fn void InitializeBox();
			 *
			 * @brief Sets us the local mass values of the Collider based on the BoxShape.
			 * @author  Bryce Standley
			 */
			void InitializeBox();

			/**
			* @fn void InitializeSphere();
			*
			* @brief Sets us the local mass values of the Collider based on the SphereShape.
			* @author  Bryce Standley
			*/
			void InitializeSphere();

			/**
			* @fn void InitializeCapsule();
			*
			* @brief Sets us the local mass values of the Collider based on the CapsuleShape.
			* @author  Bryce Standley
			*/
			void InitializeCapsule();

			

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
			* @var m_LocalPosition
			*
			* @brief The position of the Collider locally to its parent Rigidbody.
			* @note The position should always be at 0,0,0 ie the centre of the Rigidbody.
			* @note However the position should be changed if the object requires multiple colliders with different positions relative to the Rigidbody.
			*/
			glm::vec3 m_LocalPosition = {};

			/**
			* @var m_LocalOrientation
			*
			* @brief The orientation of the Collider locally to its parent Rigidbody.
			*/
			glm::quat m_LocalOrientation = {};

			/**
			* @var m_Mass
			*
			* @brief The local BodyMass information for this Collider.
			*/
			BodyMass m_Mass;

			InertiaTensor m_InertiaTensor;

			uint32_t ID = 0;

			/**
			 * @var m_Volume
			 *
			 * @brief The volume of the collider in meters cubed.
			 */
			float m_Volume = 0.0f;

			/**
			* @var m_Density
			*
			* @brief The density of the colliders material in kg per meter cubed. Default 1000kg/m3 ie the density of water.
			*/
			float m_Density = 1.0f;
			
			friend class PhysicsEngine;
			friend class EditorUI;
		};
	
}
