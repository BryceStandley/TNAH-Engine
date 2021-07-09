#include "DebugGUI.h"

DebugGUI::DebugGUI(std::string scriptPath)
{
    //load in debug ui from lua script
    lua_State* L = LuaManager::getInstance().getLuaState();
	debugger = Debugger::GetInstance();

    if (!luaL_dofile(L, scriptPath.c_str()))
    {
    	
    	
        luabridge::LuaRef con = getGlobal(L, "console");
        luabridge::LuaRef col = getGlobal(L, "collisions");
        luabridge::LuaRef wep = getGlobal(L, "weapons");
        luabridge::LuaRef anim = getGlobal(L, "animations");
        luabridge::LuaRef md = getGlobal(L, "md2");
        luabridge::LuaRef tok = getGlobal(L, "token");
        luabridge::LuaRef fs = getGlobal(L, "fsm");
	    luabridge::LuaRef logPath = getGlobal(L, "logPath");
	    luabridge::LuaRef logT = getGlobal(L, "logType");
	    luabridge::LuaRef noC = getGlobal(L, "noClip");

        if (con.isBool()) { console = con.cast<bool>(); }
        if (col.isBool()) { collisions = col.cast<bool>(); }
        if (wep.isBool()) { weapons = wep.cast<bool>(); }
        if (anim.isBool()) { animations = anim.cast<bool>(); }
        if (md.isBool()) { md2 = md.cast<bool>(); }
        if (tok.isBool()) { token = tok.cast<bool>(); }
        if (fs.isBool()) { fsm = fs.cast<bool>(); }
        if(logPath.isString()) {logFilePath = logPath.cast<std::string>();}
        if(logT.isNumber()) { logType = logT.cast<int>(); }
	    if (noC.isBool()) { noClip = noC.cast<bool>(); }

        debugger->debugToConsole = console;
	    debugger->debugCollisionsToConsole = collisions;
	    debugger->debugWeapons = weapons;
	    debugger->debugAnimationsToConsole = animations;
	    debugger->debugMD2ToConsole = md2;
	    debugger->debugFSMToConsole = fsm;
	    debugger->debugTokensToConsole = token;
	    debugger->logFilePath = logFilePath;
	    debugger->noClip = noClip;

	    switch (logType)
	    {
		    case 0:
			    debugger->debugInfoToLogFile = true;
			    debugger->debugWarningToLogFile = false;
			    debugger->debugEngineToLogFile = false;
			    debugger->debugErrorsToLogFile = false;
			    debugger->type = Debugger::LogType::INFO;
			    break;
		    case 1:
			    debugger->debugWarningToLogFile = true;
			    debugger->debugInfoToLogFile = false;
			    debugger->debugEngineToLogFile = false;
			    debugger->debugErrorsToLogFile = false;
			    debugger->type = Debugger::LogType::WARNING;
			    break;
		    case 2:
			    debugger->debugEngineToLogFile = true;
			    debugger->debugWarningToLogFile = false;
			    debugger->debugInfoToLogFile = false;
			    debugger->debugErrorsToLogFile = false;
			    debugger->type = Debugger::LogType::ENGINE;
			    break;
		    case 3:
			    debugger->debugErrorsToLogFile = true;
			    debugger->debugEngineToLogFile = false;
			    debugger->debugWarningToLogFile = false;
			    debugger->debugInfoToLogFile = false;
			    debugger->type = Debugger::LogType::ERROR;
			    break;
		    case 4:
			    debugger->debugEngineToLogFile = true;
			    debugger->debugWarningToLogFile = true;
			    debugger->debugInfoToLogFile = true;
			    debugger->debugErrorsToLogFile = true;
			    debugger->type = Debugger::LogType::ALL;
			    break;
		    default:
			    debugger->debugEngineToLogFile = true;
			    debugger->debugWarningToLogFile = false;
			    debugger->debugInfoToLogFile = false;
			    debugger->debugErrorsToLogFile = false;
			    debugger->type = Debugger::LogType::ENGINE;
			    break;
	    }



    }
    else
    {
        std::cout << "DebugGUI.cpp::Error Reading script file, Defaults loaded" << std::endl;
        console = false;
        collisions = false;
        weapons = false;
        animations = false;
        md2 = false;
        token = false;
        fsm = false;
        noClip = false;


	    debugger->debugToConsole = console;
	    debugger->debugCollisionsToConsole = collisions;
	    debugger->debugWeapons = weapons;
	    debugger->debugAnimationsToConsole = animations;
	    debugger->debugMD2ToConsole = md2;
	    debugger->debugFSMToConsole = fsm;
	    debugger->debugTokensToConsole = token;
	    debugger->logFilePath = logFilePath;
	    debugger->noClip = noClip;
    }

    if(debugger->renderColliders)
    {
    	PhysicsManager::GetInstance()->GetPhysicsWorld()->setIsDebugRenderingEnabled(true);
    }
}


void DebugGUI::Draw()
{
	static const char* logTypes[]{"INFO", "WARNING", "ENGINE", "ERROR", "ALL"};
	static int selectedType = 2;


    std::string windowName = "Debug";

    //Set window size and position before creating the window context from imgui
    ImGui::SetNextWindowSize(ImVec2(0, 0));
    //ImGui::SetNextWindowPos(ImVec2((float)w->SCR_WIDTH + (float)((float)w->SCR_WIDTH - (ImGui::GetWindowWidth() * 1.1f)), 0), true);
    ImGui::SetNextWindowPos(ImVec2(0, 0), true);
    ImGui::Begin(windowName.c_str()); //Create the window

    ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
	ImGui::Checkbox("Sticky FPS", &debugger->stickyFPSCounter);
    ImGui::Checkbox("Debug Basics to Console", &debugger->debugToConsole);
    ImGui::Checkbox("Debug Collisions to Console", &debugger->debugCollisionsToConsole);
    ImGui::Checkbox("Debug FSM to Console", &debugger->debugFSMToConsole);
    ImGui::Checkbox("Debug Weapons to Console", &debugger->debugWeapons);
    ImGui::Checkbox("Debug Animations to Console", &debugger->debugAnimationsToConsole);
    ImGui::Checkbox("Debug MD2 to Console", &debugger->debugMD2ToConsole);
	ImGui::Checkbox("Debug Tokens to Console", &debugger->debugTokensToConsole);
    ImGui::Checkbox("Debug Player Position to Screen", &debugger->debugPlayerPos);
    ImGui::Checkbox("No Camera Clip", &debugger->noClip);
    ImGui::Combo("LogType", &selectedType, logTypes, IM_ARRAYSIZE(logTypes));

    if(ImGui::Button("Toggle Render Colliders"))
    {
	    PhysicsManager::GetInstance()->SetDebugPhysicsRendering(!PhysicsManager::GetInstance()->GetPhysicsWorld()->getIsDebugRenderingEnabled());
    }


	switch (selectedType)
	{
		case 0:
			debugger->debugInfoToLogFile = true;
			debugger->debugWarningToLogFile = false;
			debugger->debugEngineToLogFile = false;
			debugger->debugErrorsToLogFile = false;
			debugger->type = Debugger::LogType::INFO;
			break;
		case 1:
			debugger->debugWarningToLogFile = true;
			debugger->debugInfoToLogFile = false;
			debugger->debugEngineToLogFile = false;
			debugger->debugErrorsToLogFile = false;
			debugger->type = Debugger::LogType::WARNING;
			break;
		case 2:
			debugger->debugEngineToLogFile = true;
			debugger->debugWarningToLogFile = false;
			debugger->debugInfoToLogFile = false;
			debugger->debugErrorsToLogFile = false;
			debugger->type = Debugger::LogType::ENGINE;
			break;
		case 3:
			debugger->debugErrorsToLogFile = true;
			debugger->debugEngineToLogFile = false;
			debugger->debugWarningToLogFile = false;
			debugger->debugInfoToLogFile = false;
			debugger->type = Debugger::LogType::ERROR;
			break;
		case 4:
			debugger->debugEngineToLogFile = true;
			debugger->debugWarningToLogFile = true;
			debugger->debugInfoToLogFile = true;
			debugger->debugErrorsToLogFile = true;
			debugger->type = Debugger::LogType::ALL;
			break;
		default:
			debugger->debugEngineToLogFile = true;
			debugger->debugWarningToLogFile = false;
			debugger->debugInfoToLogFile = false;
			debugger->debugErrorsToLogFile = false;
			debugger->type = Debugger::LogType::ENGINE;
			break;
	}


    ImGui::End();
}