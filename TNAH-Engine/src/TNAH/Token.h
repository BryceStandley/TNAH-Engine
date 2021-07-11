#pragma once
#include "GameObject.h"
	/**
	 * @class Token
	 * @brief Abstract GameObject class for in game tokens
	 *
	 * @author Christopher Logan
	 * @version 01
	 * @date 25/03/2021
	 *
	 * @todo add functionality for the tokens
	 *
	 * @bugs none to be seen
	 *
	 **/
using namespace luabridge;
class TNAH_API Token : public GameObject
{
public:

		/*
		* @brief Parameterised Token constructor that takes various parameters 
		* @param p - represents the position vector
		* @param rot - represents the rotation vector
		* @param s - represents the token scale value
		* @param gameRenderer - a pointer to the renderer
		* @param script - a string that is a path to the token script
		*/
	Token(glm::vec3 p, glm::vec3 rot, float s, Renderer* gameRenderer, std::string script);
	
		/*
		* @brief Updates the game object with functionality
		* @param time - the time since the last frame (deltatime)
		*/
	void Update(float time);
	
		/*
		* @brief a function that is executed when a token is collected and removed
		*/
	virtual bool Kill();

		/**
		* @brief makes use of the view information and graphics renderer to render the token to the screen
		* @param lens - holds the information that allows you to project and view the model
		* @param time - represents deltatime, which is the difference between the previous frame and the current frame
		* @param gameRenderer - a pointer to the renderer which is used to render the enemy model
		*/
	void Render(View lens, float time, Renderer* gameRenderer);

private:
	std::string tokenType;
	float speed;
	float duration;
	glm::vec3 spin;
};

