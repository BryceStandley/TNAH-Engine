#pragma once

#include <TNAH/Core/Core.h>
#include "TNAH/Core/UUID.h"
#include "TNAH/Scene/SceneCamera.h"
#include "TerrainComponent.h"
#include "PhysicsComponents.h"
#include "LightComponents.h"
#include "AudioComponents.h"


#include "TNAH/Renderer/Mesh.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>


/**********************************************************************************************//**
 * @namespace	tnah
 * 				
 * @file	Components.h
 * 			
 * @brief	Includes and defines structures for each inbuilt components within the engine.
 * 			Standard components are defined within this file, more specific components 
 * 			i.e. Physics related components are defined within the PhysicsComponents.h file
 * 	
 * @author	Bryce Standley
 * @date	20/07/2021
 **************************************************************************************************/

namespace tnah {

	struct IDComponent
	{
		UUID ID = 0;
	};

	struct TagComponent
	{
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent& other) = default;
		TagComponent(const std::string& tag)
			: Tag(tag) {}

		operator std::string& () { return Tag; }
		operator const std::string& () const { return Tag; }
	};

	struct RelationshipComponent
	{
		UUID ParentHandle = 0;
		std::vector<UUID> Children;

		RelationshipComponent() = default;
		RelationshipComponent(const RelationshipComponent& other) = default;
		RelationshipComponent(UUID parent)
			: ParentHandle(parent) {}
	};


	/**********************************************************************************************//**
	 * @struct	Transform
	 *
	 * @brief	Transform component, placed on every object to give it a real transform in the scene
	 * 			i.e. Position, Rotation (Quaternion), Scale and as well as a raw transform 
	 * 			matrix for rendering
	 *
	 * @author	Bryce Standley
	 * @date	20/07/2021
	 **************************************************************************************************/

	struct TransformComponent
	{
		glm::vec3 Position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };

		glm::vec3 Up = { 0.0f, 1.0f, 0.0f };
		glm::vec3 Right = { 1.0f, 0.0f, 0.0f };
		glm::vec3 Forward = { 0.0f, 0.0f, -1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent& other) = default;
		TransformComponent(const glm::vec3& position)
			: Position(position) {}

		glm::mat4 GetTransform() const
		{
			return glm::translate(glm::mat4(1.0f), Position)
				* glm::toMat4(glm::quat(Rotation))
				* glm::scale(glm::mat4(1.0f), Scale);
		}
	};

	/**********************************************************************************************//**
	 * @struct	CameraComponent
	 *
	 * @brief	A camera component that holds all the required information for a camera
	 *
	 * @author	Nukee
	 * @date	3/08/2021
	 **************************************************************************************************/

	struct CameraComponent
	{
		SceneCamera Camera;
		bool Primary = true;

		CameraComponent() = default;
		CameraComponent(const CameraComponent& other) = default;

		operator SceneCamera& () { return Camera; }
		operator const SceneCamera& () const { return Camera; }
	};


	/**********************************************************************************************//**
	 * @struct	MeshComponent
	 *
	 * @brief	A mesh component holds all the information to do with 3D meshes
	 *
	 * @author	Bryce Standley
	 * @date	3/08/2021
	 **************************************************************************************************/

	struct MeshComponent
	{
		Ref<tnah::Model> Model;

		MeshComponent() = default;
		MeshComponent(const MeshComponent& other) = default;
		MeshComponent(const Ref<tnah::Model>& model)
			: Model(model) {}

		operator Ref<tnah::Model>() { return Model; }
	};

	/**********************************************************************************************//**
	 * @struct	NativeScript
	 *
	 * @brief	A native script component allows the user to create overrides that will attach to the
	 * 			game object. Native scripts are written in C++ and provided within the application using
	 * 			the engine.
	 *
	 * @author	Bryce Standley
	 * @date	20/07/2021
	 **************************************************************************************************/

	struct NativeScript 
	{
	};

	/**********************************************************************************************//**
	 * @struct	CSharpScript
	 *
	 * @brief	A C# script component allows the user to create overrides attached to the game object
	 * 			within the application using the engine. A C# script is written in C# and provided 
	 * 			within the application using the engine.
	 *
	 * @author	NukBryce Standley
	 * @date	20/07/2021
	 **************************************************************************************************/

	struct CSharpScript 
	{
	};

}
