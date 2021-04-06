#include "Scene.h"
Scene::Scene(std::string name, Renderer * render)
{
	this->sceneName = name;
	gameRenderer = render;

	Init();
}


Scene::~Scene()
{
	delete[]gameRenderer;
	delete[]gameTerrain;
	delete[]gameSkybox;
	for (int i = gameObjects.size()-1; i > 0; i--)
		delete[]gameObjects[i];
	delete[]factory;
}

void Scene::Run(View lens, float time)
{
	//Terrain
	gameRenderer->BindTexture(gameTerrain->GetTextIds());
	Shader t = gameTerrain->GetShader();
	gameRenderer->SetShaderTerrain(t, lens);
	gameTerrain->SetShader(t);
	gameRenderer->RenderTerrain(gameTerrain->GetVAO(), gameTerrain->GetIndicesSize());

	//Skybox
	gameRenderer->SetShaderSkybox(gameSkybox->skyShader, lens);
	gameRenderer->RenderSkybox(gameSkybox->VAO, gameSkybox->texture);

	//Models
	for (int x = 0; x < gameObjects.size(); x++)
	{
		gameObjects[x]->Update(0.1);
		if (x != playerInd)
		{
			gameRenderer->SetShader(gameObjects[x]->GetShader(), lens);
			for (int i = 0; i < gameObjects[x]->GetModel().meshes.size(); i++)
			{
				Shader s = gameObjects[x]->GetShader();
				gameRenderer->RenderModel(s, gameObjects[x]->GenerateMatFourForMesh(i), gameObjects[x]->GetModel().meshes[i]);
				gameObjects[x]->SetShader(s);
			}
		}
	}

	//If game object is of type player
	UpdatePlayer(lens.GetPosition());
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


}

void Scene::UpdatePlayer(glm::vec3 position)
{
	glm::vec3 pos = position;
	float worldx, worldz;

	worldx = (pos.x / 100.0f) * (float)gameTerrain->getSize();
	worldz = (pos.z / 100.0f) * (float)gameTerrain->getSize();
	
	pos.y = 1.5f + ((gameTerrain->getAverageHeight((int)worldx, (int)worldz) / gameTerrain->getSize()) * 100.0f);

	if (gameTerrain->getAverageHeight((int)worldx, (int)worldz) >= 10.0f)
	{
		pos.x = gameObjects[playerInd]->GetPos().x;
		pos.y = gameObjects[playerInd]->GetPos().y;
		pos.z = gameObjects[playerInd]->GetPos().z;
	}
    pos = CheckSceneCollision(pos);

	gameObjects[playerInd]->SetPos(pos);
}

void Scene::MakeGameObject(std::string t, std::string modelName, std::string shaderV, std::string shaderF, float scale, float x, float y, float z, float speed)
{
	GameObject* newGameObject = factory->GetGameObject(t, modelName, shaderV, shaderF, scale, glm::vec3(x, y, z), speed);
	if (newGameObject != nullptr)
	{
		gameObjects.push_back(newGameObject);
	}
	else
	{
		std::cout << "ERROR::GAME_ASSET_FACTORY::TYPE_UNKNOWN" << std::endl;
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

glm::vec3 Scene::CheckSceneCollision(glm::vec3 pos)
{
    glm::vec3 player = gameObjects[playerInd]->GetPos();
    glm::vec3 playerSphereOrigin(pos.x, pos.y - 0.75f, pos.z);
    float playerSphereRadius = 2.0f;

    int numberOfCollisions = 0;
    glm::vec3 shiftDelta = glm::vec3(0,0,0);

    for(auto &go : gameObjects)
    {
        float distance = glm::distance(playerSphereOrigin, go->GetPos());
        if(go->GetTag() == BoundingBox::TOKEN && distance < playerSphereRadius) {std::cout << "Token Hit" << std::endl; continue;}
        if(go->GetTag() == BoundingBox::ENEMY && distance < playerSphereRadius) {std::cout << "Enemy Hit" << std::endl; continue;}
        if(go->GetTag() != BoundingBox::STATIC_OBJECT) continue;
        if(distance < playerSphereRadius)
        {
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