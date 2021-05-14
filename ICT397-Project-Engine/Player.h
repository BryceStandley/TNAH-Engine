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
 *
 * @bugs none to be seen
 *
 **/
using namespace luabridge;
class Player : public GameObject
{
public:
		/*
		* @breif Default constructor
		*/
	Player(glm::vec3 p, glm::vec3 rot, float s, Renderer* gameRenderer, std::string script);

	stateMachine<Player>* getFSM()const { return playerFSM; }

	int getHealth() { return health; }

	void setHealth(int h) { health = h; }

	int getPoints() { return points; }

	void increasePoints(int p) {
		points += p * multiplier;
		//multiplier = 0;
	}

	int getMultiplier() { return multiplier; }

	void setMultiplier(int m) { multiplier = m; }

	int getDamage() { return damage; }
	void setDamage(int d) { damage = d; }


	bool hasToken = true;
	int token = 0;

	//void decreaseHealth(int h) {h}



		/*
		* @breif Updates the game object with functionality
		* @param time - the time since the last frame (deltatime)
		*/
	void Update(float time);

	virtual void Render(View lens, float time, Renderer* gameRenderer);

	void SetSate(Md2Commands state);

private:
	
	stateMachine<Player>* playerFSM;

	int health = 100;
	int points = 0;
	int multiplier = 1;
	int damage = 50;


	float xRotationOffset;
	float yRotationOffset;
	float zRotationOffset;
	float yPositionOffset;
    Model bModel;
};

