﻿#include "tnahpch.h"
#include "EditorUI.h"

#include <imgui.h>
#include "imgui_internal.h"
#include "TNAH/Scene/Components/EditorCamera.h"

namespace tnah {

    void EditorUI::DrawComponentProperties(GameObject* object)
    {
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
    		auto& c = object->GetComponent<CameraComponent>().Camera;
			static int selectedType = 1;
    		static const char* CameraTypes[]
    		{
    			"Orthographic", "Perspective"	
    		};
    		bool modified = false;
    		ImGui::Combo("##T", &selectedType, CameraTypes, IM_ARRAYSIZE(CameraTypes));
    		if(selectedType == 0)
    		{
    			//Ortho
    			if(c.GetProjectionType() == SceneCamera::ProjectionType::Perspective)
    			{
    				c.SetOrthographic(10);
    			}
    			auto s = c.m_OrthographicSize;
    			auto n = c.m_OrthographicNear;
    			auto f = c.m_OrthographicFar;
    			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.9f, 0.2f, 0.2f, 1.0f));
    			ImGui::Text("Orthographic Cameras currently not supported");
    			ImGui::PopStyleColor();
    			modified |= DrawFloatControl("Size", s, 0, 50);
    			modified |= DrawFloatControl("Near Plane", n, -10, 10);
    			modified |= DrawFloatControl("Far Plane", f, -10, 10);

    			if(modified)
    			{
    				c.SetOrthographicSize(s);
    				c.SetOrthographicNearClip(n);
    				c.SetOrthographicNearClip(f);
    			}
    		}
    		else
    		{
    			if(c.GetProjectionType() == SceneCamera::ProjectionType::Orthographic)
    			{
    				c.SetPerspective(60);
    			}
    			auto fov = glm::degrees(c.m_PerspectiveFOV);
    			auto nearc = c.m_PerspectiveNear;
    			auto farc = c.m_PerspectiveFar;
    			
    			modified |= DrawFloatControl("Field of View", fov, 60, 120);
    			modified |=DrawFloatControl("Near Plane", nearc,  0.01f, 1.0f);
    			modified |=DrawFloatControl("Far Plane", farc,  100.0f, 10000.0f);
    			
    			if(modified)
    			{
    				c.SetPerspectiveVerticalFOV(fov);
    				c.SetPerspectiveNearClip(nearc);
    				c.SetPerspectiveFarClip(farc);
    			}
    		}
    		
    		
    		
    		ImGui::Separator();
    	}
    	

    	if(object->HasComponent<EditorCameraComponent>())
    	{
    		ImGui::Text("Editor Camera");
    		auto& c = object->GetComponent<EditorCameraComponent>().EditorCamera;
    		auto fov = glm::degrees(c.m_PerspectiveFOV);
    		auto nearc = c.m_PerspectiveNear;
    		auto farc = c.m_PerspectiveFar;
    		float w = (float)c.m_ViewportWidth;
    		float h = (float)c.m_ViewportHeight;
    		bool modified = false;
    		DrawFloatControl("Viewport Width", w, 0,0, true);
    		DrawFloatControl("Viewport Height", h, 0,0, true);
			modified |= DrawFloatControl("Field of View", fov, 60, 120);
			modified |=DrawFloatControl("Near Plane", nearc,  0.01f, 1.0f);
			modified |=DrawFloatControl("Far Plane", farc,  100.0f, 10000.0f);
			if(modified)
			{
				c.SetPerspectiveVerticalFOV(fov);
				c.SetPerspectiveNearClip(nearc);
				c.SetPerspectiveFarClip(farc);
			}
    		
    		ImGui::Separator();
    	}
    	
		if(object->HasComponent<TerrainComponent>())
		{
			auto& t = object->GetComponent<TerrainComponent>().SceneTerrain;
			ImGui::Text("Terrain");
			DrawVec2Control("Size", t->m_Size, true);
			ImGui::BulletText("Maybe have more options here to set the terrain textures?");
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
    	if(material->m_Shader->m_FilePaths.second.compare("")) singleFile = true;
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
    		ImGui::Text(text.c_str());
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
}