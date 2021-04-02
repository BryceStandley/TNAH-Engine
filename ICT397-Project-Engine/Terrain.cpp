#include "Terrain.h"
#include <glad/glad.h>
#include <vector>
// pairs terrain object with fragment shader
Terrain::Terrain()
{
    //shader = new Shader("vertex.glsl", "fragment.glsl");
    //LoadHeightField("test-heightmap.raw",512);
    //generateTerrain();
    //modelSetup();
}

Terrain::~Terrain()
{
    delete[] terrainData;
    t.vertex.clear();
    t.indices.clear();
    t.texCoords.clear();
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
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

// generates the terrain by placing position, colour and texture vertices into a vector
void Terrain::generateTerrain()
{
    float colorVal = 0.0f;
    t.texCoords.push_back(glm::vec2(0, 0));
    for (unsigned int z = 0; z < getSize(); ++z)
    {
        for (unsigned int x = 0; x < getSize(); ++x)
        {
            colorVal = (float)getHeightColor(x, z) / 255;

            t.vertex.push_back(glm::vec3(x * scaleX, getHeight(x, z) / 10.0f, z * scaleZ)); //position values
            t.vertex.push_back(glm::vec3(colorVal, colorVal, colorVal)); // color values
            glm::vec2 tex(((float)x / getSize()) * 5.0f, ((float)z / getSize()) * 5.0f);
            t.vertex.push_back(glm::vec3(tex.x, 0.0f, tex.y)); // texture values

            if (z + 1 < getSize())
            {
                t.indices.push_back((z * getSize() + x));

                t.indices.push_back((z * getSize()) + x + getSize());
            }

            if (maxHeight < getHeight(x, z) / 10.0f) { maxHeight = getHeight(x, z) / 10.0f; }
            if (minHeight > getHeight(x, z) / 10.0f) { minHeight = getHeight(x, z) / 10.0f; }

        }

        t.indices.push_back(0xFFFFFFFFF);
    }
}

// readies the model by buffering the vertex data and defining what vertices are position, colour, texture
void Terrain::modelSetup()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, t.vertex.size() * sizeof(glm::vec3), &t.vertex[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, t.indices.size() * sizeof(unsigned int), &t.indices[0], GL_STATIC_DRAW);

    //postion attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //color attributes
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //texture attributes
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

}

void Terrain::setTextures(unsigned int tex1, unsigned int tex2, unsigned int tex3, unsigned int tex4, unsigned int tex5)
{
    texIds.push_back(tex1);
    texIds.push_back(tex2);
    texIds.push_back(tex3);
    texIds.push_back(tex4);
    texIds.push_back(tex5);

    shader.use();
    shader.setInt("texture0", 0);
    shader.setInt("texture1", 1);
    shader.setInt("texture2", 2);
    shader.setInt("texture3", 3);
    shader.setInt("texture4", 4);
}


