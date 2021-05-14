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

    /**
    * @class Model
    * @brief Holds the model information of objects, can be md2 or Fbx models
    *
    * @author Christopher Logan
    * @version 01
    * @date 25/04/2021
    *
    **/
class Model
{
public:
    Model() {}

    Model(std::string const& path, Renderer* r, bool check)
    {
        SetMd2(check);
        LoadModel(path, r, "");
        animations = true;
    }

    Model(std::string const& path, Renderer* r, bool check, std::string pathTexture, bool anim)
    {
        if(Debugger::GetInstance()->debugMD2ToConsole) std::cout << "Made it 4.1" << std::endl;
        SetMd2(check);
        if(Debugger::GetInstance()->debugMD2ToConsole) std::cout << "Made it 4.3" << std::endl;
        LoadModel(path, r, pathTexture);
        if(Debugger::GetInstance()->debugMD2ToConsole) std::cout << "Made it 4.7" << std::endl;
        animations = anim;
    }

    void SetMd2(bool check) {
        if(Debugger::GetInstance()->debugMD2ToConsole) std::cout << "Made it 4.2" << std::endl;
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
    void LoadModel(std::string const& path, Renderer* gameRenderer, std::string pathTexture);
    //void Render(View lens, Shader& shader, glm::vec3 pos, glm::vec3 rot, float scale, bool rotate, float time);
    void Render(View lens, Shader &shader, glm::vec3 pos, glm::vec3 rot, float scale, bool rotate, float time, float direction, Renderer * gameRenderer);

    void SetState(Md2Commands cmd) { currentState = md2Model.StartAnimation(cmd); }
    Md2State GetState() const { return currentState; }

    Mesh* GetMesh(int i) { return &fbxModel.meshes[i]; }
private:
    glm::mat4 GenerateMatFour(glm::vec3 pos, glm::vec3 rot, float scale, bool rotate);
    Fbx fbxModel;
    Md2 md2Model;
    bool fbx;
    bool md2;
    Md2State currentState;
    bool animations;
};