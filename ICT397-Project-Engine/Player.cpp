#include "Player.h"

Player::Player(glm::vec3 p, glm::vec3 rot, float s, Renderer* gameRenderer, std::string script) : GameObject(p, rot, s, gameRenderer)
{
	lua_State* L = LuaManager::getInstance().getLuaState();
    bool bull = false;

    if(Debugger::GetInstance()->debugMD2ToConsole) std::cout << "Made it 1" << std::endl;

    if(!luaL_dofile(L, script.c_str()))
    {
        if(Debugger::GetInstance()->debugMD2ToConsole) std::cout << "Made it 2" << std::endl;
        LuaRef type = getGlobal(L, "check");
        LuaRef rot = getGlobal(L, "rotate");
        LuaRef bullet = getGlobal(L, "bullet");

        LuaRef mod = getGlobal(L, "model");
        LuaRef tex = getGlobal(L, "texture");
        LuaRef vert = getGlobal(L, "vertShader");
        LuaRef frag = getGlobal(L, "fragShader");

        LuaRef xRot = getGlobal(L, "xRotOffset");
        LuaRef yRot = getGlobal(L, "yRotOffset");
        LuaRef zRot = getGlobal(L, "zRotOffset");

        LuaRef yPos = getGlobal(L, "yPosOffset");

        std::string file;
        std::string vertS;
        std::string fragS;
        std::string texture;
        float xr = 0, yr = 0, zr = 0, yp = 0;
        bool check = false, rotate = false;

        if(Debugger::GetInstance()->debugMD2ToConsole) std::cout << "Made it 3" << std::endl;
        if (type.isBool())
        {
            check = type.cast<bool>();
        }

        if (rot.isBool())
        {
            rotate = rot.cast<bool>();
        }

        if(bullet.isBool())
        {
            bull = bullet.cast<bool>();
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

        if(tex.isString())
        {
            texture = tex.cast<std::string>();
        }

        if (xRot.isNumber())
        {
            xr = xRot.cast<float>();
        }

        if (yRot.isNumber())
        {
            yr = yRot.cast<float>();
        }

        if (zRot.isNumber())
        {
            zr = zRot.cast<float>();
        }

        if (yPos.isNumber())
        {
            yp = yPos.cast<float>();
        }
        if(Debugger::GetInstance()->debugMD2ToConsole) std::cout << "Made it 4 -> check = " << check << std::endl;
        Model tempModel(file, gameRenderer, check, texture, false);
        if(Debugger::GetInstance()->debugMD2ToConsole) std::cout << "Made it 4-5" << std::endl;
        SetModel(tempModel);
        if(Debugger::GetInstance()->debugMD2ToConsole) std::cout << "Made it 5" << std::endl;

        Shader tempShader(vertS.c_str(), fragS.c_str());
        SetShader(tempShader);

        xRotationOffset = xr;
        yRotationOffset = yr;
        zRotationOffset = zr;

        yPositionOffset = yp;
        SetRotate(rotate);
        if(Debugger::GetInstance()->debugMD2ToConsole) std::cout << "Made it 6" << std::endl;
        if(bull)
        {
            if(Debugger::GetInstance()->debugMD2ToConsole) std::cout << "Made it 7" << std::endl;
            LuaRef bulletMod = getGlobal(L, "bulletModel");
            LuaRef bulletTex = getGlobal(L, "bulletTexture");

            std::string bulletModel;
            std::string bulletTexture;

            if(bulletMod.isString())
            {
                bulletModel = bulletMod.cast<std::string>();
            }

            if(bulletTex.isString())
            {
                bulletTexture = bulletTex.cast<std::string>();
            }
            if(Debugger::GetInstance()->debugMD2ToConsole) std::cout << "Made it 8" << std::endl;
            Model tempBulletModel(bulletModel, gameRenderer, check, bulletTexture, false);
            bModel = tempBulletModel;
            if(Debugger::GetInstance()->debugMD2ToConsole) std::cout << "Made it 9" << std::endl;
        }


    }
    else if (!luaL_dofile(L, "./res/scripts/gameobjects/player_default.lua"))
    {
        std::cout << "Player script not found, loading default script" << std::endl;
        LuaRef type = getGlobal(L, "check");
        LuaRef rot = getGlobal(L, "rotate");
        LuaRef bullet = getGlobal(L, "bullet");

        LuaRef mod = getGlobal(L, "model");
        LuaRef tex = getGlobal(L, "texture");
        LuaRef vert = getGlobal(L, "vertShader");
        LuaRef frag = getGlobal(L, "fragShader");

        LuaRef xRot = getGlobal(L, "xRotOffset");
        LuaRef yRot = getGlobal(L, "yRotOffset");
        LuaRef zRot = getGlobal(L, "zRotOffset");

        LuaRef yPos = getGlobal(L, "yPosOffset");

        std::string file;
        std::string vertS;
        std::string fragS;
        std::string texture;
        float xr = 0, yr = 0, zr = 0, yp = 0;
        bool check = false, rotate = false;

        if (type.isBool())
        {
            check = type.cast<bool>();
        }

        if (rot.isBool())
        {
            rotate = rot.cast<bool>();
        }

        if(bullet.isBool())
        {
            bull = bullet.cast<bool>();
        }

        if (mod.isString())
        {
            file = mod.cast<std::string>();
        }

        if(tex.isString())
        {
            texture = tex.cast<std::string>();
        }

        if (vert.isString())
        {
            vertS = vert.cast<std::string>();
        }

        if (frag.isString())
        {
            fragS = frag.cast<std::string>();
        }

        if (xRot.isNumber())
        {
            xr = xRot.cast<float>();
        }

        if (yRot.isNumber())
        {
            yr = yRot.cast<float>();
        }

        if (zRot.isNumber())
        {
            zr = zRot.cast<float>();
        }

        if (yPos.isNumber())
        {
            yp = yPos.cast<float>();
        }

        Model tempModel(file, gameRenderer, check, texture, false);
        SetModel(tempModel);

        Shader tempShader(vertS.c_str(), fragS.c_str());
        SetShader(tempShader);

        xRotationOffset = xr;
        yRotationOffset = yr;
        zRotationOffset = zr;

        yPositionOffset = yp;
        SetRotate(rotate);

        if(bull)
        {
            LuaRef bulletMod = getGlobal(L, "bulletModel");
            LuaRef bulletTex = getGlobal(L, "bulletTexture");

            std::string bulletModel;
            std::string bulletTexture;

            if(bulletMod.isString())
            {
                bulletModel = bulletMod.cast<std::string>();
            }

            if(bulletTex.isString())
            {
                bulletTexture = bulletTex.cast<std::string>();
            }

            Model tempBulletModel(bulletModel, gameRenderer, check, bulletTexture, false);
            bModel = tempBulletModel;
        }
	}
	else
	{
		std::cout << "ERROR::NO_PLAYER_SCRIPTS_FOUND" << std::endl;
	}

	playerFSM = new stateMachine<Player>(this);
	playerFSM->setCurrentState(&main_state::getInstance());
	playerFSM->setGlobalState(&glob_state::getInstance());

	SetType("player");
	Update(0.0f);

	if (Debugger::GetInstance()->debugToConsole) std::cout << xRotationOffset << " " << yRotationOffset << " " << zRotationOffset << " " << yPositionOffset << std::endl;
}

void Player::Update(float time)
{

	playerFSM->update();
/*
	if (singleton<Manager>::getInstance().token == "SpeedUp") 
	{
		singleton<Manager>::getInstance().speed = 10;
		increasePoints(50);

	}
		
	else
		singleton<Manager>::getInstance().speed = 5;
    if(Debugger::GetInstance()->debugTokensToConsole) std::cout << "Token = " << singleton<Manager>::getInstance().token << ", Duration = " << singleton<Manager>::getInstance().timer << std::endl;
*/
 }

void Player::Render(View lens, float time, Renderer* gameRenderer)
{
    glm::vec3 pos = lens.GetPosition();
    pos.y += yPositionOffset;
    //SetRotation(glm::vec3(xRotatioonOffset + lens.GetRotation().x * -1, yRotatioonOffset + lens.GetRotation().y * -1, lens.GetRotation().z + zRotatioonOffset));

    SetRotation(glm::vec3(yRotationOffset + lens.GetRotation().y * -1, xRotationOffset + lens.GetRotation().x *-1, zRotationOffset + lens.GetRotation().z *-1));
    Model temp = GetModel();
    Shader s = GetShader();
    temp.Render(lens, s, pos, GetRotation(), GetScale(), GetRotate(), time, 0, gameRenderer);
    SetShader(s);
    SetModel(temp);
}