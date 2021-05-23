--terrain.lua
--heightmap = "./res/heightmaps/test-heightmap.raw"

-- 3k Height map
--heightmap = "./res/heightmaps/3kheightmap.raw"
--terrainSize = 3072

-- 1k height map
heightmap = "./res/heightmaps/1kheightmap-3.raw"
--heightmap = "./res/heightmaps/1-5k.raw"
terrainSize = 1024;

xScale = 1
yScale = 5
zScale = 1

tex1 = "./res/images/terrain/dirtTile.jpg"
tex2 = "./res/images/terrain/grassTile.jpg"
tex3 = "./res/images/terrain/mountainTile.jpg"
tex4 = "./res/images/terrain/snowTile.jpg"
detailMap = "./res/images/terrain/detailMap.jpg"

vs = "./res/shader/vertex.glsl"
fs = "./res/shader/fragment.glsl"
