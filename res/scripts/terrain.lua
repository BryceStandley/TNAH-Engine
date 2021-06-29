--terrain.lua
--heightmap = "./res/heightmaps/test-heightmap.raw"

-- 3k Height map
--heightmap = "./res/heightmaps/3kheightmap.raw"
--terrainSize = 3072

-- 1k height map
--heightmap = "./res/heightmaps/1kheightmap-6-128.raw"
--heightmap = "./res/heightmaps/1k-128.raw"
heightmap = "./res/heightmaps/1k.tga"
terrainSize = 256;
xScale = 12;
yScale = 12;
zScale = 12;

--Test Height heightmaps
--[[
heightmap = "./res/heightmaps/testMaps/map.tga"
terrainSize = 16;
xScale = 1;
yScale = 1;
zScale = 1;]]--

tex1 = "./res/images/terrain/dirtTile.jpg"
tex2 = "./res/images/terrain/grassTile.jpg"
tex3 = "./res/images/terrain/mountainTile.jpg"
tex4 = "./res/images/terrain/snowTile.jpg"
detailMap = "./res/images/terrain/detailMap.jpg"

vs = "./res/shader/vertex.glsl"
fs = "./res/shader/fragment.glsl"
smoothingPasses = 0;
