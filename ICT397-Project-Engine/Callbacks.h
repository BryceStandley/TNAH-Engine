#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include "stb_image.h"




void framebufferCallback(GLFWwindow* window, int width, int height);


unsigned int TextureFromFile(const char* path, const std::string& directory);