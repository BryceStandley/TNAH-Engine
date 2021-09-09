#include "tnahpch.h"
#include "EditorUI.h"
#include "TNAH/Scene/Components/Components.h"



#include "TNAH/Core/FileManager.h"

namespace tnah {

	static std::string search = "";
	static ComponentTypes selectedComponent = ComponentTypes::None;
	void EditorUI::DrawComponentProperties(GameObject& object)
	{
		
		if(object.HasComponent<TagComponent>())
		{
			auto& tag = object.GetComponent<TagComponent>();
			DrawTextControl("Name", tag.Tag);
			ImGui::Separator();
		}
		
	   
		if(object.HasComponent<TransformComponent>())
		{
			ImGui::Text("Transform");
			auto& t = object.GetComponent<TransformComponent>();
			DrawVec3Control("Position", t.Position);
			DrawVec3Control("Rotation", t.Rotation);
			DrawVec3Control("Scale", t.Scale, false, 1);
			ImGui::Separator();
		}

		if(object.HasComponent<CameraComponent>())
		{
			ImGui::Text("Camera");
			auto& c = object.GetComponent<CameraComponent>();
			static int selectedType = 1;
			static const char* CameraTypes[]
			{
				"Orthographic", "Perspective"	
			};

			static int selectedClear = 1;
			static const char* CameraClear[] {"Skybox", "Color"};
			bool modified = false;
			ImGui::Combo("##T", &selectedType, CameraTypes, IM_ARRAYSIZE(CameraTypes));
			ImGui::Combo("##C", &selectedClear, CameraClear, IM_ARRAYSIZE(CameraClear));
			if(selectedClear == 0)
			{
				ImGui::Text("Display some text here for setting a skybox or use default");
				
			}
			else if(selectedClear == 1 && c.ClearMode == CameraClearMode::Color)
			{
				Draw4ColorControl("Clear Color", c.ClearColor);
			}

			if(c.ClearMode == CameraClearMode::Skybox && selectedClear == 1)
			{
				if(ImGui::Button("Save"))
				{
					c.SetClearMode(CameraClearMode::Color);
				}
			}

			if(c.ClearMode == CameraClearMode::Color && selectedClear == 0)
			{
				if(ImGui::Button("Save"))
				{
					c.SetClearMode(CameraClearMode::Skybox);
				}
			}

			if(c.ClearMode == CameraClearMode::None)
			{
				if(ImGui::Button("Reset"))
				{
					c.SetClearMode(CameraClearMode::Skybox);
				}
			}

			
			if(selectedType == 0)
			{
				//Ortho
				if(c.Camera.GetProjectionType() == SceneCamera::ProjectionType::Perspective)
				{
					c.Camera.SetOrthographic(10);
				}
				auto s = c.Camera.m_OrthographicSize;
				auto n = c.Camera.m_OrthographicNear;
				auto f = c.Camera.m_OrthographicFar;
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.9f, 0.2f, 0.2f, 1.0f));
				ImGui::Text("Orthographic Cameras currently not supported");
				ImGui::PopStyleColor();
				modified |= DrawFloatControl("Size", s, 0, 50);
				modified |= DrawFloatControl("Near Plane", n, -10, 10);
				modified |= DrawFloatControl("Far Plane", f, -10, 10);

				if(modified)
				{
					c.Camera.SetOrthographicSize(s);
					c.Camera.SetOrthographicNearClip(n);
					c.Camera.SetOrthographicNearClip(f);
				}
			}
			else
			{
				if(c.Camera.GetProjectionType() == SceneCamera::ProjectionType::Orthographic)
				{
					c.Camera.SetPerspective(60);
				}
				auto fov = c.Camera.GetPerspectiveVerticalFOV();
				auto nearc = c.Camera.m_PerspectiveNear;
				auto farc = c.Camera.m_PerspectiveFar;
				
				modified |= DrawFloatControl("Field of View", fov, 60, 120);
				modified |=DrawFloatControl("Near Plane", nearc,  0.01f, 1.0f);
				modified |=DrawFloatControl("Far Plane", farc,  100.0f, 10000.0f);
				
				if(modified)
				{
					c.Camera.SetPerspectiveVerticalFOV(fov);
					c.Camera.SetPerspectiveNearClip(nearc);
					c.Camera.SetPerspectiveFarClip(farc);
				}
			}

			if(Camera::Main != &c.Camera) // only allow the camera to be removed if its not the main camera
			{
				if(DrawRemoveComponentButton("camera"))
				{
					object.RemoveComponent<CameraComponent>();
				}
			}
			
			ImGui::Separator();
		}
		

		if(object.HasComponent<EditorCameraComponent>())
		{
			ImGui::Text("Editor Camera");
			auto& c = object.GetComponent<EditorCameraComponent>();
			auto fov = glm::degrees(c.EditorCamera.m_PerspectiveFOV);
			auto nearc = c.EditorCamera.m_PerspectiveNear;
			auto farc = c.EditorCamera.m_PerspectiveFar;
			float w = (float)c.EditorCamera.m_ViewportWidth;
			float h = (float)c.EditorCamera.m_ViewportHeight;
			bool modified = false;
			static int selectedClear = 1;
			static const char* CameraClear[] {"Skybox", "Color"};
			ImGui::Combo("##C", &selectedClear, CameraClear, IM_ARRAYSIZE(CameraClear));
			if(selectedClear == 0)
			{
				ImGui::Text("Display some text here for setting a skybox or use default");
				
			}
			else if(selectedClear == 1 && c.ClearMode == CameraClearMode::Color)
			{
				Draw4ColorControl("Clear Color", c.ClearColor);
			}

			if(c.ClearMode == CameraClearMode::Skybox && selectedClear == 1)
			{
				if(ImGui::Button("Save"))
				{
					c.SetClearMode(CameraClearMode::Color);
				}
			}

			if(c.ClearMode == CameraClearMode::Color && selectedClear == 0)
			{
				if(ImGui::Button("Save"))
				{
					c.SetClearMode(CameraClearMode::Skybox);
				}
			}

			if(c.ClearMode == CameraClearMode::None)
			{
				if(ImGui::Button("Reset"))
				{
					c.SetClearMode(CameraClearMode::Skybox);
				}
			}

			DrawFloatControl("Viewport Width", w, 0,0, true);
			DrawFloatControl("Viewport Height", h, 0,0, true);
			modified |= DrawFloatControl("Field of View", fov, 60, 120);
			modified |=DrawFloatControl("Near Plane", nearc,  0.01f, 1.0f);
			modified |=DrawFloatControl("Far Plane", farc,  100.0f, 10000.0f);
			if(modified)
			{
				c.EditorCamera.SetPerspectiveVerticalFOV(fov);
				c.EditorCamera.SetPerspectiveNearClip(nearc);
				c.EditorCamera.SetPerspectiveFarClip(farc);
			}
			
			ImGui::Separator();
		}
		
		if(object.HasComponent<TerrainComponent>())
		{
			auto& t = object.GetComponent<TerrainComponent>().SceneTerrain;
			ImGui::Text("Terrain");
			DrawVec2Control("Size", t->m_Size, true);
			ImGui::BulletText("Maybe have more options here to set the terrain textures?");

			if(DrawRemoveComponentButton("terrain"))
			{
				object.RemoveComponent<TerrainComponent>();
			}
			
			ImGui::Separator();
		}
		
		if(object.HasComponent<MeshComponent>())
		{
			auto m = object.GetComponent<MeshComponent>().Model;
			ImGui::Text("Mesh");
			if(m)
			{
				DrawTextControl("Model File", m->m_FilePath, false, true);
				if(ImGui::Button("Change Mesh"))
				{
					if (FileManager::OpenMesh())
					{
						auto file = FileManager::GetActiveFile();
						if (file->FileOpenError == FileError::PathInvalid)
						{
							TNAH_WARN("The path or file was invalid!");
						}
						else
						{
							object.GetComponent<MeshComponent>().LoadMesh(file->FilePath);
						}
					}
				}
				ImGui::Separator();
				ImGui::Text("Sub Meshes");
				int count = 0;
				for(auto& mesh : m->m_Meshes)
				{
					std::string label = "SubMesh " + std::to_string(count);
					if(ImGui::CollapsingHeader(label.c_str()))
					{
						DrawMaterialProperties(false, mesh.m_Material);
					}
					count++;
				}
			}
			else
			{
				std::string error = "Empty";
				DrawTextControl("Model File", error, true);
				if(ImGui::Button("Add Mesh"))
				{
					if (FileManager::OpenMesh())
					{
						auto file = FileManager::GetActiveFile();
						if (file->FileOpenError == FileError::PathInvalid)
						{
							TNAH_WARN("The path or file was invalid!");
						}
						else
						{
							object.GetComponent<MeshComponent>().LoadMesh(file->FilePath);
						}
					}
				}
				ImGui::Separator();
				ImGui::Text("Sub Meshes");
				if(ImGui::CollapsingHeader("Empty"))
				{
					DrawMaterialProperties(true);
				}
			}
			
			if(DrawRemoveComponentButton("Mesh"))
			{
				object.RemoveComponent<MeshComponent>();
			}
			
			ImGui::Separator();
		}

		if(object.HasComponent<LightComponent>())
		{
			auto& l = object.GetComponent<LightComponent>().Light;
			auto name = l->GetTypeAsString() + " Light";
			ImGui::Text(name.c_str());
			if(l->GetType() == Light::LightType::Directional)
			{
				DrawVec3Control("Direction", l->GetDirection());
				DrawFloatControl("Intensity", l->GetIntensity(), 0, 10);
				Draw4ColorControl("Color", l->GetColor());
				DrawVec3Control("Ambient", l->GetAmbient());
				DrawVec3Control("Diffuse", l->GetDiffuse());
				DrawVec3Control("Specular", l->GetSpecular());
			}
			else if(l->GetType() == Light::LightType::Point)
			{
				DrawFloatControl("Intensity", l->GetIntensity(), 0, 10);
				Draw4ColorControl("Color", l->GetColor());
				DrawVec3Control("Ambient", l->GetAmbient());
				DrawVec3Control("Diffuse", l->GetDiffuse());
				DrawVec3Control("Specular", l->GetSpecular());
			}
			else if(l->GetType() == Light::LightType::Spot)
			{
				DrawFloatControl("Intensity", l->GetIntensity(), 0, 10);
				Draw4ColorControl("Color", l->GetColor());
				DrawVec3Control("Ambient", l->GetAmbient());
				DrawVec3Control("Diffuse", l->GetDiffuse());
				DrawVec3Control("Specular", l->GetSpecular());
			}
			else
			{
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.9f, 0.2f, 0.2f, 1.0f));
				ImGui::Text("ERROR: Unknown light type");
				ImGui::PopStyleColor();
			}
			if(!l->m_IsSceneLight)
			{
				if(DrawRemoveComponentButton("Light"))
				{
					object.RemoveComponent<LightComponent>();
				}
			}
		}

		if(object.HasComponent<AudioListenerComponent>())
		{
			auto& listener = object.GetComponent<AudioListenerComponent>();
			ImGui::Text("Audio Listener");
			
			//ImGui::RadioButton("Active Listening: ", listener.m_ActiveListing);
			
			ImGui::Checkbox("Active listener", &listener.m_ActiveListing);

			if(DrawRemoveComponentButton("AudioListener"))
			{
				object.RemoveComponent<AudioListenerComponent>();
			}
			
			ImGui::Separator();
		}

		if(object.HasComponent<AudioSourceComponent>())
		{
			auto& source = object.GetComponent<AudioSourceComponent>();
			ImGui::Text("Audio Source");

			if(source.GetStartLoad())
			{
				DrawTextControl("Source File", source.m_File.RelativeDirectory);
				if(ImGui::Button("Change audio file"))
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
							source.m_File = file;
							source.m_Loaded = false;
							source.SetStartLoad(true);
						}
					}
				}
				ImGui::Checkbox("3D Audio", &source.m_3D);
				ImGui::Checkbox("Loop", &source.m_Loop);

				DrawFloatControl("Volume", source.m_Volume, 0, 1);
			
				if(source.m_3D)
				{
					DrawFloatControl("Minimum Reach Distance", source.m_MinDistance, 0, 100);	
				}
			
				ImGui::Text("Testing Options");
				ImGui::Checkbox("Shoot", &source.m_Shoot);
				ImGui::Checkbox("Pause", &source.m_Paused);
				if(DrawRemoveComponentButton("AudioSource"))
				{
					object.RemoveComponent<AudioSourceComponent>();
				}	
			}
			else
			{
				if(ImGui::Button("Add audio file"))
				{
					if (FileManager::OpenAudio())
					{
						auto soundFile = FileManager::GetActiveFile();
						if (soundFile->FileOpenError == FileError::PathInvalid)
						{
							TNAH_WARN("The path or file was invalid!");
						}
						else
						{
							Resource file = {soundFile->FilePath};
							source.m_File = file;
							source.m_Loaded = false;
							source.SetStartLoad(true);
						}
					}
				}
			}
			
			
			ImGui::Separator();
		}

		if(object.HasComponent<RigidBodyComponent>())
		{
			auto & rb = object.GetComponent<RigidBodyComponent>();

			if(rb.m_BodyType == rp3d::BodyType::KINEMATIC)
			{
				ImGui::Text("Object Type: Kinematic");
				if(ImGui::Button("Change to Dynamic"))
				{
					rb.SetBodyType(rp3d::BodyType::DYNAMIC);
				}
			}
			else
			{
				ImGui::Text("Object Type: Dynamic");
				if(ImGui::Button("Change to Kinematic"))
				{
					rb.SetBodyType(rp3d::BodyType::STATIC);
					rb.SetBodyType(rp3d::BodyType::KINEMATIC);
				}
			}
			ImGui::Checkbox("Edit mode", &rb.edit);
			ImGui::Checkbox("Keyboard Controls", &rb.useEdit);
			ImGui::Separator();
			ImGui::Text("Colliders");
			bool hasCollider = false;
		
			if(object.HasComponent<BoxColliderComponent>())
			{
				auto & box = object.GetComponent<BoxColliderComponent>();
				rp3d::Vector3 s = ((rp3d::BoxShape*)(box.Components.Shape))->getHalfExtents();
				std::string text = "Actual Size: " + std::to_string(s.x) + " " + std::to_string(s.y) + " " + std::to_string(s.z);
				ImGui::Text("Box Collider");
				ImGui::Separator();
				ImGui::Text(text.c_str());
				DrawVec3Control("Size", box.Size);
				
				if(ImGui::Button("Change Size"))
				{
					((rp3d::BoxShape*)(box.Components.Shape))->setHalfExtents(Math::ToRp3dVec3(box.Size));
					box.Components.BodyCollider = rb.UpdateCollider(box.Components.BodyCollider, box.Components.Shape, rp3d::Transform::identity());
				}
				hasCollider = true;
			}

			if(!hasCollider)
				ImGui::Text("No colliders added");
		}

		ImGui::Separator();
		
		//Only add components to scene objects, the editor camera cant have components added to it
		if(!object.HasComponent<EditorCameraComponent>())
		{
			ImGui::Separator();
			ImGui::NewLine();
			auto width = ImGui::GetWindowWidth();
			static bool addComponentPressed = false;
			if(!addComponentPressed)
			{
				if (ImGui::Button("Add Component", {width, 0}))
				{
					
					addComponentPressed = true;
				}
			}
			else
			{
				//draw add component section
				
				DrawTextControl("Search", search);
				std::transform(search.begin(), search.end(), search.begin(), ::tolower);
				ImGui::NewLine();
				if(DrawAddComponent(object, search)) { addComponentPressed = false; search = ""; selectedComponent = ComponentTypes::None; }
				if(!ImGui::IsWindowFocused()) addComponentPressed = false;
			}
		}

		ImGui::Separator();
	}

	bool EditorUI::Draw4ColorControl(const std::string& label, glm::vec4& value, bool readOnly, const glm::vec4& resetValue)
	{
		bool modified = false;
		ImGui::PushID(label.c_str());
		ImGui::Text(label.c_str());
		ImGui::NextColumn();
		ImGui::PushItemWidth(-1);
		
		if(!readOnly)
		{
			if(ImGui::ColorEdit4("##C", glm::value_ptr(value)))
				modified = true;
		}
		else
		{
			ImGui::InputFloat4("##C", glm::value_ptr(value), "%.3f", ImGuiInputTextFlags_ReadOnly);
		}
		ImGui::PopItemWidth();
		ImGui::NextColumn();
		ImGui::PopID();
		
		return modified;
	}

	bool EditorUI::DrawMaterialProperties(bool empty, Ref<Material> material)
	{
		if(!empty)
		{
			bool singleFile = false;
			if(std::strcmp(material->m_Shader->m_FilePaths.second.c_str(), "") == 0) singleFile = true;
			ImGui::Text("Material");
			ImGui::Separator();
			ImGui::Text("Shader");
			DrawTextControl("Name", material->m_Shader->m_ShaderName);
			if(singleFile)
				DrawTextControl("Source", material->m_Shader->m_FilePaths.first);
			else
			{
				DrawTextControl("Vertex Source", material->m_Shader->m_FilePaths.first);
				DrawTextControl("Fragment Source", material->m_Shader->m_FilePaths.second);
			}
			ImGui::BulletText("Maybe make the shader option a file input to select a new shader file");
			ImGui::Separator();
			ImGui::Text("Properties");
			DrawFloatControl("Shininess", material->m_Properties.Shininess);
			DrawFloatControl("Metalness", material->m_Properties.Metalness);
			ImGui::Separator();
			ImGui::Text("Texture");

			auto size = ImGui::GetWindowWidth();
			size = (size /  4.0f) * 2;
		
			for(auto& t : material->m_Textures)
			{
				if(ImGui::CollapsingHeader(t->m_TextureResource.CustomName.c_str()))
				{
					glm::vec2 s = {t->m_Width, t->m_Height};
					DrawTextControl("Path", t->m_TextureResource.RelativeDirectory);
					DrawVec2Control("Size", s, true);
					ImGui::Separator();
					if(ImGui::CollapsingHeader("Preview"))
					{
						ImGui::Image((void*)(intptr_t)t->m_RendererID, ImVec2(size, size));
					}	
				}
			}

			ImGui::Text("Maybe Add a 3D Material preview on a sphere for PBR materials?");
			return true;
		}
		
		ImGui::Text("No material to display");
		return false;
		
	}

	bool EditorUI::DrawRemoveComponentButton(const std::string& id)
	{
		std::string label = "Remove Component##" + id;
		return DrawRedButton(label);
	}

	bool EditorUI::DrawResetButton(const std::string& id)
	{
		std::string label = "Reset##" + id;
		return DrawRedButton(label);
	}

	bool EditorUI::DrawFloatControl(const std::string& label, float& value, float min, float max,
	                                bool readOnly)
	{
		bool modified = false;
		ImGui::PushID(label.c_str());
		ImGui::Text(label.c_str());
		ImGui::NextColumn();
		ImGui::PushItemWidth(-1);
		if (!readOnly)
		{
			if (ImGui::SliderFloat("##V", &value, min, max))
				modified = true;
		}
		else
		{
			ImGui::InputFloat("##V", &value, 0.0F, 0.0F, "%.3f", ImGuiInputTextFlags_ReadOnly);
		}

		ImGui::PopItemWidth();
		ImGui::NextColumn();
		ImGui::PopID();

		return modified;
	}

	bool EditorUI::DrawVec4Control(const std::string& label, glm::vec4& values, bool readOnly, float resetValue,
		float columnWidth)
	{
		bool modified = false;

		const ImGuiIO& io = ImGui::GetIO();
		auto boldFont = io.Fonts->Fonts[0];

		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushFont(boldFont);
		if (!readOnly && ImGui::Button("X", buttonSize))
		{
			values.x = resetValue;
			modified = true;
		}

		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		if(!readOnly) modified |= ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
		else ImGui::Text("%.3f", values.x);
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushFont(boldFont);
		if (!readOnly && ImGui::Button("Y", buttonSize))
		{
			values.y = resetValue;
			modified = true;
		}

		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		if(!readOnly) modified |= ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
		else ImGui::Text("%.3f", values.y);
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushFont(boldFont);
		if (!readOnly && ImGui::Button("Z", buttonSize))
		{
			values.z = resetValue;
			modified = true;
		}

		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		if(!readOnly) modified |= ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
		else ImGui::Text("%.3f", values.z);
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.8f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.5f, 0.5f, 0.5f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushFont(boldFont);
		if (!readOnly && ImGui::Button("W", buttonSize))
		{
			values.w = resetValue;
			modified = true;
		}

		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		if(!readOnly) modified |= ImGui::DragFloat("##W", &values.w, 0.1f, 0.0f, 0.0f, "%.2f");
		else ImGui::Text("%.3f", values.w);
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();

		ImGui::Columns(1);

		ImGui::PopID();

		return modified;
	}

	bool EditorUI::DrawVec2Control(const std::string& label, glm::vec2& values, bool readOnly, float resetValue,
		float columnWidth)
	{
		bool modified = false;

		const ImGuiIO& io = ImGui::GetIO();
		auto boldFont = io.Fonts->Fonts[0];

		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushFont(boldFont);
		if (!readOnly && ImGui::Button("X", buttonSize))
		{
			values.x = resetValue;
			modified = true;
		}

		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		if(!readOnly) modified |= ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
		else ImGui::Text("%.3f", values.x);
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushFont(boldFont);
		if (!readOnly && ImGui::Button("Y", buttonSize))
		{
			values.y = resetValue;
			modified = true;
		}

		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		if(!readOnly) modified |= ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
		else ImGui::Text("%.3f", values.y);
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();

		ImGui::Columns(1);

		ImGui::PopID();

		return modified;
	}
	
	bool EditorUI::DrawVec3Control(const std::string& label, glm::vec3& values, bool readOnly, float resetValue, float columnWidth)
	{
		bool modified = false;

		const ImGuiIO& io = ImGui::GetIO();
		auto boldFont = io.Fonts->Fonts[0];

		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushFont(boldFont);
		if (!readOnly && ImGui::Button("X", buttonSize))
		{
			values.x = resetValue;
			modified = true;
		}

		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		if(!readOnly) modified |= ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
		else ImGui::Text("%.3f", values.x);
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushFont(boldFont);
		if (!readOnly && ImGui::Button("Y", buttonSize))
		{
			values.y = resetValue;
			modified = true;
		}

		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		if(!readOnly) modified |= ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
		else ImGui::Text("%.3f", values.y);
		
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushFont(boldFont);
		if (!readOnly && ImGui::Button("Z", buttonSize))
		{
			values.z = resetValue;
			modified = true;
		}

		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		if(!readOnly) modified |= ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
		else ImGui::Text("%.3f", values.z);
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();

		ImGui::Columns(1);

		ImGui::PopID();
		ImGui::NewLine();

		return modified;
	}

	static uint32_t s_Counter = 0;
	static char s_IDBuffer[16];
	bool EditorUI::DrawTextControl(const char* label, std::string& text, bool error, bool readOnly)
	{
		bool modified = false;
		int flags = 0;
		ImGui::Text(label);
		ImGui::NextColumn();
		ImGui::PushItemWidth(-1);

		char buffer[256];
		strcpy_s<256>(buffer, text.c_str());

		s_IDBuffer[0] = '#';
		s_IDBuffer[1] = '#';
		memset(s_IDBuffer + 2, 0, 14);
		sprintf_s(s_IDBuffer + 2, 14, "%o", s_Counter++);
		std::string name = "##";
		name += label;
		
		flags = readOnly ? ImGuiInputTextFlags_ReadOnly : 0; 
		
		if (error)
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.9f, 0.2f, 0.2f, 1.0f));
		if (ImGui::InputText(name.c_str(), buffer, 256, flags))
		{
			text = buffer;
			modified = true;
		}
		if (error)
			ImGui::PopStyleColor();
		ImGui::PopItemWidth();
		ImGui::NextColumn();

		return modified;
	}

	bool EditorUI::DrawRedButton(const std::string& label)
	{
		bool pressed = false;
		ImGui::PushItemWidth(ImGui::GetWindowWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });
		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		auto buttonSize = ImGui::GetWindowWidth();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		
		if(ImGui::Button(label.c_str(), {buttonSize, 0}))
		{
			pressed = true;
		}

		ImGui::PopStyleColor(3);
		ImGui::PopItemWidth();
		ImGui::PopStyleVar();

		return pressed;
	}

	std::list<ComponentTypes> EditorUI::GetPossibleComponentTypes(std::vector<ComponentTypes> typesHeld)
	{
		std::list allTypes =
			{
				ComponentTypes::ID, ComponentTypes::Tag, ComponentTypes::Relationship, ComponentTypes::Transform,
				ComponentTypes::Camera, ComponentTypes::EditorCamera, ComponentTypes::Editor, ComponentTypes::Skybox,
				ComponentTypes::Light, ComponentTypes::Terrain, ComponentTypes::Mesh, ComponentTypes::PlayerController,
				ComponentTypes::AudioListener, ComponentTypes::AudioSource, ComponentTypes::RigidBody, ComponentTypes::BoxCollider
			};

		std::list<ComponentTypes> allTypesNotHeld = allTypes;

		for(auto type: typesHeld)
		{
			//remove any items from the list that are held by the game object
			allTypesNotHeld.remove(type);
		}
		allTypesNotHeld.remove(ComponentTypes::EditorCamera);
		allTypesNotHeld.remove(ComponentTypes::Editor);

		return allTypesNotHeld;
		
	}

	bool EditorUI::DrawAddComponent(GameObject& object, const std::string& searchTerm)
	{
		auto componentsCanShow = GetPossibleComponentTypes(object.GetComponentList());

		bool emptySearch = searchTerm.compare("") == 0 ? true : false;
		

		if(selectedComponent == ComponentTypes::None)
		{
			if(!emptySearch)
			{
				selectedComponent = FindAndDrawComponentSearchTerm(componentsCanShow, searchTerm);
			}
			else
			{
				selectedComponent = DrawComponentList(componentsCanShow);
			}
		}

		if(selectedComponent != ComponentTypes::None)
		{
			ImGui::Text("Selected:");
			std::string text = FindStringFromComponentType(selectedComponent);
			ImGui::Text(text.c_str());
			if(DrawResetButton("AddComponent"))
			{
				selectedComponent = ComponentTypes::None;
			}
			ImGui::NewLine();
			if(selectedComponent != ComponentTypes::None)
			{
				auto width = ImGui::GetWindowWidth();
				if(ImGui::Button("Add", {width, 0}))
				{
			
					return AddComponentFromType(object, selectedComponent);
					
				}
			}
		}

		return false;
		
	}

	ComponentTypes EditorUI::FindAndDrawComponentSearchTerm(std::list<ComponentTypes> typesToSearch, const std::string& searchTerm)
	{
		auto types = FindAllComponentsContaining(typesToSearch, searchTerm);
		
		return  DrawComponentList(types);
	}

	ComponentTypes EditorUI::DrawComponentList(std::list<ComponentTypes> componentsToDisplay)
	{
		auto width = ImGui::GetWindowWidth();
		for(auto t : componentsToDisplay)
		{
			if(ImGui::Button(FindStringFromComponentType(t).c_str(), {width, 0}))
			{
				return t;
			}
		}
		return ComponentTypes::None;
	}
	

	std::list<ComponentTypes> EditorUI::FindAllComponentsContaining(std::list<ComponentTypes> componentsToSearch, const std::string& term)
	{
		std::list<ComponentTypes> foundComponents;
		
		if(IDComponent::s_SearchString.find(term) != std::string::npos && Utility::Contains<ComponentTypes>(componentsToSearch, ComponentTypes::ID))
			foundComponents.emplace_back(ComponentTypes::ID);

		if(TagComponent::s_SearchString.find(term) != std::string::npos && Utility::Contains<ComponentTypes>(componentsToSearch, ComponentTypes::Tag))
			foundComponents.emplace_back(ComponentTypes::Tag);

		if(RelationshipComponent::s_SearchString.find(term) != std::string::npos && Utility::Contains<ComponentTypes>(componentsToSearch, ComponentTypes::Relationship))
			foundComponents.emplace_back(ComponentTypes::Relationship);

		if(TransformComponent::s_SearchString.find(term) != std::string::npos && Utility::Contains<ComponentTypes>(componentsToSearch, ComponentTypes::Transform))
			foundComponents.emplace_back(ComponentTypes::Transform);

		if(CameraComponent::s_SearchString.find(term) != std::string::npos && Utility::Contains<ComponentTypes>(componentsToSearch, ComponentTypes::Camera))
			foundComponents.emplace_back(ComponentTypes::Camera);

		if(EditorCameraComponent::s_SearchString.find(term) != std::string::npos && Utility::Contains<ComponentTypes>(componentsToSearch, ComponentTypes::EditorCamera))
			foundComponents.emplace_back(ComponentTypes::EditorCamera);

		if(EditorComponent::s_SearchString.find(term) != std::string::npos && Utility::Contains<ComponentTypes>(componentsToSearch, ComponentTypes::Editor))
			foundComponents.emplace_back(ComponentTypes::Editor);

		if(SkyboxComponent::s_SearchString.find(term) != std::string::npos && Utility::Contains<ComponentTypes>(componentsToSearch, ComponentTypes::Skybox))
			foundComponents.emplace_back(ComponentTypes::Skybox);

		if(LightComponent::s_SearchString.find(term) != std::string::npos && Utility::Contains<ComponentTypes>(componentsToSearch, ComponentTypes::Light))
			foundComponents.emplace_back(ComponentTypes::Light);

		if(TerrainComponent::s_SearchString.find(term) != std::string::npos && Utility::Contains<ComponentTypes>(componentsToSearch, ComponentTypes::Terrain))
			foundComponents.emplace_back(ComponentTypes::Terrain);

		if(MeshComponent::s_SearchString.find(term) != std::string::npos && Utility::Contains<ComponentTypes>(componentsToSearch, ComponentTypes::Mesh))
			foundComponents.emplace_back(ComponentTypes::Mesh);

		if(PlayerControllerComponent::s_SearchString.find(term) != std::string::npos && Utility::Contains<ComponentTypes>(componentsToSearch, ComponentTypes::PlayerController))
			foundComponents.emplace_back(ComponentTypes::PlayerController);

		if(AudioSourceComponent::s_SearchString.find(term) != std::string::npos && Utility::Contains<ComponentTypes>(componentsToSearch, ComponentTypes::AudioSource))
			foundComponents.emplace_back(ComponentTypes::AudioSource);

		if(AudioListenerComponent::s_SearchString.find(term) != std::string::npos && Utility::Contains<ComponentTypes>(componentsToSearch, ComponentTypes::AudioListener))
			foundComponents.emplace_back(ComponentTypes::AudioListener);

		if(RigidBodyComponent::s_SearchString.find(term) != std::string::npos && Utility::Contains<ComponentTypes>(componentsToSearch, ComponentTypes::RigidBody))
			foundComponents.emplace_back(ComponentTypes::RigidBody);

		if(BoxColliderComponent::s_SearchString.find(term) != std::string::npos && Utility::Contains<ComponentTypes>(componentsToSearch, ComponentTypes::BoxCollider))
			foundComponents.emplace_back(ComponentTypes::BoxCollider);
		
		return foundComponents;
	}

	std::string EditorUI::FindStringFromComponentType(ComponentTypes type)
    {
        switch (type)
        {
        case ComponentTypes::None:
            return "No Component";
        case ComponentTypes::ID:
            return "ID Component";
        case ComponentTypes::Tag:
            return "Tag Component";
        case ComponentTypes::Relationship:
            return "Relationship Component";
        case ComponentTypes::Transform:
            return "Transform Component";
        case ComponentTypes::Camera:
            return "Camera Component";
        case ComponentTypes::EditorCamera:
            return "Editor Camera Component";
        case ComponentTypes::Editor:
            return "Editor Component";
        case ComponentTypes::Skybox:
            return "Skybox Component";
        case ComponentTypes::Light:
            return "Light Component";
        case ComponentTypes::Terrain:
            return "Terrain Component";
        case ComponentTypes::Mesh:
            return "Mesh Component";
        case ComponentTypes::PlayerController:
            return "Player Controller Component";
        case ComponentTypes::AudioSource:
            return "Audio Source Component";
        case ComponentTypes::AudioListener:
            return "Audio Listener Component";
        case ComponentTypes::RigidBody:
			return "Rigid Body Component";
        case ComponentTypes::BoxCollider:
        	return "Box Collider Component";
        default: return "";
        }
    }

	std::string EditorUI::FindComponentTypeCategory(ComponentTypes type)
	{
		switch (type)
		{
		case ComponentTypes::None:
			break;
		case ComponentTypes::ID:
			break;
		case ComponentTypes::Tag:
			break;
		case ComponentTypes::Relationship:
			break;
		case ComponentTypes::Transform:
			break;
		case ComponentTypes::Camera:
			return "Camera";
		case ComponentTypes::EditorCamera:
			break;
		case ComponentTypes::Editor:
			break;
		case ComponentTypes::Skybox:
			return "Camera";
		case ComponentTypes::Light:
			return "Light";
		case ComponentTypes::Terrain:
			return "Mesh";
		case ComponentTypes::Mesh:
			return "Mesh";
		case ComponentTypes::PlayerController:
			return "Control";
		case ComponentTypes::AudioSource:
			return "Audio";
		case ComponentTypes::AudioListener:
			return "Audio";
		default: return "";
		}
		return "";
	}


	bool EditorUI::AddComponentFromType(GameObject& object, ComponentTypes type)
    {
        switch (type)
        {
        case ComponentTypes::None:
            return false;
        case ComponentTypes::ID:
            return false;
        case ComponentTypes::Tag:
            return false;
        case ComponentTypes::Relationship:
            return false;
        case ComponentTypes::Transform:
            return false;
        case ComponentTypes::Camera:
            object.AddComponent<CameraComponent>();
            return true;
        case ComponentTypes::EditorCamera:
            return false;
        case ComponentTypes::Editor:
            return false;
        case ComponentTypes::Skybox:
            object.AddComponent<SkyboxComponent>();
            return true;
        case ComponentTypes::Light:
            object.AddComponent<LightComponent>();
            return true;
        case ComponentTypes::Terrain:
            object.AddComponent<TerrainComponent>();
            return true;
        case ComponentTypes::Mesh:
            object.AddComponent<MeshComponent>();
            return true;
        case ComponentTypes::PlayerController:
            object.AddComponent<PlayerControllerComponent>();
            return true;
        case ComponentTypes::AudioSource:
            object.AddComponent<AudioSourceComponent>();
            return true;
        case ComponentTypes::AudioListener:
            object.AddComponent<AudioListenerComponent>();
            return true;
        case ComponentTypes::RigidBody:
        	object.AddComponent<RigidBodyComponent>(object.Transform());
        	return true;
        case ComponentTypes::BoxCollider:
        	if(object.HasComponent<RigidBodyComponent>())
        	{
        		auto& rb = object.GetComponent<RigidBodyComponent>();
        		auto& b = object.AddComponent<BoxColliderComponent>();
        		b.Components.BodyCollider = rb.AddCollider(b.Components.Shape, rp3d::Transform::identity());
        		return true;
        	}
        	else
        	{
        		auto& rb = object.AddComponent<RigidBodyComponent>(object.Transform());
        		auto& b = object.AddComponent<BoxColliderComponent>();
        		b.Components.BodyCollider = rb.AddCollider(b.Components.Shape, rp3d::Transform::identity());
        		return true;
        	}
        default: return false;
        }
    }

}
