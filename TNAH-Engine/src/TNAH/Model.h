#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include<glm/gtx/matrix_decompose.hpp>
#include "stb_image.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "Shader.h"


#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>


#include "Callbacks.h"
#include "OpenGL.h"
#include "Fbx.h"
#include "Md2.h"

#include "Debugger.h"

#include <reactphysics3d/reactphysics3d.h>

    /**
    * @class Model
    * @brief Holds the model information of objects, can be md2 or Fbx models
    *
    * @author Christopher Logan
    * @version 01
    * @date 25/04/2021
    *
    **/
class TNAH_API Model
{
public:

        /**
        * @brief default constructor
        *
        **/
    Model() {}


        /**
        * @brief Model constructor that takes various parameters
        * @param path - represents the path to the model
        * @param r - a pointer to the renderer
        * @param check - a boolean variable that checks if the model is MD2 or FBX
        *
        **/
    Model(std::string const& path, Renderer* r, bool check)
    {
        SetMd2(check);
        LoadModel(path, r, "");
        animations = true;
    }


       /**
       * @brief Model constructor that takes various parameters
       * @param path - represents the path to the model
       * @param r - a pointer to the renderer
       * @param check - a boolean variable that checks if the model is MD2 or FBX
       * @param pathTexture - a string representing the path to the model texture
       * @bool anim - a boolean flag indicating whether or not animations are true or false
       *
       **/
    Model(std::string const& path, Renderer* r, bool check, std::string pathTexture, bool anim)
    {
        SetMd2(check);
        LoadModel(path, r, pathTexture);
        animations = anim;
    }

       /**
       * @brief Function that will set the model to MD2 is the boolean provided is true, otherwise it will assign the model to be an FBX
       * @param check - represents the check to see if the model is MD2 or not
       * 
       **/
    void SetMd2(bool check) {
        if (check)
        {
            md2 = true;
            fbx = false;
        }
        else
        {
            md2 = false;
            fbx = true;
        }
    }

        /**
        * @brief Function responible for loading the model
        * @param path - represents the filepath to the model
        * @param gameRenderer - represents a pointer to the gameRenderer
        * @param pathTexture - a string that represents the path to the models texture
        *
        **/
    void LoadModel(std::string const& path, Renderer* gameRenderer, std::string pathTexture);
    //void Render(View lens, Shader& shader, glm::vec3 pos, glm::vec3 rot, float scale, bool rotate, float time);

        /**
        * @brief makes use of the view information and graphics renderer among other things to render the model
        * @param lens - holds the information that allows you to project and view the model
        * @param shader - represents the shader object used by the model
        * @param pos - the vec3 position of the model
        * @param rot - rotation vector of the model
        * @param scale - scale of the object
        * @param rotate - bool value confirming whether or not the model rotates
        * @param time - represents deltatime, which is the difference between the previous frame and the current frame
        * @param direction - the direction of the model
        * @param gameRenderer - a pointer to the renderer which is used to render the enemy model
        * @param p - represents if player exists or not
        */
    void Render(View lens, Shader &shader, glm::vec3 pos, glm::vec3 rot, float scale, bool rotate, float time, float direction, Renderer * gameRenderer, bool p);

        /**
        * @brief sets the animation state of the model to the command provided as parameter
        * @param cmd - represents the animation state that the function will provide the start animation function
        * 
        */
    void SetState(Md2Commands cmd) { currentState = md2Model.StartAnimation(cmd); }

        /**
        * @brief gets and returns the current Md2State of the Model
        * @return Md2State
        */
    Md2State GetState() const { return currentState; }

        /**
        * @brief gets and returns a pointer to the Mesh of the Model
        * @return Mesh*
        */
    Mesh* GetMesh(int i) { return &fbxModel.meshes[i]; }


private:

        /**
        * @brief generates and returns a matrix used to render the model with the correct scale, rotation, and position
        * @param pos - position vector
        * @param rot - rotation vector
        * @param scale - scale factor of the model
        * @param rotate - bool true/false flag which determines whether or not the model rotates
        * @return glm::mat4
        */
    glm::mat4 GenerateMatFour(glm::vec3 pos, glm::vec3 rot, float scale, bool rotate);
    Fbx fbxModel;
    Md2 md2Model;
    bool fbx;
    bool md2;
    Md2State currentState;
    bool animations;
};