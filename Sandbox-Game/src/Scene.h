#pragma once
#include "TNAH.h"
namespace game {
    class Scene : public tnah::Scene
    {
    public:
        Scene(std::string name, Renderer* render);
        ~Scene();
        void Unload();
        void Load(std::string file);
        bool LoadSaveFile();
        void Run(View lens, float time, bool exit);
        void Init();
        void UpdatePlayer(glm::vec3 newPos, glm::vec3 rotation, float time, View lens);
        void UpdateGameObject(glm::vec3 newPos, int i, float time);
        void MakeGameObject(std::string t, std::string script, float scale, float x, float y, float z);
        void MakeSaveGameObject(std::string t, std::string script, float scale, float x, float y, float z, float health, float ammo, std::string state, int savedPoints, int savedTokens, int savedKills);
        void MoveObjectAwayFromPlayer();
        glm::vec3 EnemyObstacleAvoidance(GameObject* self, glm::vec3 newPosition);
        void FireWeapon(glm::vec3 weaponStartPos, glm::vec3 forward, float fireDistance);
        void EnemyFireWeapon(GameObject* enemy, float fireDistance);
        glm::vec3 CheckSceneCollision(glm::vec3 pos);

        void RunPlayer(View lens, float time, bool exit);


    };
}