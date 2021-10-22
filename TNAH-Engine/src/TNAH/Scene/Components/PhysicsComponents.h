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

		bool Edit = false;

		bool UseEdit = false;

		RigidBodyComponent();

		RigidBodyComponent(const RigidBodyComponent& other) = default;

		RigidBodyComponent(GameObject& gameObject, const Physics::BodyType& type = Physics::BodyType::Dynamic);

		void OnUpdate(TransformComponent& transform);

		void ApplyForce(const glm::vec3& direction, const glm::vec3& force);

		void ApplyTorque(const glm::vec3& direction, const glm::vec3& torque);

		Ref<Physics::Collider> AddCollider(const glm::vec3& size);

		Ref<Physics::Collider> AddCollider(const float& sphereRadius);

		Ref<Physics::Collider> AddCollider(const float& capsuleRadius, const float& capsuleHeight);

	private:
		inline static std::string s_SearchString = "rigidbody component";
		inline static ComponentTypes s_Types = { { ComponentVariations::RigidBody }, { {ComponentCategory::Physics}} };

		friend class EditorUI;
	};

}
