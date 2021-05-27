--scene1.lua
--6/04/21 Christopher Logan
--07/04/2021 Bryce Standley - Added for loops for placing objects on the terrain
-- Format cs:MakeGameObject(type, "modelfolder", "vertexshader", "fragmentshader", scale, x, y, z, speed);
--print("Scene 1 script loaded")

playerX = (52 * 12) / 2;
playerZ = (52 * 12) / 2;

cs:MakeGameObject("player", "./res/scripts/gameobjects/player_default.lua", 0.075, playerX, 3.5, playerZ);

--Make this static object invisible to the plyer
cs:MakeGameObject("static",  "./res/scripts/gameobjects/static_tree3.lua", 0.005, -100, 1.2, -100);

minX = 120;
maxX = 430;
minZ = minX;
maxZ = maxX;

for i = 0, 1
do
    x = math.random(minX, maxX)
    z = math.random(minZ, maxZ)
    cs:MakeGameObject("enemy",  "./res/scripts/gameobjects/enemy_zarlag.lua", 0.05, x, 1.2, z);   
end
cs:MakeGameObject("water",  "./res/scripts/gameobjects/static_water.lua", 0.05, playerX, 0.5, playerZ);

y = 1--Y value for all tokens
for i = 0, 2
do
    x = math.random(minX, maxX)
    z = math.random(minZ, maxZ)
    cs:MakeGameObject("token",  "./res/scripts/gameobjects/token_doublepoints.lua", 0.005, x, y, z);
    x = math.random(minX, maxX)
    z = math.random(minZ, maxZ)
    cs:MakeGameObject("token", "./res/scripts/gameobjects/token_speedup.lua", 0.005, x, y, z);
    x = math.random(minX, maxX)
    z = math.random(minZ, maxZ)
    cs:MakeGameObject("token",  "./res/scripts/gameobjects/token_healthrefill.lua", 0.005, x, y, z);
    x = math.random(minX, maxX)
    z = math.random(minZ, maxZ)
    cs:MakeGameObject("token",  "./res/scripts/gameobjects/token_doubledmg.lua", 0.005, x, y, z);
	
	
end

--These loops dont check if there is a model already in its place
--Make 10 Yellow Trees with random positions
y = 0
for i = 0, 10
do
    x = math.random(minX, maxX)
    z = math.random(minZ, maxZ)
    cs:MakeGameObject("static", "./res/scripts/gameobjects/static_tree3.lua", 0.04,x, y, z);
end

--Make 10 Red Trees with random positions
for i = 0, 10
do
    x = math.random(minX, maxX)
    z = math.random(minZ, maxZ)
    cs:MakeGameObject("static",  "./res/scripts/gameobjects/static_tree2.lua", 0.04,x, y, z);
end

for i = 0, 10
do
    x = math.random(minX, maxX)
    z = math.random(minZ, maxZ)
    cs:MakeGameObject("static",  "./res/scripts/gameobjects/static_tree1.lua", 0.04,x, y, z);
end

y = 0
--Make 10 stones with random positions
for i = 0, 15
do
    x = math.random(minX, maxX)
    z = math.random(minZ, maxZ)
    cs:MakeGameObject("static",  "./res/scripts/gameobjects/static_stone2.lua", 0.02, x, y, z);
end

--Make 10 stones with random positions
for i = 0, 15
do
    x = math.random(minX, maxX)
    z = math.random(minZ, maxZ)
    cs:MakeGameObject("static",  "./res/scripts/gameobjects/static_stone1.lua", 0.02, x, y, z);
end
