#include "EditorLayer.h"

#include "TNAH/Core/Math.h"

#include <imgui.h>
#include <glm/gtx/string_cast.hpp>
#include "TNAH/Layers/ImGuizmo.h"
#include "TNAH/Scene/Components/Components.h"
#include "TNAH/Editor/EditorUI.h"
#include "TNAH/Scene/Serializer.h"
#include "TNAH/Core/Math.h"

namespace tnah {

		EditorLayer::EditorLayer()
			: Layer("Editor Layer"),  m_FocusedWindow(FocusedWindow::None), m_SelectedGameObject(nullptr), m_HasObjectSelected(false), m_GizmoType(-1), m_SnapValue(1.0f)
		{
			
		}

		void EditorLayer::OnUpdate(Timestep deltaTime)
		{	

			if(m_SceneViewActive && m_State != EditorState::LoadingScene)
			{
				if(m_SelectedGameObject != nullptr)
				{
					if(Input::IsKeyPressed(Key::F))
					{
						auto & editorTransform = m_EditorCamera.GetComponent<TransformComponent>();
						auto & gameObjectTransform = m_SelectedGameObject->GetComponent<TransformComponent>();
						glm::vec3 newPos(gameObjectTransform.Position);
						newPos.x -= 6.5;
						newPos.y += 2.5;
						editorTransform.Position = newPos;
						editorTransform.Rotation = glm::vec3(0, -15, 0);	
					}
				}
				
				if(Input::IsKeyPressed(Key::LeftShift) || Input::IsKeyPressed(Key::RightShift))
				{
					auto& cam = m_ActiveScene->GetEditorCamera().Transform();
					if(Input::IsKeyPressed(Key::Down) || Input::IsKeyPressed(Key::S)) cam.Position -= cam.Forward * 5.0f * deltaTime.GetSeconds();
					if(Input::IsKeyPressed(Key::Up) || Input::IsKeyPressed(Key::W)) cam.Position += cam.Forward * 5.0f * deltaTime.GetSeconds();
					if(Input::IsKeyPressed(Key::Left) || Input::IsKeyPressed(Key::A)) cam.Position -= cam.Right * 5.0f * deltaTime.GetSeconds();
					if(Input::IsKeyPressed(Key::Right) || Input::IsKeyPressed(Key::D)) cam.Position += cam.Right * 5.0f * deltaTime.GetSeconds();

					if(Input::IsMouseButtonPressed(Mouse::ButtonLeft))
					{
						Application::Get().GetWindow().SetCursorDisabled(true);
						auto mousePos = tnah::Input::GetMousePos();
						if (m_FirstMouseInput)
						{
							m_LastMouseXPos = mousePos.first;
							m_LastMouseYPos = mousePos.second;
							m_FirstMouseInput = false;
						}

						float offsetX = mousePos.first - m_LastMouseXPos;
						float offsetY = m_LastMouseYPos - mousePos.second;
						m_LastMouseXPos = mousePos.first;
						m_LastMouseYPos = mousePos.second;
						offsetX *= m_CameraMouseSensitivity;
						offsetY *= m_CameraMouseSensitivity;
						cam.Rotation.x += offsetX;
						cam.Rotation.y -= offsetY;
						if (cam.Rotation.y > 89.0f)
						{
							cam.Rotation.y = 89.0f;
						}
						if (cam.Rotation.y < -89.0f)
						{
							cam.Rotation.y = -89.0f;
						}
					}
				}
				else
				{
					Application::Get().GetWindow().SetCursorDisabled(false);
				}
			}
			//Rendering is managed by the scene!
			if(m_ActiveScene != nullptr) m_ActiveScene->OnUpdate(deltaTime);
		}

		void EditorLayer::OnFixedUpdate(PhysicsTimestep ps)
		{
			//if(m_ActiveScene != nullptr) m_ActiveScene->OnFixedUpdate(ps);
		}

		void EditorLayer::OnImGuiRender()
		{
			//toggles for each view/window
			static bool dockspaceOpen = true;
			static bool sceneViewOpen = true;
			static bool gameViewOpen = true;
			static bool statsViewOpen = true;
			static bool propertiesOpen = true;
			static bool notImplPopup = false;
			static bool hierarchyOpen = true;
			static bool helpOpen = false;

			//Imgui dock space setup, DONT TOUCH
			static bool opt_fullscreen_persistant = true;
			static ImGuiDockNodeFlags opt_Flags = ImGuiDockNodeFlags_None;
			bool opt_fullscreen = opt_fullscreen_persistant;

			ImGuiIO& io = ImGui::GetIO();
			ImGuiStyle& style = ImGui::GetStyle();
			
			ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
			if (opt_fullscreen)
			{
				const ImGuiViewport* viewport = ImGui::GetMainViewport();
				ImGui::SetNextWindowPos(viewport->Pos);
				ImGui::SetNextWindowSize(viewport->Size);
				ImGui::SetNextWindowViewport(viewport->ID);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
				window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
				window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
			}

			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0, 0});
			ImGui::Begin("Dockspace Demo", &dockspaceOpen, window_flags);
			ImGui::PopStyleVar();

			if(opt_fullscreen)
				ImGui::PopStyleVar(2);

			float minWinSizeX = style.WindowMinSize.x;
			style.WindowMinSize.x = 370.0f;
			if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
			{
				ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
				ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), opt_Flags);
			}

			style.WindowMinSize.x = minWinSizeX;

			//******************************************************************************//
			// Add any menu items or windows here following the same structure as below
			//Menu bar of the editor
			if (ImGui::BeginMainMenuBar())
			{
			
				if (ImGui::BeginMenu("File"))
				{
					if (ImGui::MenuItem("New Scene"))
					{
						if (!FileManager::NewScene())
						{
							
							auto sceneFile = FileManager::GetActiveFile();
							if (sceneFile->FileOpenError == FileError::PathInvalid)
							{
								TNAH_WARN("The path or file was invalid!");
							}
						}
						else
						{
							m_State = EditorState::LoadingScene;
							CloseScene(m_ActiveScene);
							m_HasObjectSelected = false;
							m_SelectedGameObject = nullptr;
							m_ActiveScene = Scene::CreateNewEditorScene();
							m_EditorCamera = m_ActiveScene->GetEditorCamera();
							m_EditorSceneFramebuffer = m_ActiveScene->GetEditorSceneFramebuffer();
							m_EditorGameFramebuffer = m_ActiveScene->GetEditorGameFramebuffer();
							m_State = EditorState::Edit;
						}
					}

					if (ImGui::MenuItem("Open Scene"))
					{
						if (!FileManager::OpenScene())
						{
							auto sceneFile = FileManager::GetActiveFile();
							if (sceneFile->FileOpenError == FileError::PathInvalid)
							{
								TNAH_WARN("The path or file was invalid!");
							}
						}
						else
						{
							m_State = EditorState::LoadingScene;
							m_HasObjectSelected = false;
							m_SelectedGameObject = nullptr;
							auto sceneFile = FileManager::GetActiveFile();
							if(m_ActiveScene != nullptr)
							{
								CloseScene(m_ActiveScene);
								m_ActiveScene = Serializer::DeserializeScene(sceneFile->FilePath);
								if(m_ActiveScene != nullptr)
								{
									m_EditorCamera = m_ActiveScene->GetEditorCamera();
									m_EditorGameFramebuffer = m_ActiveScene->GetEditorGameFramebuffer();
									m_EditorSceneFramebuffer = m_ActiveScene->GetEditorSceneFramebuffer();
									m_State = EditorState::Edit;
								}
							}
							else
							{
								TNAH_ERROR("Failed to load scene file");
								m_ActiveScene = Ref<Scene>::Create(true);
							}
						}
					}

					if (ImGui::MenuItem("Save Scene"))
					{
						if (!FileManager::SaveScene())
						{
							auto sceneFile = FileManager::GetActiveFile();
							if (sceneFile->FileOpenError == FileError::PathInvalid)
							{
								TNAH_WARN("The path or file was invalid!");
							}
						}
						else
						{
							auto sceneFile = FileManager::GetActiveFile();
							// serialize the scene
							Serializer::SerializeScene(m_ActiveScene, sceneFile->FilePath);
						}

					}

					if (ImGui::MenuItem("Save Scene As"))
					{
						if (!FileManager::SaveSceneAs())
						{
							auto sceneFile = FileManager::GetActiveFile();
							if (sceneFile->FileOpenError == FileError::PathInvalid)
							{
								TNAH_WARN("The path or file was invalid!");
							}
						}
						else
						{
							auto sceneFile = FileManager::GetActiveFile();
							// save the scene with the new file name and path
							Serializer::SerializeScene(m_ActiveScene, sceneFile->FilePath);
						}
					}

					ImGui::Separator();

					if (ImGui::MenuItem("Close Editor")) Application::Get().Close();
					ImGui::Separator();

					ImGui::Text("Current API:");
					std::string label = RendererAPI::GetAPI() == RendererAPI::API::OpenGL ? "OpenGL" : "Unknown";
					ImGui::Text(label.c_str());
					
					ImGui::EndMenu();
				}

				if (ImGui::BeginMenu("View"))
				{
					if (ImGui::MenuItem("Scene View"))
					{
						sceneViewOpen = !sceneViewOpen;
					}
					if(ImGui::MenuItem("Game View"))
					{
						gameViewOpen = !gameViewOpen;
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

				if (ImGui::BeginMenu("Options"))
				{
					if (ImGui::MenuItem("Snap"))
					{
						//TODO Add popup for snap option
						/*ImGui::Checkbox("Active", &m_Snap);
						ImGui::Text("Add options to change snap amount (feeling to lazy rn ngl)");*/
					}
					ImGui::EndMenu();
				}
				
				if(m_ActiveScene != nullptr)
				{
					if (ImGui::BeginMenu("GameObject"))
					{
						if (ImGui::MenuItem("Create Empty GameObject"))
						{
							m_ActiveScene->CreateGameObject("Game Object (" + std::to_string(CountGameObjects("Game Object")) + ")");
						}

						if (ImGui::BeginMenu("Create 3D GameObject"))
						{
							if (ImGui::MenuItem("Cube"))
							{
								auto newObject = m_ActiveScene->CreateGameObject("Cube (" + std::to_string(CountGameObjects("Cube")) + ")");
								newObject.AddComponent<MeshComponent>("assets/Editor/meshes/cube.fbx");
							}

							if (ImGui::MenuItem("Sphere"))
							{
								auto newObject = m_ActiveScene->CreateGameObject("Sphere (" + std::to_string(CountGameObjects("Sphere")) + ")");
								newObject.AddComponent<MeshComponent>("assets/Editor/meshes/sphere.fbx");
							}

							if (ImGui::MenuItem("Plane"))
							{
								auto newObject = m_ActiveScene->CreateGameObject("Plane (" + std::to_string(CountGameObjects("Plane")) + ")");
								newObject.AddComponent<MeshComponent>("assets/Editor/meshes/plane.fbx");
							}

							if (ImGui::MenuItem("Cylinder"))
							{
								auto newObject = m_ActiveScene->CreateGameObject("Cylinder (" + std::to_string(CountGameObjects("Cylinder")) + ")");
								newObject.AddComponent<MeshComponent>("assets/Editor/meshes/cylinder.fbx");
							}
							
							ImGui::EndMenu();
						}

						if (ImGui::BeginMenu("Create Audio GameObject"))
						{
							if(ImGui::MenuItem("Audio Listener"))
							{
								auto newObject = m_ActiveScene->CreateGameObject("AudioListener (" + std::to_string(CountGameObjects("AudioListener")) + ")");
								newObject.AddComponent<AudioListenerComponent>();
							}

							if(ImGui::MenuItem("Audio Source"))
							{
								if (FileManager::OpenAudio())
								{
									auto soundFile = FileManager::GetActiveFile();
									if (soundFile->FileOpenError == FileError::PathInvalid)
									{
										TNAH_WARN("The path or file was invalid!");
									}
									else if(soundFile->FileOpenError != FileError::UserClosed)
									{
										Resource file = {soundFile->FilePath};
										auto newObject = m_ActiveScene->CreateGameObject("AudioSource (" + std::to_string(CountGameObjects("AudioSource")) + ")");
										auto & temp = newObject.AddComponent<AudioSourceComponent>(soundFile->FilePath);
										temp.SetStartLoad(true);
									}
								}
							}
							
							ImGui::EndMenu();
						}
						
						ImGui::EndMenu();
					}
				}

				if(gameViewOpen && m_ActiveScene != nullptr)
				{
					if (ImGui::BeginMenu("Game View"))
					{
						if(ImGui::BeginMenu("Resolution"))
						{
							if (ImGui::MenuItem("640 x 480 (480p)"))
							{
								FramebufferSpecification spec{ 640, 480 };
								m_EditorGameFramebuffer->Rebuild(spec);
								auto& ec = m_ActiveScene->GetSceneCamera().GetComponent<CameraComponent>();
								ec.Camera.SetViewportSize(spec.Width, spec.Height);
							}
							if (ImGui::MenuItem("1280 x 720 (720p)"))
							{
								FramebufferSpecification spec{ 1280, 720 };
								m_EditorGameFramebuffer->Rebuild(spec);
								auto& ec = m_ActiveScene->GetSceneCamera().GetComponent<CameraComponent>();
								ec.Camera.SetViewportSize(spec.Width, spec.Height);
							}
							if (ImGui::MenuItem("1920 x 1080 (1080p)"))
							{
								FramebufferSpecification spec{ 1920, 1080 };
								m_EditorGameFramebuffer->Rebuild(spec);
								auto& ec = m_ActiveScene->GetSceneCamera().GetComponent<CameraComponent>();
								ec.Camera.SetViewportSize(spec.Width, spec.Height);
							}
							if (ImGui::MenuItem("2560 x 1080 (UW 1080p)"))
							{
								FramebufferSpecification spec{ 2560, 1080 };
								m_EditorGameFramebuffer->Rebuild(spec);
								auto& ec = m_ActiveScene->GetSceneCamera().GetComponent<CameraComponent>();
								ec.Camera.SetViewportSize(spec.Width, spec.Height);

							}
							if (ImGui::MenuItem("2560 x 1440 (1440p)"))
							{
								FramebufferSpecification spec{ 2560, 1440 };
								m_EditorGameFramebuffer->Rebuild(spec);
								auto& ec = m_ActiveScene->GetSceneCamera().GetComponent<CameraComponent>();
								ec.Camera.SetViewportSize(spec.Width, spec.Height);
							}
							if (ImGui::MenuItem("3840 x 2160 (4K)"))
							{
								FramebufferSpecification spec{ 3840, 2160 };
								m_EditorGameFramebuffer->Rebuild(spec);
								auto& ec = m_ActiveScene->GetSceneCamera().GetComponent<CameraComponent>();
								ec.Camera.SetViewportSize(spec.Width, spec.Height);
							}
							ImGui::EndMenu();
						}
						ImGui::EndMenu();
					}
				}

				if (ImGui::BeginMenu("Help"))
				{
					if (ImGui::MenuItem("Key Bindings"))
					{
						helpOpen = true;

					}
					ImGui::EndMenu();
				}

				ImGui::EndMainMenuBar();
			}

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 2));
		ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(0, 0));
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.305f, 0.31f, 0.5f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.15f, 0.1505f, 0.151f, 0.5f));

		
		{
			ImGui::Begin("##tool_bar", NULL, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
			float size = ImGui::GetWindowHeight() - 4.0f;
			ImGui::SameLine((ImGui::GetWindowContentRegionMax().x / 2.0f) - (1.5f * (ImGui::GetFontSize() + ImGui::GetStyle().ItemSpacing.x)) - (size / 2.0f));
			Ref<Texture2D> buttonTex = m_State == EditorState::Play ? m_StopButtonTex : m_PlayButtonTex;
			if (ImGui::ImageButton((void*)(intptr_t)buttonTex->GetRendererID(), ImVec2(size, size), ImVec2(0, 0), ImVec2(1, 1), 0))
			{
				// if in play mode and the button is pressed, change to edit mode or play mode if currently in edit mode
				m_State = m_State == EditorState::Play ? EditorState::Edit : EditorState::Play;
			}

			ImGui::SameLine();
			if(ImGui::ImageButton((ImTextureID)(size_t)m_PauseButtonTex->GetRendererID(), {size, size}, {0,0}, {1,1}, 0))
			{
				m_State = EditorState::Pause;
			}
			
			

			ImGui::PopStyleColor(3);
			ImGui::PopStyleVar(2);
			ImGui::End();
		}
		

			if (helpOpen)
			{
				ImGui::OpenPopup("Key Bindings");
				if (ImGui::BeginPopup("Key Bindings"))
				{
					ImGui::Text("Editor Camera");
					ImGui::BulletText("Movement: Shift + Arrow Keys");
					ImGui::BulletText("View: Shift + Mouse Scroll button");

					ImGui::Separator();

					if (ImGui::Button("Close"))
					{
						helpOpen = false;
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndPopup();
				}

				//put other help popups here
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
				ImGui::Separator();
				ImGui::Text("Debug");
				if(ImGui::Button("Toggle Collider Render"))
				{
					Physics::PhysicsEngine::ToggleColliderRendering();
				}
				ImGui::End();
			}

			if(gameViewOpen)
			{
				ImGui::Begin("Game View", &gameViewOpen);
				if(ImGui::IsWindowFocused()) m_FocusedWindow = FocusedWindow::GameView;
				auto size = ImGui::GetContentRegionAvail();
				uint32_t id = 0;
				FramebufferSpecification spec;
				if(m_EditorGameFramebuffer == nullptr)
				{
					id = Renderer::GetMissingTexture()->GetRendererID();
					spec.Width = (uint32_t)size.x;
					spec.Height = (uint32_t)size.y * (uint32_t)(1280.0f / 720.0f);
				}
				else
				{
					id = m_EditorGameFramebuffer->GetColorAttachment();
					spec = m_EditorGameFramebuffer->GetSpecification();
					
				}
				float imageHeight = Math::Remap((float)spec.Height, 0.0f, (float)spec.Height, 0.0f, (float)size.y);
				glm::vec2 imageSize  = {size.x, imageHeight};
				auto window = glm::vec2(ImGui::GetWindowWidth(), ImGui::GetWindowHeight());

				auto s = (window - imageSize) * 0.5f;
				ImGui::SetCursorPos({s.x, s.y});
				ImGui::Image((void*)(intptr_t)id, {imageSize.x, imageSize.y}, {0,0}, {-1, -1});
				
				ImGui::End();
				
			}
			
			//Scene View Window 
			if (sceneViewOpen)
			{

				ImGui::Begin("Scene View", &sceneViewOpen);
				if (ImGui::IsWindowFocused()) m_FocusedWindow = FocusedWindow::SceneView;
				uint32_t id = 0;
				ImVec2 size = ImGui::GetContentRegionAvail();
				

				if(m_EditorCamera && m_State != EditorState::LoadingScene)
				{
 					if(!Math::CompareImVec2(ImGui::GetWindowSize(), m_SceneViewSize))
					{
 						if(!Input::IsMouseButtonPressed(Mouse::ButtonLeft))
 						{
 							m_SceneViewSize = ImGui::GetWindowSize();
 							auto& cam = m_EditorCamera.GetComponent<EditorCameraComponent>();
 							cam.EditorCamera.SetProjectionMatrix(glm::perspectiveFov(glm::radians(45.0f), size.x, size.y, 0.1f, 1000.0f));
 							cam.EditorCamera.SetViewportSize((uint32_t)size.x, (uint32_t)size.y);
 							if(m_EditorSceneFramebuffer == nullptr)
 								id = Renderer::GetMissingTexture()->GetRendererID();
 							else
 							{
 								FramebufferSpecification spec = {(uint32_t)size.x, (uint32_t)size.y};
 								m_EditorSceneFramebuffer->Rebuild(spec);
 								id = m_EditorSceneFramebuffer->GetColorAttachment();
 							}
 						}
					}
					else
					{
						id = m_EditorSceneFramebuffer->GetColorAttachment();
					}
					
				}

				ImGui::Image((void*)(intptr_t)id, size, {0, 0}, {1, -1});

				if(m_SceneViewActive)
				{
					auto viewportStart = ImGui::GetItemRectMin();

					ImGui::SetNextWindowPos(ImVec2(viewportStart.x + 10, viewportStart.y + 5));
					ImGui::SetNextWindowSize(ImVec2(128 * 2, 38));
					ImGui::SetNextWindowBgAlpha(0.75f);
					ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 7.0f);
					ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(6, 4));
					ImGui::Begin("##viewport_tools", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking);
					const ImVec4 c_SelectedGizmoButtonColor = ImVec4(0.925490196f, 0.619607843f, 0.141176471f, 1.0f);
					const ImVec4 c_UnselectedGizmoButtonColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

			
					ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
					ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0, 0, 0, 0));
					ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0, 0, 0, 0));

					ImVec2 iconSize = { 24,24 };
					if (ImGui::ImageButton((void*)(intptr_t)m_SelectToolTex->GetRendererID(), iconSize, ImVec2(0, 0), ImVec2(1, 1), -1, ImVec4(0, 0, 0, 0), m_GizmoType == -1 ? c_SelectedGizmoButtonColor : c_UnselectedGizmoButtonColor))
						m_GizmoType = -1;
					ImGui::SameLine();
					if (ImGui::ImageButton((void*)(intptr_t)m_MoveToolTex->GetRendererID(), iconSize, ImVec2(0, 0), ImVec2(1, 1), -1, ImVec4(0, 0, 0, 0), m_GizmoType == ImGuizmo::OPERATION::TRANSLATE ? c_SelectedGizmoButtonColor : c_UnselectedGizmoButtonColor))
						m_GizmoType = ImGuizmo::OPERATION::TRANSLATE;
					ImGui::SameLine();
					if (ImGui::ImageButton((void*)(intptr_t)m_RotateToolTex->GetRendererID(), iconSize, ImVec2(0, 0), ImVec2(1, 1), -1, ImVec4(0, 0, 0, 0), m_GizmoType == ImGuizmo::OPERATION::ROTATE ? c_SelectedGizmoButtonColor : c_UnselectedGizmoButtonColor))
						m_GizmoType = ImGuizmo::OPERATION::ROTATE;
					ImGui::SameLine();
					if (ImGui::ImageButton((void*)(intptr_t)m_ScaleToolTex->GetRendererID(), iconSize, ImVec2(0, 0), ImVec2(1, 1), -1, ImVec4(0, 0, 0, 0), m_GizmoType == ImGuizmo::OPERATION::SCALE ? c_SelectedGizmoButtonColor : c_UnselectedGizmoButtonColor))
						m_GizmoType = ImGuizmo::OPERATION::SCALE;
					ImGui::SameLine();

					//Need to add some sort of style to it
					if(!m_Snap)
						if(ImGui::Button("Snap"))
							m_Snap = !m_Snap;
			
					ImGui::PopStyleColor(3);

					ImGui::End();
					ImGui::PopStyleVar(2);
				}
				

				
				if (m_GizmoType != -1 && m_SelectedGameObject && m_ActiveScene && m_State != EditorState::LoadingScene)
				{
					m_Snap = Input::IsKeyPressed(Key::LeftControl);
					float rw = (float)ImGui::GetWindowWidth();
					float rh = (float)ImGui::GetWindowHeight();
					ImGuizmo::SetOrthographic(false);
					ImGuizmo::SetDrawlist();
					ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, rw, rh);
					auto& e_Camera = m_EditorCamera.GetComponent<EditorCameraComponent>();
					glm::mat4 c_Proj = e_Camera.EditorCamera.GetProjectionMatrix();
					glm::mat4 c_View = e_Camera.EditorCamera.GetViewMatrix();
					auto& e_Transform = m_SelectedGameObject->Transform();
					glm::mat4 c_Transform = e_Transform.GetTransform();
					auto snap = GetSnapValue();
					float snapValues[3] = {snap, snap, snap};
					ImGuizmo::Manipulate(glm::value_ptr(e_Camera.EditorCamera.GetViewMatrix()),
						glm::value_ptr(e_Camera.EditorCamera.GetProjectionMatrix()),
						(ImGuizmo::OPERATION)m_GizmoType,
						ImGuizmo::LOCAL,
						glm::value_ptr(c_Transform),
						nullptr,
						m_Snap ? snapValues : nullptr);
					
					if (ImGuizmo::IsUsing())
					{
						glm::vec3 position, rotation, scale;
						Math::DecomposeTransform(c_Transform, position, rotation, scale);
							glm::vec3 delta = rotation - e_Transform.Rotation;
							e_Transform.Position = position;
							e_Transform.Rotation += delta;
							e_Transform.Scale = scale;
						
					}
				}
				ImGui::End();
			}

			

			if (hierarchyOpen)
			{
				ImGui::Begin("Hierarchy", &hierarchyOpen);
				if (ImGui::IsWindowFocused()) m_FocusedWindow = FocusedWindow::Hierarchy;


				ImGui::Separator();
				if(m_ActiveScene != nullptr && m_State != EditorState::LoadingScene)
				{
					auto size = ImGui::GetWindowSize();
					auto objects = m_ActiveScene->GetGameObjectsInScene();
					for (auto& go : objects)
					{
						auto& g = go.second;
						std::string name = "GameObject";
						if (g.HasComponent<TagComponent>()) name = g.GetComponent<TagComponent>().Tag;

						if (m_SelectedGameObject != nullptr && m_SelectedGameObject->GetTag() == name)
						{
							ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.0f, 0.3f, 1.0f, 1.0f });
							ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.0f, 0.5f, 1.0f, 1.0f });
						}
						else
						{
							ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.38f, 0.38f, 0.38f, 1.0f });
							ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.63f, 0.63f, 0.63f, 1.0f });
						}

						if (ImGui::Button(name.c_str(), {size.x, 0}))
						{
							m_HasObjectSelected = true;
							m_SelectedGameObject = m_ActiveScene->GetRefGameObject(g.GetUUID());
						}

						ImGui::PopStyleColor(2);
					}
				}

				ImGui::End();
			}

			if (propertiesOpen)
			{
				ImGui::Begin("Properties", &propertiesOpen);
				if (ImGui::IsWindowFocused()) m_FocusedWindow = FocusedWindow::Properties;

				if (m_HasObjectSelected)
				{
					// TODO: Properties rendering
					//Create a UI class that takes in the selected gameobject
					//That class will check for every type of component the engine supports
					// like if(object->HasComponent<MeshComponent>()
					// Then use a set function to each part of the components property panel
					// like DrawVec3Control()
					if(m_State != EditorState::LoadingScene) EditorUI::DrawComponentProperties(*m_SelectedGameObject, true);

				}
				else
				{
					if(m_ActiveScene != nullptr && m_State != EditorState::LoadingScene)
					{
						EditorUI::DrawComponentProperties(m_EditorCamera, true);
					}
				}

				ImGui::End();
			}




			//*************************************************************//
			// End the Docking space for the editor, DONT REMOVE THIS
			// All dockable windows must be defined above
			// This End() is ending the ImGui docking space and anything below it
			// cant be docked
			ImGui::End();

			if(m_FocusedWindow != FocusedWindow::SceneView)
			{
				m_SceneViewActive = false;
			}
			else
			{
				m_SceneViewActive = true;
			}
		}

		void EditorLayer::OnEvent(Event& event)
		{
			
			auto& e = (tnah::KeyPressedEvent&)event;
			if (e.GetEventType() == EventType::KeyPressed)
			{
				auto k = (KeyPressedEvent&)e;

				//Toggle Wireframe on or off
				if (k.GetKeyCode() == tnah::Key::D2)
				{
					m_Wireframe = !m_Wireframe;
					RenderCommand::SetWireframe(m_Wireframe);
				}

				//Toggle Fullscreen
				if (k.GetKeyCode() == tnah::Key::D3)
				{
					m_Fullscreen = !m_Fullscreen;
					Application::Get().GetWindow().ToggleFullScreen(m_Fullscreen);
				}

				//Toggle VSync
				if (k.GetKeyCode() == tnah::Key::D4)
				{
					m_VSync = !m_VSync;
					Application::Get().GetWindow().SetVSync(m_VSync);
				}
			}
			
			
		}

		void EditorLayer::CloseScene(Ref<Scene> scene)
		{
			m_EditorGameFramebuffer = nullptr;
			m_EditorSceneFramebuffer = nullptr;

			m_SelectedGameObject = nullptr;
			 TNAH_CORE_ASSERT(m_ActiveScene->GetRefCount() == 1, "Scene cant be destroyed! Something is still holding a reference!");
			m_ActiveScene = nullptr;
		}

		EditorLayer::~EditorLayer()
		{
		}

		void EditorLayer::OnAttach()
		{
			m_ActiveScene = Ref<Scene>::Create(true);
			if(m_ActiveScene != nullptr)
			{
			
				m_EditorSceneFramebuffer = m_ActiveScene->GetEditorSceneFramebuffer();
				m_EditorGameFramebuffer = m_ActiveScene->GetEditorGameFramebuffer();
				m_EditorCamera = m_ActiveScene->GetEditorCamera();
				
				m_SelectToolTex = (Texture2D::Create("assets/Editor/icons/SelectTool.png"));
				m_MoveToolTex = (Texture2D::Create("assets/Editor/icons/MoveTool.png"));
				m_RotateToolTex = (Texture2D::Create("assets/Editor/icons/RotateTool.png"));
				m_ScaleToolTex = (Texture2D::Create("assets/Editor/icons/ScaleTool.png"));

				m_PlayButtonTex = (Texture2D::Create("assets/Editor/icons/PlayButton.png"));
				m_PauseButtonTex = (Texture2D::Create("assets/Editor/icons/PauseButton.png"));
				m_StopButtonTex = (Texture2D::Create("assets/Editor/icons/StopButton.png"));
				
				m_SelectedGameObject = nullptr;
			}
		}
	
		float EditorLayer::GetSnapValue()
		{
			switch (m_GizmoType)
			{
			case  ImGuizmo::OPERATION::TRANSLATE: return 0.5f;
			case  ImGuizmo::OPERATION::ROTATE: return 45.0f;
			case  ImGuizmo::OPERATION::SCALE: return 0.5f;
			default: return 0.5f;
			}
			return 0.0f;
		}


		void EditorLayer::OnDetach()
		{
		}

		int EditorLayer::CountGameObjects(std::string name)
		{
			int num = 1;
			auto objects = m_ActiveScene->GetGameObjectsInScene();
			for (auto& go : objects)
			{
				auto& g = go.second;
				std::string object_name = "GameObject";
				if (g.HasComponent<TagComponent>()) object_name = g.GetComponent<TagComponent>().Tag;
				if (object_name.find(name) != std::string::npos)
				{
					num++;
				}
			}
			return num;
		}


}
