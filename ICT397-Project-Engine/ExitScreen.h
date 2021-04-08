/**
 * @brief Holds information about the exit screen and its functions
 * @author Bryce Standley
 * @date 08/04/2021
 * @version 1
 */

#ifndef EXITSCREEN_H
#define EXITSCREEN_H

#include "OpenGL.h"
#include <vector>
#include <glm/glm.hpp>
#include "TextureLoader.h"
#include "Shader.h"

class ExitScreen
{
public:
    ExitScreen() = default;

    void Init();
    //Renderer* renderer;
    Shader shader;
    std::vector<glm::vec3> vertexData;
    std::vector<unsigned int> indicesData;
    TextureLoader textureLoader;
    bool exitScreenDisplay = false;
    unsigned int tex;
    unsigned int VAO = 0, VBO = 0, EBO = 0;

    void SetExitScreenDisplay(bool i){exitScreenDisplay = i;}

    Shader GetShader(){return shader;}

private:

};


#endif //EXITSCREEN_H
