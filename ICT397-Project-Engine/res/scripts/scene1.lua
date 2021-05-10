--scene1.lua
--6/04/21 Christopher Logan
--07/04/2021 Bryce Standley - Added for loops for placing objects on the terrain
-- Format cs:MakeGameObject(type, "modelfolder", "vertexshader", "fragmentshader", scale, x, y, z, speed);
print("Scene 1 script loaded")

cs:MakeGameObject("player", "./res/scripts/gameobjects/player_default.lua", 0.001, 100, 2, 100);

cs:MakeGameObject("enemy",  "./res/scripts/gameobjects/enemy_zarlag.lua", 0.05, 50, 1.2, 50);
cs:MakeGameObject("enemy",  "./res/scripts/gameobjects/enemy_zarlag.lua", 0.05, 30, 1.2, 70);
cs:MakeGameObject("enemy",  "./res/scripts/gameobjects/enemy_zarlag.lua", 0.05, 90, 1.2, 70);

y = 1--Y value for all tokens
for i = 0, 5
do
    x = math.random(40, 150)
    z = math.random(40, 150)
    cs:MakeGameObject("token",  "./res/scripts/gameobjects/token_freehit.lua", 0.005, x, y, z);
    x = math.random(40, 150)
    z = math.random(40, 150)
    cs:MakeGameObject("token", "./res/scripts/gameobjects/token_speedup.lua", 0.005, x, y, z);
    x = math.random(40, 150)
    z = math.random(40, 150)
    cs:MakeGameObject("token",  "./res/scripts/gameobjects/token_doubledmg.lua", 0.005, x, y, z);
end

--These loops dont check if there is a model already in its place
--Make 10 Yellow Trees with random positions
y = -0.2
for i = 0, 10
do
    x = math.random(10, 190)
    z = math.random(10, 190)
    cs:MakeGameObject("static", "./res/scripts/gameobjects/static_yellowtree.lua", 0.005,x, y, z);
end

--Make 10 Red Trees with random positions
for i = 0, 10
do
    x = math.random(10, 190)
    z = math.random(10, 190)
    cs:MakeGameObject("static",  "./res/scripts/gameobjects/static_redtree.lua", 0.005,x, y, z);
end

y = -0.2
--Make 10 stones with random positions
for i = 0, 15
do
    x = math.random(50, 150)
    z = math.random(50, 150)
    cs:MakeGameObject("static",  "./res/scripts/gameobjects/static_stonediamond.lua", 0.02, x, y, z);
end


