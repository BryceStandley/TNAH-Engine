#pragma once

#include <stdbool.h>
#include <TNAH-App.h>
#include <imgui.h>
#include <glm/gtx/string_cast.hpp>
#include "TNAH/Layers/ImGuizmo.h"
namespace tnah {

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();

		void OnUpdate(Timestep deltaTime) override;
		void OnFixedUpdate(PhysicsTimestep ps) override;
		void OnImGuiRender() override;

		void OnEvent(Event& event) override;
		void CloseScene(Ref<Scene> scene);
		float GetSnapValue();

		~EditorLayer() override;
		void OnAttach() override;
		void OnDetach() override;
	private:
		enum class FocusedWindow
		{
			None, SceneView, GameView, Statistics, Properties, Hierarchy
		};

		enum class EditorState
		{
			LoadingScene = 0, Play = 1, Edit = 2, Pause = 3
		};
	
		EditorState m_State = EditorState::Edit;
		
		Ref<Scene> m_ActiveScene;
		GameObject m_EditorCamera;
		FocusedWindow m_FocusedWindow;

		GameObject* m_SelectedGameObject;
		bool m_HasObjectSelected;
		bool m_FirstMouseInput = true;
		float m_LastMouseXPos = 0.0f;
		float m_LastMouseYPos = 0.0f;
		float m_CameraMouseSensitivity = 0.1f;
		bool m_CameraMovementToggle = true;
		bool m_CursorDisable = false;
		bool m_Snap = false;

		Ref<Texture2D> m_SelectToolTex, m_MoveToolTex, m_RotateToolTex, m_ScaleToolTex, m_PlayButtonTex, m_StopButtonTex, m_PauseButtonTex;
		
		int m_GizmoType; // -1 = no gizmo

		//Scene view framebuffer
		Ref<Framebuffer> m_EditorSceneFramebuffer;
		Ref<Framebuffer> m_EditorGameFramebuffer;
		ImVec2 m_SceneViewSize = {0,0};
		bool m_SceneViewActive = false;
		glm::vec3 m_SnapValue;
		int CountGameObjects(std::string name);
		
	};
	


}

