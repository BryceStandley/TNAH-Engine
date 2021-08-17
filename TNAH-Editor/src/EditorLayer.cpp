#include "EditorLayer.h"


#include <imgui.h>
#include "TNAH/Layers/ImGuizmo.h"

namespace tnah {

		EditorLayer::EditorLayer()
			: Layer("Editor Layer")
		{
			m_ActiveScene = Scene::CreateEmptyScene();
			m_SelectToolTex.reset(Texture2D::Create("assets/Editor/icons/SelectTool.png"));
			m_MoveToolTex.reset(Texture2D::Create("assets/Editor/icons/MoveTool.png"));
			m_RotateToolTex.reset(Texture2D::Create("assets/Editor/icons/RotateTool.png"));
			m_ScaleToolTex.reset(Texture2D::Create("assets/Editor/icons/ScaleTool.png"));
		}

		void EditorLayer::OnUpdate(Timestep deltaTime)
		{


			//Rendering is managed by the scene!
			m_ActiveScene->OnUpdate(deltaTime);
		}

		void EditorLayer::OnFixedUpdate(PhysicsTimestep ps)
		{
			m_ActiveScene->OnFixedUpdate(ps);
		}

		void EditorLayer::OnImGuiRender()
		{
			//toggles for each view/window
			static bool dockspaceOpen = true;
			static bool sceneViewOpen = true;
			static bool statsViewOpen = true;

			//Imgui dock space setup, DONT TOUCH
			static bool opt_fullscreen = true;
			static bool opt_padding = false;
			static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
			ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
			if (opt_fullscreen)
			{
				const ImGuiViewport* viewport = ImGui::GetMainViewport();
				ImGui::SetNextWindowPos(viewport->WorkPos);
				ImGui::SetNextWindowSize(viewport->WorkSize);
				ImGui::SetNextWindowViewport(viewport->ID);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
				window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
				window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
			}
			else
			{
				dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
			}

			if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
				window_flags |= ImGuiWindowFlags_NoBackground;

			if (!opt_padding)
				ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
			ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
			if (!opt_padding)
				ImGui::PopStyleVar();

			if (opt_fullscreen)
				ImGui::PopStyleVar(2);

			// Submit the DockSpace
			ImGuiIO& io = ImGui::GetIO();
			if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
			{
				ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
				ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
			}

			//******************************************************************************//
			// Add any menu items or windows here following the same structure as below

			//Menu bar of the editor
			if (ImGui::BeginMainMenuBar())
			{
				if (ImGui::BeginMenu("File"))
				{
					if(ImGui::MenuItem("New Scene"))
					{
						if(!FileManager::NewScene())
						{
							auto sceneFile = FileManager::GetActiveFile();
							if(sceneFile->FileOpenError == FileError::PathInvalid)
							{
								TNAH_WARN("The path or file was invalid!");
							}
						}
						else
						{
							m_ActiveScene = Scene::CreateNewEditorScene();
							m_EditorCamera = m_ActiveScene->GetEditorCameraGameObject();
						}
					}

					if (ImGui::MenuItem("Open Scene"))
					{
						if (!FileManager::OpenScene())
						{
							auto sceneFile = FileManager::GetActiveFile();
							if(sceneFile->FileOpenError == FileError::PathInvalid)
							{
								TNAH_WARN("The path or file was invalid!");
							}
						}
						else
						{
							auto sceneFile = FileManager::GetActiveFile();
							m_ActiveScene = Scene::CreateEditorSceneFromFile(sceneFile->FilePath);
							m_EditorCamera = m_ActiveScene->GetEditorCameraGameObject();
						}
					}

					if (ImGui::MenuItem("Save Scene"))
					{
						if (!FileManager::SaveScene())
						{
							auto sceneFile = FileManager::GetActiveFile();
							if(sceneFile->FileOpenError == FileError::PathInvalid)
							{
								TNAH_WARN("The path or file was invalid!");
							}
						}
						else
						{
							auto sceneFile = FileManager::GetActiveFile();
							// serialize the scene
						}
						
					}

					if (ImGui::MenuItem("Save Scene As"))
					{
						if (!FileManager::SaveSceneAs())
						{
							auto sceneFile = FileManager::GetActiveFile();
							if(sceneFile->FileOpenError == FileError::PathInvalid)
							{
								TNAH_WARN("The path or file was invalid!");
							}
						}
						else
						{
							auto sceneFile = FileManager::GetActiveFile();
							// save the scene with the new file name and path
						}
					}

					ImGui::Separator();

					if (ImGui::MenuItem("Close Editor")) Application::Get().Close();
					ImGui::EndMenu();
				}

				if (ImGui::BeginMenu("View"))
				{
					if (ImGui::MenuItem("Scene View"))
					{
						sceneViewOpen = !sceneViewOpen;
					}
					if (ImGui::MenuItem("Statistics View"))
					{
						statsViewOpen = !statsViewOpen;
					}

					ImGui::EndMenu();
				}
				
				ImGui::EndMainMenuBar();
			}

			
			if(ImGui::BeginMenuBar())
			{
				auto size = ImGui::GetWindowPos();
				size.y += 100;
				ImGui::SetNextWindowSize(size);
				ImGui::SetNextWindowBgAlpha(0.75f);
				const ImVec4 c_SelectedGizmoButtonColor = ImVec4(0.925490196f, 0.619607843f, 0.141176471f, 1.0f);
				const ImVec4 c_UnselectedGizmoButtonColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0, 0, 0, 0));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0, 0, 0, 0));
				
				ImVec2 iconSize = {24,24};
				if(ImGui::ImageButton((void*)m_SelectToolTex->GetRendererID(), iconSize, ImVec2(0,0), ImVec2(1,1), -1, ImVec4(0,0,0,0), m_GizmoType == -1 ? c_SelectedGizmoButtonColor : c_UnselectedGizmoButtonColor))
					m_GizmoType = -1;
				ImGui::SameLine();
				if(ImGui::ImageButton((void*)m_MoveToolTex->GetRendererID(), iconSize, ImVec2(0,0), ImVec2(1,1), -1, ImVec4(0,0,0,0), m_GizmoType == ImGuizmo::OPERATION::TRANSLATE ? c_SelectedGizmoButtonColor : c_UnselectedGizmoButtonColor))
					m_GizmoType = ImGuizmo::OPERATION::TRANSLATE;
				ImGui::SameLine();
				if(ImGui::ImageButton((void*)m_RotateToolTex->GetRendererID(), iconSize, ImVec2(0,0), ImVec2(1,1), -1, ImVec4(0,0,0,0), m_GizmoType == ImGuizmo::OPERATION::ROTATE ? c_SelectedGizmoButtonColor : c_UnselectedGizmoButtonColor))
					m_GizmoType = ImGuizmo::OPERATION::ROTATE;
				ImGui::SameLine();
				if(ImGui::ImageButton((void*)m_ScaleToolTex->GetRendererID(), iconSize, ImVec2(0,0), ImVec2(1,1), -1, ImVec4(0,0,0,0), m_GizmoType == ImGuizmo::OPERATION::SCALE ? c_SelectedGizmoButtonColor : c_UnselectedGizmoButtonColor))
					m_GizmoType = ImGuizmo::OPERATION::SCALE;

				ImGui::PopStyleColor(3);
				ImGui::EndMenuBar();
			}

			

			//Stats window
			//Add stats to the editor to see whats going on
			if(statsViewOpen)
			{
				ImGui::Begin("Statistics", &statsViewOpen);
				ImGui::BulletText("Draw Calls: %d", Renderer::GetDrawCallsPerFrame());
				ImGui::BulletText("Textures Loaded: %d", Renderer::GetTotalLoadedTextures());
				ImGui::BulletText("Shaders Loaded: %d", Renderer::GetTotalLoadedShaders());
				ImGui::BulletText("Models Loaded: %d", Renderer::GetTotalLoadedModels());
				ImGui::End();
			}


			//Scene View Window 
			if (sceneViewOpen)
			{
				// for now imgui is just rendering the missing texture image but
				// we need to render the scene from the editor camera to a framebuffer and then
				// pass that in as a texture to imgui to make it seem its a scene view

				ImGui::Begin("Scene View", &sceneViewOpen);
				//ImGui::Image(Renderer::GetSceneView());
				auto framebuffer = Renderer::GetMissingTexture();
				uint32_t id = framebuffer->GetRendererID();
				auto size = ImGui::GetContentRegionAvail();
				ImGui::Image((void*)id, size);
				ImGui::End();
			}


			//*************************************************************//
			// End the Docking space for the editor, DONT REMOVE THIS
			// All dockable windows must be defined above
			// This End() is ending the ImGui docking space and anything below it
			// cant be docked
			ImGui::End(); 
		}

		void EditorLayer::OnEvent(Event& event)
		{

		}




}
