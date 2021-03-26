#include "bruteForce.h"
void bruteForce::generateTerrain()
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
            t.vertex.push_back(glm::vec3(tex.x, 0.0f, tex.y));

            if (z + 1 < getSize())
            {
                t.indices.push_back((z * getSize() + x));

                t.indices.push_back((z * getSize()) + x + getSize());
            }
        }

        t.indices.push_back(0xFFFFFFFFF);
    }
}



void bruteForce::modelSetup()
{
    unsigned int VBO2;
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

void bruteForce::Render()
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLE_STRIP, t.indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void bruteForce::resetTerrain()
{
    t.vertex.clear();
    t.indices.clear();
    t.texCoords.clear();
}