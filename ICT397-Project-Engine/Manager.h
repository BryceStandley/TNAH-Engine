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
	std::string prevToken = "none";
	bool fireWeapon = false;
	float weaponTimer = 0;
	float timer = 0;
	Difficulty difficulty = normal;
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

	void UpdateWeapon(float time)
	{
		if (weaponTimer <= 0)
		{
			fireWeapon = true;
			weaponTimer = 0;
		}
		else
		{
			weaponTimer -= time;
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

