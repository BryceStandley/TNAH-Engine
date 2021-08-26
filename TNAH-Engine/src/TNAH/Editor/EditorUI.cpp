#include "tnahpch.h"
#include "EditorUI.h"
#include "TNAH/Scene/Components/Components.h"

#include <imgui.h>
#include "imgui_internal.h"
#include "TNAH/Scene/Components/Components.h"
#include "TNAH/Core/FileManager.h"

namespace tnah {
    void EditorUI::DrawComponentProperties(GameObject* object)
    {

        if(object->HasComponent<TagComponent>())
        {
        	auto& tag = object->GetComponent<TagComponent>();
			DrawTextControl("Name", tag.Tag, "GameObject");
        	ImGui::Separator();
        }
    	
       
        if(object->HasComponent<TransformComponent>())
        {
        	ImGui::Text("Transform");
            auto& t = object->GetComponent<TransformComponent>();
            DrawVec3Control("Position", t.Position);
            DrawVec3Control("Rotation", t.Rotation);
            DrawVec3Control("Scale", t.Scale, false, 1);
        	ImGui::Separator();
        }

    	if(object->HasComponent<CameraComponent>())
    	{
    		ImGui::Text("Camera");
    		auto& c = object->GetComponent<CameraComponent>();
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
    			auto fov = glm::degrees(c.Camera.m_PerspectiveFOV);
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
    		
    		if(DrawRemoveComponentButton())
    		{
    			object->RemoveComponent<CameraComponent>();
    		}
    		
    		ImGui::Separator();
    	}
    	

    	if(object->HasComponent<EditorCameraComponent>())
    	{
    		ImGui::Text("Editor Camera");
    		auto& c = object->GetComponent<EditorCameraComponent>();
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
    	
		if(object->HasComponent<TerrainComponent>())
		{
			auto& t = object->GetComponent<TerrainComponent>().SceneTerrain;
			ImGui::Text("Terrain");
			DrawVec2Control("Size", t->m_Size, true);
			ImGui::BulletText("Maybe have more options here to set the terrain textures?");

			if(DrawRemoveComponentButton())
			{
				object->RemoveComponent<TerrainComponent>();
			}
			
			ImGui::Separator();
		}
    	
    	if(object->HasComponent<MeshComponent>())
    	{
    		auto m = object->GetComponent<MeshComponent>().Model;
			ImGui::Text("Mesh");
    		DrawTextControl("Model File", m->m_FilePath);
    		ImGui::Separator();
    		ImGui::Text("Sub Meshes");
    		int count = 0;
    		for(auto& mesh : m->m_Meshes)
    		{
    			std::string label = "SubMesh " + std::to_string(count);
    			if(ImGui::CollapsingHeader(label.c_str()))
    			{
    				DrawMaterialProperties(mesh.m_Material);
    			}
    			count++;
    		}
    		
    		if(DrawRemoveComponentButton())
    		{
    			object->RemoveComponent<MeshComponent>();
    		}
    		
    		ImGui::Separator();
    	}

    	if(object->HasComponent<LightComponent>())
    	{
    		auto& l = object->GetComponent<LightComponent>().Light;
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
    			if(DrawRemoveComponentButton())
    			{
    				object->RemoveComponent<LightComponent>();
    			}
    		}
    	}

    	if(object->HasComponent<AudioListener>())
    	{
    		auto& listener = object->GetComponent<AudioListener>();
    		ImGui::Text("Audio Listener");
    		
    		//ImGui::RadioButton("Active Listening: ", listener.m_ActiveListing);
    		
			ImGui::Checkbox("Active listener", &listener.m_ActiveListing);

    		if(DrawRemoveComponentButton())
    		{
    			object->RemoveComponent<AudioListener>();
    		}
			
    		ImGui::Separator();
    	}

    	if(object->HasComponent<AudioSource3D>())
    	{
    		auto& source = object->GetComponent<AudioSource3D>();
    		ImGui::Text("Audio Source 3D");
    		
    		DrawTextControl("Model File", source.m_File.RelativeDirectory);
    		
    		DrawFloatControl("Volume", source.m_Volume, 0, 1);
    		DrawFloatControl("Minimum Reach Distance", source.m_MinDistance, 0, 100);

    		if(DrawRemoveComponentButton())
    		{
    			object->RemoveComponent<AudioSource3D>();
    		}
			
    		ImGui::Separator();
    	}
		
    	
    	//Only add components to scene objects, the editor camera cant have components added to them
    	if(!object->HasComponent<EditorCameraComponent>())
    	{
    		const char* items[] = { "Camera", "Terrain", "Mesh",  "Light", "AudioListener", "AudioSource3D"};
    		static int item_current_idx = 0;
    		const char* combo_preview_value = items[item_current_idx];
    		if (ImGui::BeginCombo("Components", combo_preview_value))
    		{
    			for (int n = 0; n < IM_ARRAYSIZE(items); n++)
    			{
    				const bool is_selected = (item_current_idx == n);
    				if (ImGui::Selectable(items[n], is_selected))
    					item_current_idx = n;
    				if (is_selected)
    					ImGui::SetItemDefaultFocus();
    			}
    			ImGui::EndCombo();
    		}
    		
    		if (ImGui::Button("Add Component"))
    		{
    			if (!object->HasComponent<CameraComponent>() && items[item_current_idx] == "Camera")
    			{
    				object->AddComponent<CameraComponent>();
    			}

    			if (!object->HasComponent<EditorCameraComponent>() && items[item_current_idx] == "EditorCamera")
    			{
    				object->AddComponent<EditorCameraComponent>();
    			}

    			if (!object->HasComponent<TerrainComponent>() && items[item_current_idx] == "Terrain")
    			{
    				//Add windows prompt to find heightmap
    				object->AddComponent<TerrainComponent>("assets/heightmaps/1k.tga");
    			}

    			if (!object->HasComponent<MeshComponent>() && items[item_current_idx] == "Mesh")
    			{
    				//Add windows prompt to find mesh
    				object->AddComponent<MeshComponent>("assets/Editor/meshes/cube_texture.fbx");
    			}

    			if (!object->HasComponent<LightComponent>() && items[item_current_idx] == "Light")
    			{
    				object->AddComponent<LightComponent>();
    			}

    			if (!object->HasComponent<AudioListener>() && items[item_current_idx] == "AudioListener")
    			{
    				object->AddComponent<AudioListener>();
    			}

    			if (!object->HasComponent<AudioSource3D>() && items[item_current_idx] == "AudioSource3D")
    			{
    				Resource file = {"file.wav"};
    				object->AddComponent<AudioSource3D>(file, 10.0f, 1.0f, false);
    				/*if (!FileManager::OpenScene())
    				{
    					auto sceneFile = FileManager::GetActiveFile();
    					if (sceneFile->FileOpenError == FileError::PathInvalid)
    					{
    						TNAH_WARN("The path or file was invalid!");
    					}
    					else
    					{
    						object->AddComponent<AudioSource3D>(sceneFile->FileName);
    					}
    				}*/
    			}
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

	bool EditorUI::DrawMaterialProperties(Ref<Material> material)
    {
    	bool singleFile = false;
    	if(std::strcmp(material->m_Shader->m_FilePaths.second.c_str(), "") == 0) singleFile = true;
    	ImGui::Text("Material");
    	ImGui::Separator();
    	ImGui::Text("Shader");
		DrawTextControl("Name", material->m_Shader->m_ShaderName, "", true);
    	if(singleFile)
    		DrawTextControl("Source", material->m_Shader->m_FilePaths.first, "", true);
    	else
    	{
    		DrawTextControl("Vertex Source", material->m_Shader->m_FilePaths.first, "", true);
    		DrawTextControl("Fragment Source", material->m_Shader->m_FilePaths.second, "", true);
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
    		if(ImGui::CollapsingHeader(t->m_Name.c_str()))
    		{
    			glm::vec2 s = {t->m_Width, t->m_Height};
    			DrawTextControl("Path", t->m_Path, "", true);
    			DrawVec2Control("Size", s, true);
    			ImGui::Separator();
    			if(ImGui::CollapsingHeader("Preview"))
    			{
    				ImGui::Image((void*)t->m_RendererID, ImVec2(size, size));
    			}	
    		}
    	}

    	ImGui::Text("Maybe Add a 3D Material preview on a sphere for PBR materials?");
    	return true;
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
	bool EditorUI::DrawTextControl(const std::string& label, std::string& text, const std::string& resetText, bool readOnly)
    {
    	bool modified = false;

    	ImGui::Text(label.c_str());
    	ImGui::NextColumn();
    	ImGui::PushItemWidth(-1);
		char buffer[256];
    	strcpy_s<256>(buffer, text.c_str());


    	s_IDBuffer[0] = '#';
    	s_IDBuffer[1] = '#';
    	memset(s_IDBuffer + 2, 0, 14);
    	sprintf_s(s_IDBuffer + 2, 14, "%o", s_Counter++);
    	if (!readOnly)
    	{
    		if (ImGui::InputText(s_IDBuffer, buffer, 256))
    		{
    			text = buffer;
    			modified = true;
    		}
    	}
    	else
    	{
    		ImGui::InputText(s_IDBuffer, buffer, 256, ImGuiInputTextFlags_ReadOnly);
    	}

    	ImGui::PushItemWidth(ImGui::GetWindowWidth());
    	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });
    	float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
    	ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

    	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
    	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
    	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
    	
    	if(!readOnly && ImGui::Button("Reset"))
    	{
    		text = resetText;
    		modified = true;
    	}

    	ImGui::PopStyleColor(3);
    	ImGui::PopItemWidth();
    	ImGui::PopStyleVar();

    	return modified;
    }

	bool EditorUI::DrawRemoveComponentButton()
	{
		bool pressed = false;
		ImGui::PushItemWidth(ImGui::GetWindowWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });
		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
    	
		if(ImGui::Button("Remove Component"))
		{
			pressed = true;
		}

		ImGui::PopStyleColor(3);
		ImGui::PopItemWidth();
		ImGui::PopStyleVar();

		return pressed;
	}

}
