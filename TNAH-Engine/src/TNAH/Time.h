#pragma once

	/**
	* @class Time
	* @brief Time class is responsible for managing the time between frames
	*
	* @author Christoper Logan
	* @version 01
	* @date 12/03/2021 Christopher Logan, Started
	*
	*
	**/
class TNAH_API Time
{
public:

		/**
		* @brief default constructor used to initialise lastframe variable
		*/
	Time()
	{
		lastFrame = 0;
	}

		/**
		* @brief takes in the current frame and performs per-frame time logic to update the time 
		* @param currentFrame - represents the current frame being rendered
		*/
	void UpdateTime(float currentFrame)
	{
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
	}

		/**
		* @brief gets and returns the value of delta
		* @return float
		*/
	float DeltaTime()
	{
		return deltaTime;
	}

private:
		/// time between the current frame and the last frame
	float deltaTime;
	float lastFrame;
};

