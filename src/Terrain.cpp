#include "Terrain.h"
#include <glad/glad.h>
#include <vector>
// pairs terrain object with fragment shader
Terrain::Terrain()
{
    scaleX = 1;
    scaleY = 1;
    scaleZ = 1;
}

Terrain::~Terrain()
{
    delete[] terrainData;
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Terrain::Init()
{
    luaLoader();
    LoadHeightField(filename, size);
    setScalingFactor(scaleX, scaleY, scaleZ);
    generateTerrain();
}

void Terrain::luaLoader()
{
    using namespace luabridge;

    lua_State* L = LuaManager::getInstance().getLuaState();


    if (luaL_dofile(L, "./res/scripts/terrain.lua")) 
    {
        std::cout << "File not found" << std::endl;
    }
    else
    {
        std::string heightMap;
        std::string texture1;
        std::string texture2;
        std::string texture3;
        std::string texture4;
        std::string texture5;
        std::string vertShader;
        std::string fragShader;
        
        int tSize;
        int xScaler;
        int yScaler;
        int zScaler;

        LuaRef heightmap = getGlobal(L, "heightmap");
        LuaRef terrainSize = getGlobal(L, "terrainSize");
        LuaRef xScale = getGlobal(L, "xScale");
        LuaRef yScale = getGlobal(L, "yScale");
        LuaRef zScale = getGlobal(L, "zScale");
        LuaRef tex1 = getGlobal(L, "tex1");
        LuaRef tex2 = getGlobal(L, "tex2");
        LuaRef tex3 = getGlobal(L, "tex3");
        LuaRef tex4 = getGlobal(L, "tex4");
        LuaRef tex5 = getGlobal(L, "detailMap");
        LuaRef vs = getGlobal(L, "vs");
        LuaRef fs = getGlobal(L, "fs");
        LuaRef sp = getGlobal(L, "smoothingPasses");

        if (heightmap.isString())
        {
            heightMap = heightmap.cast<std::string>();
            this->filename = heightMap;
        }

        if (terrainSize.isNumber())
        {
            tSize = terrainSize.cast<int>();
            this->size = tSize;
        }

        if (xScale.isNumber())
        {
            xScaler = xScale.cast<int>();
            this->scaleX = (float)xScaler;
        }

        if (yScale.isNumber())
        {
            yScaler = yScale.cast<int>();
            this->scaleY = (float)yScaler;
        }

        if (zScale.isNumber())
        {
            zScaler = zScale.cast<int>();
            this->scaleZ = (float)zScaler;
        }

        if (tex1.isString())
        {
            texture1 = tex1.cast<std::string>();
            this->tex1 = texture1;
        }

        if (tex2.isString())
        {
            texture2 = tex2.cast<std::string>();
            this->tex2 = texture2;
        }

        if (tex3.isString())
        {
            texture3 = tex3.cast<std::string>();
            this->tex3 = texture3;
        }

        if (tex4.isString())
        {
            texture4 = tex4.cast<std::string>();
            this->tex4 = texture4;
        }

        if (tex5.isString())
        {
            texture5 = tex5.cast<std::string>();
            this->tex5 = texture5;
        }

        if(vs.isString())
        {
            vertShader = vs.cast<std::string>();
        }

        if (fs.isString())
        {
            fragShader = fs.cast<std::string>();
        }

        if(sp.isNumber())
        {
        	smoothingPasses = sp.cast<int>();
        }

        Shader shad(vertShader.c_str(), fragShader.c_str());
        shader = shad;
    }
}


void Terrain::attachShader(Shader shad)
{
    shader = shad;
}

bool Terrain::LoadHeightField(std::string filename, int size)
{

	stbi_set_flip_vertically_on_load(1);
	int width, height, bytesPerPixel;
	const auto imageData = stbi_load(filename.c_str(), &width, &height, &bytesPerPixel, 0);
	if (imageData == nullptr)
	{
		// Return empty vector in case of failure
		std::cout << "Failed to load heightmap image " << filename << "!" << std::endl;
	}

	std::vector<float> result;
	auto pixelPtr = &imageData[0];
	for (auto z = 0; z < height; ++z)
	{
		for (auto x = 0; x < width; ++x)
		{
			result.emplace_back((float(*pixelPtr) / 255.0f) * MAX_HEIGHT);
			pixelPtr += bytesPerPixel;
		}
	}

	stbi_image_free(imageData);
	terrainHeights = result;
	sizeX = width;
	sizeZ = height;
	stbi_set_flip_vertically_on_load(0);
	return true;



}

void Terrain::setScalingFactor(float xScale, float yScale, float zScale) {
    scaleX = xScale;
    scaleY = yScale;
    scaleZ = zScale;
}

float Terrain::getHeight(int xpos, int zpos) {
    if (xpos < 0) { xpos = 0; }
    if (zpos < 0) { zpos = 0; }
    if(xpos > sizeX) {xpos = sizeX;}
    if(zpos > sizeZ) { zpos = sizeZ;}
    if (inBounds(xpos, zpos))
    {
        return terrainHeights[zpos * sizeZ + xpos];
    }
    else
    {
	    return terrainHeights[((zpos - 1)  * sizeZ) + xpos];
    }
}

float Terrain::GetVertexHeight(int xPos, int zPos)
{
	if (xPos < 0) { xPos = 0; }
	if (zPos < 0) { zPos = 0; }
	if(xPos > sizeX) {xPos = sizeX;}
	if(zPos > sizeZ) { zPos = sizeZ;}
	if(inBounds(xPos, zPos))
	{
		return vertex.position[(zPos * sizeZ) + xPos].y;
	}
	else
	{
		return vertex.position[((zPos - 1) * sizeZ) + xPos].y;
	}
}

std::vector<float> Terrain::GetTerrainHeights()
{
	return terrainHeights;
}

void Terrain::SetVertexHeight(int xPos, int zPos, float newHeight)
{
	if (inBounds(xPos, zPos))
		vertex.position[(zPos * sizeZ) + xPos].y = newHeight;
		 //terrainData[(zPos * size) + xPos] = (newHeight * scaleY);
	else
		//terrainData[(zPos - 1 * size) + xPos] = newHeight * scaleY;
		vertex.position[(zPos - 1 * sizeZ) + xPos].y = newHeight;
}

float Terrain::getAverageHeight(int xpos, int zpos)
{
    std::vector<float> heights;

    //stopping the position over flowing
    if(xpos > sizeX) xpos = sizeX - 2;
    if(zpos > sizeZ) zpos = sizeZ - 2;


	float inX = (float)xpos / 4.0f;
	float inZ = (float)zpos / 4.0f;
	int intX =  xpos;
	int intZ =  zpos;
	float fracX = inX - intX;
	float fracZ = inZ - intZ;

	float v1 = GetVertexHeight(intX, intZ);
	float v2 = GetVertexHeight(intX + 1, intZ);
	float v3 = GetVertexHeight(intX, intZ + 1);
	float v4 = GetVertexHeight(intX + 1, intZ + 1);
	float i1 = Interpolate(v1, v2, fracX);
	float i2 = Interpolate(v3, v4, fracX);
	return Interpolate(i1, i2, fracZ);

/*


    heights.push_back(GetVertexHeight(xpos, zpos));


    heights.push_back(GetVertexHeight(xpos - 1 , zpos - 1));
    heights.push_back(GetVertexHeight(xpos, zpos - 1));
    heights.push_back(GetVertexHeight(xpos + 1, zpos - 1));

    heights.push_back(GetVertexHeight(xpos - 1, zpos) );
    heights.push_back(GetVertexHeight(xpos + 1, zpos));

    heights.push_back(GetVertexHeight(xpos - 1, zpos + 1));
    heights.push_back(GetVertexHeight(xpos, zpos + 1));
    heights.push_back(GetVertexHeight(xpos + 1, zpos + 1));

    float tot = 0.0f;
    for (float h : heights)
    {
        tot += h;
    }

    return tot / (float)heights.size();*/
}

float Terrain::getHeightColor(int xpos, int zpos) {
    if (inBounds(xpos, zpos)) {
        return terrainHeights[(zpos * sizeZ) + xpos];
    }
    return 1;
}

bool Terrain::inBounds(int xpos, int zpos)
{


    if ((xpos >= 0 && (float)xpos < (float)sizeX * scaleX) && (zpos >= 0 && zpos < (float)sizeZ * scaleZ))
        return true;
    else
        return false;
}

int Terrain::getSize()
{
    return size;
}

void Terrain::generateVertices(Vertex& vertex)
{
	//TerrainHeightScale(0, MAX_HEIGHT);

    for (unsigned int z = 0; z < sizeZ; ++z)
    {
        for (unsigned int x = 0; x < sizeX; ++x)
        {
            glm::vec3 positions((float)x * scaleX, getHeight((int)x, (int)z) * scaleY, (float)z * scaleZ);
            vertex.position.push_back(positions);
	        if(positions.y > highestPoint.y) { highestPoint = glm::vec3(x, positions.y, z);}
	        if(positions.y < lowestPoint.y) { lowestPoint = glm::vec3(x, positions.y, z);}
        }
    }
}




void Terrain::SmoothTerrain(Vertex& vert, float smoothFactor)
{
	for(int z = 0; z < sizeZ; ++z)
	{
		for(int x = 0; x < sizeX; ++x)
		{
			float corners = (GetVertexHeight(x-1, z-1) + GetVertexHeight(x + 1, z - 1) + GetVertexHeight(x - 1, z + 1) +
					GetVertexHeight(x + 1, z + 1)) / 16.0f;
			float sides = (GetVertexHeight(x - 1, z) + GetVertexHeight(x + 1, z) + GetVertexHeight(x, z - 1) +
					GetVertexHeight(x, z + 1)) / 8.0f;
			float center = GetVertexHeight(x,z) / 4.0f;
			float newHeight = (corners + sides + center);

            if (newHeight > highestPoint.y) { highestPoint = glm::vec3(x, newHeight, z); }
            if (newHeight < lowestPoint.y) { lowestPoint = glm::vec3(x, newHeight, z); }
			SetVertexHeight(x, z, newHeight);
		}
	}

/*
	for(int x = 1; x < size - 1; ++x)
	{
		for(int z = 1; z < size - 1; ++z)
		{
			float inX = (float)x / 4.0f;
			float inZ = (float)z / 4.0f;
			int intX =  x;
			int intZ =  z;
			float fracX = inX - intX;
			float fracZ = inZ - intZ;

			float v1 = GetVertexHeight(intX, intZ);
			float v2 = GetVertexHeight(intX + 1, intZ);
			float v3 = GetVertexHeight(intX, intZ + 1);
			float v4 = GetVertexHeight(intX + 1, intZ + 1);
			float i1 = Interpolate(v1, v2, fracX);
			float i2 = Interpolate(v3, v4, fracX);
			float newHeight = Interpolate(i1, i2, fracZ) / 5.0f;

			SetVertexHeight(x, z, newHeight);
		}
	}
 */

}

float Terrain::Interpolate(float a, float b, float blend)
{
	double theta = blend * M_PI;
	float f = (float) (1.0f - cos(theta)) * 0.5f;
	return a * (1.0f - f) + b * f;
}

void Terrain::generateIndices(std::vector<unsigned int>& indices)
{

	for (unsigned int z = 0; z < sizeZ - 1; ++z)
	{
		for (unsigned int x = 0; x < sizeX - 1; ++x) {
			indices.push_back((x * getSize() + z));             // 0
			indices.push_back(((x * getSize() + 1) + z));       // 1
			indices.push_back((((x + 1) * getSize()) + z));     // 3

			indices.push_back(((x * getSize() + 1) + z));       // 1
			indices.push_back(((x + 1) * getSize()) + (z + 1)); // 2
			indices.push_back((((x + 1) * getSize()) + z));     // 3
		}
	}
    return;
}

void Terrain::generateColors(Vertex& vertex)
{
    float colorVal = 0.0f;

    for (int z = 0; z < sizeZ; ++z)
    {
        for (int x = 0; x < sizeX; ++x)
        {
            colorVal = GetVertexHeight(x, z) / 255.0f;
            glm::vec3 color(0.0f, colorVal, 0.0f);
            vertex.color.push_back(color);
        }
    }
}

void Terrain::generateTextures(Vertex& vertex)
{

	unsigned int tracker = 0;
	float prevx = vertex.position[0].x;
	int s = 1;
	int x = 0;
	int z = 0;
	glm::vec3 texCoords;
	for (auto &vert : vertex.position) {
		if (static_cast<int>(prevx) != static_cast<int>(vert.x))
		{
			x++;
			z = 0;
			prevx = vert.x;
		}
		if (tracker == 0)
		{
			texCoords.x = static_cast<float>(x) / static_cast<float>(s);
			texCoords.y = static_cast<float>(z) / static_cast<float>(s);
			tracker++;
		}
		else
		{
			texCoords.x = static_cast<float>(x) / static_cast<float>(s);
			texCoords.y = static_cast<float>(z) / static_cast<float>(s);
			tracker = 0;
		}
		z++;
		vertex.texture.push_back(texCoords);
	}
}

void Terrain::generateNormals()
{
    for (unsigned int z = 0; z < getSize(); ++z)
    {
        for (unsigned int x = 0; x < getSize(); ++x)
        {
            const glm::vec3& west = vertex.position[(x > 0 ? x - 1 : 0) + z * getSize()];
            const glm::vec3& east = vertex.position[(x < getSize() - 1 ? x + 1 : x) + z * getSize()];

            glm::vec3 slope_x = east - west;

            const glm::vec3& south = vertex.position[x + (z > 0 ? z - 1 : 0) * getSize()];
            const glm::vec3& north = vertex.position[x + (z < getSize() - 1 ? z + 1 : z) * getSize()];

            glm::vec3 slope_y = north - south;


            glm::vec3 normal = cross(slope_x, slope_y);
            glm::vec3 normalized = glm::normalize(normal);
            vertex.normal.push_back(normalized);
        }
    }

}

// generates the terrain by placing position, colour and texture vertices into a vector
void Terrain::generateTerrain()
{
    generateVertices(vertex);

	//run the smoother how ever many times
	for(int i = 0; i < smoothingPasses; i++)
	{
		SmoothTerrain(vertex, 0);
	}

    generateColors(vertex);
    generateTextures(vertex);

    generateIndices(Indices);
    generateNormals();

    for (unsigned i = 0; i < vertex.position.size(); ++i)
    {
        totalData.push_back(vertex.position[i]);
        totalData.push_back(vertex.color[i]);
        totalData.push_back(vertex.texture[i]);
        totalData.push_back(-vertex.normal[i]);

    }



}

void Terrain::setTextures()
{
    unsigned int t1 = t.loadTexture(tex1);
    unsigned int t2 = t.loadTexture(tex2);
    unsigned int t3 = t.loadTexture(tex3);
    unsigned int t4 = t.loadTexture(tex4);
    unsigned int t5 = t.loadTexture(tex5);

    texIds.push_back(t1);
    texIds.push_back(t2);
    texIds.push_back(t3);
    texIds.push_back(t4);
    texIds.push_back(t5);

    shader.use();
    shader.setInt("texture0", 0);
    shader.setInt("texture1", 1);
    shader.setInt("texture2", 2);
    shader.setInt("texture3", 3);
    shader.setInt("texture4", 4);
}


