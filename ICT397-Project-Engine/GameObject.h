#pragma once
#include "Model.h"
class GameObject
{
public:
	//void CheckCollisions();
	//virtual void OnCollision(GameObject &collisionObject);
	GameObject() { pos = glm::vec3(0, 0, 0); }
	//GameObject(glm::vec3 pos, float colSize, float objSize);
	void SetPos(glm::vec3 p) { pos = p; }
	//void SetScale(float size);
	//void SetSphereSIze(float size);
	glm::vec3 GetPos() const { return pos; }
	//float GetScale() const;
	//float GetSphereSize() const;
	Model model;
	Shader shader;
private:
	glm::vec3 pos;
};

