--scene1.lua
--6/04/21 Christopher Logan
--07/04/2021 Bryce Standley - Added object name
-- Format cs:MakeGameObject(type, "modelfolder", "vertexshader", "fragmentshader", scale, x, y, z, speed);
print("Scene x script loaded")
cs:MakeGameObject("player", "./res/models/weapons/Bennelli_M4-Texture.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 1, 0, 0, 0, 0);
cs:MakeGameObject("token",  "./res/models/tokens/Free_Hit.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.005, 50, 1, 50, 10);
cs:MakeGameObject("token", "./res/models/tokens/Speed_Up.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.005, 30, 1, 50, 10);
cs:MakeGameObject("token",  "./res/models/tokens/Double_Damage.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.005, 30, 1, 30, 10);
cs:MakeGameObject("static",  "./res/models/environment/Yellow_Tree-With-Texture.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.005, 20, 1, 50, 10);
cs:MakeGameObject("static",  "./res/models/environment/tree-birch-tex.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.005, 30, 0.5, 40, 10);
cs:MakeGameObject("static",  "./res/models/environment/stone-oval-tex.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.02, 60, 0.5, 40, 10);

