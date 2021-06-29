--player_default.lua
--Default player script if given script isnt found

check = true;
rotate = false;
bullet = true;
--model = "./res/models/weapons/Bennelli_M4-Texture.fbx";
model = "./res/models/weapons/Bennelli_M4.md2";
texture = "./res/models/weapons/Textures_Guns.png";
bulletModel = "./res/models/weapons/bullet.md2";
bulletTexture = "./res/models/weapons/Textures_Guns.png";
vertShader = "./res/shader/md2vert.vert";
fragShader = "./res/shader/md2frag.frag";

xRotOffset = 0;
yRotOffset = 0;
zRotOffset = 0;

yPosOffset = -0.02;

doubleDamage = {}

doubleDamage[1] = function (Player)
	Player:SetToken(false)
	Player:incrementTokensCollected()
	Player:increasePoints(50)
	Player:setDamage(Player:getDamage() * 2)

	Player:SetPrevInstanceToken("DoubleDamage")
	Player:SetInstanceToken("none")
end

doubleDamage[2] = function (Player)
	if string.match(Player:GetPrevInstanceToken(), "DoubleDamage") and Player:GetInstanceTimer() <= 0 then
		Player:ChangeState("main")
	end

	if string.match(Player:GetInstanceToken(), "DoubleDamage") and string.match(Player:GetPrevInstanceToken(), "DoubleDamage") then
       Player:ChangeState("DoubleDamage")
	end

	if string.match(Player:GetInstanceToken(), "DoublePoints") then
		Player:ChangeState("doublePoints")
	end

	if string.match(Player:GetInstanceToken(), "healthRefill") then 
		Player:ChangeState("healthRefill")
	end

	if string.match(Player:GetInstanceToken(), "SpeedUp") then 
		Player:ChangeState("speedBoost")
	end
end

doubleDamage[3] = function (Player)
	Player:setDamage(Player:getDamage() / 2)
end

healthRefill = {}

healthRefill[1] = function (Player)
	Player:SetToken(false)
	Player:incrementTokensCollected()
	Player:increasePoints(50)

	if Player:getHealth() < 100 then
		Player:setHealth(100);
	end
end

healthRefill[2] = function (Player)
	Player:ChangeState("main")
end

healthRefill[3] = function (Player)

end

speedBoost = {}

speedBoost[1] = function (Player)
	Player:SetToken(false)
	Player:incrementTokensCollected()
	Player:increasePoints(50)

	Player:SetPrevInstanceToken("SpeedUp")
	Player:SetInstanceToken("none")
end

speedBoost[2] = function (Player)
	if string.match(Player:GetPrevInstanceToken(), "SpeedUp") and Player:GetInstanceTimer() <= 0 then
		Player:SetInstanceSpeed(5.0)
		Player:ChangeState("main")
	else
		Player:SetInstanceSpeed(10.0)
	end

	
	if string.match(Player:GetInstanceToken(), "SpeedUp") and string.match(Player:GetPrevInstanceToken(), "SpeedUp") then
       Player:ChangeState("speedBoost")
	end

	if string.match(Player:GetInstanceToken(), "DoublePoints") then
		Player:ChangeState("doublePoints")
	end

	if string.match(Player:GetInstanceToken(), "healthRefill") then 
		Player:ChangeState("healthRefill")
	end

	if string.match(Player:GetInstanceToken(), "DoubleDamage") then 
		Player:ChangeState("doubleDamage")
	end
end

speedBoost[3] = function (Player)
	Player:SetInstanceSpeed(5.0)
end

death = {}

death[1] = function (Player)
	Player:setMultiplier(1)
end

death[2] = function (Player)

end

death[3] = function (Player)

end

doublePoints = {}

doublePoints[1] = function (Player)
	Player:SetToken(false)
	Player:incrementTokensCollected()
	Player:increasePoints(50)
	Player:setMultiplier(2)

	Player:SetPrevInstanceToken("DoublePoints")
	Player:SetInstanceToken("none")
end

doublePoints[2] = function (Player)
	if string.match(Player:GetPrevInstanceToken(), "DoublePoints") and Player:GetInstanceTimer() <= 0 then
		Player:SetInstanceSpeed(5)
		Player:ChangeState("main")
	end

	
	if string.match(Player:GetInstanceToken(), "DoublePoints") and string.match(Player:GetPrevInstanceToken(), "DoublePoints") then
       Player:ChangeState("doublePoints")
	end

	if string.match(Player:GetInstanceToken(), "SpeedUp") then
		Player:ChangeState("speedBoost")
	end

	if string.match(Player:GetInstanceToken(), "HealthRefill") then 
		Player:ChangeState("healthRefill")
	end

	if string.match(Player:GetInstanceToken(), "DoubleDamage") then 
		Player:ChangeState("doubleDamage")
	end
end

doublePoints[3] = function (Player)
	Player:setMultiplier(1)
end

global = {}

global[1] = function (Player)
	
end

global[2] = function (Player)
	if string.match(Player:GetInstanceToken(), "SpeedUp") and Player:GetToken() then
		Player:ChangeState("speedBoost")
	end

	if string.match(Player:GetInstanceToken(), "DoublePoints") and Player:GetToken() then
		Player:ChangeState("doublePoints")
	end

	if string.match(Player:GetInstanceToken(), "HealthRefill") and Player:GetToken() then
		Player:ChangeState("healthRefill")
	end

	if string.match(Player:GetInstanceToken(), "DoubleDamage") and Player:GetToken() then
		Player:ChangeState("doubleDamage")
	end

	if Player:getHealth() == 0 then
		Player:ChangeState("main")
	end
end

global[3] = function (Player)

end

mainState = {}

mainState[1] = function (Player)
	Player:SetToken(true)
end

mainState[2] = function (Player)

end

mainState[3] = function (Player)

end



