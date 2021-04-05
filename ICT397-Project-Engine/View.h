#pragma once
#include <glm/glm.hpp>

	/**
	* @class View
	* @brief Holds matrix and position information to allow 
	* other parts of the engine to have access to this information,
	* without sending their whole classes
	*
	* @author Christoper Logan
	* @version 01
	* @date 22/03/2021 Christopher Logan, Started
	*
	*
	**/
class View
{
public:

		/**
		* @brief sets the projection matrix 
		* @param const p - represents the matrix that is assigned to the projection
		*/
	void SetProjection(const glm::mat4 p) { projection = p; }

		/**
		* @brief sets the view matrix
		* @param const v - represents the matrix that is assigned to the view
		*/
	void SetView(const glm::mat4 v) { view = v; }

		/**
		* @brief sets the models matrix
		* @param const m - represents the matrix that is assigned to the model
		*/
	void SetModel(const glm::mat4 m) { model = m; }

		/**
		* @brief sets the skyview matrix
		* @param const s - represents the matrix that is assigned to the skyview
		*/
	void SetSkyview(const glm::mat4 s) { skyview = s; }

		/**
		* @brief sets the position matrix
		* @param const p - represents the matrix that is assigned to the position
		*/
	void SetPosition(const glm::vec3 p) { position = p; }

		/**
		* @brief gets and returns the projection matrix
		* @returns glm::mat4 
		*/
	glm::mat4 GetProjection() { return projection; }
		
		/**
		* @brief gets and returns the view matrix
		* @returns glm::mat4
		*/
	glm::mat4 GetView() { return view; }

		/**
		* @brief gets and returns the model matrix
		* @returns glm::mat4
		*/
	glm::mat4 GetModel() { return model; }

		/**
		* @brief gets and returns the skyview matrix
		* @returns glm::mat4
		*/
	glm::mat4 GetSkyview() { return skyview; }

		/**
		* @brief gets and returns the position matrix
		* @returns glm::mat4
		*/
	glm::vec3 GetPosition() { return position; }

private:
	glm::mat4 projection;
	glm::mat4 view;
	glm::mat4 model;
	glm::mat4 skyview;
	glm::vec3 position;
};

