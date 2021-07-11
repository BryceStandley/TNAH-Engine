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
	SHOOT,
	IDLE,


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


	/**
	 * @class Md2
	 * @brief A class responsible for loading, rendering and animating MD2 models
	 * @author Dylan Blereau
	 * 
	 * @version 01
	 * @date 10/04/21
	 *
	 **/
class TNAH_API Md2
{
public:

		/**
		* @brief Default constructor
		*/
	Md2() {}

		/**
		* @brief Loads the MD2 model
		* @param sFilename - represents a pointer to the model file path
		* @param tFilename - represents a pointer the path of the models texture file
		* @param vShader - represents a pointer to the models vertex shader
		* @param fShader - represents a pointer to the models fragment shader
		* @param gameRenderer - represents a pointer to the game engine renderer
		*/
	void LoadModel(const char* sFilename, const char* tFilename, const char* vShader, const char* fShader, Renderer* gameRenderer);

		/**
		* @brief Renders the MD2 Model
		* @param animState - represents a pointer to the models animation state
		* @param proj - represents the projection matrix
		* @param view - represents the view matrix
		* @param genFour - represents the genFour matrix
		* @param direction - represents the direction the model is facing
		* @param gameRenderer - represents a pointer to the game engine renderer
		*/
	void RenderModel(Md2State* animState, glm::mat4 proj, glm::mat4 view, glm::mat4 genFour, float direction, Renderer * gameRenderer);

		/**
		* @brief Renders the MD2 Model
		* @param animState - represents a pointer to the models animation state
		* @param proj - represents the projection matrix
		* @param view - represents the view matrix
		* @param pos - represents the models position vector
		* @param rot - represents the models rotation vector
		* @param direction - represents the direction the model is facing
		* @param gameRenderer - represents a pointer to the game engine renderer
		*/
	void RenderModel(Md2State* animState, glm::mat4 proj, glm::mat4 view, glm::vec3 pos, glm::vec3 rot, float direction, Renderer* gameRenderer);

		/**
		* @brief starts the models animation specified by the type given as a parameter
		* @param type - the animation command type
		* @return Md2State
		*/
	Md2State StartAnimation(Md2Commands type);

		/**
		* @brief updates the animation
		* @param animState - represents a pointer to the models animation state
		* @param fTimePassed - represents the time passed between frames
		* @param gameRenderer - represents a pointer to the game engine renderer
		*/
	void UpdateAnimation(Md2State* animState, float fTimePassed, Renderer* gameRenderer);


		/**
		* @brief gets and returns the position of the model
		* @return glm::vec3
		*/
	glm::vec3 GetPos() { return position; }

		/**
		* @brief sets the position of the model to the position specified as a parameter
		* @param p - reperesents the position that the model position will be set to
		*/
	void setPos(glm::vec3 p) { position = p; }

		/**
		* @brief an array containing all the frames required for each MD2 animation
		* @return Md2State
		*/
	static Md2State animationList[23];

		/**
		* @brief gets and loads a texture from a specified file path
		* @param path - represents the file path to the texture
		* @return unsigned int
		*/
	unsigned int TextureFromFile(std::string path);

		///shader object
	Shader shader;

		/**
		* @brief gets the state provided as a parameter and uses it to start the models animation
		* @param state - reperesents the model state
		* @return Md2State
		*/
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

