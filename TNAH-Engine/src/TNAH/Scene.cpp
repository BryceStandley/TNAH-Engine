#include "tnahpch.h"
#include "Scene.h"
namespace tnah {

    Scene::Scene(std::string name, Renderer* render)
    {
        this->sceneName = name;
        gameRenderer = render;
        loaded = false;
        Init();
    }


    Scene::~Scene()
    {
        delete[]gameRenderer;
        delete[]gameTerrain;
        delete[]gameSkybox;
        gameObjects.clear();
        delete[]factory;
    }

    float Scene::Lerp(float a, float b, float t)
    {
        return (a * (1.0f - t)) + (b * t);
    }

    float Scene::Interpolate(float a, float b, float blend)
    {
        double theta = blend * M_PI;
        float f = (float)(1.0f - cos(theta)) * 0.5f;
        return a * (1.0f - f) + b * f;
    }

    float Scene::BilinearInterpolation(glm::vec3 p)
    {
        int intX = p.x;
        int intZ = p.z;
        float fracX = p.x - intX;
        float fracZ = p.z - intZ;

        float v1 = PlayerToTerrainPosition(glm::vec3(intX, 0, intZ), glm::vec3(0, 0, 0)).y;
        float v2 = PlayerToTerrainPosition(glm::vec3(intX, 0, intZ), glm::vec3(1, 0, 0)).y;
        float v3 = PlayerToTerrainPosition(glm::vec3(intX, 0, intZ + 1), glm::vec3(0, 0, 1)).y;
        float v4 = PlayerToTerrainPosition(glm::vec3(intX, 0, intZ), glm::vec3(1, 0, 1)).y;
        float i1 = Interpolate(v1, v2, fracX);
        float i2 = Interpolate(v3, v4, fracX);
        float newHeight = Interpolate(i1, i2, fracZ);
        return  newHeight;
    }


    glm::vec3 Scene::WorldToTerrainPosition(glm::vec3 p, bool average)
    {
        //std::cout << "Updaing position" << Debugger::GetInstance()->DebugVec3(p) << std::endl;
        float worldx, worldz;
        worldx = Remap(p.x, 0, 52.0f * gameTerrain->GetScales().x, 0, (float)gameTerrain->getSize());
        worldz = Remap(p.z, 0, 52.0f * gameTerrain->GetScales().z, 0, (float)gameTerrain->getSize());
        if (average)
        {
            float y = (gameTerrain->getAverageHeight((int)worldx, (int)worldz));
            y = Remap(y, gameTerrain->GetMinHeight().y, gameTerrain->GetMaxHeight().y, 2, 80.0f);
            p.y = y;
        }
        else
        {
            //p.y = (gameTerrain->GetVertexHeight((int)worldx, (int)worldz) / (worldToTerrainScaleFactor * gameTerrain->GetScales().y));
            float y = gameTerrain->GetVertexHeight((int)worldx, (int)worldz);
            p.y = Remap(y, gameTerrain->GetMinHeight().y, gameTerrain->GetMaxHeight().y, 2, 80.0f);
        }
        return p;
    }


  
    float Scene::Remap(float value, float oldMin, float oldMax, float newMin, float newMax)
    {
        float out = newMin + (newMax - newMin) * ((value - oldMin) / (oldMax - oldMin));
        return out;
    }

    glm::vec3 Scene::PlayerToTerrainPosition(glm::vec3 p, glm::vec3 terrainPosMovement)
    {
        float worldx, worldy, worldz;
        worldx = Remap(p.x, 0, 52.0f * gameTerrain->GetScales().x, 0, (float)gameTerrain->getSize() - 1);
        worldz = Remap(p.z, 0, 52.0f * gameTerrain->GetScales().z, 0, (float)gameTerrain->getSize() - 1);
        worldy = gameTerrain->GetVertexHeight(worldx + terrainPosMovement.x, worldz + terrainPosMovement.z);
        return glm::vec3(worldx, worldy, worldz);
    }


    int Scene::FindPlayerIndice(std::vector<GameObject*> go)
    {
        for (int x = 0; x < go.size(); x++)
        {
            if (go[x]->GetType() == "player")
            {
                return x;
            }
        }
    }

}