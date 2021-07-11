#include "Scene.h"

namespace game {
    Scene::Scene(std::string name, Renderer* render)
    {
        this->sceneName = name;
        gameRenderer = render;
        loaded = false;
        Scene::Init();
    }


    Scene::~Scene()
    {
        delete[]gameRenderer;
        delete[]gameTerrain;
        delete[]gameSkybox;
        gameObjects.clear();
        delete[]factory;
    }


        void Scene::Unload()
        {
            //Entity, asset manager, gameobjects
            gameObjects.erase(gameObjects.begin(), gameObjects.end());
            factory->ResetFactory();
            singleton<Manager>::getInstance().Reset();
            entityMan::getInstance().ClearEntitys();
            mainMenuGui->displayDeathScreen = false;
            loaded = false;
        }

        void Scene::Load(std::string file)
        {
            if (!loaded)
            {
                lua_State* L = LuaManager::getInstance().getLuaState();
                setGlobal(L, this, "cs");

                if (luaL_dofile(L, file.c_str()))
                {
                    std::cout << "Scene lua file not found" << std::endl;
                }
                else
                {
                    std::cout << "WORLD::RUNNING" << std::endl;
                }

                playerInd =  tnah::Scene::FindPlayerIndice(gameObjects);
                Player* p = (Player*)gameObjects[playerInd];
                p->Reset();

                if (!gameObjects.empty())
                {
                    for (auto& gameObject : gameObjects)
                    {
                        if (gameObject->GetType() == "enemy")
                            entityMan::getInstance().RegisterEntity(gameObject);
                    }
                }
                gameGui->DisplayGameUI();
                loaded = true;
            }
        }

        bool Scene::LoadSaveFile()
        {
            if (!loaded)
            {
                std::ifstream file("./res/save.sav");
                if (file.is_open())
                {
                    std::string type;
                    std::string dif;

                    file >> dif;
                    if (dif == "hard")
                    {
                        singleton<Manager>::getInstance().difficulty = Manager::Difficulty::hard;
                    }
                    else if (dif == "easy")
                    {
                        singleton<Manager>::getInstance().difficulty = Manager::Difficulty::easy;
                    }
                    else
                    {
                        singleton<Manager>::getInstance().difficulty = Manager::Difficulty::normal;
                    }


                    while (file >> type)
                    {
                        if (type == "player")
                        {
                            std::string script, state;
                            float scale, x, y, z, health;
                            int points, kills, tokens;
                            file >> script >> scale >> x >> y >> z >> health >> state >> points >> kills >> tokens;
                            MakeSaveGameObject(type, script, scale, x, y, z, health, 0, state, points, tokens, kills);
                        }
                        else if (type == "enemy")
                        {
                            std::string script, state;
                            float scale, x, y, z, health, ammo;
                            file >> script >> scale >> x >> y >> z >> health >> ammo >> state;
                            MakeSaveGameObject(type, script, scale, x, y, z, health, ammo, state, 0, 0, 0);
                        }
                        else if (type == "token")
                        {
                            std::string script;
                            float scale, x, y, z;
                            file >> script >> scale >> x >> y >> z;
                            MakeSaveGameObject(type, script, scale, x, y, z, 0, 0, "", 0, 0, 0);
                        }
                        else if (type == "static")
                        {
                            std::string script;
                            float scale, x, y, z;
                            file >> script >> scale >> x >> y >> z;
                            MakeSaveGameObject(type, script, scale, x, y, z, 0, 0, "", 0, 0, 0);
                        }
                        else if (type == "water")
                        {
                            float scale, x, y, z;
                            std::string script;
                            file >> script >> scale >> x >> y >> z;
                            MakeSaveGameObject(type, script, scale, x, y, z, 0, 0, "", 0, 0, 0);
                        }
                    }


                    playerInd = tnah::Scene::FindPlayerIndice(gameObjects);


                    if (!gameObjects.empty())
                    {
                        for (auto& gameObject : gameObjects)
                        {
                            if (gameObject->GetType() == "enemy")
                                entityMan::getInstance().RegisterEntity(gameObject);
                        }
                    }

                    loaded = true;
                    return true;

                }
            }
            return false;
        }

        void Scene::Run(View lens, float time, bool exit)
        {


            if (exitScreen.exitScreenDisplay)
            {
                endScreenGUI->Draw();
            }
            else if (!mainMenuGui->displayMainMenu && !mainMenuGui->displayPauseMenu && !mainMenuGui->displaySettings && !mainMenuGui->displayDifficulty && !mainMenuGui->displayControls)
            {
                singleton<Manager>::getInstance().Update(time);
                singleton<Manager>::getInstance().UpdateWeapon(time);
                singleton<Manager>::getInstance().UpdateEnemyDeath(time);
                gameRenderer->BindTexture(gameTerrain->GetTextIds());
                Shader t = gameTerrain->GetShader();
                gameRenderer->SetShaderTerrain(t, lens);
                gameTerrain->SetShader(t);
                gameRenderer->RenderTerrain(gameTerrain->GetVAO(), gameTerrain->GetIndicesSize());

                //Skybox
                gameRenderer->SetShaderSkybox(gameSkybox->skyShader, lens);
                gameRenderer->RenderSkybox(gameSkybox->VAO, gameSkybox->texture);

                std::vector<GameObject*> gameObjectsToRemoveFromScene;

                //Physics
                if (PhysicsManager::GetInstance()->GetPhysicsWorld()->getIsDebugRenderingEnabled())
                {
                    gameRenderer->RenderReactDebugger(PhysicsManager::GetInstance()->GetDebugRenderer(), lens);
                }

                //Check if token is on the ground and set it to static
                for (auto go : gameObjects)
                {
                    if (go->GetTag() == (BoundingBox::CollisionTag*)BoundingBox::CollisionTag::TOKEN && go->rigidBody->isSleeping())
                    {
                        go->rigidBody->setType(rp3d::BodyType::KINEMATIC);
                        go->rigidBody->enableGravity(false);
                    }
                }


                //Models
                for (int x = 0; x < gameObjects.size(); x++)
                {
                    gameObjects[x]->Update(time);
                    if (x != playerInd)
                    {
                        gameObjects[x]->Render(lens, time, gameRenderer);
                        if (gameObjects[x]->GetType() == "enemy")
                        {
                            auto* e = (Enemy*)gameObjects[x];
                            UpdateGameObject(e->GetTergetPosition(), x, time);
                            if (e->GetFireWeapon()) { EnemyFireWeapon(e, 5); }
                            if (!gameObjects[x]->Kill())
                            {
                                gameObjectsToRemoveFromScene.emplace_back(gameObjects[x]);
                            }
                        }
                    }
                }




                std::vector<GameObject*>::iterator removed;
                for (auto& go : gameObjectsToRemoveFromScene)
                {
                    //if(Debugger::GetInstance()->debugCollisionsToConsole) std::cout << "Scene.cpp::INFO::GameObject - " + go->GetName() +" hit and removed from scene" << std::endl;
                    glm::vec3 pp = gameObjects[playerInd]->GetPos();
                    int chosenOne = 0;
                    float distance = 0;
                    for (int i = 0; i < spawnPoints.size(); i++)
                    {
                        float newDistance = glm::distance(pp, spawnPoints[i]);

                        if (newDistance > distance)
                        {
                            distance = newDistance;
                            chosenOne = i;
                        }
                    }

                    auto* e = (Enemy*)go;
                    e->ResetEnemy(spawnPoints[chosenOne]);
                    //Spawn New GameObject
                }

                if (singleton<Manager>::getInstance().enemyDeathTimer <= 0 && singleton<Manager>::getInstance().hasKills)
                {
                    for (auto* go : gameObjects)
                    {
                        if (go->GetTag() == (BoundingBox::CollisionTag*)BoundingBox::ENEMY)
                        {
                            auto* e = (Enemy*)go;
                            //e->SetKillFSM(true);
                        }
                    }
                }


                //if the player is firing, fire the weapon duh
                if (playerWeapon.firingWeapon && playerWeapon.canFireWeapon && singleton<Manager>::getInstance().weaponTimer <= 0)
                {
                    playerWeapon.firingWeapon = false;
                    singleton<Manager>::getInstance().weaponTimer = 5.0f / 17.0f;
                    singleton<Manager>::getInstance().fireWeapon = false;
                    playerWeapon.canFireWeapon = false;
                    auto* p = (Player*)gameObjects[playerInd];
                    p->FireWeapon();
                    FireWeapon(gameObjects[playerInd]->GetPos(), lens.GetForward(), 15.0f);
                }

                //if the timer is 0 and we can fire again
                if (singleton<Manager>::getInstance().weaponTimer <= 0)
                {
                    auto* p = (Player*)gameObjects[playerInd];
                    p->BackToIdle();
                    playerWeapon.canFireWeapon = true;
                }

                //If game object is of type player
                UpdatePlayer(lens.GetPosition(), lens.GetRotation(), time, lens);

                //GameUI
                if (gameGui)
                {
                    auto* p = (Player*)gameObjects[playerInd];
                    gameGui->terrainHeight = PlayerToTerrainPosition(p->GetPos(), glm::vec3(0, 0, 0)).y;
                    gameGui->Draw(p);
                }

            }
            else
            {
                mainMenuGui->Draw();
            }
        }

        void Scene::Init()
        {
            gameTerrain = new Terrain();
            gameTerrain->Init();
            gameTerrain->setTextures();

            gameTerrain->generateTerrain();

            gameSkybox = new Skybox();
            factory = new GameAssetFactory(gameRenderer);
            gameRenderer->TerrainSetup(gameTerrain->GetTotalData(), gameTerrain->GetIndicies(), gameTerrain->VAO, gameTerrain->VBO, gameTerrain->EBO);
            gameRenderer->SkyboxSetup(gameSkybox->GetSkyVerts(), gameSkybox->GetCubeFaces(), gameSkybox->VAO, gameSkybox->VBO, gameSkybox->texture, gameSkybox->skyShader);

            exitScreen.Init("./res/models/group/photo.fbx", gameRenderer);

            gameGui = new GameGUI("./res/scripts/menus/game.lua");
            endScreenGUI = new EndScreenGUI("./res/scripts/menus/endScreen.lua");
            mainMenuGui = MainMenuGUI::GetInstance();
            spawnPoints.emplace_back(glm::vec3(409, 4.5, 262));
            spawnPoints.emplace_back(glm::vec3(137, 8, 372));
            spawnPoints.emplace_back(glm::vec3(184, 11, 201));
            spawnPoints.emplace_back(glm::vec3(312, 6, 312));
            spawnPoints.emplace_back(glm::vec3(312, 6, 436));

            physicsManager = PhysicsManager::GetInstance();
            physicsManager->CreateTerrainCollider(gameTerrain);
        }


        void Scene::UpdatePlayer(glm::vec3 newPos, glm::vec3 rotation, float time, View lens)
        {
            auto player = (Player*)gameObjects[playerInd];
            
            if (!gameWindow->isPlayerMoving && !player->velocityReset)
            {
                gameObjects[playerInd]->rigidBody->setMass(1000.0f);
                rp3d::Vector3 cLv = gameObjects[playerInd]->rigidBody->getLinearVelocity();
                rp3d::Vector3 lv = rp3d::Vector3(0, cLv.y, 0);
                gameObjects[playerInd]->rigidBody->setLinearVelocity(lv);
                player->velocityReset = true;
            }

            if (!Debugger::GetInstance()->noClip && gameWindow->isPlayerMoving)
            {
                gameObjects[playerInd]->rigidBody->setMass(10.0f);
                player->velocityReset = false;
                float forceFactor = 1000.0f;

                glm::vec3 currentPos = gameObjects[playerInd]->GetPos();
                glm::vec3 direction = newPos - currentPos;
                rp3d::Vector3 force = PhysicsManager::GetInstance()->GLMVec3toRP3DVec3(direction);
                force.x *= forceFactor;
                force.z *= forceFactor;
                gameObjects[playerInd]->rigidBody->applyForceToCenterOfMass(force);

                //Checking and capping the players velocity
                rp3d::Vector3 lv = gameObjects[playerInd]->rigidBody->getLinearVelocity();
                float velocityCap = 30;
                glm::vec3 v = player->cappedVelocity;
                bool capped = false;
                if (lv.x > velocityCap)
                {
                    lv.x = velocityCap;
                    v = glm::vec3(lv.x, lv.y, lv.z);
                    capped = true;
                }
                else if (lv.x < -velocityCap)
                {
                    lv.x = -velocityCap;
                    v = glm::vec3(lv.x, lv.y, lv.z);
                    capped = true;
                }

                if (lv.y > velocityCap)
                {
                    lv.y = velocityCap;
                    v = glm::vec3(lv.x, lv.y, lv.z);
                    capped = true;
                }
                else if (lv.y < -velocityCap)
                {
                    lv.y = -velocityCap;
                    v = glm::vec3(lv.x, lv.y, lv.z);
                    capped = true;
                }

                if (lv.z > velocityCap)
                {
                    lv.z = velocityCap;
                    v = glm::vec3(lv.x, lv.y, lv.z);
                    capped = true;
                }
                else if (lv.z < -velocityCap)
                {
                    lv.z = -velocityCap;
                    v = glm::vec3(lv.x, lv.y, lv.z);
                    capped = true;
                }

                player->cappedVelocity = v;
                if (capped) gameObjects[playerInd]->rigidBody->setLinearVelocity(rp3d::Vector3(v.x, v.y, v.z));
            }
            //resolve the rb position back to glm position for the camera
            rp3d::Transform t = gameObjects[playerInd]->rigidBody->getTransform();
            rp3d::Vector3 p = t.getPosition();
            newPos.x = (p.x / 10) * 2;
            newPos.y = (p.y / 10) * 2;
            newPos.z = (p.z / 10) * 2;
            gameObjects[playerInd]->SetPos(newPos);

        }

        void Scene::UpdateGameObject(glm::vec3 newPos, int i, float time)
        {

            glm::vec3 currentPos = gameObjects[i]->GetPos();
            glm::vec3 direction = newPos - currentPos;
            rp3d::Vector3 force = PhysicsManager::GetInstance()->GLMVec3toRP3DVec3(direction);
            force *= 50;
            gameObjects[i]->rigidBody->applyForceToCenterOfMass(force);

            //resolve the rb position back to glm position
            rp3d::Transform t = gameObjects[i]->rigidBody->getTransform();
            rp3d::Vector3 p = t.getPosition();
            newPos.x = (p.x / 10) * 2;
            newPos.y = (p.y / 10) * 2;
            newPos.z = (p.z / 10) * 2;

            gameObjects[i]->SetPos(newPos);
        }

        void Scene::MakeGameObject(std::string t, std::string script, float scale, float x, float y, float z)
        {
            //Check the terrain height to make sure the object isn't under the terrain;
            y += WorldToTerrainPosition(glm::vec3(x, y, z), false).y;

            GameObject* newGameObject = factory->GetGameObject(t, script, scale, glm::vec3(x, y, z));
            if (newGameObject != nullptr)
            {
                gameObjects.push_back(newGameObject);

                if (t == "player")
                {
                    gameWindow->UpdateCamera(newGameObject->GetPos());
                    gameWindow->Update();
                }

                if (t == "water") { waterIndex = (int)gameObjects.size() - 1; }
                else { waterIndex = -1; }
            }
            else
            {
                if (Debugger::GetInstance()->debugToConsole) std::cout << "Scene.cpp::ERROR::GAME_ASSET_FACTORY::TYPE_UNKNOWN" << std::endl;
            }
        }

        void Scene::MakeSaveGameObject(std::string t, std::string script, float scale, float x, float y, float z, float health, float ammo, std::string state, int savedPoints, int savedTokens, int savedKills)
        {
            //Check the terrain height to make sure the object isn't under the terrain;
            //y += WorldToTerrainPosition(glm::vec3(x,y,z), false).y;

            GameObject* newGameObject = factory->GetGameObjectSave(t, script, scale, glm::vec3(x, y, z), health, ammo, state, savedPoints, savedTokens, savedKills);
            if (newGameObject != nullptr)
            {
                gameObjects.push_back(newGameObject);

                if (t == "player")
                {
                    gameWindow->UpdateCamera(newGameObject->GetPos());
                    gameWindow->Update();
                }

                if (t == "water") { waterIndex = (int)gameObjects.size() - 1; }
                else { waterIndex = -1; }
            }
            else
            {
                if (Debugger::GetInstance()->debugToConsole) std::cout << "Scene.cpp::ERROR::GAME_ASSET_FACTORY::TYPE_UNKNOWN" << std::endl;
            }
        }

        void Scene::MoveObjectAwayFromPlayer()
        {
            for (auto& go : gameObjects)
            {
                if (go->GetTag() == (BoundingBox::CollisionTag*)BoundingBox::CollisionTag::PLAYER) continue;
                if (glm::distance(go->GetPos(), gameObjects[playerInd]->GetPos()) < 3.0f)
                {
                    glm::vec3 pos = go->GetPos();
                    pos.x += 3.0f;
                    pos.z += 3.0f;
                    pos.y = WorldToTerrainPosition(pos, true).y;
                    go->SetPos(pos);
                }
            }
        }

        glm::vec3 Scene::EnemyObstacleAvoidance(GameObject* self, glm::vec3 newPosition)
        {
            for (auto& go : gameObjects)
            {
                if (go->GetTag() == (BoundingBox::CollisionTag*)BoundingBox::CollisionTag::PLAYER) continue;// dont check against the player
                if (go == self) continue; // dont check against it self
                if (go->GetTag() == (BoundingBox::CollisionTag*)BoundingBox::CollisionTag::TOKEN) continue;
                while (glm::distance(newPosition, go->GetPos()) < 3.5f)
                {
                    newPosition.x += 0.1f;
                }
            }
            return newPosition;

        }

        void Scene::FireWeapon(glm::vec3 weaponStartPos, glm::vec3 forward, float fireDistance)
        {

            playerWeapon.canFireWeapon = true;
            forward = glm::normalize(forward);
            glm::vec3 directionVector = forward * fireDistance;
            glm::vec3 finalEndPoint = weaponStartPos + directionVector;
            bool enemyHit = false;
            float i = 1;
            std::vector<GameObject*> deadEnemyObjects;
            while (i < fireDistance)
            {
                glm::vec3 point = weaponStartPos + (forward * i);

                for (auto* go : gameObjects)
                {
                    if (go->GetTag() == (BoundingBox::CollisionTag*)BoundingBox::ENEMY)
                    {
                        auto* e = (Enemy*)go;

                        glm::vec3 eme = e->GetPos();
                        eme.y = point.y;
                        //std::cout << "Distance: " << glm::distance(eme, point) << " Point: " << Debugger::GetInstance()->DebugVec3(point) << " Player: " << Debugger::GetInstance()->DebugVec3(eme) << std::endl;
                        if (glm::distance(eme, point) <= 0.5f && !e->startTimer)
                        {
                            //hit the enemy, trigger damage
                            if (Debugger::GetInstance()->debugWeapons)
                                //std::cout << "Scene.cpp::INFO::Player Shot Enemy!" << std::endl;
                                enemyHit = true;
                            auto* p = (Player*)gameObjects[playerInd];
                            e->decreaseHealth(p->getDamage());
                            if (e->getHealth() <= 0)
                            {
                                //trigger death animation
                                e->SetState(19);
                                e->startTimer = true;
                                p->increasePoints(50);
                                singleton<Manager>::getInstance().enemyDeathTimer = 5.0f / 17.0f;
                                p->incrementKillCount();
                            }
                            break;
                        }
                    }
                }
                if (enemyHit) break;

                i += 0.5f;
            }
            if (!deadEnemyObjects.empty())
            {
                std::vector<GameObject*>::iterator removed;
                for (auto* go : deadEnemyObjects)
                {
                    removed = std::remove(gameObjects.begin(), gameObjects.end(), go);
                }
            }
        }

        void Scene::EnemyFireWeapon(GameObject* enemy, float fireDistance)
        {
            auto* p = (Player*)gameObjects[playerInd];
            auto* e = (Enemy*)enemy;
            e->SetFireWeapon(false);
            //glm::vec3 forward = e->GetPos() - (p->GetPos() * (e->GetAccuracy() * (0.1f + static_cast <float> (rand()) / ( static_cast <float> (RAND_MAX/(1.0))))));
            glm::vec3 forward = p->GetPos() - e->GetPos();
            forward = glm::normalize(forward);

            glm::vec3 directionVector = forward * fireDistance;
            glm::vec3 finalEndPoint = e->GetPos() + directionVector;
            float i = 1;
            while (i < fireDistance)
            {
                glm::vec3 point = e->GetPos() + (forward * i);

                glm::vec3 pl = p->GetPos();
                pl.y = point.y;
                if (rand() % 100 <= (100 * e->GetAccuracy() * 0.5f))  //glm::distance(pl, point) <= e->GetAccuracy())
                {

                    p->setHealth(p->getHealth() - e->GetDamage());
                    if (p->getHealth() <= 0)
                    {
                        // tell the player to die
                        gameGui->DisplayDeathScreen();
                    }
                    break;
                }


                i += 0.5f;
            }
        }

        glm::vec3 Scene::CheckSceneCollision(glm::vec3 pos)
        {
            glm::vec3 player = gameObjects[playerInd]->GetPos();
            glm::vec3 playerSphereOrigin(pos.x, pos.y - 0.75f, pos.z);
            float playerSphereRadius = 2.0f;

            int numberOfCollisions = 0;
            glm::vec3 shiftDelta = glm::vec3(0, 0, 0);

            std::vector<GameObject*> gameObjectsToRemoveFromScene;
            for (auto& go : gameObjects)
            {
                //Skip the player, we dont want collisions between the player and the player
                if (go->GetTag() == (BoundingBox::CollisionTag*)BoundingBox::PLAYER) continue;

                float distance = glm::distance(playerSphereOrigin, go->GetPos());

                if (go->GetTag() == (BoundingBox::CollisionTag*)BoundingBox::TOKEN && distance < playerSphereRadius)
                {
                    if (Debugger::GetInstance()->debugCollisionsToConsole) std::cout << "Scene.cpp::INFO::Token GameObject - " << go->GetName() << " Hit" << std::endl;
                    go->Kill();
                    gameObjectsToRemoveFromScene.emplace_back(go);
                    continue;
                }

                if (go->GetTag() == (BoundingBox::CollisionTag*)BoundingBox::STATIC_OBJECT && distance < playerSphereRadius || go->GetTag() == (BoundingBox::CollisionTag*)BoundingBox::ENEMY && distance < playerSphereRadius)
                {
                    if (Debugger::GetInstance()->debugCollisionsToConsole) std::cout << "Scene.cpp::INFO::Static GameObject - " + go->GetName() + " hit" << std::endl;
                    //Simple Collisions/distance checking, More complex collision detection is work in progress
                    glm::vec3 dir = go->GetPos() - playerSphereOrigin;
                    //the player is too close to a object and will be stopped
                    pos.x = player.x;
                    pos.y = player.y;
                    pos.z = player.z;

                }

            }
            std::vector<GameObject*>::iterator removed;
            for (auto& go : gameObjectsToRemoveFromScene)
            {
                //if(Debugger::GetInstance()->debugCollisionsToConsole) std::cout << "Scene.cpp::INFO::GameObject - " + go->GetName() +" hit and removed from scene" << std::endl;
                removed = std::remove(gameObjects.begin(), gameObjects.end(), go);
                gameObjects.erase(removed);
            }

  

            return pos;
        }


        void Scene::RunPlayer(View lens, float time, bool exit)
        {
            if (loaded)
            {
                if (!exitScreen.exitScreenDisplay)
                    gameObjects[playerInd]->Render(lens, time, gameRenderer);
            }
        }
    }