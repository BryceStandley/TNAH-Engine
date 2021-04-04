#pragma once
#include "Model.h"
class GameObject
{
public:
	//void CheckCollisions();
	//virtual void OnCollision(GameObject &collisionObject);
	GameObject() { pos = glm::vec3(0, 0, 0); scale = 0.2; rotate = false; }
	GameObject(glm::vec3 p, glm::vec3 fixRot, glm::vec3 rot, float s) { pos = p; rotation = rot; scale = s; }
	//GameObject(glm::vec3 pos, float colSize, float objSize);
	void SetRotation(glm::vec3 r) { rotation = r; }
	void SetPos(glm::vec3 p) { pos = p; }
	void SetScale(float size) { scale = size; }
	//void SetSphereSIze(float size);
	glm::vec3 GetPos() const { return pos; }
	glm::vec3 GetRotation() const { return rotation; }
	float GetScale() const { return scale; }
	//float GetSphereSize() const;
	glm::mat4 GenerateMatFour();
	glm::mat4 GenerateMatFourForMesh(int i);
	Model model;
	Shader shader;
	bool rotate;
private:
	glm::vec3 pos;
	glm::vec3 rotation;
	float scale;
};

