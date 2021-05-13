#pragma once
typedef float v3[3];

struct Md2Values
{
	int identify;
	int version;

	int skinWidth;
	int skinhHight;
	int frameSize;

	int numSkins;
	int numVerts;
	int numTex;
	int numTri;
	int numCmds;
	int numFrames;

	int ofsSkins;
	int ofsTex;
	int ofsTri;
	int ofsFrames;
	int ofsCmds;
	int ofsEnd;

};

struct Md2Vertex
{
	unsigned char verts[3];
	unsigned char light;

};

struct Md2Frame
{
	float scale[3];
	float translate[3];
	char name[16];
	Md2Vertex verts[1];
};

struct Md2Animation
{
	int firstFrame;
	int lastFrame;
	int fps;
};

typedef enum {
	STAND,
	RUN,
	WALK,
	ATTACK,
	PAIN_A,
	PAIN_B,
	PAIN_C,
	JUMP,
	FLIP,
	SALUTE,
	FALLBACK,
	WAVE,
	POINTING,
	CROUCH_STAND,
	CROUCH_WALK,
	CROUCH_ATTACK,
	CROUCH_PAIN,
	CROUCH_DEATH,
	DEATH_FALLBACK,
	DEATH,
	DEATH_FALLBACKSLOW,


	MAX_ANIMATIONS

} Md2Commands;

#include "Shader.h"
#include "OpenGL.h"
#include "Buffer.h"
#include "TextureLoader.h"
#include "Md2.h"
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include "Debugger.h"

class Md2
{
public:
	Md2() {}

	void LoadModel(const char* sFilename, const char* tFilename, const char* vShader, const char* fShader, Renderer* gameRenderer);

	void RenderModel(Md2State* animState, glm::mat4 proj, glm::mat4 view, glm::vec3 position, glm::vec3 rotation, float direction, Renderer * gameRenderer);

	Md2State StartAnimation(Md2Commands type);
	void UpdateAnimation(Md2State* animState, float fTimePassed, Renderer* gameRenderer);
	void PauseAnimation();
	void StopAnimation();
	glm::vec3 GetPos() { return position; }
	void setPos(glm::vec3 p) { position = p; }

	static Md2State animationList[21];
	unsigned int TextureFromFile(std::string path);
	Shader shader;
	Md2State GetState(Md2Commands state)
	{
		return StartAnimation(state);
	}
private:
	unsigned int modelVAO, VAO, VBO, EBO, textureId;

	glm::vec3 position;

	std::vector<unsigned int> uiFramesBuffer;
	std::vector<int> commands;
	Md2Values information;
	std::vector<std::vector<glm::vec3>> vertices;
	std::vector<std::vector<int>> normals;

	int number;
};

