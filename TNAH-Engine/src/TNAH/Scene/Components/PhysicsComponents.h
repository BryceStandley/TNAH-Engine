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
 **************************************************************************************************/

	class RigidBodyComponent : public Component
	{
	public:
		enum class ForceType
		{
			FromWorld, FromLocal, FromCentre
		};
		
		glm::vec3 Position = {0,0,0};
		glm::vec3 Rotation = {0,0,0};
		glm::quat Orientation = {0,0,0,0};
		rp3d::RigidBody* Body = nullptr;
		bool edit = false;
		bool useEdit = false;

		RigidBodyComponent();
		RigidBodyComponent(const RigidBodyComponent& other) = default;

		RigidBodyComponent(const glm::vec3& position, const glm::vec3& rotation);
		RigidBodyComponent(const TransformComponent& transform);
		RigidBodyComponent(const TransformComponent& transform, rp3d::BodyType type);
		RigidBodyComponent(const rp3d::Transform& transform);
		RigidBodyComponent(const rp3d::Vector3& position, const rp3d::Vector3& rotation);
		RigidBodyComponent(const rp3d::Vector3& position, const rp3d::Quaternion orientation);
		
		rp3d::Collider* AddCollider(rp3d::CollisionShape* collider, const rp3d::Transform &transform);
		rp3d::Collider* UpdateCollider(rp3d::Collider * oldCollider, rp3d::CollisionShape* collider, const rp3d::Transform &transform);
		void RemoveCollider(rp3d::Collider* collider);
		void ApplyForce(const ForceType& forceType, const glm::vec3& direction, const glm::vec3& force, const glm::vec3& forcePoint) const;
		void ApplyTorque(const glm::vec3& torque) const;
		void SetBodyType(rp3d::BodyType newType);
		rp3d::BodyType GetType() const {return m_BodyType;}
	private:
		rp3d::BodyType m_BodyType;
		rp3d::Transform m_Transform = rp3d::Transform::identity();
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
		glm::vec3 Size = {1.0f, 1.0f, 1.0f};
		rp3d::BoxShape* Collider;
		rp3d::Collider* colliderPointer = nullptr;

		BoxColliderComponent();
		BoxColliderComponent(const BoxColliderComponent& other) = default;

		BoxColliderComponent(const glm::vec3& size);
		BoxColliderComponent(const rp3d::Vector3& size);
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
		rp3d::HeightFieldShape* Collider;
		std::vector<float> HeightData;
		float MinHeight = 0.0f;
		float MaxHeight = 1.0f;
		uint32_t TotalRows = 10;
		uint32_t TotalColumns = 10;

	HeightFieldColliderComponent();
	HeightFieldColliderComponent(const HeightFieldColliderComponent& other) = default;

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

		SphereColliderComponent();
		SphereColliderComponent(const SphereColliderComponent& other) = default;

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
		float Radius = 1.0f;
		float Height = 2.0f;
		rp3d::CapsuleShape* Collider = nullptr;

		CapsuleColliderComponent();
		CapsuleColliderComponent(const CapsuleColliderComponent& other) = default;

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
		enum class ShapeType
        {
            Convex, Concave
        };

		ShapeType ColliderType = ShapeType::Convex;
		std::vector<glm::vec3> MeshVertexPositions;
		std::vector<uint32_t> MeshIndices;
		rp3d::Collider* colliderPointer = nullptr;
		rp3d::ConvexMeshShape* GetConvexCollider() const { return m_ConvexCollider; }
		rp3d::ConcaveMeshShape* GetConcaveCollider() const { return m_ConcaveCollider; }
		
		MeshColliderComponent();
		MeshColliderComponent(const MeshColliderComponent& other);
			
		MeshColliderComponent(const Mesh& mesh);

		MeshColliderComponent(const std::vector<glm::vec3>& vertexPositions, const std::vector<uint32_t>& indices)
			:MeshVertexPositions(vertexPositions), MeshIndices(indices) {}
		
	private:
		rp3d::ConvexMeshShape* m_ConvexCollider = nullptr;
		rp3d::ConcaveMeshShape* m_ConcaveCollider = nullptr;

		//Convex
		rp3d::PolyhedronMesh* m_PolyhedronMesh = nullptr;
		rp3d::PolygonVertexArray* m_PolygonVertexArray = nullptr;
		rp3d::PolygonVertexArray::PolygonFace* m_PolygonFace = nullptr;

		/**
		 * @fn CreateConvexPolygonArray
		 *
		 * @brief Helper to create the polygon vertex array object
		 */
		void CreateConvexPolygonArray();
		
		//Concave
		rp3d::TriangleVertexArray* m_TriangleVertexArray = nullptr;
		rp3d::TriangleMesh* m_TriangleMesh = nullptr;

		/**
		 * @fn CreateTriangleVertexArray
		 *
		 * @brief Helper to create triangle vertex array object
		 */
		void CreateTriangleVertexArray();
	};


}
