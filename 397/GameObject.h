#pragma once
#include "Model.h"
#include "BoundingBox.h"
#include "Input.h"
#include "Debugger.h"
#include "Telegram.h"
#include "Manager.h"
#include "singleton.h"
#include <reactphysics3d/reactphysics3d.h>

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
using namespace tnah;
class TNAH_API GameObject
{
public:
		/**
		* @brief  Default constructor
		*/
	GameObject() { rotation = glm::vec3(0, 0, 0); rotate = false; pos = glm::vec3(0, 0, 0); scale = 0.2; rotate = false; boundingBox = BoundingBox();}

		/**
		* @brief Constructor
		* @param p - The position
		* @param fixRot - The fixed rotation
		* @param rot - The new rotation
		* @param s - The scale
		*/
	GameObject(glm::vec3 p, glm::vec3 rot, float s, Renderer* gameRenderer) { pos = p; rotation = rot; scale = s; rotate = false; boundingBox = BoundingBox();}

		/**
		* @brief Updates the classes functionality
		* @param time - The time between frames
		*/
	virtual void Update(float time);

		/**
		* @brief Sets a new model
		* @param m - The new value
		*/
	void SetModel(Model m) { model = m; }

		/**
		* @brief Set new shader
		* @param s - The new value
		*/
	void SetShader(tnah::Shader s) { shader = s; }

		/**
		* @brief Set rotate bool
		* @param r - The new value
		*/
	void SetRotate(bool r) { rotate = r; }

		/**
		* @brief Sets the rotation value
		* @param r - The new value
		*/
	void SetRotation(glm::vec3 r) { rotation = r; }

		/**
		* @brief Sets the position
		* @param p - The new value
		*/
	void SetPos(glm::vec3 p) { pos = p; }

		/**
		* @brief Sets the scale value
		* @param size - The new value
		*/
	void SetScale(float size) { scale = size; }

		/**
		* @brief Gets the position value
		* @return pos
		*/
	glm::vec3 GetPos() const { return pos; }

		/**
		* @brief Gets the rotation value
		* @return rotation
		*/
	glm::vec3 GetRotation() const { return rotation; }

		/**
		* @brief Gets the scale value
		* @return scale
		*/
	float GetScale() const { return scale; }

		/**
		* @brief Gets the model
		* @return model
		*/
	Model GetModel() { return model; }

		/**
		* @brief Gets the shader
		* @return shader
		*/
	tnah::Shader GetShader() { return shader; }

		/**
		* @brief Sets the type of object
		* @param t - The type
		*/
	void SetType(std::string t) { type = t; }

		/**
		* @brief Gets the type of object
		* @return type
		*/
	std::string GetType(){ return type; }

		 /**
		 * @brief Sets gameobject's bounding box object
		 * @param b
		 */
	void SetBoundingBox(BoundingBox b){boundingBox = b;}

		 /**
		 * @brief Gets a gameobjec's boundingbox object
		 * @return BoundingBox
		 */
    BoundingBox GetBoundingBox(){return boundingBox;}


		 /**
		 * @brief Sets tag of a given object
		 * @param t
		 */
    void SetCollisionTag(BoundingBox::CollisionTag t){tag = t;}

		 /**
		 * @brief Gets the objects tag
		 * @return tag
		 */
    BoundingBox::CollisionTag* GetTag(){return &tag;}

		 /**
		 * @brief Sets the name of a game object
		 * @param n
		 */
    void SetName(std::string n) {name = n;}

		 /**
		 * @brief Gets the name of a Gameobject
		 * @return string name
		 */
    std::string GetName(){return name;}

		 /**
		 * @brief Renders the game object
		 * @param lens - The lens values for projection, positons, ect
		 * @param time - The deltatime value
		 * @param gameRenderer - the renderer pointer itself
		 */
	virtual void Render(View lens, float time, Renderer* gameRenderer);

		 /**
		 * @brief Gets the rotate bool
		 * @return true if the object needs to be rotated when rendering
		 */
	bool GetRotate() { return rotate; }

		 /**
		 * @brief Gets the id
		 * @return the game object id
		 */
	int GetId() { return id; }

		 /**
		 * @brief Sets the id
		 * @param i - the id to be set
		 */
	void SetId(int i) { id = i; }

		 /**
		 * @brief Handles messages from other game objects
		 * @return false by default
		 */
	virtual bool handleMessage(const Telegram message){ return false; }

		 /**
		 * @brief Kill information used in other game objects
		 * @return false by default
		 */
	virtual bool Kill(){ return false; }

		 /**
		 * @brief Gets the script name
		 * @return scriptName
		 */
	std::string GetScriptName() const { return scriptName; }

		 /**
		 * @brief Sets the script name
		 * @param name - The script name being set
		 */
	void SetScriptName(const std::string name) { scriptName = name; }

		 /**
		 * @brief Returns the streamed values for the game object
		 * @return streamed Values of the game object
		 */
	virtual std::string StreamValues();

	rp3d::Collider* collider;
	rp3d::RigidBody* rigidBody;

private:
	///The game objects id
	int id;
		///The model for the object and its meshes
	Model model;

		///The shader for the game object
	Shader shader;

		///If the object needs aditional rotations
	bool rotate;

		///The name of the object
	std::string name;

		///The type of object it is
	std::string type;


	///The rotation of the object
	glm::vec3 rotation;

		///The scale of the object
	float scale;

		///The colliding tag of the object
    BoundingBox::CollisionTag tag;

		///The bounding box for the object
	BoundingBox boundingBox;

		///The name for the script used for the game object
	std::string scriptName;



protected:
///The position of the pobject
glm::vec3 pos;
};

