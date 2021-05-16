#pragma once
#include<string>

typedef enum
{
	easy,
	normal,
	hard
} Difficulty;
class Manager
{
public:
	float speed = 5;
	std::string token = "none";
	float timer = 0;
	Difficulty difficulty = normal;
	void Update(float time)
	{
		if (timer <= 0)
		{
			//prevToken = token;
			token = "none";
			timer = 0;
		}
		else
		{
			timer -= time;
		}
	}

	void Reset()
	{
		speed = 5;
		token = "none";
		timer = 0;
		difficulty = normal;
	}
};

