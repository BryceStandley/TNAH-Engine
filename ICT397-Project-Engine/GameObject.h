#pragma once
#include "Model.h"
#include "BoundingBox.h"
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
	GameObject() { rotation = glm::vec3(0, 0, 0); rotate = false; pos = glm::vec3(0, 0, 0); scale = 0.2; rotate = false; speed = 0; boundingBox = BoundingBox();}

		/**
		* @brief Constructor
		* @param p - The position
		* @param fixRot - The fixed rotation
		* @param rot - The new rotation
		* @param s - The scale
		*/
	GameObject(glm::vec3 p, glm::vec3 fixRot, glm::vec3 rot, float s) { pos = p; rotation = rot; scale = s; speed = 0; rotate = false; boundingBox = BoundingBox();}

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
	void SetShader(Shader s) { shader = s; }

		/**
		* @brief Set rotate bool
		* @param r - The new value
		*/
	void SetRotate(bool r) { rotate = r; }

		/**
		* @brief Sets the speed value
		* @param s - The new value
		*/
	void SetSpeed(float s) { speed = s; }

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
		* @brief Gets the speed value
		* @return speed
		*/
	float GetSpeed() { return speed; }

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
		* @brief Generates the matrix for the model, taking into account scale, rotation, position
		* @return mat4
		*/
	glm::mat4 GenerateMatFour();

		/**
		* @brief Generate the matrix for the model times the matrix for mesh i
		* @param i - the point to the mesh
		* @return mat4
		*/
	glm::mat4 GenerateMatFourForMesh(int i);

		/**
		* @brief Gets the model
		* @return model
		*/
	Model GetModel() { return model; }

		/**
		* @brief Gets the shader
		* @return shader
		*/
	Shader GetShader() { return shader; }

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
    BoundingBox::CollisionTag GetTag(){return tag;}

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


private:
	Model model;
	Shader shader;
	bool rotate;
	std::string name;
	std::string type;
	float speed;
	glm::vec3 pos;
	glm::vec3 rotation;
	float scale;
    BoundingBox::CollisionTag tag;
	BoundingBox boundingBox;
};

