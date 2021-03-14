#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const float* vPos, int vPosCount)
{
    vertCount = vPosCount / 3;

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vPosCount * sizeof(float), vPos, GL_STATIC_DRAW);

    glGenVertexArrays(1, &VAO);                                                         
    glBindVertexArray(VAO);

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    std::cout << vertCount << std::endl;
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
}

VertexBuffer::VertexBuffer(std::vector<glm::vec3> vPos, std::vector<int> indices)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vPos.size() * sizeof(glm::vec3), &vPos[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    vertCount = indices.size();
}

VertexBuffer::VertexBuffer(std::vector<float> vPos, int vPosCount)
{
    vertCount = vPosCount*2;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vPosCount * sizeof(float), &vPos[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void VertexBuffer::Render()
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLE_STRIP, vertCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

VertexBuffer::~VertexBuffer()
{
    if (VBO != GL_NONE)
    {
        glDeleteBuffers(1, &VBO);
    }

    if (VAO != GL_NONE)
    {
        glDeleteVertexArrays(1, &VAO);
    }
}