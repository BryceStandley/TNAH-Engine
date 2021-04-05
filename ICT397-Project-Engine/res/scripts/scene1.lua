--scene1.lua
--6/04/21 Christopher Logan
print("Scene x script loaded")
cs:MakeGameObject("player", "", "", "", 0, 0, 0, 0, false);
cs:MakeGameObject("token", "./res/models/tokens/fbx/Free_Hit.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.05, 50, 2, 50, true);
cs:MakeGameObject("token", "./res/models/tokens/fbx/Free_Hit.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.05, 30, 2, 50, true);
cs:MakeGameObject("token", "./res/models/tokens/fbx/Free_Hit.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.05, 30, 2, 30, true);

