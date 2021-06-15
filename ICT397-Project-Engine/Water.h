#pragma once
#ifndef WATER_H
#define WATER_H
#include "GameObject.h"

class Water : public GameObject
{
public:
    Water(glm::vec3 p, glm::vec3 rot, float s, Renderer* gameRenderer, std::string script) : GameObject(p, rot, s, gameRenderer)
    {
        lua_State* L = LuaManager::getInstance().getLuaState();
        SetScriptName(script);
        if (!luaL_dofile(L, script.c_str()))
        {
            LuaRef type = getGlobal(L, "check");
            LuaRef rot = getGlobal(L, "rotate");
            LuaRef mod = getGlobal(L, "model");
            LuaRef vert = getGlobal(L, "vertShader");
            LuaRef frag = getGlobal(L, "fragShader");

            std::string file;
            std::string vertS;
            std::string fragS;
            bool check = false, rotate = false;

            if (type.isBool())
            {
                check = type.cast<bool>();
            }

            if (rot.isBool())
            {
                rotate = rot.cast<bool>();
            }

            if (mod.isString())
            {
                file = mod.cast<std::string>();
            }

            if (vert.isString())
            {
                vertS = vert.cast<std::string>();
            }

            if (frag.isString())
            {
                fragS = frag.cast<std::string>();
            }

            Model tempModel(file, gameRenderer, check);
            SetModel(tempModel);

            Shader tempShader(vertS.c_str(), fragS.c_str());
            SetShader(tempShader);

            SetRotate(rotate);
        }
        else if (!luaL_dofile(L, "./res/scripts/gameobjects/static_default.lua"))
        {
            std::cout << "Static script not found, loading default script" << std::endl;
            LuaRef type = getGlobal(L, "check");
            LuaRef rot = getGlobal(L, "rotate");
            LuaRef mod = getGlobal(L, "model");
            LuaRef vert = getGlobal(L, "vertShader");
            LuaRef frag = getGlobal(L, "fragShader");

            std::string file;
            std::string vertS;
            std::string fragS;
            bool check = false, rotate = false;

            if (type.isBool())
            {
                check = type.cast<bool>();
            }

            if (rot.isBool())
            {
                rotate = rot.cast<bool>();
            }

            if (mod.isString())
            {
                file = mod.cast<std::string>();
            }

            if (vert.isString())
            {
                vertS = vert.cast<std::string>();
            }

            if (frag.isString())
            {
                fragS = frag.cast<std::string>();
            }

            Model tempModel(file, gameRenderer, check);
            SetModel(tempModel);

            Shader tempShader(vertS.c_str(), fragS.c_str());
            SetShader(tempShader);

            SetRotate(rotate);
        }
        else
        {
            std::cout << "ERROR::NO_WATER_SCRIPTS_FOUND" << std::endl;
        }
        
        FBO = 0;
        DBO = 0;
        colourTextureID = 0;
        depthTextureID = 0;
        size = 100;
    }
    /**
    * @brief Update function that updates the functionality
    * @param time - the time since the last frame
    */
    void Update(float time);

    /**
     * @brief Sets the water FBO
     * @param f
     */
    void SetFBO(unsigned int f) {FBO = f;}

    /**
     * @brief Gets the Water FBO
     * @return FBO
     */
    unsigned int GetFBO(){return FBO;}

    void SetDBO(unsigned int d){DBO = d;}
    unsigned int GetDBO(){return DBO;}


    void SetColourTextureID(unsigned int c) {colourTextureID = c;}
    unsigned int GetColourTextureID(){return colourTextureID;}

    void SetDepthTextureID(unsigned int d) {depthTextureID = d;}
    unsigned int GetDepthTextureID(){return depthTextureID;}

    void SetSize(int s) { size = s;}

    int GetSize(){return size;}

private:
    ///Framebuffer id
    unsigned int FBO{};

    ///Depthbuffer id
    unsigned int DBO{};

    ///Colour buffer texture id
    unsigned int colourTextureID{};

    ///Depth buffer texture id
    unsigned int depthTextureID{};

    ///Size of the water in pixels
    int size{};

};


#endif //WATER_H
