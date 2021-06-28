#include "Scene.h"
Scene::Scene(std::string name, Renderer * render)
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

        FindPlayerIndice();
	    Player* p = (Player*)gameObjects[playerInd];
	    p->Reset();

        if (!gameObjects.empty())
        {
            for (auto & gameObject : gameObjects)
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


	        FindPlayerIndice();


	        if (!gameObjects.empty())
	        {
		        for (auto & gameObject : gameObjects)
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
    else if(!mainMenuGui->displayMainMenu && !mainMenuGui->displayPauseMenu && !mainMenuGui->displaySettings && !mainMenuGui->displayDifficulty && !mainMenuGui->displayControls)
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
	    if(PhysicsManager::GetInstance()->GetPhysicsWorld()->getIsDebugRenderingEnabled())
	    {
		    gameRenderer->RenderReactDebugger(PhysicsManager::GetInstance()->GetDebugRenderer(), lens);
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
				    UpdateGameObject(e->GetPos(), x, time);
				    if(e->GetFireWeapon()) { EnemyFireWeapon(e, 5); }
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

		if(singleton<Manager>::getInstance().enemyDeathTimer <= 0 && singleton<Manager>::getInstance().hasKills)
		{
			for( auto* go : gameObjects)
			{
				if(go->GetTag() == BoundingBox::ENEMY)
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
	    UpdatePlayer(lens.GetPosition(), lens.GetRotation(), time);

        //GameUI
        if (gameGui)
        {
        	auto* p = (Player*)gameObjects[playerInd];
        	gameGui->terrainHeight = PlayerToTerrainPosition(p->GetPos(), glm::vec3(0,0,0)).y;
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


void Scene::UpdatePlayer(glm::vec3 newPos, glm::vec3 rotation, float time)
{
	if(!Debugger::GetInstance()->noClip)
	{
		glm::vec3 currentPos = gameObjects[playerInd]->GetPos();
        glm::vec3 direction = newPos - currentPos;
        std::cout << Debugger::GetInstance()->DebugVec3(direction) << std::endl;
		rp3d::Vector3 force = PhysicsManager::GetInstance()->GLMVec3toRP3DVec3(direction);
		force *= 50;
		gameObjects[playerInd]->rigidBody->applyForceToCenterOfMass(force);

		//resolve the rb position back to glm position for the camera
		rp3d::Transform t = gameObjects[playerInd]->rigidBody->getTransform();
		rp3d::Vector3 p = t.getPosition();
		newPos.x = (p.x / 10) * 2;
		newPos.y = (p.y / 10) * 2;
		newPos.z = (p.z / 10) * 2;
	}
	gameObjects[playerInd]->SetPos(newPos);

	/*
	if(playerStartPosition == glm::vec3(-1000,-1000, -1000)) { playerStartPosition = position;}
    if(position == gameObjects[playerInd]->GetPos()) return;

    glm::vec3 newPos = position;
    if(!Debugger::GetInstance()->noClip)
    {
	    newPos = WorldToTerrainPosition(position, false);
	    newPos.y += Lerp(1.5f, 3.0f, time * 4.0f);
	    //std::cout << Lerp(1.5f, 3.0f, time * 4.0f) << std::endl;
	    //newPos.y = Lerp(newPos.y + 2.0f, newPos.y + 3.0f,  time * 2.0f );

	    //newPos.y = BilinearInterpolation(position);


	    if (newPos.y >= 125.0f)
	    {
		    newPos.x = gameObjects[playerInd]->GetPos().x;
		    newPos.y = gameObjects[playerInd]->GetPos().y;
		    newPos.z = gameObjects[playerInd]->GetPos().z;
	    }

	    newPos = CheckSceneCollision(newPos);

	    gameObjects[playerInd]->SetPos(newPos);

	    if (gameObjects[waterIndex] != nullptr && waterIndex != -1)
	    {
		    if (glm::distance(newPos, gameObjects[waterIndex]->GetPos()) < 15.0f)
		    {
			    std::cout << "take water dmg" << std::endl;
			    //take 10 health from the player if they get to close to the water
			    Player *p = (Player *) gameObjects[playerInd];
			    p->setHealth(p->getHealth() - 10);
			    if (p->getHealth() <= 0)
			    {
				    p->setHealth(0);
				    // tell the player to die
				    gameGui->DisplayDeathScreen();
			    }
		    }
	    }
    }
    else
    {
	    gameObjects[playerInd]->SetPos(newPos);
    }
    */
}
float Scene::Lerp(float a, float b, float t)
{
	return (a * (1.0f - t)) + (b * t);
}

float Scene::Interpolate(float a, float b, float blend)
{
	double theta = blend * M_PI;
	float f = (float) (1.0f - cos(theta)) * 0.5f;
	return a * (1.0f - f) + b * f;
}

float Scene::BilinearInterpolation(glm::vec3 p)
{
	int intX =  p.x;
	int intZ =  p.z;
	float fracX = p.x - intX;
	float fracZ = p.z - intZ;

	float v1 = PlayerToTerrainPosition(glm::vec3(intX, 0, intZ), glm::vec3(0,0,0)).y;
	float v2 = PlayerToTerrainPosition(glm::vec3(intX, 0, intZ), glm::vec3(1,0,0)).y;
	float v3 = PlayerToTerrainPosition(glm::vec3(intX, 0, intZ + 1), glm::vec3(0,0,1)).y;
	float v4 = PlayerToTerrainPosition(glm::vec3(intX, 0, intZ), glm::vec3(1,0,1)).y;
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
	if(average)
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


void Scene::UpdateGameObject(glm::vec3 position, int i, float time)
{
    position = EnemyObstacleAvoidance(gameObjects[i], position);

	glm::vec3 newPos = WorldToTerrainPosition(position, true);
	newPos.y += 1.2f;

	//newPos.y += Lerp(0.9f, 1.4f, time * 4.0f);

    if (newPos.y >= 25.0f)
    {
	    newPos.x = gameObjects[i]->GetPos().x;
	    newPos.y = gameObjects[i]->GetPos().y;
	    newPos.z = gameObjects[i]->GetPos().z;
    }

	gameObjects[i]->SetPos(newPos);
}

void Scene::MakeGameObject(std::string t, std::string script, float scale, float x, float y, float z)
{
    //Check the terrain height to make sure the object isn't under the terrain;
    y += WorldToTerrainPosition(glm::vec3(x,y,z), false).y;

	GameObject* newGameObject = factory->GetGameObject(t, script, scale, glm::vec3(x, y, z));
	if (newGameObject != nullptr)
	{
		gameObjects.push_back(newGameObject);

		if(t == "player")
		{
			gameWindow->UpdateCamera(newGameObject->GetPos());
			gameWindow->Update();
		}

		if(t == "water") { waterIndex = (int)gameObjects.size() - 1;}
		else {waterIndex = -1;}
	}
	else
	{
		if(Debugger::GetInstance()->debugToConsole) std::cout << "Scene.cpp::ERROR::GAME_ASSET_FACTORY::TYPE_UNKNOWN" << std::endl;
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

	    if(t == "player")
	    {
		    gameWindow->UpdateCamera(newGameObject->GetPos());
		    gameWindow->Update();
	    }

        if (t == "water") { waterIndex = (int)gameObjects.size() - 1; }
        else {waterIndex = -1;}
    }
    else
    {
        if (Debugger::GetInstance()->debugToConsole) std::cout << "Scene.cpp::ERROR::GAME_ASSET_FACTORY::TYPE_UNKNOWN" << std::endl;
    }
}

void Scene::FindPlayerIndice()
{
    for (int x = 0; x < gameObjects.size(); x++)
    {
        if (gameObjects[x]->GetType() == "player")
        {
            playerInd = x;
            break;
        }
    }
}

void Scene::MoveObjectAwayFromPlayer()
{
    for(auto &go : gameObjects)
    {
        if(go->GetTag() == BoundingBox::CollisionTag::PLAYER) continue;
        if(glm::distance(go->GetPos(), gameObjects[playerInd]->GetPos()) < 3.0f)
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
    for(auto &go : gameObjects)
    {
        if(go->GetTag() == BoundingBox::CollisionTag::PLAYER) continue;// dont check against the player
        if(go == self) continue; // dont check against it self
        if(go->GetTag() == BoundingBox::CollisionTag::TOKEN) continue;
        while(glm::distance(newPosition, go->GetPos()) < 3.5f)
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
    while(i < fireDistance)
    {
        glm::vec3 point = weaponStartPos + (forward * i);

        for(auto* go : gameObjects)
        {
            if(go->GetTag() == BoundingBox::ENEMY)
            {
	            auto *e = (Enemy *) go;

            	glm::vec3 eme = e->GetPos();
            	eme.y = point.y;
	            //std::cout << "Distance: " << glm::distance(eme, point) << " Point: " << Debugger::GetInstance()->DebugVec3(point) << " Player: " << Debugger::GetInstance()->DebugVec3(eme) << std::endl;
            	if(glm::distance(eme, point) <= 0.5f && !e->startTimer )
	            {
		            //hit the enemy, trigger damage
		            if (Debugger::GetInstance()->debugWeapons)
			            //std::cout << "Scene.cpp::INFO::Player Shot Enemy!" << std::endl;
		            enemyHit = true;
		            auto* p = (Player*) gameObjects[playerInd];
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
        if(enemyHit) break;

        i += 0.5f;
    }
    if(!deadEnemyObjects.empty())
    {
	    std::vector<GameObject*>::iterator removed;
    	for(auto* go : deadEnemyObjects)
	    {
    		removed = std::remove(gameObjects.begin(), gameObjects.end(), go);
	    }
    }
}

void Scene::EnemyFireWeapon(GameObject* enemy, float fireDistance)
{
	auto *p = (Player *) gameObjects[playerInd];
	auto *e = (Enemy *) enemy;
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
    glm::vec3 shiftDelta = glm::vec3(0,0,0);

    std::vector<GameObject *> gameObjectsToRemoveFromScene;
    for (auto& go : gameObjects)
    {
        //Skip the player, we dont want collisions between the player and the player
        if (go->GetTag() == BoundingBox::PLAYER) continue;

        float distance = glm::distance(playerSphereOrigin, go->GetPos());

        if (go->GetTag() == BoundingBox::TOKEN && distance < playerSphereRadius)
        {
            if(Debugger::GetInstance()->debugCollisionsToConsole) std::cout << "Scene.cpp::INFO::Token GameObject - " << go->GetName() << " Hit" << std::endl;
            go->Kill();
            gameObjectsToRemoveFromScene.emplace_back(go);
            continue;
        }

        if (go->GetTag() == BoundingBox::STATIC_OBJECT && distance < playerSphereRadius || go->GetTag() == BoundingBox::ENEMY && distance < playerSphereRadius)
        {
            if (Debugger::GetInstance()->debugCollisionsToConsole) std::cout << "Scene.cpp::INFO::Static GameObject - " + go->GetName() + " hit" << std::endl;
            //Simple Collisions/distance checking, More complex collision detection is work in progress
            glm::vec3 dir = go->GetPos() - playerSphereOrigin;
            //the player is too close to a object and will be stopped
            pos.x = player.x;
            pos.y = player.y;
            pos.z = player.z;

        }
    


        /*//Get the information about the bounding box of a gameobject
        BoundingBox box = go->GetBoundingBox();
        std::vector<glm::vec3> vertex = box.GetVertexData();
        std::vector<int> index = box.GetIndiceData();
        std::vector<glm::vec3> normal = box.GetNormalData();
        int numberOfTriangles = (int)index.size()/3;

        for(int i = 0; i < numberOfTriangles; i++)
        {
            bool outsidePlane = false;
            bool outsideAllVerts = false;
            bool outsideAllEdges = false;

            //find points
            glm::vec3 a = vertex[i];
            glm::vec3 b = vertex[i+1];
            glm::vec3 c = vertex[i+2];

            //find vectors between points
            glm::vec3 ab = b - a;
            glm::vec3 ac = c - a;
            glm::vec3 bc = c - b;

            //find normal of the required triangle
            glm::vec3 pN = glm::cross(ab, ac);

            //check the normal is horizontal to the player
            if(pN.y > 0.1f) continue;

            //Find the sphere to plane distance
            float d = glm::dot(-((a + b + c) / 3.0f), pN);

            float ppd = glm::dot(pN, playerSphereOrigin) + d;//add square root if d isnt normalized

            //player Shphere is outside the triangles plane
            if(ppd > playerSphereRadius) {outsidePlane = true; continue;}

            bool outsideA = pow(glm::distance(a, playerSphereOrigin), 2) > pow(playerSphereRadius, 2);
            bool outsideB = pow(glm::distance(b, playerSphereOrigin), 2) > pow(playerSphereRadius,2);
            bool outsideC = pow(glm::distance(c, playerSphereOrigin), 2) > pow(playerSphereRadius,2);

            //sphere is outside of the triangle points
            if(outsideA && outsideB && outsideC) outsideAllVerts = true;

            glm::vec3 ip;

            if(!intersectRaySegmentSphere(a, ab, playerSphereOrigin, pow(playerSphereRadius,2), ip) &&
                !intersectRaySegmentSphere(b, ac, playerSphereOrigin, pow(playerSphereRadius,2), ip) &&
                !intersectRaySegmentSphere(c, bc, playerSphereOrigin, pow(playerSphereRadius,2), ip)) outsideAllEdges = true;

            if(outsideAllEdges && outsideAllVerts) continue;

            numberOfCollisions++;
            shiftDelta += pN * (playerSphereRadius - ppd);

        }
         */
    }
    std::vector<GameObject*>::iterator removed;
    for(auto &go : gameObjectsToRemoveFromScene)
    {
        //if(Debugger::GetInstance()->debugCollisionsToConsole) std::cout << "Scene.cpp::INFO::GameObject - " + go->GetName() +" hit and removed from scene" << std::endl;
        removed = std::remove(gameObjects.begin(), gameObjects.end(), go);
        gameObjects.erase(removed);
    }

    /*if(numberOfCollisions != 0)
    {
        shiftDelta /= numberOfCollisions;
        glm::normalize(shiftDelta);

        pos += shiftDelta;
    }*/

    return pos;
}

bool Scene::intersectRaySegmentSphere(glm::vec3 o, glm::vec3 d, glm::vec3 so, float radius, glm::vec3 &ip)
{
    //we pass in d non-normalized to keep it's length
    //then we use that length later to compare the intersection point to make sure
    //we're within the actual ray segment
    auto l = (float)sqrt(pow(d.x,2) + pow(d.y, 2) + pow(d.z, 2));
    d /= l;

    glm::vec3 m = o - so;
    float b = glm::dot(m, d);
    float c = glm::dot(m, m) - radius;

    // Exit if r’s origin outside s (c > 0) and r pointing away from s (b > 0)
    if(c > 0.0f && b > 0.0f)
        return false;
    float discr = b*b - c;

    // A negative discriminant corresponds to ray missing sphere
    if(discr < 0.0f)
        return false;

    // Ray now found to intersect sphere, compute smallest t value of intersection
    float t = -b - sqrtf(discr);

    // If t is negative, ray started inside sphere so clamp t to zero
    if(t < 0.0f)
        t = 0.0f;
    ip = o + (d * t);

    //here's that last segment check I was talking about
    if(t > l)
        return false;

    return true;
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
	worldy = gameTerrain->GetVertexHeight(worldx + terrainPosMovement.x , worldz + terrainPosMovement.z);
	return glm::vec3(worldx, worldy, worldz);
}

void Scene::RunPlayer(View lens, float time, bool exit)
{
    if (loaded)
    {
        if (!exitScreen.exitScreenDisplay)
            gameObjects[playerInd]->Render(lens, time, gameRenderer);
    }
}