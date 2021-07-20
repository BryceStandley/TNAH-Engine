#pragma once

namespace tnah {

	/**********************************************************************************************//**
 * @struct	RigidBody
 *
 * @brief	A physics rigidbody allows physics to be simulated on a object
 *
 * @author	Bryce Standley
 * @date	20/07/2021
 **************************************************************************************************/

	struct RigidBody 
	{
	};

	/**********************************************************************************************//**
	 * @struct	ColisionBody
	 *
	 * @brief	A colision body is similar to a rigidbody but doesn't allow physics to interact with the
	 * 			object. The user is required to manually move the object.
	 *
	 * @author	Bryce Standley
	 * @date	20/07/2021
	 **************************************************************************************************/

	struct ColisionBody 
	{
	};

	/**********************************************************************************************//**
	 * @struct	BoxCollider
	 *
	 * @brief	A box collider is a simple collider of a box or cube.
	 *
	 * @author	Bryce Standley
	 * @date	20/07/2021
	 **************************************************************************************************/

	struct BoxCollider 
	{
	};

	/**********************************************************************************************//**
	 * @struct	HeightMeshCollider
	 *
	 * @brief	Height field collider using height values. Used for terrains
	 *
	 * @author	Bryce Standley
	 * @date	20/07/2021
	 **************************************************************************************************/

	struct HeightMeshCollider 
	{
	};

	/**********************************************************************************************//**
	 * @struct	SphereCollider
	 *
	 * @brief	A sphere collider is a simple collider using a sphere shape.
	 *
	 * @author	Bryce Standley
	 * @date	20/07/2021
	 **************************************************************************************************/

	struct SphereCollider 
	{
	};

	/**********************************************************************************************//**
	 * @struct	CapsuleCollider
	 *
	 * @brief	A capsule collider is a simple collider using a capsule shape.
	 *
	 * @author	Bryce Standley
	 * @date	20/07/2021
	 **************************************************************************************************/

	struct CapsuleCollider 
	{
	};

	/**********************************************************************************************//**
	 * @struct	MeshCollider
	 *
	 * @brief	A mesh collider is a complex collider using either a convex or concave mesh shape to
	 * 			construct the collider
	 *
	 * @author	Bryce Standley
	 * @date	20/07/2021
	 **************************************************************************************************/

	struct MeshCollider
	{
		enum class ShapeType
		{
			Convex, Concave
		};
	};


}