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

void VertexBuffer::Render()
{
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertCount);                                                                           
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