#pragma once
#include "Model.h"
class GameObject
{
public:
	void CheckCollisions();
	virtual void OnCollision(GameObject &collisionObject);
	GameObject();
	GameObject(glm::vec3 pos, float colSize, float objSize);
	void SetPos(glm::vec3 pos);
	void SetScale(float size);
	void SetSphereSIze(float size);
	glm::vec3 GetPos() const;
	float GetScale() const;
	float GetSphereSize() const;
	Model model;
private:
	float scale;
	float sphereSize;
	//Physics of some kind
};

