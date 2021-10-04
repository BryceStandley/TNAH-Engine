#pragma once
#pragma warning(push, 0)
#include <reactphysics3d/reactphysics3d.h>

#pragma warning(pop)

#include <entt.hpp>

#include "TNAH/Physics/PhysicsTimestep.h"
#include "TNAH/Scene/Components/Components.h"
#include "TNAH/Scene/Components/PhysicsComponents.h"

namespace tnah
{
 struct TnahRigidBodyComponent;
 struct CollisionBodyComponent;
 /**
     * @class	PhysicsManager
     *
     * @brief	Manager for physics that inherits from the RefCounted class. This class is to remain private and contain
     * all ReactPhysics3D world objects. Any control of the PhysicsManager should be done from tnah::Physics
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

        void OnFixedUpdate(PhysicsTimestep timestep) const;

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

        void DestroyRigidBody(rp3d::RigidBody* rigidBody) const;

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

        friend class Physics;
    };

    /**
     * @class	Physics
     *
     * @brief	A physics class responsible for the engine physics
     *
     * @author	Dylan Blereau
     * @date	12/09/2021
     */

    class Physics
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

        static void OnFixedUpdate(PhysicsTimestep timestep, entt::basic_view<entt::entity, entt::exclude_t<>, TransformComponent, TnahRigidBodyComponent> view);

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
         * @fn	static rp3d::CollisionBody* Physics::CreateCollisionBody(const TransformComponent& transformValues);
         *
         * @brief	Creates collision body
         *
         * @author	Dylan Blereau
         * @date	12/09/2021
         *
         * @param 	transformValues	The transform values.
         *
         * @returns	Null if it fails, else the new collision body.
         */

        static rp3d::CollisionBody* CreateCollisionBody(const TransformComponent& transformValues);

        /**
         * @fn	static void Physics::DestroyCollisionBody(rp3d::CollisionBody * body);
         *
         * @brief	Destroys the collision body described by body
         *
         * @author	Dylan Blereau
         * @date	12/09/2021
         *
         * @param [in,out]	body	If non-null, the body.
         */

        static void DestroyCollisionBody(rp3d::CollisionBody * body);

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

        static void DestroyRigidbody(rp3d::RigidBody* body);

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

        static rp3d::RigidBody* CreateRigidbody(const TransformComponent& transform);

        /**
         * @fn	static rp3d::RigidBody* Physics::CreateRigidbody(const rp3d::Transform transform);
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

        static rp3d::RigidBody* CreateRigidbody(const rp3d::Transform transform);

        /**
         * @fn	static rp3d::RigidBody* Physics::CreateRigidbody(const glm::vec3& position, const glm::vec3& rotation);
         *
         * @brief	Creates a rigidbody
         *
         * @author	Dylan Blereau
         * @date	12/09/2021
         *
         * @param 	position	The position.
         * @param 	rotation	The rotation.
         *
         * @returns	Null if it fails, else the new rigidbody.
         */

        static rp3d::RigidBody* CreateRigidbody(const glm::vec3& position, const glm::vec3& rotation);

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
         * @fn	static rp3d::BoxShape* Physics::CreateBoxShape(const float& halfX, const float& halfY, const float& halfZ);
         *
         * @brief	Creates box shape
         *
         * @author	Dylan Blereau
         * @date	12/09/2021
         *
         * @param 	halfX	The half x coordinate.
         * @param 	halfY	The half y coordinate.
         * @param 	halfZ	The half z coordinate.
         *
         * @returns	Null if it fails, else the new box shape.
         */

        static rp3d::BoxShape* CreateBoxShape(const float& halfX, const float& halfY, const float& halfZ);

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

        static rp3d::BoxShape* CreateBoxShape(const glm::vec3& halfExtents);

        /**
         * @fn	static rp3d::BoxShape* Physics::CreateBoxShape(const rp3d::Vector3& halfExtents);
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

        static rp3d::BoxShape* CreateBoxShape(const rp3d::Vector3& halfExtents);

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

        static rp3d::SphereShape* CreateSphereShape(const float& radius);

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

        static rp3d::CapsuleShape* CreateCapsuleShape(const float& radius, const float& height);

        /**
         * @fn	static rp3d::HeightFieldShape* Physics::CreateHeightFieldShape(const int& columns, const int& rows, const float& minHeight, const float& maxHeight, const float* terrainColliderHeightData);
         *
         * @brief	Creates height field shape
         *
         * @author	Dylan Blereau
         * @date	12/09/2021
         *
         * @param 	columns					 	The columns.
         * @param 	rows					 	The rows.
         * @param 	minHeight				 	The minimum height.
         * @param 	maxHeight				 	The maximum height.
         * @param 	terrainColliderHeightData	Information describing the terrain collider height.
         *
         * @returns	Null if it fails, else the new height field shape.
         */

        static rp3d::HeightFieldShape* CreateHeightFieldShape(const int& columns, const int& rows, const float& minHeight, const float& maxHeight, const float* terrainColliderHeightData);

        /**
         * @fn	static rp3d::PolyhedronMesh* Physics::CreatePolyhedronMesh(rp3d::PolygonVertexArray* polygonVertexArray);
         *
         * @brief	Creates polyhedron mesh
         *
         * @author	Dylan Blereau
         * @date	12/09/2021
         *
         * @param [in,out]	polygonVertexArray	If non-null, array of vertices.
         *
         * @returns	Null if it fails, else the new polyhedron mesh.
         */

        static rp3d::PolyhedronMesh* CreatePolyhedronMesh(rp3d::PolygonVertexArray* polygonVertexArray);

        /**
         * @fn	static rp3d::ConvexMeshShape* Physics::CreateConvexMeshShape(rp3d::PolyhedronMesh* polyhedronMesh);
         *
         * @brief	Creates convex mesh shape
         *
         * @author	Dylan Blereau
         * @date	12/09/2021
         *
         * @param [in,out]	polyhedronMesh	If non-null, the polyhedron mesh.
         *
         * @returns	Null if it fails, else the new convex mesh shape.
         */

        static rp3d::ConvexMeshShape* CreateConvexMeshShape(rp3d::PolyhedronMesh* polyhedronMesh);

        /**
         * @fn	static rp3d::ConcaveMeshShape* Physics::CreateConcaveMeshShape(rp3d::TriangleMesh* triangleMesh);
         *
         * @brief	Creates concave mesh shape
         *
         * @author	Dylan Blereau
         * @date	12/09/2021
         *
         * @param [in,out]	triangleMesh	If non-null, the triangle mesh.
         *
         * @returns	Null if it fails, else the new concave mesh shape.
         */

        static rp3d::ConcaveMeshShape* CreateConcaveMeshShape(rp3d::TriangleMesh* triangleMesh);

        /**
         * @fn	static rp3d::TriangleMesh* Physics::CreateTriangleMesh();
         *
         * @brief	Creates triangle mesh
         *
         * @author	Dylan Blereau
         * @date	12/09/2021
         *
         * @returns	Null if it fails, else the new triangle mesh.
         */

        static rp3d::TriangleMesh* CreateTriangleMesh();

        /**
         * @fn	void Physics::CreateTerrainCollider(tnah::Terrain* terrain);
         *
         * @brief	Creates terrain collider
         *
         * @author	Dylan Blereau
         * @date	12/09/2021
         *
         * @param [in,out]	terrain	If non-null, the terrain.
         */

        void CreateTerrainCollider(tnah::Terrain* terrain);
    
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
    
    private:

     
        /** @brief a static reference to the active physics manager */
        static Ref<PhysicsManager> m_PhysicsManager;

        /** @brief Transform used for rendering the colliders within the scene*/
        static TransformComponent m_ColliderTransform;
        friend class Scene;
        friend class Renderer;
    };

    
}
