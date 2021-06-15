#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include "stb_image.h"

/**
 * @brief Framebuffer callback for GLFW
 * @param window
 * @param width
 * @param height
 */
void framebufferCallback(GLFWwindow* window, int width, int height);

/**
 * @brief Load texture from file
 * @param path
 * @param directory
 * @return unsigned int
 */
unsigned int TextureFromFile(const char* path, const std::string& directory);