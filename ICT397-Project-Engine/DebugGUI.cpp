#include "DebugGUI.h"

DebugGUI::DebugGUI(std::string scriptPath)
{
    //load in debug ui from lua script
    lua_State* L = LuaManager::getInstance().getLuaState();

    if (!luaL_dofile(L, scriptPath.c_str()))
    {
        luabridge::LuaRef fr = getGlobal(L, "fps");
        luabridge::LuaRef con = getGlobal(L, "console");
        luabridge::LuaRef col = getGlobal(L, "collisions");
        luabridge::LuaRef wep = getGlobal(L, "weapons");
        luabridge::LuaRef anim = getGlobal(L, "animations");
        luabridge::LuaRef md = getGlobal(L, "md2");
        luabridge::LuaRef tok = getGlobal(L, "token");
        luabridge::LuaRef fs = getGlobal(L, "fsm");

        if (fr.isBool()) { fps = fr.cast<bool>(); }
        if (con.isBool()) { console = con.cast<bool>(); }
        if (col.isBool()) { collisions = col.cast<bool>(); }
        if (wep.isBool()) { weapons = wep.cast<bool>(); }
        if (anim.isBool()) { animations = anim.cast<bool>(); }
        if (md.isBool()) { md2 = md.cast<bool>(); }
        if (tok.isBool()) { token = tok.cast<bool>(); }
        if (fs.isBool()) { fsm = fs.cast<bool>(); }

        Debugger::GetInstance()->debugToConsole = console;
        Debugger::GetInstance()->debugCollisionsToConsole = collisions;
        Debugger::GetInstance()->debugWeapons = weapons;
        Debugger::GetInstance()->debugAnimationsToConsole = animations;
        Debugger::GetInstance()->debugMD2ToConsole = md2;
        Debugger::GetInstance()->debugFSMToConsole = fsm;
        Debugger::GetInstance()->debugTokensToConsole = token;
    }
    else
    {
        std::cout << "DebugGUI.cpp::Error Reading script file, Defaults loaded" << std::endl;
        fps = true;
        console = false;
        collisions = false;
        weapons = false;
        animations = false;
        md2 = false;
        token = false;
        fsm = false;


        Debugger::GetInstance()->debugToConsole = console;
        Debugger::GetInstance()->debugCollisionsToConsole = collisions;
        Debugger::GetInstance()->debugWeapons = weapons;
        Debugger::GetInstance()->debugAnimationsToConsole = animations;
        Debugger::GetInstance()->debugMD2ToConsole = md2;
        Debugger::GetInstance()->debugFSMToConsole = fsm;
        Debugger::GetInstance()->debugTokensToConsole = token;
    }
}


void DebugGUI::Draw()
{
    std::string windowName = "Debug";

    //Set window size and position before creating the window context from imgui
    ImGui::SetNextWindowSize(ImVec2(0, 0));
    //ImGui::SetNextWindowPos(ImVec2((float)w->SCR_WIDTH + (float)((float)w->SCR_WIDTH - (ImGui::GetWindowWidth() * 1.1f)), 0), true);
    ImGui::SetNextWindowPos(ImVec2(0, 0), true);
    ImGui::Begin(windowName.c_str()); //Create the window

    ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
	ImGui::Checkbox("Sticky FPS", &Debugger::GetInstance()->stickyFPSCounter);
    ImGui::Checkbox("Debug Basics to Console", &Debugger::GetInstance()->debugToConsole);
    ImGui::Checkbox("Debug Collisions to Console", &Debugger::GetInstance()->debugCollisionsToConsole);
    ImGui::Checkbox("Debug FSM to Console", &Debugger::GetInstance()->debugFSMToConsole);
    ImGui::Checkbox("Debug Weapons to Console", &Debugger::GetInstance()->debugWeapons);
    ImGui::Checkbox("Debug Animations to Console", &Debugger::GetInstance()->debugAnimationsToConsole);
    ImGui::Checkbox("Debug MD2 to Console", &Debugger::GetInstance()->debugMD2ToConsole);
	ImGui::Checkbox("Debug Tokens to Console", &Debugger::GetInstance()->debugTokensToConsole);
    ImGui::Checkbox("Debug Player Position to Screen", &Debugger::GetInstance()->debugPlayerPos);
    //Add ImGui::Text() fields here to add more data to the debug window


    ImGui::End();
}