#include "EndScreenGUI.h"

EndScreenGUI::EndScreenGUI(std::string scriptPath)
{
	lua_State* L = LuaManager::getInstance().getLuaState();

	if (!luaL_dofile(L, scriptPath.c_str()))
	{
		luabridge::LuaRef i = luabridge::getGlobal(L, "imageLocation");

		if (i .isString()) endscreenImage = i.cast<std::string>();

	}
	else
	{
		endscreenImage = "./res/images/exitScreen.png";
	}


	bool ret = LoadTextureFromFile(endscreenImage, &my_image_texture, &my_image_width, &my_image_height);
	IM_ASSERT(ret);
}

void EndScreenGUI::Draw()
{
	bool open = false;
	bool* open_ptr = &open;

	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoBackground;
	window_flags |= ImGuiWindowFlags_NoTitleBar;
	


	std::string windowName = "EndScreen";
	//Set window size and position before creating the window context from imgui
	ImVec2 size = ImGui::GetIO().DisplaySize;
	ImGui::SetNextWindowSize(size);
	ImGui::SetNextWindowPos(ImVec2(0, 0), true);
	ImGui::Begin(windowName.c_str(), open_ptr, window_flags); //Create the window
	
	ImGui::Image((void*)(intptr_t)my_image_texture, size);

	ImGui::End();
}


// Simple helper function to load an image into a OpenGL texture with common settings
bool EndScreenGUI::LoadTextureFromFile(std::string filename, GLuint* out_texture, int* out_width, int* out_height)
{
	if (filename.find(".png") != std::string::npos) // if the image is a png, flip 
	{
		stbi_set_flip_vertically_on_load(true);
	}

	// Load from file
	int image_width = 0;
	int image_height = 0;
	unsigned char* image_data = stbi_load(filename.c_str() , &image_width, &image_height, NULL, 4);
	if (image_data == NULL)
		return false;

	// Create a OpenGL texture identifier
	GLuint image_texture;
	glGenTextures(1, &image_texture);
	glBindTexture(GL_TEXTURE_2D, image_texture);

	// Setup filtering parameters for display
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

	// Upload pixels into texture
	#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
	#endif
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
	stbi_image_free(image_data);

	*out_texture = image_texture;
	*out_width = image_width;
	*out_height = image_height;

	return true;
}