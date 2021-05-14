#pragma once
#include<string>
class Manager
{
public:
	float speed = 5;
	std::string token = "none";
	float timer = 0;

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
};

