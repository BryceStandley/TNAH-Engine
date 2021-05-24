--scene1.lua
--6/04/21 Christopher Logan
--07/04/2021 Bryce Standley - Added for loops for placing objects on the terrain
-- Format cs:MakeGameObject(type, "modelfolder", "vertexshader", "fragmentshader", scale, x, y, z, speed);
--print("Scene 1 script loaded")

cs:MakeGameObject("player", "./res/scripts/gameobjects/player_default.lua", 0.075, 153, 3.5, 153);
cs:MakeGameObject("static",  "./res/scripts/gameobjects/static_tree3.lua", 0.005, 40, 1.2, 40);



for i = 0, 10
do
    x = math.random(40, 180)
    z = math.random(40, 180)
    cs:MakeGameObject("enemy",  "./res/scripts/gameobjects/enemy_zarlag.lua", 0.05, x, 1.2, z);   
end
cs:MakeGameObject("water",  "./res/scripts/gameobjects/static_water.lua", 0.05, 50, 0.5, 50);

y = 1--Y value for all tokens
for i = 0, 2
do
    x = math.random(40, 280)
    z = math.random(40, 280)
    cs:MakeGameObject("token",  "./res/scripts/gameobjects/token_doublepoints.lua", 0.005, x, y, z);
    x = math.random(40, 280)
    z = math.random(40, 280)
    cs:MakeGameObject("token", "./res/scripts/gameobjects/token_speedup.lua", 0.005, x, y, z);
    x = math.random(40, 280)
    z = math.random(40, 280)
    cs:MakeGameObject("token",  "./res/scripts/gameobjects/token_healthrefill.lua", 0.005, x, y, z);
    x = math.random(40, 280)
    z = math.random(40, 280)
    cs:MakeGameObject("token",  "./res/scripts/gameobjects/token_doubledmg.lua", 0.005, x, y, z);
	
	
end

--These loops dont check if there is a model already in its place
--Make 10 Yellow Trees with random positions
y = -0.2
for i = 0, 10
do
    x = math.random(40, 280)
    z = math.random(40, 280)
    cs:MakeGameObject("static", "./res/scripts/gameobjects/static_tree3.lua", 0.04,x, y, z);
end

--Make 10 Red Trees with random positions
for i = 0, 10
do
    x = math.random(40, 280)
    z = math.random(40, 280)
    cs:MakeGameObject("static",  "./res/scripts/gameobjects/static_tree2.lua", 0.04,x, y, z);
end

for i = 0, 10
do
    x = math.random(40, 280)
    z = math.random(40, 280)
    cs:MakeGameObject("static",  "./res/scripts/gameobjects/static_tree1.lua", 0.04,x, y, z);
end

y = -0.2
--Make 10 stones with random positions
for i = 0, 15
do
    x = math.random(40, 280)
    z = math.random(40, 280)
    cs:MakeGameObject("static",  "./res/scripts/gameobjects/static_stone2.lua", 0.02, x, y, z);
end

--Make 10 stones with random positions
for i = 0, 15
do
    x = math.random(40, 280)
    z = math.random(40, 280)
    cs:MakeGameObject("static",  "./res/scripts/gameobjects/static_stone1.lua", 0.02, x, y, z);
end