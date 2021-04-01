#pragma once
#include <string>
#include "Terrain.h"
#include "Input.h"
#include "camera.h"
class Window
{
public:
	virtual void Init(std::string title, int h, int w) { }
	virtual void Buffer() = 0;
	virtual bool GameInput(float deltaTime) { return false; }
	virtual void Terminate() {}
	virtual void Clear() {}
	virtual void FrameBuffer() {}
	virtual void Projection() {}
	virtual void Projection(const glm::mat4& view, const glm::mat4& projection) {}
	virtual void SetShader(Shader shader) {}
	virtual void SetShaderSkybox(Shader shader) {}
	virtual void SetShaderTerrain(Shader shader) {}
	virtual void Restart() {}
	virtual Camera GetCamera() { Camera c(glm::vec3(0, 0, 0)); return c; }
	virtual void MouseMove() {}

private:
	Input gameInput;	
	Terrain *t;
};

