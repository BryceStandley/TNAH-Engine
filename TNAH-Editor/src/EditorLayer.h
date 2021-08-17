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


	private:
		Scene* m_ActiveScene;
		Ref<GameObject> m_EditorCamera;

		Ref<GameObject> m_SelectedGameObject;

		Ref<Texture2D> m_SelectToolTex, m_MoveToolTex, m_RotateToolTex, m_ScaleToolTex;
		
		int m_GizmoType = -1; // -1 = no gizmo
	};


}

