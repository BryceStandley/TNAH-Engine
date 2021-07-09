#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Debugger.h"


    /**
    * @class Shader
    * @brief A class that is responsible for shaders, allowing you to open/use shaders and set uniforms of various types for use in the shaders
    *
    * @author Dylan Blereau
    * @version 01
    * @date 01/03/2021 Dylan Blereau, Started
    *
    **/
class Shader
{
public:
        /// shader ID
    unsigned int ID;

        /// default constructor
    Shader() {};

        /**
        * @brief A constructor that takes in paths to the shaders and generates them 
        * @param vertexPath - represents the path to the vertex shader
        * @param fragmentPath - represents the path to the fragment shader
        * @param geometryPath - represents the path to the geometry shader (set to null in this case)
        */
    Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
    
        /**
        * @brief Allows you to activate and use the shader  
        */
    void use();
   
        /**
        * @brief sets a boolean for use in the shader program
        * @param name - represents the name of the variable
        * @param value - represents the variable value
        */
    void setBool(const std::string& name, bool value) const;
    
        /**
        * @brief sets an integer for use in the shader program
        * @param name - represents the name of the variable
        * @param value - represents the variable value
        */
    void setInt(const std::string& name, int value) const;
    
        /**
        * @brief sets a float for use in the shader program
        * @param name - represents the name of the variable
        * @param value - represents the variable value
        */
    void setFloat(const std::string& name, float value) const;
    
        /**
        * @brief sets a vec2 for use in the shader program
        * @param name - represents the name of the variable
        * @param value - represents the variable value
        */
    void setVec2(const std::string& name, const glm::vec2& value) const;

        /**
        * @brief sets a vec2 for use in the shader program (Overloaded to allow two floats to define the vec2)
        * @param name - represents the name of the variable
        * @param x - sets the x value
        * @param y - sets the y value
        */
    void setVec2(const std::string& name, float x, float y) const;
    
        /**
        * @brief sets a vec3 for use in the shader program
        * @param name - represents the name of the variable
        * @param value - represents the variable value
        */
    void setVec3(const std::string& name, const glm::vec3& value) const;

        /**
        * @brief sets a vec3 for use in the shader program (Overloaded to allow three floats to define the vec3)
        * @param name - represents the name of the variable
        * @param x - sets the x value
        * @param y - sets the y value
        * @param z - sets the z value
        */
    void setVec3(const std::string& name, float x, float y, float z) const;
    
        /**
        * @brief sets a vec4 for use in the shader program
        * @param name - represents the name of the variable
        * @param value - represents the variable value
        */
    void setVec4(const std::string& name, const glm::vec4& value) const;
    
        /**
        * @brief sets a vec4 for use in the shader program (Overloaded to allow four floats to define the vec4)
        * @param name - represents the name of the variable
        * @param x - sets the x value
        * @param y - sets the y value
        * @param z - sets the z value
        * @param w - sets the w value
        */
    void setVec4(const std::string& name, float x, float y, float z, float w);
    
        /**
        * @brief sets a mat2 for use in the shader program
        * @param name - represents the name of the variable
        * @param mat - represents the variable value
        */
    void setMat2(const std::string& name, const glm::mat2& mat) const;
    
        /**
        * @brief sets a mat3 for use in the shader program
        * @param name - represents the name of the variable
        * @param mat - represents the variable value
        */
    void setMat3(const std::string& name, const glm::mat3& mat) const;
    
        /**
        * @brief sets a mat4 for use in the shader program
        * @param name - represents the name of the variable
        * @param mat - represents the variable value
        */
    void setMat4(const std::string& name, const glm::mat4& mat) const;

	// Return the location of a uniform variable inside a shader program
	GLint getUniformLocation(const std::string& variableName, bool errorIfMissing = true) const;

	// Return the location of an attribute variable inside a shader program
	GLint getAttribLocation(const std::string& variableName, bool errorIfMissing = true) const;

	//Unbind the shader from the program
	void unbind() const;


private:
    
        /**
        * @brief checks for errors in the shaders
        * @param shader - represents the shader
        * @param type - represents the type of shader
        */
    void checkCompileErrors(GLuint shader, std::string type);
};
#endif