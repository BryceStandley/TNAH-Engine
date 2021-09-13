#pragma once

#include <stdbool.h>
#include <TNAH-App.h>
#include <imgui.h>
#include <glm/gtx/string_cast.hpp>
#include "TNAH/Layers/ImGuizmo.h"
namespace tnah {

		/**
		 * @class	EditorLayer
		 *
		 * @brief	An editor layer.
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 */

	class EditorLayer : public Layer
	{
	public:

			/**
			 * @fn	EditorLayer::EditorLayer();
			 *
			 * @brief	Default constructor
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 */

		EditorLayer();

			/**
			 * @fn	void EditorLayer::OnUpdate(Timestep deltaTime) override;
			 *
			 * @brief	Executes the functions on update
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 *
			 * @param 	deltaTime	The delta time.
			 */

		void OnUpdate(Timestep deltaTime) override;

			/**
			 * @fn	void EditorLayer::OnFixedUpdate(PhysicsTimestep ps) override;
			 *
			 * @brief	Executes the function on fixed update
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 *
			 * @param 	ps	The PhysicsTimestep.
			 */

		void OnFixedUpdate(PhysicsTimestep ps) override;

			/**
			 * @fn	void EditorLayer::OnImGuiRender() override;
			 *
			 * @brief	Executes when ImGui is rendering
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 */

		void OnImGuiRender() override;

		/**
		 * @fn	void EditorLayer::OnEvent(Event& event) override;
		 *
		 * @brief	Executes the 'event' action
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @param [in,out]	event	The event.
		 */

		void OnEvent(Event& event) override;

			/**
			 * @fn	void EditorLayer::CloseScene(Ref<Scene> scene);
			 *
			 * @brief	Closes a scene
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 *
			 * @param 	scene	A smart pointer to the scene.
			 */

		void CloseScene(Ref<Scene> scene);

			/**
			 * @fn	float EditorLayer::GetSnapValue();
			 *
			 * @brief	Gets snap value
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 *
			 * @returns	The ImGuizmo snap value.
			 */

		float GetSnapValue();

			/**
			 * @fn	EditorLayer::~EditorLayer() override;
			 *
			 * @brief	Destructor
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 */

		~EditorLayer() override;

		/**
		 * @fn	void EditorLayer::OnAttach() override;
		 *
		 * @brief	Executes the function on attach
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 */

		void OnAttach() override;

			/**
			 * @fn	void EditorLayer::OnDetach() override;
			 *
			 * @brief	Executes the function on detach
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 */

		void OnDetach() override;
	private:

			/**
			 * @enum	FocusedWindow
			 *
			 * @brief	Values that represent the editor windows
			 */

		enum class FocusedWindow
		{
			None, SceneView, GameView, Statistics, Properties, Hierarchy
		};

			/**
			 * @enum	EditorState
			 *
			 * @brief	Values that represent editor states
			 */

		enum class EditorState
		{
			LoadingScene = 0, Play = 1, Edit = 2, Pause = 3
		};
	

			/** @brief	The state of the editior is initially assigned to edit */
		EditorState m_State = EditorState::Edit;
		

			
			
			/** @brief	Pointer to active scene */
		Ref<Scene> m_ActiveScene;

			
			/** @brief	The editor camera */
		GameObject m_EditorCamera;



			/** @brief	The focused window */
		FocusedWindow m_FocusedWindow;


			/** @brief	A pointer to selected game object */
		GameObject* m_SelectedGameObject;


			/** @brief	True if has object selected, false if not */
		bool m_HasObjectSelected;
	

			/** @brief	True to first mouse input */
		bool m_FirstMouseInput = true;


			/** @brief	The last mouse x coordinate position */
		float m_LastMouseXPos = 0.0f;


			/** @brief	The last mouse y coordinate position */
		float m_LastMouseYPos = 0.0f;


			/** @brief	The camera mouse sensitivity */
		float m_CameraMouseSensitivity = 0.1f;


			/** @brief	True to camera movement toggle, false to stop camaeraMovement */
		bool m_CameraMovementToggle = true;

			
			/** @brief	True if cursor disabled, false if enabled */
		bool m_CursorDisable = false;


			/** @brief	True to snap, false to not snap */
		bool m_Snap = false;

		/** @brief	True to enable, false to disable the wireframe */
		bool m_Wireframe = false;

		/** @brief	True to fullscreen */
		bool m_Fullscreen = false;

		/** @brief	True to synchronize */
		bool m_VSync = false;

			/**
			 * @property	Ref<Texture2D> m_SelectToolTex, m_MoveToolTex, m_RotateToolTex, m_ScaleToolTex, m_PlayButtonTex, m_StopButtonTex, m_PauseButtonTex
			 *
			 * @brief	various ref pointers to various Texture2D variables
			 *
			 */

		Ref<Texture2D> m_SelectToolTex, m_MoveToolTex, m_RotateToolTex, m_ScaleToolTex, m_PlayButtonTex, m_StopButtonTex, m_PauseButtonTex;
		

			/** @brief	-1 = no gizmo */
		int m_GizmoType;

			/** @brief	Pointer to the editor scene framebuffer. */
		
		Ref<Framebuffer> m_EditorSceneFramebuffer;

			
			/** @brief	Pointer to editor game framebuffer */
		Ref<Framebuffer> m_EditorGameFramebuffer;


			/** @brief	Size of the scene view */
		ImVec2 m_SceneViewSize = {0,0};

			
			/** @brief	True to make scene view active, false to keep it deactivated*/
		bool m_SceneViewActive = false;

			/** @brief	glm::vec3 representing the snap value */
		glm::vec3 m_SnapValue;

			/**
			 * @fn	int EditorLayer::CountGameObjects(std::string name);
			 *
			 * @brief	Count game object of the given name and names them accordingly
			 *
			 * @author	Dylan Blereau
			 * @date	7/09/2021
			 *
			 * @param 	name	The name of the gameObject.
			 *
			 * @returns	The total number of game objects.
			 */

		int CountGameObjects(std::string name);
		
	};
	


}

