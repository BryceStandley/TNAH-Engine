#include "Terrain.h"
#include "luaManager.h"
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
    //textures
}

void Terrain::luaLoader()
{
    using namespace luabridge;

    lua_State* L = LuaManager::getInstance().getLuaState();

    if (luaL_dofile(L, "terrain.lua"))
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
            this->scaleX = xScaler;
        }

        if (yScale.isNumber())
        {
            yScaler = yScale.cast<int>();
            this->scaleY = yScaler;
        }

        if (zScale.isNumber())
        {
            zScaler = zScale.cast<int>();
            this->scaleZ = zScaler;
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
    }

}


void Terrain::attachShader(Shader shad)
{
    shader = shad;
}

bool Terrain::LoadHeightField(std::string filename, int size)
{
    std::ifstream file(filename, std::ios::binary);

    if (!file)
    {
        std::cout << "File aint here brother" << std::endl;
        return false;
    }
    if (terrainData)
        delete[] terrainData;

    if (size > 0)
    {
        int nSize = size * size;
        terrainData = new unsigned char[nSize];
    }

    if (terrainData == NULL)
        return false;

    file.seekg(0, std::ios::end);
    int length = file.tellg();

    file.seekg(0, std::ios::beg);
    file.read(reinterpret_cast<char*>(terrainData), length);
    file.close();
    this->size = size;

    return true;
}

void Terrain::setScalingFactor(float xScale, float yScale, float zScale) {
    scaleX = xScale;
    scaleY = yScale;
    scaleZ = zScale;
}

float Terrain::getHeight(int xpos, int zpos) {
    if (inBounds(xpos, zpos))
        return ((float)(terrainData[(zpos * size) + xpos]) * scaleY);
    else
        return ((float)(terrainData[(zpos - 1 * size) + xpos]) * scaleY);
}

/**
* 
* 
* \author Bryce Standley
* \date   April 2021
* \param xpos
* \param zpos
* \return average height around a given x and z point in the terrain
*/
float Terrain::getAverageHeight(int xpos, int zpos)
{
    std::vector<float> heights;
    heights.push_back(getHeight(xpos, zpos) / 10.0f);

    heights.push_back(getHeight(xpos - 1 , zpos - 1) / 10.0f);
    heights.push_back(getHeight(xpos, zpos - 1) / 10.0f);
    heights.push_back(getHeight(xpos + 1, zpos - 1) / 10.0f);

    heights.push_back(getHeight(xpos - 1, zpos) / 10.0f);
    heights.push_back(getHeight(xpos + 1, zpos) / 10.0f);

    heights.push_back(getHeight(xpos - 1, zpos + 1) / 10.0f);
    heights.push_back(getHeight(xpos, zpos + 1) / 10.0f);
    heights.push_back(getHeight(xpos + 1, zpos + 1) / 10.0f);

    float tot = 0.0f;
    for (float h : heights)
    {
        tot += h;
    }

    return tot / heights.size();
}

unsigned char Terrain::getHeightColor(int xpos, int zpos) {
    if (inBounds(xpos, zpos)) {
        return terrainData[zpos * size + xpos];
    }
    return 1;
}

bool Terrain::inBounds(int xpos, int zpos)
{
    if ((xpos >= 0 && xpos < size * scaleX) && (zpos >= 0 && zpos < size * scaleZ))
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
    for (unsigned int z = 0; z < getSize(); ++z)
    {
        for (unsigned int x = 0; x < getSize(); ++x)
        {
            glm::vec3 positions(x * scaleX, getHeight(x, z) / 10.0f, z * scaleZ);
            vertex.position.push_back(positions);
        }
    }
}

void Terrain::generateIndices(std::vector<unsigned int>& indices)
{
    for (unsigned int z = 0; z < getSize(); ++z)
    {
        for (unsigned int x = 0; x < getSize(); ++x)
        {
            if (z + 1 < getSize())
            {
                indices.push_back((z * getSize() + x));

                indices.push_back((z * getSize()) + x + getSize());
            }
        }
        indices.push_back(0xFFFFFFFFF);
    }
}

void Terrain::generateColors(Vertex& vertex)
{
    float colorVal = 0.0f;

    for (unsigned int z = 0; z < getSize(); ++z)
    {
        for (unsigned int x = 0; x < getSize(); ++x)
        {
            colorVal = (float)getHeightColor(x, z) / 255;
            glm::vec3 color(0.0f, colorVal, 0.0f);
            vertex.color.push_back(color);
        }
    }
}

void Terrain::generateTextures(Vertex& vertex)
{

    for (unsigned int z = 0; z < getSize(); ++z)
    {
        for (unsigned int x = 0; x < getSize(); ++x)
        {
            glm::vec3 tex(((float)x / getSize()) * 5.0f, 0.0f, ((float)z / getSize()) * 5.0f);
            vertex.texture.push_back(tex);
        }
    }
}

void Terrain::generateNormals(std::vector<unsigned int>& indices)
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
    generateColors(vertex);
    generateTextures(vertex);

    generateIndices(Indices);
    generateNormals(Indices);

    for (unsigned i = 0; i < vertex.position.size(); ++i)
    {
        totalData.push_back(vertex.position[i]);
        totalData.push_back(vertex.color[i]);
        totalData.push_back(vertex.texture[i]);
        totalData.push_back(-vertex.normal[i]);

    }
    modelSetup();
}

// readies the model by buffering the vertex data and defining what vertices are position, colour, texture
void Terrain::modelSetup()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, totalData.size() * sizeof(glm::vec3), &totalData[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(unsigned int), &Indices[0], GL_STATIC_DRAW);

    //postion attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //color attributes
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //texture attributes
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //normal attributes
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(9 * sizeof(float)));
    glEnableVertexAttribArray(3);
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


