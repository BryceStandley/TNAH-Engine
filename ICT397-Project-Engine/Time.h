#pragma once
class Time
{
public:
	Time()
	{
		lastFrame = 0;
	}

	void UpdateTime(float currentFrame)
	{
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
	}

	float DeltaTime()
	{
		return deltaTime;
	}

private:
	float deltaTime;
	float lastFrame;
};

