#pragma once
#include <string>
#include "Terrain.h"
#include "Input.h"
#include "camera.h"
#include "View.h"
#include "Time.h"
#include "Scene.h"

class Window
{
public:
		/**
		* @brief Initilises the window class, setting the title height and width
		* @param title - The title of the window
		* @param h - The height of the window
		* @param w - The width of the window
		*/
	virtual void Init(std::string title, int h, int w) { }

		/**
		* @brief Calls the buffer
		*/
	virtual void Buffer() = 0;

		/**
		* @brief Holds the game input logic for the keyboard, uses the input variable to set the actual keys
		* @param deltaTime - Takes in delta time for the movement of the camera
		*/
	virtual void GameInput(float deltaTime) {}


		/**
		* @brief Sets the termination information for the class
		*/
	virtual void Terminate() {}

		/**
		* @brief Calls the frame buffer
		*/
	virtual void FrameBuffer() {}

		/**
		* @brief Getter for the camera
		* @return camera
		*/
	virtual Camera GetCamera() { Camera c(glm::vec3(0, 0, 0)); return c; }

		/**
		* @brief Updates the camera position
		*/
	virtual void UpdateCamera(glm::vec3 p) {}

		/**
		* @brief Sets mouse movmenet
		*/
	virtual void MouseMove() {}

		/**
		* @brief Getter for the lens
		* @return lens
		*/
	virtual View GetLens() { return View(); }

		/**
		* @brief Updates the window for things such as time, lens values
		*/
	virtual void Update() {}

		/**
		* @brief Getter for deltaTime
		* @return gameTime.DetaTime()
		*/
	virtual float GetTime() { return 0; }


		/**
		* @brief Checks if the window is running still
		*/
	virtual bool Running() { return false; }

		/**
		* @brief Gets the display value
		* @return exitDisplay
		*/
	virtual bool GetDisplay() { return false; }

    virtual void SetRefWindow(Window* w){}
};