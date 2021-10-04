#pragma once

#include "TNAH/Physics/Physics.h"

#include "TNAH/Renderer/Mesh.h"
#include "ComponentIdentification.h"

namespace tnah{

	/**
	 * @struct ColliderComponents
	 *
	 * @brief Contains the shape and collider pointers to be used within the physics system
	 *
	 * @author Bryce Standley
	 * @date 09/09/2021
	 * 
	 * @param Shape ReactPhysics3D collision shape, base type of all colliders
	 * @param BodyCollider ReactPhysics3D collider
	 * @param TransformRelativeToCollisionBody ReactPhysics3D transform relative to the collision body transform.
	 */
	struct ColliderComponents
	{
		rp3d::CollisionShape* Shape = nullptr;
		rp3d::Collider* BodyCollider = nullptr;
		rp3d::Transform TransformRelativeToCollisionBody = rp3d::Transform::identity();

		ColliderComponents() = default;
		ColliderComponents(rp3d::CollisionShape* shape, rp3d::Collider* bodyCollider, rp3d::Transform transform)
			:Shape(shape), BodyCollider(bodyCollider), TransformRelativeToCollisionBody(transform)
		{}

		~ColliderComponents() = default;
	};
	

	/**********************************************************************************************//**
 * @class	RigidBodyComponent
 *
 * @brief	A physics rigidbody allows physics to be simulated on a object
 *
 * @author	Bryce Standley
 * @date	20/07/2021
 * 			
 * @author	Christopher Logan
 * @date	05/09/2021
 **************************************************************************************************/

	struct RigidBodyComponent
	{
		enum class ForceType
		{
			FromWorld, FromLocal, FromCentre
		};
		
		/** @brief	The position */
		glm::vec3 Position = {0,0,0};
		/** @brief	The rotation */
		glm::vec3 Rotation = {0,0,0};
		/** @brief	The orientation */
		glm::quat Orientation = {0,0,0,0};
		/** @brief	The body */
		rp3d::RigidBody* Body = nullptr;

		/** @brief	True to edit */
		bool Edit = false;
		/** @brief	True to use edit */
		bool UseEdit = false;

		


		/**********************************************************************************************//**
		 * @fn	RigidBodyComponent::RigidBodyComponent();
		 *
		 * @brief	Default constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 **************************************************************************************************/

		RigidBodyComponent();

		/**********************************************************************************************//**
		 * @fn	RigidBodyComponent::RigidBodyComponent(const RigidBodyComponent& other) = default;
		 *
		 * @brief	Defaulted copy constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	other	The other.
		 **************************************************************************************************/

		RigidBodyComponent(const RigidBodyComponent& other) = default;

		/**********************************************************************************************//**
		 * @fn	RigidBodyComponent::RigidBodyComponent(const glm::vec3& position, const glm::vec3& rotation);
		 *
		 * @brief	Constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	position	The position.
		 * @param 	rotation	The rotation.
		 **************************************************************************************************/

		RigidBodyComponent(const glm::vec3& position, const glm::vec3& rotation);

		/**********************************************************************************************//**
		 * @fn	RigidBodyComponent::RigidBodyComponent(const TransformComponent& transform);
		 *
		 * @brief	Constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	transform	The transform.
		 **************************************************************************************************/

		RigidBodyComponent(const TransformComponent& transform);

		/**********************************************************************************************//**
		 * @fn	RigidBodyComponent::RigidBodyComponent(const TransformComponent& transform, rp3d::BodyType type);
		 *
		 * @brief	Constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	transform	The transform.
		 * @param 	type	 	The type.
		 **************************************************************************************************/

		RigidBodyComponent(const TransformComponent& transform, rp3d::BodyType type);

		/**********************************************************************************************//**
		 * @fn	RigidBodyComponent::RigidBodyComponent(const rp3d::Transform& transform);
		 *
		 * @brief	Constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	transform	The transform.
		 **************************************************************************************************/

		RigidBodyComponent(const rp3d::Transform& transform);

		/**********************************************************************************************//**
		 * @fn	RigidBodyComponent::RigidBodyComponent(const rp3d::Vector3& position, const rp3d::Vector3& rotation);
		 *
		 * @brief	Constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	position	The position.
		 * @param 	rotation	The rotation.
		 **************************************************************************************************/

		RigidBodyComponent(const rp3d::Vector3& position, const rp3d::Vector3& rotation);


		/**********************************************************************************************//**
		 * @fn	RigidBodyComponent::RigidBodyComponent(const rp3d::Vector3& position, const rp3d::Quaternion& orientation);
		 *
		 * @brief	Constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	position   	The position.
		 * @param 	orientation	The orientation.
		 **************************************************************************************************/

		RigidBodyComponent(const rp3d::Vector3& position, const rp3d::Quaternion& orientation);
		



		/**********************************************************************************************//**
		 * @fn	rp3d::Collider* RigidBodyComponent::AddCollider(rp3d::CollisionShape* collider, const rp3d::Transform &transform);
		 *
		 * @brief	Adds a collider to 'transform'
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param [in,out]	collider 	If non-null, the collider.
		 * @param 		  	transform	The transform.
		 *
		 * @returns	Null if it fails, else a pointer to a rp3d::Collider.
		 **************************************************************************************************/
		rp3d::Collider* AddCollider(rp3d::CollisionShape* collider, const rp3d::Transform &transform);

		/**********************************************************************************************//**
		* @fn	rp3d::Collider* RigidBodyComponent::AddCollider(ColliderComponents colliderComponents);
		*
		* @brief	Adds a collider to the rigidbody
		*
		* @author	Bryce Standley
		* @date	10/09/2021
		*
		* @param [in,out]	colliderComponents 	Components of the collider to add
		*
		* @returns	Null if it fails, else a pointer to a rp3d::Collider.
		**************************************************************************************************/
		rp3d::Collider* AddCollider(ColliderComponents colliderComponents);

		/**********************************************************************************************//**
		 * @fn	rp3d::Collider* RigidBodyComponent::UpdateCollider(rp3d::Collider * oldCollider, rp3d::CollisionShape* collider, const rp3d::Transform &transform);
		 *
		 * @brief	Updates the collider
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param [in,out]	oldCollider	If non-null, the old collider.
		 * @param [in,out]	collider   	If non-null, the collider.
		 * @param 		  	transform  	The transform.
		 *
		 * @returns	Null if it fails, else a pointer to a rp3d::Collider.
		 **************************************************************************************************/
		rp3d::Collider* UpdateCollider(rp3d::Collider * oldCollider, rp3d::CollisionShape* collider, const rp3d::Transform &transform);

		/**********************************************************************************************//**
		* @fn	rp3d::Collider* RigidBodyComponent::UpdateCollider(ColliderComponents colliderComponents);
		*
		* @brief	Updates the collider
		*
		* @author	Bryce Standley
		* @date	10/09/2021
		*
		* @param [in,out]	colliderComponents	the components of the collider to update
		*
		* @returns	Null if it fails, else a pointer to a rp3d::Collider.
		**************************************************************************************************/
		rp3d::Collider* UpdateCollider(ColliderComponents colliderComponents);


		/**********************************************************************************************//**
		 * @fn	void RigidBodyComponent::RemoveCollider(rp3d::Collider* collider);
		 *
		 * @brief	Removes the collider described by collider
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param [in,out]	collider	If non-null, the collider.
		 **************************************************************************************************/

		void RemoveCollider(rp3d::Collider* collider);

		/**********************************************************************************************//**
		 * @fn	void RigidBodyComponent::ApplyForce(const ForceType& forceType, const glm::vec3& direction, const glm::vec3& force, const glm::vec3& forcePoint) const;
		 *
		 * @brief	Applies the force
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	forceType 	Type of the force.
		 * @param 	direction 	The direction.
		 * @param 	force	  	The force.
		 * @param 	forcePoint	The force point.
		 **************************************************************************************************/

		void ApplyForce(const ForceType& forceType, const glm::vec3& direction, const glm::vec3& force, const glm::vec3& forcePoint) const;

		/**********************************************************************************************//**
		 * @fn	void RigidBodyComponent::ApplyTorque(const glm::vec3& torque) const;
		 *
		 * @brief	Applies the torque described by torque
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	torque	The torque.
		 **************************************************************************************************/

		void ApplyTorque(const glm::vec3& torque) const;

		/**********************************************************************************************//**
		 * @fn	void RigidBodyComponent::SetBodyType(rp3d::BodyType newType);
		 *
		 * @brief	Sets body type
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	newType	Type of the new.
		 **************************************************************************************************/

		void SetBodyType(rp3d::BodyType newType);

		/**********************************************************************************************//**
		 * @fn	rp3d::BodyType RigidBodyComponent::GetType() const
		 *
		 * @brief	Gets the type
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @returns	The type.
		 **************************************************************************************************/

		rp3d::BodyType GetType() const {return m_BodyType;}

		/**********************************************************************************************//**
		* @fn	void RigidBodyComponent::UpdateTransform(const TransformComponent& transform)
		*
		* @brief	Updates the rigidbody transform from a TransformComponent
		*
		* @author	Bryce Standley
		* @date	10/09/2021
		*
		* @param	transform The transform component to update with.
		**************************************************************************************************/
		void UpdateTransform(const TransformComponent& transform);
	
	private:
		/** @brief	Type of the body */
		rp3d::BodyType m_BodyType;
		/** @brief	The transform */
		rp3d::Transform m_Transform = rp3d::Transform::identity();
		/** @brief	List of colliders */
		std::list<rp3d::CollisionShape*> m_ColliderList;
		/** @brief	Search string for the component in the editor */
		inline static std::string s_SearchString = "rigidbody component";
		/** @brief	Component search types and groupings  */
		inline static ComponentTypes s_Types = {
			{ComponentVariations::RigidBody},
		{{ComponentCategory::Physics}}
		};
		friend class EditorUI;
	};

	/**********************************************************************************************//**
	 * @struct	CollisionBodyComponent
	 *
	 * @brief	A colision body is similar to a rigidbody but doesn't allow physics to interact with the
	 * 			object. The user is required to manually move the object.
	 *
	 * @author	Bryce Standley
	 * @date	20/07/2021
	 **************************************************************************************************/

	struct CollisionBodyComponent
	{
		CollisionBodyComponent();
		CollisionBodyComponent(const TransformComponent& transform);
		/** @brief	Position of the body */
		glm::vec3 Position = {0,0,0};
		/** @brief	Rotation of the body */
		glm::vec3 Rotation = {0,0,0};
		/** @brief	Pointer to the body */
		rp3d::CollisionBody* Body = nullptr;
		rp3d::Collider* AddCollider(rp3d::CollisionShape* collider, const rp3d::Transform &transform);
	
	private:
		/** @brief	Reactphysics transform of the body */
		rp3d::Transform m_Transform = rp3d::Transform::identity();
		/** @brief	List of colliders */
		std::list<rp3d::CollisionShape*> m_ColliderList;

		/** @brief	Search string for the component in the editor */
		inline static std::string s_SearchString = "collision body component";
		/** @brief	Groupings for adding components in the editor */
		inline static ComponentTypes s_Types = {
			{ComponentVariations::CollisionBody},
{{ComponentCategory::Physics}}
		};
		friend class EditorUI;
	};

	/**********************************************************************************************//**
	 * @class	BoxColliderComponent
	 *
	 * @brief	A box collider is a simple collider of a box or cube.
	 *
	 * @author	Bryce Standley
	 * @date	20/07/2021
	 **************************************************************************************************/

	struct BoxColliderComponent
	{
	public:
		/** @brief	The size */
		glm::vec3 Size = {1.0f, 1.0f, 1.0f};

		/** @brief	The Collider Shape and Collision Body */
		ColliderComponents Components;



		/**********************************************************************************************//**
		 * @fn	BoxColliderComponent::BoxColliderComponent();
		 *
		 * @brief	Default constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 **************************************************************************************************/

	
		

		BoxColliderComponent();

		/**********************************************************************************************//**
		 * @fn	BoxColliderComponent::BoxColliderComponent(const BoxColliderComponent& other) = default;
		 *
		 * @brief	Defaulted copy constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	other	The other.
		 **************************************************************************************************/

		BoxColliderComponent(const BoxColliderComponent& other) = default;

		/**********************************************************************************************//**
		 * @fn	BoxColliderComponent::BoxColliderComponent(const glm::vec3& size);
		 *
		 * @brief	Constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	size	The size.
		 **************************************************************************************************/

		BoxColliderComponent(const glm::vec3& size);

		/**********************************************************************************************//**
		 * @fn	BoxColliderComponent::BoxColliderComponent(const rp3d::Vector3& size);
		 *
		 * @brief	Constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	size	The size.
		 **************************************************************************************************/

		BoxColliderComponent(const rp3d::Vector3& size);

		/**********************************************************************************************//**
		 * @fn	BoxColliderComponent::BoxColliderComponent(const float& x, const float& y, const float& z);
		 *
		 * @brief	Constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	x	The x coordinate.
		 * @param 	y	The y coordinate.
		 * @param 	z	The z coordinate.
		 **************************************************************************************************/

		BoxColliderComponent(const float& x, const float& y, const float& z);
	private:
		/** @brief	Search string for the component in the editor */
		inline static std::string s_SearchString = "box collider component";
		/** @brief	Type identifiers for the component */
		inline static ComponentTypes s_Types = {
			{ComponentVariations::BoxCollider},
			{{ComponentCategory::Physics}}
		};
		friend class EditorUI;
	};

	/**********************************************************************************************//**
	 * @class	HeightFieldColliderComponent
	 *
	 * @brief	Height field collider using height values. Used for terrains
	 *
	 * @author	Bryce Standley
	 * @date	20/07/2021
	 **************************************************************************************************/

	struct HeightFieldColliderComponent
	{
	public:

		/** @brief	The collider */
		rp3d::HeightFieldShape* Collider;
		/** @brief	Information describing the height */
		ColliderComponents Components;

		

		std::vector<float> HeightData;
		/** @brief	The minimum height */
		float MinHeight = 0.0f;
		/** @brief	The maximum height */
		float MaxHeight = 1.0f;
		/** @brief	The total rows */
		uint32_t TotalRows = 10;
		/** @brief	The total columns */
		uint32_t TotalColumns = 10;

	/**********************************************************************************************//**
	 * @fn	HeightFieldColliderComponent::HeightFieldColliderComponent();
	 *
	 * @brief	Default constructor
	 *
	 * @author	Chris
	 * @date	10/09/2021
	 **************************************************************************************************/

	HeightFieldColliderComponent();

	/**********************************************************************************************//**
	 * @fn	HeightFieldColliderComponent::HeightFieldColliderComponent(const HeightFieldColliderComponent& other) = default;
	 *
	 * @brief	Defaulted copy constructor
	 *
	 * @author	Chris
	 * @date	10/09/2021
	 *
	 * @param 	other	The other.
	 **************************************************************************************************/

	HeightFieldColliderComponent(const HeightFieldColliderComponent& other) = default;

	/**********************************************************************************************//**
	 * @fn	HeightFieldColliderComponent::HeightFieldColliderComponent(const TerrainComponent& terrain);
	 *
	 * @brief	Constructor
	 *
	 * @author	Chris
	 * @date	10/09/2021
	 *
	 * @param 	terrain	The terrain.
	 **************************************************************************************************/

	HeightFieldColliderComponent(const TerrainComponent& terrain);
	private:
		/** @brief	Search string for adding the component in the editor */
		inline static std::string s_SearchString = "height field collider component";
		/** @brief	Type identifiers for the component */
		inline static ComponentTypes s_Types = {
			{ComponentVariations::HeightFieldCollider},
{{ComponentCategory::Physics}}
		};
		friend class EditorUI;
	};

	/**********************************************************************************************//**
	 * @class	SphereColliderComponent
	 *
	 * @brief	A sphere collider is a simple collider using a sphere shape.
	 *
	 * @author	Bryce Standley
	 * @date	20/07/2021
	 **************************************************************************************************/

	struct SphereColliderComponent
	{
	public:
		/** @brief	Radius of the sphere */
		float Radius = 1.0f;
		/** @brief	Components of the collider */
		ColliderComponents Components;

		

		/**********************************************************************************************//**
		 * @fn	SphereColliderComponent::SphereColliderComponent();
		 *
		 * @brief	Default constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 **************************************************************************************************/

		SphereColliderComponent();

		/**********************************************************************************************//**
		 * @fn	SphereColliderComponent::SphereColliderComponent(const SphereColliderComponent& other) = default;
		 *
		 * @brief	Defaulted copy constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	other	The other.
		 **************************************************************************************************/

		SphereColliderComponent(const SphereColliderComponent& other) = default;

		/**********************************************************************************************//**
		 * @fn	SphereColliderComponent::SphereColliderComponent(const float& radius);
		 *
		 * @brief	Constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	radius	The radius.
		 **************************************************************************************************/

		SphereColliderComponent(const float& radius);
	private:

		/** @brief	Search string for adding the component in the editor */
		inline static std::string s_SearchString = "sphere collider component";
		/** @brief	Type identifiers for the component */
		inline static ComponentTypes s_Types = {
			{ComponentVariations::SphereCollider},
{{ComponentCategory::Physics}}
		};
		friend class EditorUI;
	};

	/**********************************************************************************************//**
	 * @class	CapsuleColliderComponent
	 *
	 * @brief	A capsule collider is a simple collider using a capsule shape.
	 *
	 * @author	Bryce Standley
	 * @date	20/07/2021
	 **************************************************************************************************/

	struct CapsuleColliderComponent
	{
		
		/** @brief	The radius */
		float Radius = 1.0f;
		
		/** @brief	The height */
		float Height = 2.0f;
		
		/** @brief	The collider shape and body */
		ColliderComponents Components;

		

		/**********************************************************************************************//**
		 * @fn	CapsuleColliderComponent::CapsuleColliderComponent();
		 *
		 * @brief	Default constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 **************************************************************************************************/
		CapsuleColliderComponent();

		/**********************************************************************************************//**
		 * @fn	CapsuleColliderComponent::CapsuleColliderComponent(const CapsuleColliderComponent& other) = default;
		 *
		 * @brief	Defaulted copy constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	other	The other.
		 **************************************************************************************************/

		CapsuleColliderComponent(const CapsuleColliderComponent& other) = default;

		/**********************************************************************************************//**
		 * @fn	CapsuleColliderComponent::CapsuleColliderComponent(const float& radius, const float& height);
		 *
		 * @brief	Constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	radius	The radius.
		 * @param 	height	The height.
		 **************************************************************************************************/

		CapsuleColliderComponent(const float& radius, const float& height);
	private:
		/** @brief	Search string for adding the component in the editor */
		inline static std::string s_SearchString = "capsule collider component";
		/** @brief	Type identifiers for the component */
		inline static ComponentTypes s_Types = {
			{ComponentVariations::CapsuleCollider},
{{ComponentCategory::Physics}}
		};
		friend class EditorUI;
	};

	/**********************************************************************************************//**
	* @class	ConvexMeshColliderComponent
	*
	* @brief	A convex mesh collider complex collider using a Models meshes as a collider.
	*
	* @author	Bryce Standley
	* @date	20/07/2021
	**************************************************************************************************/

	struct ConvexMeshColliderComponent
	{
		/** @brief	The mesh vertex positions */
		std::vector<glm::vec3> MeshVertexPositions;
		
		/** @brief	The mesh indices */
		std::vector<uint32_t> MeshIndices;

		/** @brief	The Collider shape and Body components */
		ColliderComponents Components;

		


		/**********************************************************************************************//**
		 * @fn	ConvexMeshColliderComponent::ConvexMeshColliderComponent();
		 *
		 * @brief	Default constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 **************************************************************************************************/
		ConvexMeshColliderComponent();


		/**********************************************************************************************//**
		 * @fn	ConvexMeshColliderComponent::ConvexMeshColliderComponent(const Mesh& mesh);
		 *
		 * @brief	Constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	mesh	The mesh.
		 **************************************************************************************************/
		ConvexMeshColliderComponent(Ref<Model> mesh);

		/**********************************************************************************************//**
		 * @fn	ConvexMeshColliderComponent::ConvexMeshColliderComponent(const std::vector<glm::vec3>& vertexPositions, const std::vector<uint32_t>& indices)
		 *
		 * @brief	Constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	vertexPositions	The vertex positions.
		 * @param 	indices		   	The indices.
		 **************************************************************************************************/
		ConvexMeshColliderComponent(const std::vector<glm::vec3>& vertexPositions, const std::vector<uint32_t>& indices)
				:MeshVertexPositions(vertexPositions), MeshIndices(indices) {}

	private:
		
		/** @brief	Polyhedron mesh for the collider */
		rp3d::PolyhedronMesh* m_PolyhedronMesh = nullptr;
		
		/** @brief	Array of vertices */
		rp3d::PolygonVertexArray* m_PolygonVertexArray = nullptr;
		
		/** @brief	The polygon face */
		rp3d::PolygonVertexArray::PolygonFace* m_PolygonFace = nullptr;

		/**
		* @fn CreateConvexPolygonArray
		*
		* @brief Helper to create the polygon vertex array object
		*/
		void CreateConvexPolygonArray();

		inline static std::string s_SearchString = "concave mesh collider component";
		/** @brief	Type identifiers for the component */
		inline static ComponentTypes s_Types = {
			{ComponentVariations::ConvexMeshCollider},
{{ComponentCategory::Physics}}
		};
		friend class EditorUI;
	};

	/**********************************************************************************************//**
	* @class	ConcaveMeshColliderComponent
	*
	* @brief	A concave mesh collider complex collider using a Models meshes as a collider.
	*
	* @author	Bryce Standley
	* @date	20/07/2021
	**************************************************************************************************/

	struct ConcaveMeshColliderComponent
	{
		ColliderComponents Components;
		
		std::vector<glm::vec3> MeshVertexPositions;
		std::vector<uint32_t> MeshIndices;

		
		/**********************************************************************************************//**
		 * @fn	ConcaveMeshColliderComponent::ConcaveMeshColliderComponent()
		 *
		 * @brief	Constructor
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 *
		 **************************************************************************************************/
		ConcaveMeshColliderComponent();

		/**********************************************************************************************//**
		 * @fn	ConcaveMeshColliderComponent::ConcaveMeshColliderComponent(Ref<Model> model)
		 *
		 * @brief	Constructor
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 *
		 * @param 	model	Reference to a Model component.
		 **************************************************************************************************/
		ConcaveMeshColliderComponent(Ref<Model> model);

		/**********************************************************************************************//**
		 * @fn	ConcaveMeshColliderComponent::ConcaveMeshColliderComponent(const std::vector<glm::vec3>& vertexPositions, const std::vector<uint32_t>& indices)
		 *
		 * @brief	Constructor
		 *
		 * @author	Bryce Standley
		 * @date	10/09/2021
		 *
		 * @param 	vertexPositions	The vertex positions.
		 * @param 	indices		   	The indices.
		 **************************************************************************************************/
		ConcaveMeshColliderComponent(const std::vector<glm::vec3>& vertexPositions, const std::vector<uint32_t>& indices)
				:MeshVertexPositions(vertexPositions), MeshIndices(indices) {}

	private:
		
		/** @brief	Triangle vertex array of information for the mesh */
		rp3d::TriangleVertexArray* m_TriangleVertexArray = nullptr;
		/** @brief	The triangle mesh */
		rp3d::TriangleMesh* m_TriangleMesh = nullptr;

		/**
		* @fn CreateTriangleVertexArray
		*
		* @brief Helper to create triangle vertex array object
		*/
		void CreateTriangleVertexArray();

		/** @brief	Search string for adding the component in the editor */
		inline static std::string s_SearchString = "concave mesh collider component";
		/** @brief	Type identifiers for the component */
		inline static ComponentTypes s_Types = {
			{ComponentVariations::ConcaveMeshCollider},
{{ComponentCategory::Physics}}
		};
		friend class EditorUI;
	};


}
