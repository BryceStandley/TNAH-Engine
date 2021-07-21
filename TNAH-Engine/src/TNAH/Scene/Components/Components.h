#pragma once

#include <TNAH/Core/Core.h>
#include "TerrainComponent.h"
#include "PhysicsComponents.h"
#include "LightComponents.h"
#include "AudioComponents.h"

#include <glm/glm.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
	 * @class	Camera
	 *
	 * @brief	A camera component that allows an objects view to be rendered.
	 *
	 * @author	Bryce Standley
	 * @date	20/07/2021
	 **************************************************************************************************/

	class Camera 
	{
	public:
		enum class CameraType
		{
			Orthographic, Perspective
		};
		Camera()
			:m_Projection(glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f)), m_View(1.0f), m_Position({ 0.0f }), m_Rotation({0.0f})
		{
			m_ViewProjection = m_Projection * m_View;
		}

		Camera(float left, float right, float bottom, float top)
			: m_Projection(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_View(1.0f), m_Position({ 0,0,0 }), m_Rotation({0,0,0})
		{
			m_ViewProjection = m_Projection * m_View;
		}

		const glm::vec3& GetPosition() const { return m_Position; }
		inline void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }

		const glm::vec3 GetRotation() const { return m_Rotation; }
		inline void SetRotation(const glm::vec3& rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

		const glm::mat4& GetProjectionMatrix() const { return m_Projection; }
		inline void SetProjection(const glm::mat4& projection) { m_Projection = projection; }

		const glm::mat4& GetViewMatrix() const { return m_View; }
		inline void SetView(const glm::mat4& view) { m_View = view; }

		const glm::mat4& GetViewProjection() const { return m_ViewProjection; }

	private:
		inline void RecalculateViewMatrix()
		{
			if (m_CameraType == CameraType::Orthographic)
			{
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.z), { 0,0,1 });
				m_View = glm::inverse(transform);

				//Must be Projection * view not view * projection
				m_ViewProjection = m_Projection * m_View;
			}
			else
			{

			}
		}

	private:
		glm::mat4 m_Projection;
		glm::mat4 m_View;
		glm::mat4 m_ViewProjection;

		glm::vec3 m_Position;
		glm::vec3 m_Rotation;
		CameraType m_CameraType = CameraType::Orthographic;
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
