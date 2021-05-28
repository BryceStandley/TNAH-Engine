#include "Player.h"

Player::Player(glm::vec3 p, glm::vec3 rot, float s, Renderer* gameRenderer, std::string script) : GameObject(p, rot, s, gameRenderer)
{
    SetScriptName(script);
	lua_State* L = LuaManager::getInstance().getLuaState();
    bool bull = false;

    if(!luaL_dofile(L, script.c_str()))
    {
        dd = getGlobal(L, "doubleDamage");
        refill = getGlobal(L, "healthRefill");
        speedBoost = getGlobal(L, "speedBoost");
        death = getGlobal(L, "death");
        dp = getGlobal(L, "doublePoints");
        global = getGlobal(L, "global");
        mainState = getGlobal(L, "mainState");

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

        if (bullet.isBool())
        {
            bull = bullet.cast<bool>();
        }

        if (mod.isString())
        {
            file = mod.cast<std::string>();
        }

        if (tex.isString())
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

        Model tempModel(file, gameRenderer, check, texture, true);
        SetModel(tempModel);

        Shader tempShader(vertS.c_str(), fragS.c_str());
        SetShader(tempShader);

        xRotationOffset = xr;
        yRotationOffset = yr;
        zRotationOffset = zr;

        yPositionOffset = yp;
        SetRotate(rotate);

        if (bull)
        {
            LuaRef bulletMod = getGlobal(L, "bulletModel");
            LuaRef bulletTex = getGlobal(L, "bulletTexture");

            std::string bulletModel;
            std::string bulletTexture;

            if (bulletMod.isString())
            {
                bulletModel = bulletMod.cast<std::string>();
            }

            if (bulletTex.isString())
            {
                bulletTexture = bulletTex.cast<std::string>();
            }

            Model tempBulletModel(bulletModel, gameRenderer, check, bulletTexture, true);
            bModel = tempBulletModel;
        }
        health = 100;

    }
    else if (!luaL_dofile(L, "./res/scripts/gameobjects/player_default.lua"))
    {
        dd = getGlobal(L, "doubleDamage");
        refill = getGlobal(L, "healthRefill");
        speedBoost = getGlobal(L, "speedBoost");
        death = getGlobal(L, "death");
        dp = getGlobal(L, "doublePoints");
        global = getGlobal(L, "global");
        mainState = getGlobal(L, "mainState");

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

        Model tempModel(file, gameRenderer, check, texture, true);
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

            Model tempBulletModel(bulletModel, gameRenderer, check, bulletTexture, true);
            bModel = tempBulletModel;
        }
        health = 100;
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
    SetState(SHOOT);

	if (Debugger::GetInstance()->debugToConsole) std::cout << xRotationOffset << " " << yRotationOffset << " " << zRotationOffset << " " << yPositionOffset << std::endl;
}

Player::Player(glm::vec3 p, glm::vec3 rot, float s, Renderer* gameRenderer, std::string script, float h, std::string state, int savedPoints, int savedTokens, int savedKills) : GameObject(p, rot, s, gameRenderer)
{
    SetScriptName(script);
	lua_State* L = LuaManager::getInstance().getLuaState();
    bool bull = false;

    if (!luaL_dofile(L, script.c_str()))
    {
        dd = getGlobal(L, "doubleDamage");
        refill = getGlobal(L, "healthRefill");
        speedBoost = getGlobal(L, "speedBoost");
        death = getGlobal(L, "death");
        dp = getGlobal(L, "doublePoints");
        global = getGlobal(L, "global");
        mainState = getGlobal(L, "mainState");

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

        if (bullet.isBool())
        {
            bull = bullet.cast<bool>();
        }

        if (mod.isString())
        {
            file = mod.cast<std::string>();
        }

        if (tex.isString())
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

        Model tempModel(file, gameRenderer, check, texture, true);
        SetModel(tempModel);

        Shader tempShader(vertS.c_str(), fragS.c_str());
        SetShader(tempShader);

        xRotationOffset = xr;
        yRotationOffset = yr;
        zRotationOffset = zr;

        yPositionOffset = yp;
        SetRotate(rotate);

        if (bull)
        {
            LuaRef bulletMod = getGlobal(L, "bulletModel");
            LuaRef bulletTex = getGlobal(L, "bulletTexture");

            std::string bulletModel;
            std::string bulletTexture;

            if (bulletMod.isString())
            {
                bulletModel = bulletMod.cast<std::string>();
            }

            if (bulletTex.isString())
            {
                bulletTexture = bulletTex.cast<std::string>();
            }

            Model tempBulletModel(bulletModel, gameRenderer, check, bulletTexture, true);
            bModel = tempBulletModel;
        }
        health = 100;

    }
    else if (!luaL_dofile(L, "./res/scripts/gameobjects/player_default.lua"))
    {
        dd = getGlobal(L, "doubleDamage");
        refill = getGlobal(L, "healthRefill");
        speedBoost = getGlobal(L, "speedBoost");
        death = getGlobal(L, "death");
        dp = getGlobal(L, "doublePoints");
        global = getGlobal(L, "global");
        mainState = getGlobal(L, "mainState");

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

        if (bullet.isBool())
        {
            bull = bullet.cast<bool>();
        }

        if (mod.isString())
        {
            file = mod.cast<std::string>();
        }

        if (tex.isString())
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

        Model tempModel(file, gameRenderer, check, texture, true);
        SetModel(tempModel);

        Shader tempShader(vertS.c_str(), fragS.c_str());
        SetShader(tempShader);

        xRotationOffset = xr;
        yRotationOffset = yr;
        zRotationOffset = zr;

        yPositionOffset = yp;
        SetRotate(rotate);

        if (bull)
        {
            LuaRef bulletMod = getGlobal(L, "bulletModel");
            LuaRef bulletTex = getGlobal(L, "bulletTexture");

            std::string bulletModel;
            std::string bulletTexture;

            if (bulletMod.isString())
            {
                bulletModel = bulletMod.cast<std::string>();
            }

            if (bulletTex.isString())
            {
                bulletTexture = bulletTex.cast<std::string>();
            }

            Model tempBulletModel(bulletModel, gameRenderer, check, bulletTexture, true);
            bModel = tempBulletModel;
        }
        health = 100;
    }
    else
    {
        std::cout << "ERROR::NO_PLAYER_SCRIPTS_FOUND" << std::endl;
    }

	playerFSM = new stateMachine<Player>(this);
	playerFSM->setCurrentState(&main_state::getInstance());
	playerFSM->setGlobalState(&glob_state::getInstance());
    health = h;
	SetType("player");
	Update(0.0f);
    SetState(IDLE);
    kills = savedKills;
    points = savedPoints;
    tokensCollected = savedTokens;

	if (Debugger::GetInstance()->debugToConsole) std::cout << xRotationOffset << " " << yRotationOffset << " " << zRotationOffset << " " << yPositionOffset << std::endl;
}

void Player::Update(float time)
{
	playerFSM->update();
 }

void Player::Reset()
{
	kills = 0;
	SetPos(glm::vec3((52.0f * 12) / 2, 4.0f, (52.0f * 12) / 2));
	points = 0;
	tokensCollected = 0;
	health = 100;
}

void Player::Render(View lens, float time, Renderer* gameRenderer)
{
    glm::vec3 pos = lens.GetPosition();
    pos.y -= 0.05;
    SetRotation(glm::vec3(lens.GetRotation().z , 180 + lens.GetRotation().x *-1, -1 * lens.GetRotation().y));
    Model temp = GetModel();
    Shader s = GetShader();
    bModel.Render(lens, s, pos, GetRotation(), GetScale(), GetRotate(), time, 0, gameRenderer, true);
    temp.Render(lens, s, pos, GetRotation(), GetScale(), GetRotate(), time, 0, gameRenderer, true);
    SetShader(s);
    SetModel(temp);
}

void Player::SetState(Md2Commands state)
{
    Model temp = GetModel();
    temp.SetState(state);
    SetModel(temp);
    bModel.SetState(state);
}

void Player::FireWeapon()
{
    SetState(SHOOT);
}

void Player::BackToIdle()
{
    SetState(IDLE);
}

void Player::ChangeState(std::string state)
{
    if (state == "doubleDamage")
    {
        getFSM()->changeState(&singleton<doubleDamage>::getInstance());
    }
    else if (state == "healthRefill")
    {
        getFSM()->changeState(&singleton<healthRefill>::getInstance());
    }
    else if (state == "speedBoost")
    {
        getFSM()->changeState(&singleton<SpeedUp>::getInstance());
    }
    else if (state == "doublePoints")
    {
        getFSM()->changeState(&singleton<doublePoints>::getInstance());
    }
    else if (state == "death")
    {
        getFSM()->changeState(&singleton<deathState>::getInstance());
    }
    else if (state == "main")
    {
        getFSM()->changeState(&singleton<main>::getInstance());
    }
    else if (state == "global")
    {
        getFSM()->changeState(&singleton<glob>::getInstance());
    }
}
