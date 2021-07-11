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
#include "GameObject.h"

class TNAH_API ExitScreen
{
public:
    ExitScreen() = default;

    void Init(std::string name, Renderer* r);
    Renderer* renderer;
    Shader shader;
    Model exitModel;

    bool exitScreenDisplay;

    void SetExitScreenDisplay(bool i){exitScreenDisplay = i;}

    Shader GetShader(){return shader;}

    void Render(Renderer* r, View lens);
private:

};


#endif //EXITSCREEN_H
