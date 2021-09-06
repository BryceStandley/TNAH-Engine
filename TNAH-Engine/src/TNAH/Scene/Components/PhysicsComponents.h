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

	class RigidBodyComponent 
	{
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

	class CollisionBodyComponent
	{
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
	private:
	};

	/**********************************************************************************************//**
	 * @class	HeightMeshColliderComponent
	 *
	 * @brief	Height field collider using height values. Used for terrains
	 *
	 * @author	Bryce Standley
	 * @date	20/07/2021
	 **************************************************************************************************/

	class HeightMeshColliderComponent : public Component
	{
	public:
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
