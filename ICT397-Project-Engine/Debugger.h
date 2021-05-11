/**
 * @brief Used to aid in debugging
 * @author Bryce Standley
 * @date 08/04/2021
 * @version 1
 */

#ifndef DEBUGGING_H
#define DEBUGGING_H

#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>


/**
 * @class Debugger
 * @brief helper functions and flags to aid in debugging aspects of the engine
 */
class Debugger{
public:
    static Debugger* GetInstance();


    /**
     * @brief turns a vec3 into a string for console output
     * @param Vec3 a
     * @return string - string value with each XYZ of a given vec3
     */
    std::string DebugVec3(glm::vec3 a);

    /**
     * @brief flag for enabling/disabling debug and error information in the console
     */
    bool debugToConsole = false;

    /**
     * @brief flag for enabling/disabling debug information about collisions in the console
     */
    bool debugCollisionsToConsole = false;
    bool debugFSMToConsole = false;

    float ApplicationFramerate = 0.0f;

    bool drawDebugPanel = false;

    GLFWwindow* windowRef = nullptr;

private:


protected:
    Debugger() = default;
    static Debugger* instance;
};


#endif //DEBUGGING_H