#pragma once

#include <TNAH/Core/Core.h>
#include "TNAH/Core/KeyCodes.h"
#include "TNAH/Core/UUID.h"
#include "TNAH/Scene/SceneCamera.h"
#include "SkyboxComponent.h"
#include "TerrainComponent.h"
#include "PhysicsComponents.h"
#include "LightComponents.h"
#include "AudioComponents.h"


#include "TNAH/Renderer/Mesh.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include "TNAH/Core/Input.h"
#include "TNAH/Core/Math.h"


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
	 * 			i.e. Position, Rotation and Scale. Including a raw 4x4 matrix transform (mat4)
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
		TransformComponent(const glm::vec3& position, const glm::vec3& rotation,const glm::vec3& scale)
			:Position(position), Rotation(rotation), Scale(scale) {}

		glm::mat4 GetTransform() const
		{
			return glm::translate(glm::mat4(1.0f), Position)
				* glm::toMat4(glm::quat(Rotation))
				* glm::scale(glm::mat4(1.0f), Scale);
		}

		void SetTransform(const glm::mat4& transform)
		{
			Math::DecomposeTransform(transform, Position, Rotation, Scale);
			
		}
	};


	enum class CameraClearMode { Skybox, Color, None};
	/**********************************************************************************************//**
	 * @struct	CameraComponent
	 *
	 * @brief	A camera component that holds all the required information for a camera
	 *
	 * @author	Nukee
	 * @date	3/08/2021
	 **************************************************************************************************/

	class CameraComponent
	{
	public:
		SceneCamera Camera;
		CameraClearMode ClearMode = CameraClearMode::Color;
		glm::vec4 ClearColor = { 0.1f, 0.1f, 0.1f, 1.0f };
		bool Primary = true;

		void SetClearMode(const CameraClearMode& mode)
		{
			if(mode != ClearMode)
			{
				ClearMode = mode;
				m_UpdatedClear = true;
			}
		}

		CameraComponent() = default;
		CameraComponent(const CameraComponent& other) = default;

		CameraComponent(const SceneCamera& camera)
		{
			Camera = camera;
		}

		operator SceneCamera& () { return Camera; }
		operator const SceneCamera& () const { return Camera; }
	private:
		bool m_UpdatedClear = false;
		friend class EditorUI;
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
		Ref<Model> Model;

		MeshComponent() = default;
		MeshComponent(const std::string& modelPath) { Model = Model::Create(modelPath); }
		MeshComponent(const MeshComponent& other) = default;
		MeshComponent(Ref<tnah::Model> model)
			: Model(model) {}

		operator Ref<tnah::Model>() { return Model; }
	};

	enum class MovementType
	{
		Direct, Physics
	};

	class PlayerControllerComponent
	{
	public:
		
		KeyCode Forward = Key::W;
		KeyCode Backward = Key::S;
		KeyCode Left = Key::A;
		KeyCode Right = Key::D;

		std::pair<KeyCode, KeyCode> Sprint = {Key::LeftShift, Key::RightShift};
		KeyCode Jump = Key::Space;
		KeyCode Crouch = Key::C;
		MovementType MovementStyle = MovementType::Direct;

		float PlayerHeight = 3.5f;
		float MovementSpeed = 5.0f;
		float RotationSensitivity = 0.1f;
		float SprintSpeed = 10.0f;
		float CrouchSpeed = 2.5f;
		float CrouchHeightMultiplier = 0.5f;

		PlayerControllerComponent() = default;

		bool IsSprinting() const { return Input::IsKeyPressed(Sprint.first) || Input::IsKeyPressed(Sprint.second); }
		bool IsCrouched() const { return Input::IsKeyPressed(Crouch); }
		bool IsJumping() const { return Input::IsKeyPressed(Jump); }
		bool IsMoving() const { return Input::IsKeyPressed(Forward) || Input::IsKeyPressed(Backward) ||
			Input::IsKeyPressed(Left) || Input::IsKeyPressed(Right); }
		
		void SetActive(const bool& active) { m_Active = active; }
		bool IsActive() const{ return m_Active; }
	
	private:

		void ProcessMouseRotation(TransformComponent& transform)
		{
			const auto [fst, snd] = Input::GetMousePos();
            if (m_FirstMouseInput)
            {
            	m_LastMouseXPos = fst;
            	m_LastMouseYPos = snd;
            	m_FirstMouseInput = false;
            }
            float offsetX = fst - m_LastMouseXPos;
            float offsetY = m_LastMouseYPos - snd;
            m_LastMouseXPos = fst;
            m_LastMouseYPos = snd;
            offsetX *= RotationSensitivity;
            offsetY *= RotationSensitivity;
            transform.Rotation.x += offsetX;
            transform.Rotation.y -= offsetY;
            if (transform.Rotation.y > 89.0f)
            {
            	transform.Rotation.y = 89.0f;
            }
            if (transform.Rotation.y < -89.0f)
            {
            	transform.Rotation.y = -89.0f;
            }
		}

		bool m_Active = true;
		bool m_FirstMouseInput = true;
		float m_LastMouseXPos = 0.0f;
		float m_LastMouseYPos = 0.0f;
		bool m_MouseDisabled = false;
		friend class Scene;
		
	};

	struct EditorCameraComponent
	{
		SceneCamera EditorCamera;
		CameraClearMode ClearMode = CameraClearMode::Color;
		glm::vec4 ClearColor = { 0.1f, 0.1f, 0.1f, 1.0f };
		bool Primary = true;

		void SetClearMode(const CameraClearMode& mode)
		{
			if(mode != ClearMode)
			{
				ClearMode = mode;
			}
		}
		
		EditorCameraComponent() = default;
		EditorCameraComponent(const EditorCameraComponent& other) = default;

		operator SceneCamera& () { return EditorCamera; }
		operator const SceneCamera& () const { return EditorCamera; }

		friend class Scene;
	};
	
	/**
	 *	@class EditorComponent
	 *
	 *	@brief A component that's placed on a editor camera to control and maintain editor related controls and values.
	 *
	 *	@author Bryce Standley
	 *	@date 21/08/2021
	 */
	class EditorComponent
	{
	public:
		EditorComponent() = default;
		// TODO: Set up the editor component properly 
	private:
		enum class EditorMode
		{
			Edit, Play, Pause
		};

		EditorMode m_EditorMode = EditorMode::Edit;
		bool m_IsEmpty = true;
		
		
		friend class Scene;
		friend class EditorLayer;
		friend class EditorUI;
		friend class Editor;
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

	struct NativeScriptComponent
	{
		std::string Script;
		NativeScriptComponent() = default;
		NativeScriptComponent(const std::string& scriptPath)
			:Script(scriptPath) {}
	};

	/**********************************************************************************************//**
	 * @struct	CSharpScript
	 *
	 * @brief	A C# script component allows the user to create overrides attached to the game object
	 * 			within the application using the engine. A C# script is written in C# and provided 
	 * 			within the application using the engine.
	 *
	 * @author	Bryce Standley
	 * @date	20/07/2021
	 **************************************************************************************************/

	struct CSharpScript 
	{
	};

}
