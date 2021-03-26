#include "GladRenderer.h"
#include "glad/glad.h"
void GladRenderer::RenderTerrain(unsigned int VAO, int size)
{
	glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLE_STRIP, size, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void GladRenderer::BindTexture(unsigned int texture)
{
    glBindTexture(GL_TEXTURE_2D, texture);
}

void GladRenderer::DepthTest()
{
    glEnable(GL_DEPTH_TEST);
}