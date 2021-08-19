#pragma once

#include <TNAH-App.h>

namespace tnah {

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();

		void OnUpdate(Timestep deltaTime) override;
		void OnFixedUpdate(PhysicsTimestep ps) override;
		void OnImGuiRender() override;

		void OnEvent(Event& event) override;


		~EditorLayer() override;
		void OnAttach() override;
		void OnDetach() override;
	private:
		enum class FocusedWindow
		{
			None, SceneView, Statistics, Properties, Hierarchy
		};
	
		
		Scene* m_ActiveScene;
		Ref<GameObject> m_EditorCamera;
		FocusedWindow m_FocusedWindow;

		GameObject* m_SelectedGameObject;
		bool m_HasObjectSelected;
		bool m_FirstMouseInput = true;
		float m_LastMouseXPos = 0.0f;
		float m_LastMouseYPos = 0.0f;
		float m_CameraMouseSensitivity = 0.1f;
		bool m_CameraMovementToggle = true;

		Ref<Texture2D> m_SelectToolTex, m_MoveToolTex, m_RotateToolTex, m_ScaleToolTex;
		
		int m_GizmoType = -1; // -1 = no gizmo

		//Scene view framebuffer
		Ref<Framebuffer> m_SceneFramebuffer;

		char m_ObjectNames[128];
	};


}

