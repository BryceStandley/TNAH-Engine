#include "GladRenderer.h"
#include "glad/glad.h"
void GladRenderer::RenderTerrain(unsigned int VAO, int size)
{
    glPrimitiveRestartIndex(0xFFFFFFFFU);
    glEnable(GL_PRIMITIVE_RESTART);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLE_STRIP, size, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}

void GladRenderer::BindTexture(std::vector<unsigned int> textures)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, textures[2]);
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, textures[3]);
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, textures[4]);
}

void GladRenderer::DepthTest()
{
    glEnable(GL_DEPTH_TEST);
}

void GladRenderer::RenderSkybox(unsigned int VAO, unsigned int texture)
{
	glDepthFunc(GL_LEQUAL);
	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS);
}