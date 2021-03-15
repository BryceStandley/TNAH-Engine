#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const float* vPos, int vPosCount)
{
    SetBufferFloat(vPos, vPosCount);
}

VertexBuffer::VertexBuffer(std::vector<glm::vec3> vPos, std::vector<int> indices)
{
    SetBufferVec3(vPos, indices);
}

VertexBuffer::VertexBuffer(std::vector<float> vPos, int vPosCount)
{
    SetBufferVectorFloat(vPos, vPosCount);
}

void VertexBuffer::Render()
{
    //glBindVertexArray(VAO);
    //glDrawElements(GL_TRIANGLE_STRIP, vertCount, GL_UNSIGNED_INT, 0);
    //glBindVertexArray(0);
}

VertexBuffer::~VertexBuffer()
{
    Terminate();
}