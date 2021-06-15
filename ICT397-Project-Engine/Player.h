#pragma once
#include "state.h"
#include "stateMachine.h"
#include "playerStates.h"
#include "Debugger.h"

	/**
	 * @class Player
	 * @brief Abstract GameObject class for the player
	 *
	 * @author Christopher Logan
	 * @version 01
	 * @date 25/03/2021
	 *
	 * @bugs none to be seen
	 * @todo need to add player fsm and functionality
	 * 
	 * @brief Added FSM and functionality 
	 * 
	 * @author Dylan Blereau
	 * @version 02
	 * @date 17/05/2021
	 * 
	 *
	 **/
using namespace luabridge;
class Player : public GameObject
{
public:
		/**
		* @brief Player constructor that takes various parameters
		* @param p - reperesents the position vector
		* @param rot - represents the rotation vector
		* @param s - represents the player scale
		* @param gameRenderer - a pointer to the game engine renderer
		* @param script - a string repesenting the path to the enemy lua script
		*/
	Player(glm::vec3 p, glm::vec3 rot, float s, Renderer* gameRenderer, std::string script);

		/**
		* @brief Player constructor that takes various parameters
		* @param p - reperesents the position vector
		* @param rot - represents the rotation vector
		* @param s - represents the player scale
		* @param gameRenderer - a pointer to the game engine renderer
		* @param script - a string repesenting the path to the enemy lua script
		* @param h - represents player health
		* @param state - represents the player state
		* @param savedPoints - refers to the value of saved points
		* @param saveTokens - refers to the value of saved tokens
		* @param savedKills - refers to the value of saved kills
		*/
	Player(glm::vec3 p, glm::vec3 rot, float s, Renderer* gameRenderer, std::string script, float h, std::string state, int savedPoints, int savedTokens, int savedKills);
	
		/**
		* @brief gets and returns the finite state machine of the player
		* @return stateMachine<Player>*
		*/
	stateMachine<Player>* getFSM()const { return playerFSM; }


		/*
		* @brief gets and returns the player health value
		* @return int 
		*/
	int getHealth() { return health; }

		/*
		* @brief sets the health value of the player
		* @param int h - refers to the value that health will be set to
		*/
	void setHealth(int h) { health = h; }

		/*
		* @brief gets and returns the player points value
		* @return int
		*/
	int getPoints() { return points; }

		/*
		* @brief increases the points value, multiplying the value passed in as a parameter by the current points multiplier
		* @param int p - refers to value that will be added onto the current points value
		*/
	void increasePoints(int p) {points += p * multiplier;}

		/*
		* @brief gets and returns the points multiplier value
		* @return int
		*/
	int getMultiplier() { return multiplier; }

		/*
		* @brief sets the points multiplier value
		* @param int m - refers to value you want to set the multiplier to
		*/
	void setMultiplier(int m) { multiplier = m; }

		/*
		* @brief gets and returns the player damage value
		* @return int
		*/
	int getDamage() { return damage; }

		/*
		* @brief sets the damage value
		* @param int d - refers to the value that damage will be set
		*/
	void setDamage(int d) { damage = d; }

		/*
		* @brief gets and returns the player kill count
		* @return int
		*/
	int getKills() { return kills; }


		/*
		* @brief increments the player kill count
		*/
	void incrementKillCount(){ kills++; }

		/*
		* @brief gets and returns the amount of tokens collected by the player
		* @return int
		*/
	int getTokensCollected() { return tokensCollected; }

		/*
		* @brief increments the tokens collected value
		*/
	void incrementTokensCollected() { tokensCollected++; }


		/// check if player has token or not 
	bool hasToken = true;


		/*
		* @breif Updates the game object with functionality
		* @param time - the time since the last frame (deltatime)
		*/
	void Update(float time);

		/**
		* @brief makes use of the view information and graphics renderer to render the player to the screen
		* @param lens - holds the information that allows you to project and view the model
		* @param time - represents deltatime, which is the difference between the previous frame and the current frame
		* @param gameRenderer - a pointer to the renderer which is used to render the enemy model
		*/
	virtual void Render(View lens, float time, Renderer* gameRenderer);

		/**
		* @brief sets the animation state to the value provided as a parameter
		* @param state - represents the animation state
		*/
	void SetState(Md2Commands state);


		/**
		* @brief sets the shooting animation when the weapon is fired
		*/
	void FireWeapon();

		/**
		* @brief sets the idle animation when the weapon is not being fired
		*/
	void BackToIdle();

		/**
		* @brief returns a string of data that is required for saving
		* @return std::string
		*/
	virtual std::string StreamValues()
	{
		return GetType() + " " + GetScriptName() + " " + std::to_string(GetScale()) + " " + std::to_string(GetPos().x) + " " + std::to_string(GetPos().y) + " " + std::to_string(GetPos().z) + " " + std::to_string(health) + " STATE" + " " + std::to_string(points) + " " + std::to_string(kills) + " " + std::to_string(tokensCollected) + "\n";
	}

	///Resets the player game object
	void Reset();
	
		/**
		* @brief Sets the token
		*/
	void SetToken(bool tok) { hasToken = tok; }
	
	
		/**
		* @brief Gets the if the player has the token
		*/
	bool GetToken() { return hasToken; }

		/**
		* @brief Sets the instance token for the manager
		*/
	void SetInstanceToken(std::string str) { singleton<Manager>::getInstance().token = str; }

		/**
		* @brief Returns the instance token
		*/
	std::string GetInstanceToken() { return singleton<Manager>::getInstance().token; }

		/**
		* @brief Gets the previous instance token
		*/
	std::string GetPrevInstanceToken() { return singleton<Manager>::getInstance().prevToken; }

		/**
		* @brief Sets the previous instance token
		*/
	void SetPrevInstanceToken(std::string str) { singleton<Manager>::getInstance().prevToken = str; }

		/**
		* @brief Gets the instance timer
		*/
	float GetInstanceTimer() { return singleton<Manager>::getInstance().timer; }

		/**
		* @brief Gets the instance speed
		*/
	void SetInstanceSpeed(float speed) { singleton<Manager>::getInstance().speed = speed; }

		/**
		* @brief Changes the state of the ai
		*/
	void ChangeState(std::string state);

	LuaRef dd = NULL;
	LuaRef refill = NULL;
	LuaRef speedBoost = NULL;
	LuaRef death = NULL;
	LuaRef dp = NULL;
	LuaRef global = NULL;
	LuaRef mainState = NULL;
private:
	
	///Player finite state machine
	stateMachine<Player>* playerFSM;

	///Player health 
	int health = 100;
	///Current points
	int points = 0;

	///Points multiplier
	int multiplier = 1;

	///Player damage
	int damage = 20;

	///Kills
	int kills = 0;

	///Tokens colleected
	int tokensCollected = 0;

	float xRotationOffset;
	float yRotationOffset;
	float zRotationOffset;
	float yPositionOffset;
    Model bModel;
};

