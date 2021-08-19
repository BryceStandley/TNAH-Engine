#include "EditorLayer.h"


#include <imgui.h>

#include "TNAH/Layers/ImGuizmo.h"
#include "TNAH/Scene/Components/EditorCamera.h"
#include "TNAH/Editor/EditorUI.h"

namespace tnah {

		EditorLayer::EditorLayer()
			: Layer("Editor Layer"), t_Cube(nullptr), m_FocusedWindow(FocusedWindow::None), m_count(0), text("")
		{
			m_ActiveScene = Scene::CreateNewEditorScene();
		}

		void EditorLayer::OnUpdate(Timestep deltaTime)
		{
			auto& c = t_Cube->GetComponent<TransformComponent>();
			//c.Rotation.y += 2.5 * deltaTime.GetSeconds();

			if(m_FocusedWindow == FocusedWindow::SceneView)
			{
				if(Input::IsKeyPressed(Key::LeftShift) || Input::IsKeyPressed(Key::RightShift))
				{
					auto& cam = m_ActiveScene->GetEditorCameraGameObject()->GetComponent<TransformComponent>();
					if(Input::IsKeyPressed(Key::Down)) cam.Position -= cam.Forward * 5.0f * deltaTime.GetSeconds();
					if(Input::IsKeyPressed(Key::Up)) cam.Position += cam.Forward * 5.0f * deltaTime.GetSeconds();
					if(Input::IsKeyPressed(Key::Left)) cam.Position -= cam.Right * 5.0f * deltaTime.GetSeconds();
					if(Input::IsKeyPressed(Key::Right)) cam.Position += cam.Right * 5.0f * deltaTime.GetSeconds();
				}
			}
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
			static bool propertiesOpen = true;
			static bool notImplPopup = false;
			static bool hierarchyOpen = true;
			static bool helpOpen = false;

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
			if(ImGui::BeginMainMenuBar())
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
							m_SceneFramebuffer = m_ActiveScene->GetSceneFramebuffer();
						}
					}

					if(ImGui::MenuItem("Open Scene"))
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

					if(ImGui::MenuItem("Save Scene"))
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

					if(ImGui::MenuItem("Save Scene As"))
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
					if (ImGui::MenuItem("Statistics"))
					{
						statsViewOpen = !statsViewOpen;
					}
					if (ImGui::MenuItem("Properties"))
					{
						propertiesOpen = !propertiesOpen;
					}
					if (ImGui::MenuItem("Hierarchy"))
					{
						hierarchyOpen = !hierarchyOpen;
					}

					ImGui::EndMenu();
				}

				if(ImGui::BeginMenu("Resolution"))
				{
					if(ImGui::MenuItem("640 x 480 (480p)"))
					{
						FramebufferSpecification spec {640, 480};
						m_SceneFramebuffer->Reset(spec);
						auto& ec = m_EditorCamera->GetComponent<EditorCameraComponent>();
						ec.EditorCamera.SetViewportSize(spec.Width, spec.Height);
					}
					if(ImGui::MenuItem("1280 x 720 (720p)"))
					{
						FramebufferSpecification spec {1280, 720};
						m_SceneFramebuffer->Reset(spec);
						auto& ec = m_EditorCamera->GetComponent<EditorCameraComponent>();
						ec.EditorCamera.SetViewportSize(spec.Width, spec.Height);
					}
					if(ImGui::MenuItem("1920 x 1080 (1080p)"))
					{
						FramebufferSpecification spec {1920, 1080};
						m_SceneFramebuffer->Reset(spec);
						auto& ec = m_EditorCamera->GetComponent<EditorCameraComponent>();
						ec.EditorCamera.SetViewportSize(spec.Width, spec.Height);
					}
					if(ImGui::MenuItem("2560 x 1080 (UW 1080p)"))
					{
						auto& ec = m_EditorCamera->GetComponent<EditorCameraComponent>();
						ec.EditorCamera.SetViewportSize(2560, 1080);
						FramebufferSpecification spec {2560, 1080};
						m_SceneFramebuffer->Reset(spec);
						
					}
					if(ImGui::MenuItem("2560 x 1440 (1440p)"))
					{
						FramebufferSpecification spec {2560, 1440};
						m_SceneFramebuffer->Reset(spec);
						auto& ec = m_EditorCamera->GetComponent<EditorCameraComponent>();
						ec.EditorCamera.SetViewportSize(spec.Width, spec.Height);
					}
					if(ImGui::MenuItem("3840 x 2160 (4K)"))
					{
						FramebufferSpecification spec {3840, 2160};
						m_SceneFramebuffer->Reset(spec);
						auto& ec = m_EditorCamera->GetComponent<EditorCameraComponent>();
						ec.EditorCamera.SetViewportSize(spec.Width, spec.Height);
					}
					if(ImGui::MenuItem("Custom"))
					{
						notImplPopup = true;
						
						//FramebufferSpecification spec {1280, 720};
						//m_SceneFramebuffer->Reset(spec);
					}
					ImGui::EndMenu();
				}

				if(ImGui::BeginMenu("Help"))
				{
					if(ImGui::MenuItem("Key Bindings"))
					{
						helpOpen = true;
						
					}
					ImGui::EndMenu();
				}
				
				ImGui::EndMainMenuBar();
			}

			if(helpOpen)
			{
				ImGui::OpenPopup("Key Bindings");
				if(ImGui::BeginPopup("Key Bindings"))
				{
					ImGui::Text("Editor Camera");
					ImGui::BulletText("Movement: Shift + Arrow Keys");

					ImGui::Separator();

					if(ImGui::Button("Close"))
					{
						helpOpen = false;
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndPopup();
				}

				//put other help popups here
			}


			if (ImGui::BeginMenuBar())
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

				ImVec2 iconSize = { 24,24 };
				if (ImGui::ImageButton((void*)m_SelectToolTex->GetRendererID(), iconSize, ImVec2(0, 0), ImVec2(1, 1), -1, ImVec4(0, 0, 0, 0), m_GizmoType == -1 ? c_SelectedGizmoButtonColor : c_UnselectedGizmoButtonColor))
					m_GizmoType = -1;
				ImGui::SameLine();
				if (ImGui::ImageButton((void*)m_MoveToolTex->GetRendererID(), iconSize, ImVec2(0, 0), ImVec2(1, 1), -1, ImVec4(0, 0, 0, 0), m_GizmoType == ImGuizmo::OPERATION::TRANSLATE ? c_SelectedGizmoButtonColor : c_UnselectedGizmoButtonColor))
					m_GizmoType = ImGuizmo::OPERATION::TRANSLATE;
				ImGui::SameLine();
				if (ImGui::ImageButton((void*)m_RotateToolTex->GetRendererID(), iconSize, ImVec2(0, 0), ImVec2(1, 1), -1, ImVec4(0, 0, 0, 0), m_GizmoType == ImGuizmo::OPERATION::ROTATE ? c_SelectedGizmoButtonColor : c_UnselectedGizmoButtonColor))
					m_GizmoType = ImGuizmo::OPERATION::ROTATE;
				ImGui::SameLine();
				if (ImGui::ImageButton((void*)m_ScaleToolTex->GetRendererID(), iconSize, ImVec2(0, 0), ImVec2(1, 1), -1, ImVec4(0, 0, 0, 0), m_GizmoType == ImGuizmo::OPERATION::SCALE ? c_SelectedGizmoButtonColor : c_UnselectedGizmoButtonColor))
					m_GizmoType = ImGuizmo::OPERATION::SCALE;

				ImGui::PopStyleColor(3);
				ImGui::EndMenuBar();
			}

			if (notImplPopup)
			{
				ImGui::OpenPopup("Not Implemented Yet!");
				if (ImGui::BeginPopup("Not Implemented Yet!"))
				{
					ImGui::Text("This function hasn't been implemented yet!");
					if (ImGui::Button("Close"))
					{
						notImplPopup = false;
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndPopup();
				}
			}


			//Stats window
			//Add stats to the editor to see whats going on
			if (statsViewOpen)
			{
				ImGui::Begin("Statistics", &statsViewOpen);
				if (ImGui::IsWindowFocused()) m_FocusedWindow = FocusedWindow::Statistics;
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
				if (ImGui::IsWindowFocused()) m_FocusedWindow = FocusedWindow::SceneView;
				uint32_t id = 0;
				if (m_SceneFramebuffer == nullptr)
				{
					id = Renderer::GetMissingTexture()->GetRendererID();
				}
				else
				{
					id = m_SceneFramebuffer->GetColorAttachmentRendererID();
				}

				auto size = ImGui::GetContentRegionAvail();
				ImGui::Image((void*)id, size);
				ImGui::End();
			}

			if (hierarchyOpen)
			{
				ImGui::Begin("Hierarchy", &hierarchyOpen);
				if (ImGui::IsWindowFocused()) m_FocusedWindow = FocusedWindow::Hierarchy;
				ImGui::InputText("Name", m_ObjectNames, sizeof(m_ObjectNames));

				if (ImGui::Button("Create New Object"))
				{
					std::string name(m_ObjectNames);
					std::cout << name.size() << " " << name << std::endl;
					if (name.size() > 0)
					{
						bool exists = false;

						//Im not sure if tag is meant to be the title/name of the object, but im using it for now, easily can be changed if it is not
						auto objects = m_ActiveScene->GetGameObjectsInScene();
						for (auto& go : objects)
						{
							auto& g = go.second;
							std::string object_name = "GameObject";
							if (g.HasComponent<TagComponent>()) object_name = g.GetComponent<TagComponent>().Tag;
							if (name == object_name)
							{
								exists = true;
								break;
							}
						}

						if(!exists)
							m_ActiveScene->CreateGameObject(name);
						//else
						// error
					}
					else
					{
						int num = 1;

						//Im not sure if tag is meant to be the title/name of the object, but im using it for now, easily can be changed if it is not
						auto objects = m_ActiveScene->GetGameObjectsInScene();
						for (auto& go : objects)
						{
							auto& g = go.second;
							std::string object_name = "GameObject";
							if (g.HasComponent<TagComponent>()) object_name = g.GetComponent<TagComponent>().Tag;
							if (object_name.find("Game Object") != std::string::npos)
							{
								num++;
							}
						}
						m_ActiveScene->CreateGameObject("Game Object (" + std::to_string(num) + ")");
					}
				}

				ImGui::Separator();

				auto objects = m_ActiveScene->GetGameObjectsInScene();
				for(auto& go : objects)
				{
					auto& g = go.second;
					std::string name = "GameObject";
					if(g.HasComponent<TagComponent>()) name = g.GetComponent<TagComponent>().Tag;
					if(ImGui::Button(name.c_str()))
					{
						m_HasObjectSelected = true;
						m_SelectedGameObject = m_ActiveScene->GetRefGameObject(g.GetUUID());
					}
				}
				
				ImGui::End();
			}

			if(propertiesOpen)
			{
				ImGui::Begin("Properties", &propertiesOpen);
				if(ImGui::IsWindowFocused()) m_FocusedWindow = FocusedWindow::Properties;
				
				if(m_HasObjectSelected)
				{
					// TODO: Properties rendering
					//Create a UI class that takes in the selected gameobject
					//That class will check for every type of component the engine supports
					// like if(object->HasComponent<MeshComponent>()
					// Then use a set function to each part of the components property panel
					// like DrawVec3Control()
					EditorUI::DrawComponentProperties(m_SelectedGameObject);
					
				}
				else
				{
					EditorUI::DrawComponentProperties(m_EditorCamera.get());
				}
				
				ImGui::End();
			}

			


			//*************************************************************//
			// End the Docking space for the editor, DONT REMOVE THIS
			// All dockable windows must be defined above
			// This End() is ending the ImGui docking space and anything below it
			// cant be docked
			ImGui::End();

			switch (m_FocusedWindow)
			{
				case FocusedWindow::None:
					m_HasObjectSelected = false;
					m_SelectedGameObject = nullptr;
					break;
				case FocusedWindow::SceneView:
					m_HasObjectSelected = false;
					m_SelectedGameObject = nullptr;
					break;
				case FocusedWindow::Hierarchy:
					break;
				case FocusedWindow::Properties:
					break;
				case FocusedWindow::Statistics:
					m_HasObjectSelected = false;
					m_SelectedGameObject = nullptr;
					break;
				default:
					break;
			}
		}

		void EditorLayer::OnEvent(Event& event)
		{

		}

		EditorLayer::~EditorLayer()
		{
		}

		void EditorLayer::OnAttach()
		{
			m_EditorCamera = m_ActiveScene->GetEditorCameraGameObject();
			m_SceneFramebuffer = m_ActiveScene->GetSceneFramebuffer();
			m_SelectToolTex.reset(Texture2D::Create("assets/Editor/icons/SelectTool.png"));
			m_MoveToolTex.reset(Texture2D::Create("assets/Editor/icons/MoveTool.png"));
			m_RotateToolTex.reset(Texture2D::Create("assets/Editor/icons/RotateTool.png"));
			m_ScaleToolTex.reset(Texture2D::Create("assets/Editor/icons/ScaleTool.png"));

			// Test, Load a test cube from the editor mesh folder
			t_Cube = m_ActiveScene->CreateGameObject("Cube");
			auto& c = t_Cube->AddComponent<MeshComponent>("assets/Editor/meshes/cube_texture.fbx");
			m_SelectedGameObject = nullptr;
		}

		void EditorLayer::OnDetach()
		{
		}


}
