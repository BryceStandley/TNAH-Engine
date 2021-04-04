#pragma once
#include <glm/glm.hpp>
class View
{
public:

	void SetProjection(const glm::mat4 p) { projection = p; }
	void SetView(const glm::mat4 v) { view = v; }
	void SetModel(const glm::mat4 m) { model = m; }
	void SetSkyview(const glm::mat4 s) { skyview = s; }
	void SetPosition(const glm::vec3 p) { position = p; }

	glm::mat4 GetProjection() { return projection; }
	glm::mat4 GetView() { return view; }
	glm::mat4 GetModel() { return model; }
	glm::mat4 GetSkyview() { return skyview; }
	glm::vec3 GetPosition() { return position; }

private:
	glm::mat4 projection;
	glm::mat4 view;
	glm::mat4 model;
	glm::mat4 skyview;
	glm::vec3 position;
};

