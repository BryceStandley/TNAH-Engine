#pragma once
#include "GameObject.h"

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

class Player : public GameObject
{
public:
		/*
		* @breif Default constructor
		*/
	Player() :GameObject(){ Update(0.0f);}

		/*
		* @breif Updates the game object with functionality
		* @param time - the time since the last frame (deltatime)
		*/
	void Update(float time);

	virtual void Render(View lens, float time, Renderer* gameRenderer)
	{
		SetPos(lens.GetPosition());
		std::cout << "lens rotatations xyz -> " << lens.GetRotation().x << " " << lens.GetRotation().y << " " << lens.GetRotation().z << std::endl;
		SetRotation(glm::vec3(0.0f, lens.GetRotation().x, 0.0f));
		Model temp = GetModel();
		Shader s = GetShader();
		temp.Render(lens, s, GetPos(), GetRotation(), GetScale(), false, time, 0, gameRenderer);
		SetShader(s);
		SetModel(temp);
	}
};

