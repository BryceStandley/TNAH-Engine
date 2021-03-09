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
	scaleX = xScale;
	scaleY = yScale;
	scaleZ = zScale;
}