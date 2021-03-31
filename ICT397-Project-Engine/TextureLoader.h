#pragma once
#include <vector>
#include <string>
#include <glad/glad.h>
#include "stb_image.h"
#include <iostream>
#include <vector>

struct Texture
{
	std::string type;
	std::string path;
	unsigned int id = 0;
};

class TextureLoader
{
public:
	//TextureLoader();
	//~TextureLoader();
	std::vector<Texture>loadMaterialTextures(const char* str, std::string type = "texture_normal");
	unsigned int loadTexture(std::string path);
	std::vector<Texture> getTextureList() const { return textures_loaded; }

private:
	std::vector<Texture> textures_loaded;
	std::string dir = "";
};

