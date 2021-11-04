#pragma once

#include "PhysicsStructures.h"
#include "TNAH/Core/Math.h"

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
			Collider(rp3d::CollisionShape* c, Type t);

			static Ref<Collider> Create(rp3d::CollisionShape* collider, Type type);
			
			void SetPosition(const glm::vec3& position) { localPosition = position; }
			void SetOrientation(const glm::quat& orientation) { localOrientation = orientation; }

			glm::vec3 GetColliderPosition() const { return localPosition; }
			glm::quat GetColliderOrientation() const { return localOrientation; }
			
			Mass& GetColliderMass() { return mass; }
			void SetColliderMass(float m);
			Type GetType() const { return type; }
			std::pair<Type, rp3d::CollisionShape*> GetCollisionShapePair() { return { type, collider }; }

			glm::vec3 GetLocalColliderInertiaTensor();

			float GetVolume() { return volume; }
			void SetVolume(const float value) { volume = value; }
			
			float GetDensity() { return density; }
			void SetDensity(const float value) { density = value; }

			uint32_t GetId() const {return ID;}
			void SetId(const uint32_t i) {ID = i;}

		private:

			float radius;
			
			glm::vec3 size;

			void InitializeBox();
			
			void InitializeSphere();
			
			rp3d::CollisionShape* collider = nullptr;
			
			Type type = Type::Box;
			
			glm::vec3 localPosition = {};
			
			glm::quat localOrientation = {};
			
			Mass mass;

			InertiaTensor inertiaTensor;

			uint32_t ID = 0;
			
			float volume = 0.0f;
			
			float density = 1.0f;
		};
	
}
