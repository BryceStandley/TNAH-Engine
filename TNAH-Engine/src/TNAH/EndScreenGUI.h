#pragma once
#include <glad/glad.h>
#include "GUI.h"

/**
 * @brief End Screen GUI information
 * @file EndScreenGUI.h
 * @author Bryce Standley
 * @date MAY 2021
 */
class TNAH_API EndScreenGUI : public GUI
{
public:
	/**
	 * @brief Endscreen constructor
	 * @param scriptPath
	 */
	explicit EndScreenGUI(std::string scriptPath);

	/**
	 * @brief Draw override of the base GUI draw
	 */
	void Draw() override;

	/**
	 * @brief Small texture loader for ImGui
	 * @param filename
	 * @param out_texture
	 * @param out_width
	 * @param out_height
	 * @return
	 */
	bool LoadTextureFromFile(std::string filename, GLuint* out_texture, int* out_width, int* out_height);

private:
	std::string endscreenImage = "./res/images/exitScreen.png";
	int my_image_width = 0;
	int my_image_height = 0;
	GLuint my_image_texture = 0;


};

