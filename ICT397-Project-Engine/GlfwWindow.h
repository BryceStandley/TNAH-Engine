#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Window.h"
#include <iostream>
#include "Callbacks.h"
#include "singleton.h"
#include "camera.h"
#include "Shader.h"
#include "Manager.h"
#include "Debugger.h"
#include "MainMenuGUI.h"

/**
 * @class GlfwWindow
 * @brief The abstracted window class that is used for the window facade.
 * This class holds all the Glfw window information inside of it and it is an abstract class
 * of Window. It is this way as it allows us to swap the potential window system if we ever wanted to
 * add DirectX or Vulkan. The class handles all aspects of the window, anything that would require it such
 * as size, inputs, camera, time, projections and window updates.
 *
 * @author Christopher Logan
 * @version 01
 * @date 15/03/2021
 *
 *
 * @bugs none to be seen
 *
 **/

class GlfwWindow : public Window
{
public:
		/**
		* @brief Default constructor
		*/
	GlfwWindow() {}

		/**
		* @brief Default destructor
		*/
	~GlfwWindow() { Terminate(); }

		/**
		* @brief Initilises the window class, setting the title height and width
		* @param title - The title of the window
		* @param h - The height of the window
		* @param w - The width of the window
		*/
	virtual void Init(std::string title, int h, int w);

		/**
		* @brief Calls the buffer from glfw
		*/
	virtual void Buffer();

		/**
		* @brief Holds the game input logic for the keyboard, uses the input variable to set the actual keys
		* @param deltaTime - Takes in delta time for the movement of the camera
		*/
	virtual void GameInput(float deltaTime);

		/**
		* @brief Sets the termination information for the class
		*/
	virtual void Terminate();

		/**
		* @brief Calls the frame buffer, in this case the glfw one
		*/
	virtual void FrameBuffer();
	
		/**
		* @brief Getter for the camera
		* @return camera
		*/
	virtual Camera GetCamera() { return camera; }

		/**
		* @brief 
		s the camera position
		*/
	virtual void UpdateCamera(glm::vec3 p) { camera.Position = p; }

		/**
		* @brief Sets mouse movmenet
		*/
	virtual void MouseMove();

		/**
		* @brief Getter for the lens
		* @return lens
		*/
	virtual View GetLens() { return lens; }

		/**
		* @brief Updates the window for things such as time, lens values
		*/
	virtual void Update();

		/**
		* @brief Getter for deltaTime
		* @return gameTime.DetaTime()
		*/
	virtual float GetTime() { return gametime.DeltaTime(); }

		/**
		* @brief Checks if the window is running still
		*/
	virtual bool Running();

		/**
		* @brief Gets the display value
		* @return exitDisplay
		*/
	virtual bool GetDisplay() { return exitDisplay; }

	float GetCurrentTime() { return (float)glfwGetTime(); }

	virtual bool GetWeaponFire() {return fireWeapon;}

	GLFWwindow* GetGameWindow() { return gameWindow; }

	glm::vec2 GetWindowSize() { return windowSize; }



private:	

		/**
		* @brief Calls glfw projection values
		*/
	void Projection();

		/**
		* @brief Calls the clear values from glfw
		*/
	void Clear();

		/**
		* @brief Calls the restart values from glfw
		*/
	void Restart();

		///If the exit display should be displayed
	bool exitDisplay = false;

		///If the press exit display can be displayed
	bool canPressExitDisplay = true;

    ///If the wireframe display should be displayed
    bool wireDisplay = false;

    ///If the press wireframe display can be displayed
    bool canPressWireDisplay = true;

    ///If the wireframe display should be displayed
    bool debugDisplay = false;

    ///If the press wireframe display can be displayed
    bool canPressDebugDisplay = true;

	bool canFireWeapon = false;

	bool fireWeapon = false;

	bool canPressPauseButton = false;

		//The game input manager
	Input gameInput;

		///The window
	GLFWwindow* gameWindow = nullptr;

		///Light positioning
	glm::vec3 lightPos;

		///The camera
	Camera camera;
		
		///Holds information that may be needed by other classes
	View lens;

		///Calulates deltaTime
	Time gametime;

	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;

		///The last position of x on the mouse
	float lastX;

		///The last position of y on the mouse
	float lastY;

		///If the mouse has been used yet
	float firstMouse = true;

	glm::vec2 windowSize;

};
