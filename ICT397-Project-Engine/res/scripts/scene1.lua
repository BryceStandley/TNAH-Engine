--scene1.lua
--6/04/21 Christopher Logan
--07/04/2021 Bryce Standley - Added object name
-- Format cs:MakeGameObject(type, "modelfolder", "vertexshader", "fragmentshader", scale, x, y, z, speed);
print("Scene x script loaded")
cs:MakeGameObject("player", "./res/models/weapons/Bennelli_M4-Texture.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.002, 0, 0, 0, 0);
cs:MakeGameObject("token",  "./res/models/tokens/Free_Hit.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.005, 50, 1, 50, 10);
cs:MakeGameObject("token", "./res/models/tokens/Speed_Up.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.005, 30, 1, 50, 10);
cs:MakeGameObject("token",  "./res/models/tokens/Double_Damage.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.005, 30, 1, 30, 10);
cs:MakeGameObject("static",  "./res/models/environment/Yellow_Tree-With-Texture.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.01, 20, 1, 50, 0);
cs:MakeGameObject("static",  "./res/models/environment/tree-birch-tex.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.005, 30, 0.5, 40, 0);
cs:MakeGameObject("static",  "./res/models/environment/stone-oval-tex.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.02, 60, 0.5, 40, 0);
cs:MakeGameObject("static",  "./res/models/environment/tree-forest-tex.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.05, 83, 0.6, 61, 0);
cs:MakeGameObject("static",  "./res/models/environment/stone-oval-tex.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.03, 59, 0.25, 54, 0);
cs:MakeGameObject("static",  "./res/models/environment/stone-oval-tex.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.03, 39, 0.25, 33, 0);
cs:MakeGameObject("static",  "./res/models/environment/stone-oval-tex.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.03, 59, 0.25, 54, 0);
cs:MakeGameObject("static",  "./res/models/environment/stone-oval-tex.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.03, 72, 0.25, 49, 0);
cs:MakeGameObject("static",  "./res/models/environment/stone-oval-tex.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.03, 24, 0.25, 60, 0);
cs:MakeGameObject("static",  "./res/models/environment/tree-forest-tex.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.05, 15, 0.6, 42, 0);
cs:MakeGameObject("static",  "./res/models/environment/tree-forest-tex.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.05, 51, 0.6, 14, 0);
cs:MakeGameObject("static",  "./res/models/environment/tree-forest-tex.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.05, 60, 0.6, 80, 0);
cs:MakeGameObject("static",  "./res/models/environment/Yellow_Tree-With-Texture.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.01, 77, 1, 34, 0);
cs:MakeGameObject("static",  "./res/models/environment/Yellow_Tree-With-Texture.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.01, 40, 1, 52, 0);
cs:MakeGameObject("static",  "./res/models/environment/Yellow_Tree-With-Texture.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.01, 72, 1, 64, 0);
cs:MakeGameObject("static",  "./res/models/environment/Yellow_Tree-With-Texture.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.01, 44, 1, 67, 0);
cs:MakeGameObject("static",  "./res/models/environment/Yellow_Tree-With-Texture.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.01, 54, 1, 27, 0);
cs:MakeGameObject("enemy",  "./res/models/characters/Impling_With_Texture_No_Weapon.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.0025, 30, 0.2, 55, 0);
cs:MakeGameObject("enemy",  "./res/models/characters/Impling_With_Texture_No_Weapon.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.0025, 67, 0.3, 70, 0);
cs:MakeGameObject("enemy",  "./res/models/characters/Impling_With_Texture_No_Weapon.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.0025, 46, 0.65, 77, 0);
cs:MakeGameObject("enemy",  "./res/models/characters/Impling_With_Texture_No_Weapon.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.0025, 66, 0.3, 28, 0);
cs:MakeGameObject("enemy",  "./res/models/characters/Impling_With_Texture_No_Weapon.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.0025, 25, 0.4, 33, 0);
cs:MakeGameObject("enemy",  "./res/models/characters/Impling_With_Texture_No_Weapon.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.0025, 41, 0.3, 18, 0);
cs:MakeGameObject("enemy",  "./res/models/characters/Impling_With_Texture_No_Weapon.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.0025, 38, 0.5, 72, 0);
cs:MakeGameObject("enemy",  "./res/models/characters/Impling_With_Texture_No_Weapon.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.0025, 53, 0.35, 72, 0);
cs:MakeGameObject("enemy",  "./res/models/characters/Impling_With_Texture_No_Weapon.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.0025, 78, 0.35, 57, 0);
cs:MakeGameObject("enemy",  "./res/models/characters/Impling_With_Texture_No_Weapon.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.0025, 77, 0.35, 44, 0);
cs:MakeGameObject("enemy",  "./res/models/characters/Impling_With_Texture_No_Weapon.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.0025, 69, 0.35, 35, 0);
cs:MakeGameObject("enemy",  "./res/models/characters/Impling_With_Texture_No_Weapon.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.0025, 64, 0.35, 51, 0);
cs:MakeGameObject("enemy",  "./res/models/characters/Impling_With_Texture_No_Weapon.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.0025, 49, 0.35, 38, 0);
cs:MakeGameObject("enemy",  "./res/models/characters/Impling_With_Texture_No_Weapon.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.0025, 55, 0.35, 47, 0);
cs:MakeGameObject("enemy",  "./res/models/characters/Impling_With_Texture_No_Weapon.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.0025, 55, 0.35, 47, 0);
cs:MakeGameObject("enemy",  "./res/models/characters/Impling_With_Texture_No_Weapon.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.0025, 37, 0.35, 64, 0);
cs:MakeGameObject("enemy",  "./res/models/characters/Impling_With_Texture_No_Weapon.fbx", "./res/shader/modelV.glsl", "./res/shader/modelF.glsl", 0.0025, 36, 0.35, 44, 0);