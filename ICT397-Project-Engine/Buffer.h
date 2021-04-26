#pragma once
#include <glad/glad.h>
#include <vector>

class Buffer
{
public:
	Buffer();
	void CreateBuffer(int s = 0);
	void DeleteBuffer();

	void* SetBuffer(int iUsageHint);
	void* SetSubBuffer(int iUsageHint, unsigned int uiOffset, unsigned int uiLength);
	void UnsetBuffer();

	void BindVBO(int a_iBufferType = GL_ARRAY_BUFFER);
	void UploadData(int iUsageHint);

	void AddData(void* ptrData, unsigned int uiDataSize);

	void* GetDataPointer();
	unsigned int GetBufferID();

	int GetCurrentSize();

private:
	unsigned int vbo;
	int iSize;
	int iCurrentSize;
	int iBufferType;
	std::vector<unsigned char> data;

	bool bDataUploaded;
};