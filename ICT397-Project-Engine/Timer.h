#pragma once
class Timer
{
public:
	void UpdateTime(float time)
	{
		lastTime = curTime;
		curTime = time;
	}

	float GetDeltaTime()
	{
		return curTime - lastTime;
	}

	float curTime;
	float lastTime;
};

