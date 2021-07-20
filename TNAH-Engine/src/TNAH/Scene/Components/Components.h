#pragma once

#include <TNAH/Core/Core.h>
#include "TerrainComponent.h"
#include "PhysicsComponents.h"
#include "LightComponents.h"
#include "AudioComponents.h"

#include <glm/glm.hpp>
#include <glm/gtx/matrix_decompose.hpp>

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

	struct Transform
	{
		glm::mat4 TransformMatrix;

		glm::vec3 Position;
		glm::quat Rotation;
		glm::vec3 Scale;

		Transform()
		{
			TransformMatrix = glm::mat4(1.0f);
			Position = TransformMatrix[3];
			Rotation = glm::quat_cast(TransformMatrix);
			for (int i = 0; i < 3; i++)
			{
				Scale[i] = glm::length(glm::vec3(TransformMatrix[i]));
			}
		}

		Transform(const Transform&) = default;

		Transform(const glm::mat4& trans)
			:TransformMatrix(trans), Position(trans[3]), Rotation(glm::quat_cast(trans)) 
		{
			for (int i = 0; i < 3; i++)
			{
				Scale[i] = glm::length(glm::vec3(trans[i]));
			}
		}

		operator const glm::mat4& () const { return TransformMatrix; }
		operator const glm::mat4& () { return TransformMatrix; }
	};



	/**********************************************************************************************//**
	 * @struct	Camera
	 *
	 * @brief	A camera component that allows an objects view to be rendered.
	 *
	 * @author	Bryce Standley
	 * @date	20/07/2021
	 **************************************************************************************************/

	struct Camera 
	{

		enum class CameraType
		{
			Orthographic, Perspective
		};

		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		float m_Left, m_Right, m_Bottom, m_Top;
		float m_Near = -1.0f, m_Far = 1.0f;

		Camera() = default;
		Camera(const Camera&) = default;
		Camera(float left, float right, float bottom, float top)
			:m_Left(left), m_Right(right), m_Bottom(bottom), m_Top(top)
		{}



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
