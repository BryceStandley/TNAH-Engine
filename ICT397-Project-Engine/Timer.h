#pragma once
class Timer
{
public:

		/**
		* @brief takes in the current frame and performs per-frame time logic to update the time
		* @param time - the time value used in the per-frame time logic
		*/
	void UpdateTime(float time)
	{
		lastTime = curTime;
		curTime = time;
	}

		/**
		* @brief gets and returns the value of delta
		* @return float
		*/
	float GetDeltaTime()
	{
		return curTime - lastTime;
	}

	float curTime;
	float lastTime;
};

