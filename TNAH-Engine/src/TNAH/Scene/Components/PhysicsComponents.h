#pragma once

#include "TNAH/Physics/Physics.h"

#include "TNAH/Renderer/Mesh.h"

namespace tnah {

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

	class RigidBodyComponent : public Component
	{
	public:
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
		bool edit = false;
		/** @brief	True to use edit */
		bool useEdit = false;

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
		 * @fn	RigidBodyComponent::RigidBodyComponent(const rp3d::Vector3& position, const rp3d::Quaternion orientation);
		 *
		 * @brief	Constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	position   	The position.
		 * @param 	orientation	The orientation.
		 **************************************************************************************************/

		RigidBodyComponent(const rp3d::Vector3& position, const rp3d::Quaternion orientation);

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
	private:
		/** @brief	Type of the body */
		rp3d::BodyType m_BodyType;
		/** @brief	The transform */
		rp3d::Transform m_Transform = rp3d::Transform::identity();
		/** @brief	List of colliders */
		std::list<rp3d::CollisionShape*> m_ColliderList;
		inline static std::string s_SearchString = "rigidbody component";
		friend class EditorUI;
	};

	/**********************************************************************************************//**
	 * @class	CollisionBodyComponent
	 *
	 * @brief	A colision body is similar to a rigidbody but doesn't allow physics to interact with the
	 * 			object. The user is required to manually move the object.
	 *
	 * @author	Bryce Standley
	 * @date	20/07/2021
	 **************************************************************************************************/

	class CollisionBodyComponent : public Component
	{
	public:
		glm::vec3 Position = {0,0,0};
		glm::vec3 Rotation = {0,0,0};
		rp3d::CollisionBody* Body = nullptr;
	
	private:
		rp3d::Transform m_Transform = rp3d::Transform::identity();
		std::list<rp3d::CollisionShape*> m_ColliderList;
	};

	/**********************************************************************************************//**
	 * @class	BoxColliderComponent
	 *
	 * @brief	A box collider is a simple collider of a box or cube.
	 *
	 * @author	Bryce Standley
	 * @date	20/07/2021
	 **************************************************************************************************/

	class BoxColliderComponent : public Component
	{
	public:
		/** @brief	The size */
		glm::vec3 Size = {1.0f, 1.0f, 1.0f};
		/** @brief	The collider */
		rp3d::BoxShape* Collider;
		/** @brief	The collider pointer */
		rp3d::Collider* colliderPointer = nullptr;

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
		inline static std::string s_SearchString = "box collider component";
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

	class HeightFieldColliderComponent : public Component
	{
	public:
		/** @brief	The collider */
		rp3d::HeightFieldShape* Collider;
		/** @brief	Information describing the height */
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
	};

	/**********************************************************************************************//**
	 * @class	SphereColliderComponent
	 *
	 * @brief	A sphere collider is a simple collider using a sphere shape.
	 *
	 * @author	Bryce Standley
	 * @date	20/07/2021
	 **************************************************************************************************/

	class SphereColliderComponent : public Component
	{
	public:
		float Radius = 1.0f;
		rp3d::SphereShape* Collider;

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
	};

	/**********************************************************************************************//**
	 * @class	CapsuleColliderComponent
	 *
	 * @brief	A capsule collider is a simple collider using a capsule shape.
	 *
	 * @author	Bryce Standley
	 * @date	20/07/2021
	 **************************************************************************************************/

	class CapsuleColliderComponent : public Component
	{
	public:
		/** @brief	The radius */
		float Radius = 1.0f;
		/** @brief	The height */
		float Height = 2.0f;
		/** @brief	The collider */
		rp3d::CapsuleShape* Collider = nullptr;

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
	};

	/**********************************************************************************************//**
	 * @class	MeshColliderComponent
	 *
	 * @brief	A mesh collider is a complex collider using either a convex or concave mesh shape to
	 * 			construct the collider
	 *
	 * @author	Bryce Standley
	 * @date	20/07/2021
	 **************************************************************************************************/

	class MeshColliderComponent : public Component
	{
	public:

		/**********************************************************************************************//**
		 * @enum	ShapeType
		 *
		 * @brief	Values that represent shape types
		 **************************************************************************************************/

		enum class ShapeType
        {
            Convex, Concave
        };

		/** @brief	Type of the collider */
		ShapeType ColliderType = ShapeType::Convex;
		/** @brief	The mesh vertex positions */
		std::vector<glm::vec3> MeshVertexPositions;
		/** @brief	The mesh indices */
		std::vector<uint32_t> MeshIndices;
		/** @brief	The collider pointer */
		rp3d::Collider* colliderPointer = nullptr;

		/**********************************************************************************************//**
		 * @fn	rp3d::ConvexMeshShape* MeshColliderComponent::GetConvexCollider() const
		 *
		 * @brief	Gets convex collider
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @returns	Null if it fails, else the convex collider.
		 **************************************************************************************************/

		rp3d::ConvexMeshShape* GetConvexCollider() const { return m_ConvexCollider; }

		/**********************************************************************************************//**
		 * @fn	rp3d::ConcaveMeshShape* MeshColliderComponent::GetConcaveCollider() const
		 *
		 * @brief	Gets concave collider
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @returns	Null if it fails, else the concave collider.
		 **************************************************************************************************/

		rp3d::ConcaveMeshShape* GetConcaveCollider() const { return m_ConcaveCollider; }

		/**********************************************************************************************//**
		 * @fn	MeshColliderComponent::MeshColliderComponent();
		 *
		 * @brief	Default constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 **************************************************************************************************/

		MeshColliderComponent();

		/**********************************************************************************************//**
		 * @fn	MeshColliderComponent::MeshColliderComponent(const MeshColliderComponent& other);
		 *
		 * @brief	Copy constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	other	The other.
		 **************************************************************************************************/

		MeshColliderComponent(const MeshColliderComponent& other);

		/**********************************************************************************************//**
		 * @fn	MeshColliderComponent::MeshColliderComponent(const Mesh& mesh);
		 *
		 * @brief	Constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	mesh	The mesh.
		 **************************************************************************************************/

		MeshColliderComponent(const Mesh& mesh);

		/**********************************************************************************************//**
		 * @fn	MeshColliderComponent::MeshColliderComponent(const std::vector<glm::vec3>& vertexPositions, const std::vector<uint32_t>& indices)
		 *
		 * @brief	Constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	vertexPositions	The vertex positions.
		 * @param 	indices		   	The indices.
		 **************************************************************************************************/

		MeshColliderComponent(const std::vector<glm::vec3>& vertexPositions, const std::vector<uint32_t>& indices)
			:MeshVertexPositions(vertexPositions), MeshIndices(indices) {}
		
	private:
		/** @brief	The convex collider */
		rp3d::ConvexMeshShape* m_ConvexCollider = nullptr;
		/** @brief	The concave collider */
		rp3d::ConcaveMeshShape* m_ConcaveCollider = nullptr;

		/** @brief	Convex */
		rp3d::PolyhedronMesh* m_PolyhedronMesh = nullptr;
		/** @brief	Array of vertices */
		rp3d::PolygonVertexArray* m_PolygonVertexArray = nullptr;
		/** @brief	The polygon face */
		rp3d::PolygonVertexArray::PolygonFace* m_PolygonFace = nullptr;

		/*@fn CreateConvexPolygonArray  @brief Helper to create the polygon vertex array object.
		 */
		void CreateConvexPolygonArray();
		
		//Concave
		rp3d::TriangleVertexArray* m_TriangleVertexArray = nullptr;
		/** @brief	The triangle mesh */
		rp3d::TriangleMesh* m_TriangleMesh = nullptr;

		/**
		 * @fn CreateTriangleVertexArray
		 *
		 * @brief Helper to create triangle vertex array object
		 */
		void CreateTriangleVertexArray();
	};


}
