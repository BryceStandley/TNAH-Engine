#pragma once
#pragma warning(push,0)
#include <reactphysics3d/reactphysics3d.h>

#pragma warning(pop)

#include <entt.hpp>
#include "PhysicsStructs.h"
#include "Rigidbody.h"
#include "TNAH/Physics/PhysicsTimestep.h"
#include "TNAH/Scene/Components/Components.h"
#include "TNAH/Scene/Components/PhysicsComponents.h"
#include "Rigidbody.h"
#include "TNAH/Core/Timestep.h"

namespace tnah
{
	class Renderer;
	class GameObject;
}

namespace tnah::Physics
{
	class PhysicsManager : public RefCounted
	{
	public:

		PhysicsManager();

		~PhysicsManager();

		glm::vec3& GetGravity() { return m_Gravity; }
		void SetGravity(const glm::vec3& gravity) { m_Gravity = gravity; }
		void SetGravityState(const bool& state) { m_GravityEnabled = state; }
		bool& GetGravityState() { return m_GravityEnabled; }

	private:

		bool Initialise(rp3d::EventListener* CollisionEventListener);

		void OnFixedUpdate(PhysicsTimestep timestep) const;

		void Destroy();

		rp3d::RigidBody* CreateRigidBody(const TransformComponent& transform) const;

		void DestroyRigidBody(rp3d::CollisionBody* rigidbody) const;

		rp3d::CollisionBody* CreateCollisionBody(const TransformComponent& transform) const;

		void DestroyCollisionBody(rp3d::CollisionBody* body) const;

		void CreateColliderRenderer();

	private:
		rp3d::PhysicsCommon m_PhysicsCommon;

		rp3d::PhysicsWorld* m_PhysicsWorld = nullptr;

		rp3d::DefaultLogger* m_PhysicsLogger = nullptr;

		bool m_ColliderRender = false;

		bool m_ColliderRendererInit = false;

		Ref<VertexArray> m_LinesVertexArray;

		Ref<VertexBuffer> m_LinesVertexBuffer;

		Ref<VertexArray> m_TraingleVertexArray;

		Ref<VertexBuffer> m_TriangleVertexBuffer;

		Ref<Shader> m_Shader;

		VertexBufferLayout m_ColliderLayout;

		bool m_GravityEnabled = false;

		glm::vec3 m_Gravity = { 0.0f, -9.8f, 0.0f };

		bool m_Active = false;

		bool m_Logging = false;

		std::unordered_map<uint32_t, Ref<Rigidbody>> m_Rigidbodies;

		uint32_t m_TotalRigidBodies = 0;

		friend class PhysicsEngine;

	};

	class PhysicsEngine
	{
	public:
		static Ref<PhysicsManager> GetManager();

		static bool IsActive();

		static bool Init(rp3d::EventListener* collisionEventListener);

		static void OnFixedUpdate(Timestep deltaTime, PhysicsTimestep timestep, entt::registry& componentRegistry);

		static void OnUpdate(Timestep timestep);

		static void Destroy();

		static void DestroyRigidbody(Ref<Rigidbody> rigidbody);

		static Ref<Rigidbody> CreateRigidbody(GameObject& gameObject);

		static void ToggleColliderRendering();

		static bool& GetColliderRendererHandle();

		static TransformComponent GetColliderRendererTransform();

		static Ref<Collider> CreateBoxCollider(Ref<Rigidbody> rigidbody, const glm::vec3& halfExtents);

		static Ref<Collider> CreateSphereCollider(Ref<Rigidbody> rigidbody, const float& radius);

		static Ref<Collider> CreateCapsuleCollider(Ref<Rigidbody> rigidbody, const float& radius, const float& height);

	private:
		static void EnableLogging();

		static bool IsColliderRenderingEnabled();

		static std::pair<std::pair<Ref<VertexArray>, Ref<VertexBuffer>>, std::pair<Ref<VertexArray>, Ref<VertexBuffer>>> GetColliderRenderObjects();

		static Ref<Shader> GetColliderShader();

		static void UpdateColliderRenderer();

		static rp3d::DebugRenderer* GetColliderRenderer();

		static void PhysicsLoggerInit();

		static void ProcessRigidbodyVelocities(const Timestep& deltaTime, TransformComponent& transform, Ref<Rigidbody> rigidbody);
		static void ProcessRigidbodyPositions(const Timestep& deltaTime, TransformComponent& transform, Ref<Rigidbody> rigidbody);
		static void ResetRigidbodyForcesAndTorques(Ref<Rigidbody> rigidbody);

	private:
		static Ref<PhysicsManager> m_PhysicsManager;

		static TransformComponent m_ColliderTransform;

		friend class Scene;
		friend class Renderer;
	};
}