#pragma once
#pragma warning(push, 0)
#include <reactphysics3d/reactphysics3d.h>

#pragma warning(pop)

#include <entt.hpp>

#include "CollisionDetectionEngine.h"
#include "PhysicsStructures.h"
#include "Rigidbody.h"
#include "TNAH/Physics/PhysicsTimestep.h"
#include "TNAH/Scene/Components/Components.h"
#include "TNAH/Scene/Components/PhysicsComponents.h"
#include "Rigidbody.h"
#include "TNAH/Core/Timestep.h"

#include "TNAH/Scene/Components/PhysicsComponents.h"

namespace tnah {
 class Renderer;
 class GameObject;
}

namespace tnah::Physics
{
 
#pragma region PhysicsManager
 
 /**
     * @class	PhysicsManager
     *
     * @brief	Manager for physics that inherits from the RefCounted class. This class is to remain private and contain
     * all ReactPhysics3D world objects. Any control of the PhysicsManager should be done from tnah::Physics::PhysicsEngine
     *
     * @author	Chris Logan
     * @date	11/09/2021
     */

    class PhysicsManager : public RefCounted
    {
    public:

        /**
         * @fn	PhysicsManager::PhysicsManager();
         *
         * @brief	Default constructor.
         * This constructor is empty as the object requires the Physics::Initialise(rp3d::EventListener* collisionEventListener) to be called 
         *
         * @author	Dylan Blereau
         * @date	12/09/2021
         */

        PhysicsManager();

        /**
         * @fn	PhysicsManager::~PhysicsManager();
         *
         * @brief	Destructor. Safeguards prevent deletion of empty pointers of
         * PhysicsManager::m_PhysicsWorld and PhysicsManager::m_PhysicsLogger if Physics::Initialise(rp3d::EventListener* collisionEventListener)
         * was never called or Physics::Initialise(rp3d::EventListener* collisionEventListener) was called and Physics::PhysicsLoggerInit() was not.
         *
         * @author	Dylan Blereau
         * @date	12/09/2021
         */

        ~PhysicsManager();

     Ref<CollisionDetectionEngine>& GetCollisionDetectionEngine() { return m_CollisionDetectionEngine; }
    
    private:
        /**
         * @fn	bool PhysicsManager::Initialise(rp3d::EventListener * collisionEventListener);
         *
         * @brief	Initialises this object
         *
         * @author	Dylan Blereau
         * @date	12/09/2021
         *
         * @param [in,out]	collisionEventListener	If non-null, the collision event listener.
         *
         * @returns	True if it succeeds, false if it fails.
         */
        bool Initialise(rp3d::EventListener * collisionEventListener);
     
        /**
         * @fn	void PhysicsManager::OnFixedUpdate(PhysicsTimestep timestep);
         *
         * @brief	Executes the 'fixed update' action
         *
         * @author	Dylan Blereau
         * @date	12/09/2021
         *
         * @param 	timestep	The timestep.
         */
        void OnFixedUpdate(Timestep deltaTime, PhysicsTimestep timestep) const;

        /**
         * @fn	void PhysicsManager::Destroy();
         *
         * @brief	Destroys this object
         *
         * @author	Dylan Blereau
         * @date	12/09/2021
         */
        void Destroy();

        /**
         * @fn	rp3d::RigidBody* PhysicsManager::CreateRigidBody(const TransformComponent& transform);
         *
         * @brief	Creates rigid body
         *
         * @author	Dylan Blereau
         * @date	12/09/2021
         *
         * @param 	transform	A transform component.
         *
         * @returns	Null if it fails, else the new rigid body.
         */
        rp3d::RigidBody* CreateRigidBody(const TransformComponent& transform) const;

        /**
         * @fn	void PhysicsManager::DestroyRigidBody(rp3d::RigidBody* rigidBody);
         *
         * @brief	Destroys the rigid body described by rigidBody
         *
         * @author	Dylan Blereau
         * @date	12/09/2021
         *
         * @param [in,out]	rigidBody	If non-null, the rigid body.
         */
        void DestroyRigidBody(rp3d::CollisionBody* rigidBody) const;

        /**
         * @fn	rp3d::CollisionBody* PhysicsManager::CreateCollisionBody(const TransformComponent& transform);
         *
         * @brief	Creates collision body
         *
         * @author	Dylan Blereau
         * @date	12/09/2021
         *
         * @param 	transform	The transform.
         *
         * @returns	Null if it fails, else the new collision body.
         */
        rp3d::CollisionBody* CreateCollisionBody(const TransformComponent& transform) const;

        /**
         * @fn	void PhysicsManager::DestroyCollisionBody(rp3d::CollisionBody * body);
         *
         * @brief	Destroys the collision body described by body
         *
         * @author	Dylan Blereau
         * @date	12/09/2021
         *
         * @param [in,out]	body	If non-null, the body.
         */
        void DestroyCollisionBody(rp3d::CollisionBody * body) const;
     
        /**
         * @fn	void PhysicsManager::CreateColliderRenderer();
         *
         * @brief	Creates collider renderer
         *
         * @author	Dylan Blereau
         * @date	12/09/2021
         */
        void CreateColliderRenderer();

   
    
    private:
        /** @brief	The physics common */
        rp3d::PhysicsCommon m_PhysicsCommon;
     
        /** @brief	Pointer to The physics world */
        rp3d::PhysicsWorld* m_PhysicsWorld = nullptr;
     
        /** @brief	Pointer to physics logger */
        rp3d::DefaultLogger* m_PhysicsLogger = nullptr;
     
        /** @brief	True to collider render */
        bool m_ColliderRender = false;
     
     /** @brief	True if the collider renderer has been initialized */
      bool m_ColliderRendererInit = false;
     
      Ref<VertexArray> m_LinesVertexArray;
     
   /** @brief	Pointer to the buffer for lines vertex data */
   Ref<VertexBuffer> m_LinesVertexBuffer;

   /** @brief	Pointer to array for triangle vertex data */
   Ref<VertexArray> m_TriangleVertexArray;

   /** @brief	Pointer to Buffer for triangle vertex data */
   Ref<VertexBuffer> m_TriangleVertexBuffer;

   /** @brief	Shader used for the collider renderer */
   Ref<Shader> m_Shader;

   /** @brief	Layout of the collider renderer vertex buffers */
   VertexBufferLayout m_ColliderLayout;

   /** @brief	True to active */
   bool m_Active = false;

   /** @brief Used to tell the physics system if the logging should be enabled*/
   bool m_Logging = false;

     std::unordered_map<uint32_t, Ref<RigidBody>> m_Rigidbodies;

     uint32_t m_TotalRigidbodies = 0;

     std::unordered_map<uint32_t, Ref<Collider>> m_Colliders;

     uint32_t m_TotalColliders = 0;

     /** @brief a static reference to the active Collision Detection Engine */
     static Ref<CollisionDetectionEngine> m_CollisionDetectionEngine;

        friend class PhysicsEngine;
};

#pragma endregion PhysicsManager

#pragma region PhysicsEngine
 
    /**
     * @class	PhysicsEngine
     *
     * @brief	A physics class responsible for the engine physics. All actual physics calculations are processed within
     * this class.
     *
     * @author	Dylan Blereau
     * @date	12/09/2021
     */
    class PhysicsEngine
    {
    public:

        /**
         * @fn	static Ref<PhysicsManager> Physics::GetManager();
         *
         * @brief	Gets a pointer to the PhysicsManager
         *
         * @author	Dylan Blereau
         * @date	12/09/2021
         *
         * @returns	The manager.
         */
        static Ref<PhysicsManager> GetManager();

        /**
         * @fn	static bool Physics::IsActive();
         *
         * @brief	Query if the physics is active
         *
         * @author	Dylan Blereau
         * @date	12/09/2021
         *
         * @returns	True if active, false if not.
         */
        static bool IsActive();

        /**
         * @fn	static bool Physics::Initialise(rp3d::EventListener * collisionEventListener);
         *
         * @brief	Initialises the physics and its logger
         *
         * @author	Dylan Blereau
         * @date	12/09/2021
         *
         * @param [in,out]	collisionEventListener	If non-null, the collision event listener.
         *
         * @returns	True if it succeeds, false if it fails.
         */
        static bool Initialise(rp3d::EventListener * collisionEventListener);

        /**
         * @fn	static void Physics::OnFixedUpdate(PhysicsTimestep timestep);
         *
         * @brief	Executes the 'fixed update' action
         *
         * @author	Dylan Blereau
         * @date	12/09/2021
         *
         * @param 	timestep	The timestep.
         */
        static void OnFixedUpdate(Timestep deltaTime, PhysicsTimestep timestep, entt::registry& componentRegistry);

     /**
     * @fn	static void Physics::OnUpdate(Timestep timestep);
     *
     * @brief	Physics update for any disconnected objects not tied directly to the fixed physics updates.
     *
     * @author	Bryce Standley
     * @date	10/10/2021
     *
     * @param 	timestep	The timestep.
     */
     static void OnUpdate(Timestep timestep);

        /**
         * @fn	static void Physics::Destroy();
         *
         * @brief	Destroys this object
         *
         * @author	Dylan Blereau
         * @date	12/09/2021
         */
        static void Destroy();

        /**
         * @fn	static void Physics::DestroyRigidbody(rp3d::RigidBody* body);
         *
         * @brief	Destroys the rigidbody described by body
         *
         * @author	Dylan Blereau
         * @date	12/09/2021
         *
         * @param [in,out]	body	If non-null, the body.
         */
        static void DestroyRigidbody(Ref<RigidBody> rigidbody);

        /**
         * @fn	static rp3d::RigidBody* Physics::CreateRigidbody(const TransformComponent& transform);
         *
         * @brief	Creates a rigidbody
         *
         * @author	Dylan Blereau
         * @date	12/09/2021
         *
         * @param 	transform	The transform.
         *
         * @returns	Null if it fails, else the new rigidbody.
         */
        static Ref<RigidBody> CreateRigidbody(GameObject& gameObject);

        /**
         * @fn	static void Physics::ToggleColliderRendering();
         *
         * @brief	Toggle collider rendering
         *
         * @author	Dylan Blereau
         * @date	12/09/2021
         */
        static void ToggleColliderRendering();

        /**
         * @fn	static void Physics::GetColliderRendererHandle();
         *
         * @brief	Gets the Collider renderer handle
         *
         * @author	Dylan Blereau
         * @date	12/09/2021
         */
        static bool& GetColliderRendererHandle();
     
        /**
         * @fn	static TransformComponent Physics::GetColliderRendererTransform();
         *
         * @brief	Gets the transform of the renderer
         *
         * @author	Dylan Blereau
         * @date	12/09/2021
         */
        static TransformComponent GetColliderRendererTransform();
     
        /**
         * @fn	static rp3d::BoxShape* Physics::CreateBoxShape(const glm::vec3& halfExtents);
         *
         * @brief	Creates box shape
         *
         * @author	Dylan Blereau
         * @date	12/09/2021
         *
         * @param 	halfExtents	Extents of the half.
         *
         * @returns	Null if it fails, else the new box shape.
         */
        static Ref<Collider> CreateBoxCollider(Ref<RigidBody> rigidbody, const glm::vec3& halfExtents);
     
        /**
         * @fn	static rp3d::SphereShape* Physics::CreateSphereShape(const float& radius);
         *
         * @brief	Creates sphere shape
         *
         * @author	Dylan Blereau
         * @date	12/09/2021
         *
         * @param 	radius	The radius.
         *
         * @returns	Null if it fails, else the new sphere shape.
         */
        static Ref<Collider> CreateSphereCollider(Ref<RigidBody> rigidbody, const float& radius);

        /**
         * @fn	static rp3d::CapsuleShape* Physics::CreateCapsuleShape(const float& radius, const float& height);
         *
         * @brief	Creates capsule shape
         *
         * @author	Dylan Blereau
         * @date	12/09/2021
         *
         * @param 	radius	The radius.
         * @param 	height	The height.
         *
         * @returns	Null if it fails, else the new capsule shape.
         */
        static Ref<Collider> CreateCapsuleCollider(Ref<RigidBody> rigidbody, const float& radius, const float& height);
    
    private:

        /**
        * @fn	void Physics::EnableLogging();
        *
        * @brief	Enables logging for the physics system
        *
        * @author	Dylan Blereau
        * @date	12/09/2021
        *
        */
        static void EnableLogging();

        /**
        * @fn	void Physics::IsColliderRenderingEnabled();
        *
        * @brief	Checks if collider rendering is enabled
        *
        * @author	Dylan Blereau
        * @date	12/09/2021
        * 
        * @return bool If the renderer is enabled
        *
        */
        static bool IsColliderRenderingEnabled();

        /**
         * @fn	static std::pair<std::pair<Ref<VertexArray>, Ref<VertexBuffer>>, std::pair<Ref<VertexArray>, Ref<VertexBuffer>>> Physics::GetColliderRenderObjects();
         *
         * @brief	Gets collider render objects by using a pair to retreive the VAO and VBO data for lines and triangles
         *
         * @author	Dylan Blereau
         * @date	12/09/2021
         *
         * @returns	The collider render objects.
         */
        static std::pair<std::pair<Ref<VertexArray>, Ref<VertexBuffer>>, std::pair<Ref<VertexArray>, Ref<VertexBuffer>>> GetColliderRenderObjects();

        /**
         * @fn	static Ref<Shader> Physics::GetColliderShader();
         *
         * @brief	Gets collider shader
         *
         * @author	Dylan Blereau
         * @date	12/09/2021
         *
         * @returns	The collider shader.
         */
        static Ref<Shader> GetColliderShader();

        /**
         * @fn	static void Physics::UpdateColliderRenderer();
         *
         * @brief	Updates the collider renderer
         *
         * @author	Dylan Blereau
         * @date	12/09/2021
         */
        static void UpdateColliderRenderer();

        /**
         * @fn	static rp3d::DebugRenderer* Physics::GetColliderRenderer();
         *
         * @brief	Gets collider renderer
         *
         * @author	Dylan Blereau
         * @date	12/09/2021
         *
         * @returns	The collider renderer.
         */
        static rp3d::DebugRenderer* GetColliderRenderer();

        /**
         * @fn	static void Physics::PhysicsLoggerInit();
         *
         * @brief	Initialise the physics logger
         *
         * @author	Dylan Blereau
         * @date	12/09/2021
         */
        static void PhysicsLoggerInit();

     static void ProcessCollisions();
     static void ProcessRigidbodyVelocities(const Timestep& deltaTime, entt::registry& componentRegistry);
     static void ProcessRigidbodyPositions(const Timestep& deltaTime, entt::registry& componentRegistry);
     static void ResetRigidbodyForcesAndTorques(entt::registry& componentRegistry);
     static void UpdateInertiaTensor(entt::registry& componentRegistry);
     static void UpdateBodies(entt::registry& componentRegistry);
    
    private:
     
        /** @brief a static reference to the active physics manager */
        static Ref<PhysicsManager> m_PhysicsManager;
     
        /** @brief Transform used for rendering the colliders within the scene*/
        static TransformComponent m_ColliderTransform;

     friend class tnah::Scene;
     friend class tnah::Renderer;
    };

#pragma endregion PhysicsEngine

}
