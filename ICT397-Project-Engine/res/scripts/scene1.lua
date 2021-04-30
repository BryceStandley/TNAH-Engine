--scene1.lua
--6/04/21 Christopher Logan
--07/04/2021 Bryce Standley - Added for loops for placing objects on the terrain
-- Format cs:MakeGameObject(type, "modelfolder", "vertexshader", "fragmentshader", scale, x, y, z, speed);
print("Scene 1 script loaded")

cs:MakeGameObject("player", "./res/models/weapons/Bennelli_M4-Texture.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 1, 100, 2, 100, 0);
y = 1--Y value for all tokens
for i = 0, 5
do
    x = math.random(40, 150)
    z = math.random(40, 150)
    cs:MakeGameObject("token",  "./res/models/tokens/Free_Hit.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.005, x, y, z, 10);
    x = math.random(40, 150)
    z = math.random(40, 150)
    cs:MakeGameObject("token", "./res/models/tokens/Speed_Up.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.005, x, y, z, 10);
    x = math.random(40, 150)
    z = math.random(40, 150)
    cs:MakeGameObject("token",  "./res/models/tokens/Double_Damage.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.005, x, y, z, 10);
end

--These loops dont check if there is a model already in its place
--Make 10 Yellow Trees with random positions
y = -0.2
for i = 0, 10
do
    x = math.random(10, 190)
    z = math.random(10, 190)
    cs:MakeGameObject("static",  "./res/models/environment/Yellow_Tree-With-Texture.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.005,x, y, z, 10);
end

--Make 10 Red Trees with random positions
for i = 0, 10
do
    x = math.random(10, 190)
    z = math.random(10, 190)
    cs:MakeGameObject("static",  "./res/models/environment/Red_Tree-WithTexture.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.005,x, y, z, 10);
end

--Make 10 Gree Trees with random positions
for i = 0, 10
do
    x = math.random(10, 190)
    z = math.random(10, 190)
    cs:MakeGameObject("static",  "./res/models/environment/Green_Tree-WithTexture.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.005,x, y, z, 10);
end

y = -0.2
--Make 10 stones with random positions
for i = 0, 15
do
    x = math.random(50, 150)
    z = math.random(50, 150)
    cs:MakeGameObject("static",  "./res/models/environment/stone-diamond-tex.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.02, x, y, z, 10);
end

y = 1.2
--Make 15 Enemy objects
for i = 0, 2
do
    x = math.random(50, 150)
    z = math.random(50, 150)
    cs:MakeGameObject("enemy",  "res\\models\\zarlag\\Tris.md2", "./res/shader/md2vert.vert", "./res/shader/md2frag.frag", 0.05, x, y, z, 0);
	cs:MakeGameObject("enemy",  "res\\models\\zarlag\\Weapon.md2", "./res/shader/md2vert.vert", "./res/shader/md2frag.frag", 0.05, x, y, z, 0);
end


