--enemy_zarlag.lua

check = true;
rotate = true;
alive = true;
weapon = true;

model = "./res/models/zarlag/tris.md2";
texture = "./res/models/zarlag/Zlwred.jpg";
weaponModel = "./res/models/zarlag/weapon.md2";
weaponTexture = "./res/models/zarlag/WEAPON.jpg";
vertShader = "./res/shader/md2vert.vert";
fragShader = "./res/shader/md2frag.frag";

health = 100;
ammo = 10;
distance = 25.0;
damage = 10;
accuracy = 0.15;

setup = function (Enemy)
	--print(Enemy:getDifficulty());
	if string.match(Enemy:getDifficulty(), "Hard") then
		distance = 200.0;
		Enemy:setHealth(150.0)
		Enemy:SetDamage(15)
		Enemy:SetAccuracy(0.25)
		print("hard")
	elseif string.match(Enemy:getDifficulty(), "Easy") then
		distance = 20.0;
		Enemy:setHealth(80.0)
		Enemy:SetDamage(5)
		Enemy:SetAccuracy(0.1)
		print("Easy")
	end
end


wander = {}

wander[1] = function (Enemy)
	Enemy:SetState(2)
end

wander[2] = function (Enemy)
	if Enemy:getToken() and Enemy:CheckPrevState("flee") then
		Enemy:incrementCheck()
	end
	
	wanderRadius = 5.0
	wanderDistance = 35.0
	wanderJitter = 1.0
	result = Enemy:LookDirection("enemy")
	Enemy:setWander(wanderRadius, wanderDistance, wanderJitter)
	if Enemy:Distance() > 10.0 and Enemy:Distance() < distance and not Enemy:getToken() then
		Enemy:SetMoving(false)
		Enemy:ChangeState("alert")	
	elseif Enemy:Distance() > 10.0 and Enemy:Distance() < distance and Enemy:getToken() then
		Enemy:SetMoving(false)
		Enemy:ChangeState("flee")
	elseif Enemy:GetMoving() then
		curPos = Enemy:GetPos()
		enemVel = Enemy:getEnemyVelocity()
		newPos = Enemy:getNewPos()
		if Enemy:moveTo(curPos, newPos, enemVel, Enemy:GetDeltaTime(), 0) then
			Enemy:SetMoving(false)
		else
			Enemy:setDirection(-result)
		end
	else 
		pos = Enemy:GetPos()
		enemVel = Enemy:getEnemyVelocity()
		Enemy:wander(pos, enemVel, Enemy:GetDeltaTime(), "Enemy")
		Enemy:setDirection(-result)
	end
end

wander[3] = function (Enemy)

end

alert = {}

alert[1] = function (Enemy)
	Enemy:SetState(12)
	Enemy:SendMessage(1, "enemy")
end

alert[2] = function (Enemy)
	result = Enemy:LookDirection("player")

	if Enemy:getTimer() < 100.0 then
		Enemy:incrementTimer()
	else
		Enemy:ChangeState("chase")
	end

	Enemy:setDirection(-result);
end

alert[3] = function (Enemy)
	Enemy:setTimer(0)
end

flee = {}

flee[1] = function (Enemy)
	Enemy:SetState(1)
end

flee[2] = function (Enemy)
	Enemy:incrementCheck();

	if not Enemy:getCheck() then
		Enemy:ChangeState("wander")
	end

	res = Enemy:LookDirection("playerOpp")

	if Enemy:Distance() > 10.5 and Enemy:Distance() < 25.0 and not Enemy:getToken() then
		Enemy:ChangeState("chase")
	elseif Enemy:Distance() < 10.5 and not Enemy:getToken() then
		Enemy:ChangeState("attack")
	elseif Enemy:Distance() > 25.0 then
		Enemy:ChangeState("wander")
	else
		pos = Enemy:GetPos()
		vel = Enemy:getEnemyVelocity()
		Enemy:evade(pos, Enemy:getCamPos(), vel, Enemy:getVelocity(), Enemy:GetDeltaTime(), "Player")
		Enemy:setDirection(-res)
	end
end

flee[3] = function (Enemy)

end

chase = {}

chase[1] = function (Enemy)
	Enemy:SetState(1)
end

chase[2] = function (Enemy)
	result = Enemy:LookDirection("player")

	if Enemy:Distance() < 10.0 then
		Enemy:ChangeState("attack")
	elseif Enemy:Distance() > distance then
		Enemy:ChangeState("wander")
	else 
		pos = Enemy:GetPos()
		vel = Enemy:getEnemyVelocity()

		Enemy:pursue(Enemy:getCamPos(), pos, Enemy:getVelocity(), vel, Enemy:GetDeltaTime(), 0.0, "Enemy")
	end
	Enemy:setDirection(-result)
end

chase[3] = function (Enemy)

end

attack = {}

attack[1] = function (Enemy)
	Enemy:SetState(3)
end

attack[2] = function (Enemy)

	res = Enemy:LookDirection("player")

	if Enemy:Distance() > 10.5 then
		Enemy:ChangeState("chase")
	else 
		Enemy:setDirection(-res)
	end
end

attack[3] = function (Enemy)

end

die = {}

die[1] = function (Enemy)
	if not Enemy:getDeathAnim() then
		Enemy:SetSate(20)
		Enemy:setDeathAnim(true)
		Enemy:ChangeState("die")
	else
		Enemy:SetSate(19)
	end
end

die[2] = function (Enemy)
	Enemy:SetKillFSM(true)
end

die[3] = function (Enemy)
	
end

global = {}

global[1] = function (Enemy)

end

global[2] = function (Enemy)
	if Enemy:getToken() and Enemy:Distance() < 25 and not Enemy:getGlobalFlag() then 
		Enemy:ChangeState("flee")
		Enemy:setGlobalFlag(true)
	end

	if not Enemy:isAlive() then
		Enemy:ChangeState("die")
	end
end

global[3] = function (Enemy)

end
