#pragma once
#include "Model.h"
/**
 * @class GameObject
 * @brief Class that holds the main information of a game object, that is abstracted for more specific reasons
 *
 * @author Christopher Logan
 * @version 01
 * @date 25/03/2021
 *
 * @todo Add collisions
 *
 * @bugs none to be seen
 *
 **/
class GameObject
{
public:
		/**
		* @brief  Default constructor
		*/
	GameObject() { pos = glm::vec3(0, 0, 0); scale = 0.2; rotate = false; speed = 0; }

		/**
		* @brief Constructor
		* @param p - The position
		* @param fixRot - The fixed rotation
		* @param rot - The new rotation
		* @param s - The scale
		*/
	GameObject(glm::vec3 p, glm::vec3 fixRot, glm::vec3 rot, float s) { pos = p; rotation = rot; scale = s; speed = 0; }
	virtual void Update(float time);
	void SetSpeed(float s) { speed = s; }
	void SetRotation(glm::vec3 r) { rotation = r; }
	void SetPos(glm::vec3 p) { pos = p; }
	void SetScale(float size) { scale = size; }
	float GetSpeed() { return speed; }
	glm::vec3 GetPos() const { return pos; }
	glm::vec3 GetRotation() const { return rotation; }
	float GetScale() const { return scale; }
	glm::mat4 GenerateMatFour();
	glm::mat4 GenerateMatFourForMesh(int i);
	Model model;
	Shader shader;
	bool rotate;
	void SetType(std::string t) { type = t; }
	std::string GetType(){ return type; }
private:
	std::string type;
	float speed;
	glm::vec3 pos;
	glm::vec3 rotation;
	float scale;
};

