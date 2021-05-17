--token_healthrefill.lua
--health refill token script

check = false;
rotate = true;

model = "./res/models/tokens/Health_Refill.fbx";
vertShader = "./res/shader/modelV.glsl";
fragShader = "./res/shader/modelF.glsl";
type = "HealthRefill";

speed = 200;
duration = 0.001;