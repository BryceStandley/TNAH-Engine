#pragma once
#include "GameObject.h"
	 /**
	 * @class Static
	 * @brief Abstract GameObject class for static game objects
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
class TNAH_API Static : public GameObject
{
public:

		/*
		* @brief Parameterised Static constructor that takes various parameters
		* @param p - represents the position vector
		* @param rot - represents the rotation vector
		* @param s - represents the token scale value
		* @param gameRenderer - a pointer to the renderer
		* @param script - a string that is a path to the static script
		*/
	Static(glm::vec3 p, glm::vec3 rot, float s, Renderer* gameRenderer, std::string script);
	
		/**
		* @brief Update function that updates the functionality
		* @param time - the time since the last frame
		*/
	void Update(float time);
};

