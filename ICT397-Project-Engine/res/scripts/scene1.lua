--scene1.lua
--6/04/21 Christopher Logan
-- Format cs:MakeGameObject(type, "modelfolder", "vertexshader", "fragmentshader", scale, x, y, z, speed);
print("Scene x script loaded")
cs:MakeGameObject("player", "", "", "", 0, 0, 0, 0, 0);
cs:MakeGameObject("token", "./res/models/tokens/fbx/Free_Hit.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.005, 50, 1, 50, 10);
cs:MakeGameObject("token", "./res/models/tokens/fbx/Free_Hit.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.005, 30, 1, 50, 10);
cs:MakeGameObject("token", "./res/models/tokens/fbx/Free_Hit.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.005, 30, 1, 30, 10);
cs:MakeGameObject("static", "./res/models/environment/Yellow_Tree-With-Texture.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.005, 20, 1, 50, 10);
cs:MakeGameObject("static", "./res/models/environment/tree-birch-tex.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.005, 30, 0.5, 40, 10);
cs:MakeGameObject("static", "./res/models/environment/stone-oval-tex.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.02, 60, 0.5, 40, 10);
