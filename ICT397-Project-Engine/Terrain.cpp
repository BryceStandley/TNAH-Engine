#include "Terrain.h"



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

unsigned char Terrain::getHeightColor(int xpos, int zpos) {
	if (inBounds(xpos, zpos)) {
		return terrainData[zpos * size + xpos];
	}
	return 1;
}

void Terrain::setHeightAtPoint(unsigned char height, int xpos, int zpos)
{
	terrainData[(zpos * getSize()) + xpos] = height;
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

void Terrain::filterPass(float* startP, int increment, float weight) {
	float yprev = *startP; // the starting point in the terrain array
	int j = increment; // must be either +1, -1, +size, or -size
	float k = weight;
	// loop through either 
	// one row from left to right if increment = +1, or
	// one row from right to left if increment = -1, or
	// one column from top to bottom if increment = +size, or
	// one column from bottom to top if increment = -size
	for (int i = 1; i < getSize(); i++) {
		// yi = k yi-1 + (1-k) xi
		*(startP + j) = k * yprev + (1 - k) * (*(startP + j)); // 
		yprev = *(startP + j);
		j += increment;
	}
}

void Terrain::addFilter(float* terrainData, float weight) {
	int i;
	//erode left to right, starting from the beginning of each row
	for (i = 0; i < getSize(); i++)
		filterPass(&terrainData[getSize() * i], 1, weight);
	//erode right to left, starting from the end of each row
	for (i = 0; i < getSize(); i++)
		filterPass(&terrainData[getSize() * i + getSize() - 1], -1, weight);
	//erode top to bottom, starting from the beginning of each column
	for (i = 0; i < getSize(); i++)
		filterPass(&terrainData[i], getSize(), weight);
	//erode from bottom to top, starting from the end of each column
	for (i = 0; i < getSize(); i++)
		filterPass(&terrainData[getSize() * (getSize() - 1) + i], -getSize(), weight);
}

void Terrain::normaliseTerrain(float* terrainData) {
	float fMin, fMax;
	float fHeight;
	int i;
	fMin = terrainData[0];
	fMax = terrainData[0];
	//find the min and max values of the height terrainData
	for (i = 1; i < size * size; i++) {
		if (terrainData[i] > fMax)
			fMax = terrainData[i];
		else if (terrainData[i] < fMin)
			fMin = terrainData[i];
	}
	//find the range of the altitude
	if (fMax <= fMin)
		return;
	fHeight = fMax - fMin;

	//scale the values to a range of 0-255 
	for (i = 0; i < size * size; i++)
		terrainData[i] = ((terrainData[i] - fMin) / fHeight) * 255.0f;
}

bool Terrain::genFaultFormation(int iter, int hSize, int minHeight, int maxHeight, float weight, bool random)
{
	int x1, x2, z1, z2;
	float* heights = NULL;
	int displacement;
	if (hSize <= 0)
		return false;
	if (random) //create truly random map
		srand(time(NULL));
	// allocate memory for heightfield array
	size = hSize;
	heights = new float[size * size]; //allocate memory
	terrainData = new unsigned char[size * size]; // terrainData is declared in terrain class
	if (heights == NULL || terrainData == NULL)
		return false;

	// initialise the heightfield array to all zeros
	for (int i = 0; i < size * size; i++)
		heights[i] = 0.0;
	// generate heightfield 
	for (int j = 0; j < iter; j++) {
		//calculate the displacement value for the current iteration
		displacement = maxHeight - ((maxHeight - minHeight) * j) / iter;

		//pick the first random point P1(x1, z1) from the height map
		x1 = (rand() % size);
		z1 = (rand() % size);
		// pick up the second random point P2(x2, z2) and make sure it is
		// different from the first point
		do {
			x2 = (rand() % size);
			z2 = (rand() % size);
		} while (x2 == x1 && z2 == z1);
		//for each point P(x, z) in the field, calculate the new height values
		for (int z = 0; z < size; z++) {
			for (int x = 0; x < size; x++) {
				// determine which side of the line P1P2 the point P lies in
				if (((x - x1) * (z2 - z1) - (x2 - x1) * (z - z1)) > 0) {
					heights[(z * size) + x] += (float)displacement;
				}
			}
		}
		addFilter(heights, weight);
	}
	// normalise the heightfield
	normaliseTerrain(heights);
	// copy the float heightfield to terrainData (in unsign char)
	for (int z = 0; z < size; z++) {
		for (int x = 0; x < size; x++) {
			setHeightAtPoint((unsigned char)heights[(z * size) + x], x, z);
		}
	}
	// dispose of the temporary array heights
	delete[] heights;
	return true;
}
