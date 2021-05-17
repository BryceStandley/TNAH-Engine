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
    gameObjects.clear();
    factory->ResetFactory();
    singleton<Manager>::getInstance().Reset();
    entityMan::getInstance().ClearEntitys();
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
            std::cout << "WOORLD::RUNNING" << std::endl;
        }

        FindPlayerIndice();

        if (gameObjects.size() > 0)
        {
            for (int i = 0; i < gameObjects.size(); i++)
            {
                if (gameObjects[i]->GetType() == "enemy")
                    entityMan::getInstance().RegisterEntity(gameObjects[i]);
            }
        }

        loaded = true;
    }
}

void Scene::LoadSaveFile()
{
    if (!loaded)
    {
        std::ifstream file("./res/save.sav");
        if (file.is_open())
        {
            std::string type;

            while (file >> type)
            {
                if (type == "player")
                {
                    std::string script, state;
                    float scale, x, y, z, health;
                    file >> script >> scale >> x >> y >> z >> health >> state;
                    std::cout << script << " " << scale << " " << x << " " << y << " " << z << " " << health << " " << state << std::endl;
                    MakeSaveGameObject(type, script, scale, x, y, z, health, 0, state);
                }
                else if (type == "enemy")
                {
                    std::string script, state;
                    float scale, x, y, z, health, ammo;
                    file >> script >> scale >> x >> y >> z >> health >> ammo >> state;
                    std::cout << script << " " << scale << " " << x << " " << y << " " << z << " " << health << " " << ammo << " " << state << std::endl;
                    MakeSaveGameObject(type, script, scale, x, y, z, health, ammo, state);
                }
                else if (type == "token")
                {
                    std::string script;
                    float scale, x, y, z;
                    file >> script >> scale >> x >> y >> z;
                    std::cout << script << " " << scale << " " << x << " " << y << " " << z << std::endl;
                    MakeSaveGameObject(type, script, scale, x, y, z, 0, 0, "");
                }
                else if (type == "static")
                {
                    std::string script;
                    float scale, x, y, z;
                    file >> script >> scale >> x >> y >> z;
                    std::cout << script << " " << scale << " " << x << " " << y << " " << z << std::endl;
                    MakeSaveGameObject(type, script, scale, x, y, z, 0, 0, "");
                }
                else if (type == "water")
                {
                    float scale, x, y, z;
                    file >> scale >> x >> y >> z;
                    std::cout << "Water " << scale << " " << x << " " << y << " " << z << std::endl;
                    MakeSaveGameObject(type, "", scale, x, y, z, 0, 0, "");
                }
            }
        }

        FindPlayerIndice();

        if (gameObjects.size() > 0)
        {
            for (int i = 0; i < gameObjects.size(); i++)
            {
                if (gameObjects[i]->GetType() == "enemy")
                    entityMan::getInstance().RegisterEntity(gameObjects[i]);
            }
        }

        loaded = true;
    }
}

void Scene::Run(View lens, float time, bool exit)
{
    if (exitScreen.exitScreenDisplay)
    {
        //exitScreen.Render(gameRenderer, lens);

        endScreenGUI->Draw();
    }
    else
    {
        singleton<Manager>::getInstance().Update(time);
        singleton<Manager>::getInstance().UpdateWeapon(time);
        gameRenderer->BindTexture(gameTerrain->GetTextIds());
        Shader t = gameTerrain->GetShader();
        gameRenderer->SetShaderTerrain(t, lens);
        gameTerrain->SetShader(t);
        gameRenderer->RenderTerrain(gameTerrain->GetVAO(), gameTerrain->GetIndicesSize());

            //Skybox
            gameRenderer->SetShaderSkybox(gameSkybox->skyShader, lens);
            gameRenderer->RenderSkybox(gameSkybox->VAO, gameSkybox->texture);

            std::vector<GameObject*> gameObjectsToRemoveFromScene;
            //Models
            for (int x = 0; x < gameObjects.size(); x++)
            {
                gameObjects[x]->Update(0.1);
                if (x != playerInd)
                {
                    gameObjects[x]->Render(lens, time, gameRenderer);
                    if (gameObjects[x]->GetType() == "enemy")
                    {
                        UpdateGameObject(gameObjects[x]->GetPos(), x);
                        if (gameObjects[x]->Kill())
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
                removed = std::remove(gameObjects.begin(), gameObjects.end(), go);
            }

            //if the player is firing, fire the weapon duh
            if (playerWeapon.firingWeapon && playerWeapon.canFireWeapon)
            {
                playerWeapon.firingWeapon = false;
                singleton<Manager>::getInstance().weaponTimer = 5.0f / 17.0f;
                singleton<Manager>::getInstance().fireWeapon = false;
                playerWeapon.canFireWeapon = false;
                Player* p = (Player*)gameObjects[playerInd];
                p->FireWeapon();
                FireWeapon(gameObjects[playerInd]->GetPos(), lens.GetForward(), 10.0f);
            }

            //if the timer is 0 and we can fire again
            if (singleton<Manager>::getInstance().weaponTimer <= 0)
            {
                Player* p = (Player*)gameObjects[playerInd];
                p->BackToIdle();
                playerWeapon.canFireWeapon = true;
            }

    }
    //GameUI

    if (gameGui) { gameGui->Draw((Player*)gameObjects[playerInd]); }


	//If game object is of type player
	UpdatePlayer(lens.GetPosition(), lens.GetRotation());
}

void Scene::Init()
{
	gameTerrain = new Terrain();
	gameTerrain->Init();	
	gameTerrain->setTextures();

	gameTerrain->generateTerrain();
	gameSkybox = new Skybox();
	//gameSkybox = new Skybox("./res/images/skybox/right.jpg", "./res/images/skybox/left.jpg", "./res/images/skybox/top.jpg", "./res/images/skybox/bottom.jpg", "./res/images/skybox/front.jpg", "./res/images/skybox/back.jpg", "./res/shader/skybox_vert.txt", "./res/shader/skybox_frag.txt");
	factory = new GameAssetFactory(gameRenderer);
	gameRenderer->TerrainSetup(gameTerrain->GetTotalData(), gameTerrain->GetIndicies(), gameTerrain->VAO, gameTerrain->VBO, gameTerrain->EBO);
	gameRenderer->SkyboxSetup(gameSkybox->GetSkyVerts(), gameSkybox->GetCubeFaces(), gameSkybox->VAO, gameSkybox->VBO, gameSkybox->texture, gameSkybox->skyShader);

	exitScreen.Init("./res/models/group/photo.fbx", gameRenderer);

    gameGui = new GameGUI("./res/scripts/menus/game.lua");
    endScreenGUI = new EndScreenGUI("./res/scripts/menus/endScreen.lua");
}


void Scene::UpdatePlayer(glm::vec3 position, glm::vec3 rotation)
{
    if(position == gameObjects[playerInd]->GetPos()) return;

    position.y = WorldToTerrainPosition(position, true).y + 1.5f;

	if (position.y >= 10.0f)
	{
        position.x = gameObjects[playerInd]->GetPos().x;
        position.y = gameObjects[playerInd]->GetPos().y;
        position.z = gameObjects[playerInd]->GetPos().z;
	}

    position = CheckSceneCollision(position);

	gameObjects[playerInd]->SetPos(position);
}

void Scene::UpdateGameObject(glm::vec3 position, int i)
{
    position = EnemyObstacleAvoidance(gameObjects[i], position);

    position.y = WorldToTerrainPosition(position, true).y + 1.2f;

    if (position.y >= 10.0f)
    {
        position.x = gameObjects[i]->GetPos().x;
        position.y = gameObjects[i]->GetPos().y;
        position.z = gameObjects[i]->GetPos().z;
    }

    gameObjects[i]->SetPos(position);
}

void Scene::MakeGameObject(std::string t, std::string script, float scale, float x, float y, float z)
{
    //Check the terrain height to make sure the object isn't under the terrain;
    if(t != "water") y += WorldToTerrainPosition(glm::vec3(x,y,z), true).y;

	GameObject* newGameObject = factory->GetGameObject(t, script, scale, glm::vec3(x, y, z));
	if (newGameObject != nullptr)
	{
		gameObjects.push_back(newGameObject);
	}
	else
	{
		if(Debugger::GetInstance()->debugToConsole) std::cout << "Scene.cpp::ERROR::GAME_ASSET_FACTORY::TYPE_UNKNOWN" << std::endl;
	}
}

void Scene::MakeSaveGameObject(std::string t, std::string script, float scale, float x, float y, float z, float health, float ammo, std::string state)
{
    //Check the terrain height to make sure the object isn't under the terrain;
    if (t != "water") y += WorldToTerrainPosition(glm::vec3(x, y, z), true).y;

    GameObject* newGameObject = factory->GetGameObjectSave(t, script, scale, glm::vec3(x, y, z), health, ammo, state);
    if (newGameObject != nullptr)
    {
        gameObjects.push_back(newGameObject);
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
        while(glm::distance(newPosition, go->GetPos()) < 2.0f)
        {
            newPosition.x += 0.5f;
        }
    }
    return newPosition;

}

void Scene::FireWeapon(glm::vec3 weaponStartPos, glm::vec3 forward, float fireDistance)
{
    //Raycasting would be super good right now but we can use a makeshift raycast here instead

    //trigger animation
    //find a position vector from the player to a set distance forward from the camera
    //Check if there was a enemy anywhere along the vector between the player and the end point of the ray
    //stop checking if we hit a enemy even if were not at the end
    //deal damage to the enemy
    //refresh the fire timer


    playerWeapon.canFireWeapon = true;
    glm::vec3 directionVector = forward * fireDistance;
    glm::vec3 finalEndPoint = weaponStartPos + directionVector;
    bool enemyHit = false;
    float i = 1;
    while(i < fireDistance)
    {
        glm::vec3 point = weaponStartPos + (forward * i);

        for(auto* go : gameObjects)
        {
            if(go->GetTag() == BoundingBox::ENEMY && glm::distance(go->GetPos(), point) < 0.5f)
            {
                //hit the enemy, trigger damage
                if(Debugger::GetInstance()->debugWeapons) std::cout << "Scene.cpp::INFO::Player Shot Enemy!" << std::endl;
                enemyHit = true;
                break;
            }
        }
        if(enemyHit) break;

        i += 0.1f;
    }
    //reset some sort of firerate timer

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
        //if(go->GetTag() == BoundingBox::ENEMY && distance < playerSphereRadius) {
          //  if(Debugger::GetInstance()->debugCollisionsToConsole) std::cout << "Scene.cpp::INFO::Enemy GameObject - " << go->GetName() << " Hit" << std::endl;
            //gameObjectsToRemoveFromScene.emplace_back(go);
            //if(Debugger::GetInstance()->debugToConsole) std::cout << "MODEL REMOVED" << std::endl;
            //continue;
        //}
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

glm::vec3 Scene::WorldToTerrainPosition(glm::vec3 p, bool average)
{
    float worldx, worldz, worldToTerrainScaleFactor;
    worldToTerrainScaleFactor = 5.12;
    worldx = p.x * worldToTerrainScaleFactor;
    worldz = p.z * worldToTerrainScaleFactor;
    if(average) {p.y = (gameTerrain->getAverageHeight((int)worldx, (int)worldz) / worldToTerrainScaleFactor);}
    else {p.y = (gameTerrain->getHeight((int)worldx, (int)worldz) / worldToTerrainScaleFactor);}
    return p;
}

void Scene::RunPlayer(View lens, float time, bool exit)
{
    if (loaded)
    {
        if (!exitScreen.exitScreenDisplay)
            gameObjects[playerInd]->Render(lens, time, gameRenderer);
    }
}