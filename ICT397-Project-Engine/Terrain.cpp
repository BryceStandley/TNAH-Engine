#include "Terrain.h"

bool Terrain::LoadHeightFeild(std::string filename, int size)
{
	std::ifstream file(filename, std::ios::binary);

	if (!file)
	{
		std::cout << "File aint here brother" << std::endl;
		return false;
	}
	if (data)
		delete[] data;

	if (size > 0)
	{
		int nSize = size * size;
		data = new unsigned char[nSize];
	}

	if (data == NULL)
		return false;

	file.seekg(0, std::ios::end);
	int length = file.tellg();

	file.seekg(0, std::ios::beg);
	file.read(reinterpret_cast<char*>(data),length);
	file.close();
	this->size = size;

	return true;
}

void Terrain::setScalingFactor(float xScale, float yScale, float zScale) {
	sX = xScale;
	sY = yScale;
	sZ = zScale;
}

float Terrain::getHeight(int xpos, int zpos) {
	return ((float)(data[(zpos * size) + xpos]) * sY);
}

void Terrain::Render()
{
	for (int z = 0; z < size - 1; z++) {
		//loop through the x axis
		glBegin(GL_TRIANGLE_STRIP);
		for (int x = 0; x < size; x++) {

			glVertex3f((float)x * sX, getHeight(x, z), (float)z * sZ);

			glVertex3f((float)x * sX, getHeight(x, z + 1), (float)(z + 1) * sZ);
		}
		glEnd();
	}
}