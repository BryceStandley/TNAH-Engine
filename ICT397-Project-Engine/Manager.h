#pragma once
#include<string>
class Manager
{
public:
	float speed = 5;
	std::string token = "none";
	std::string prevToken = "none";
	float timer = 0;

	void Update(float time)
	{
		if (timer <= 0)
		{
			token = "none";
			timer = 0;
		}
		else
		{
			timer -= time;
		}
	}
};

