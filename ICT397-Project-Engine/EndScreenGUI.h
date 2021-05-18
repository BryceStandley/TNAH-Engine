#pragma once
#include <glad/glad.h>
#include "GUI.h"


class EndScreenGUI : public GUI
{
public:
	explicit EndScreenGUI(std::string scriptPath);

	void Draw() override;

	bool LoadTextureFromFile(std::string filename, GLuint* out_texture, int* out_width, int* out_height);

private:
	std::string endscreenImage = "./res/images/exitScreen.png";
	int my_image_width = 0;
	int my_image_height = 0;
	GLuint my_image_texture = 0;


};

