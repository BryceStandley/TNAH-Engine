--enemy_zarlag.lua

check = true;
rotate = false;
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

wander = {}

wander[1] = function (object)
local a = object:getDeltaTime
print (a) 
end

wander[2] = function ()

end

wander[3] = function ()

end