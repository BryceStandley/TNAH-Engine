#include "Buffer.h"

Buffer::Buffer()
{
	bDataUploaded = false;
	vbo = 0;
}

void Buffer::CreateBuffer(int s)
{
	glGenBuffers(1, &vbo);
	data.reserve(s);
	iSize = s;
	iCurrentSize = 0;
}

void Buffer::DeleteBuffer()
{
	glDeleteBuffers(1, &vbo);
	bDataUploaded = false;
	data.clear();
}

void* Buffer::SetBuffer(int iUsageHint)
{
	if (!bDataUploaded)return NULL;
	void* ptrRes = glMapBuffer(iBufferType, iUsageHint);
	return ptrRes;
}


void* Buffer::SetSubBuffer(int iUsageHint, unsigned int uiOffset, unsigned int uiLength)
{
	if (!bDataUploaded)return NULL;
	void* ptrRes = glMapBufferRange(iBufferType, uiOffset, uiLength, iUsageHint);
	return ptrRes;
}

void Buffer::UnsetBuffer()
{
	glUnmapBuffer(iBufferType);
}

void Buffer::BindVBO(int a_iBufferType)
{
	iBufferType = a_iBufferType;
	glBindBuffer(iBufferType, vbo);
}

void Buffer::UploadData(int iDrawingHint)
{
	glBufferData(iBufferType, data.size(), &data[0], iDrawingHint);
	bDataUploaded = true;
	data.clear();
}

void Buffer::AddData(void* ptrData, unsigned int uiDataSize)
{
	data.insert(data.end(), (unsigned char*)ptrData, (unsigned char*)ptrData + uiDataSize);
	iCurrentSize += uiDataSize;
}

void* Buffer::GetDataPointer()
{
	if (bDataUploaded)return NULL;
	return (void*)data[0];
}

unsigned int Buffer::GetBufferID()
{
	return vbo;
}

int Buffer::GetCurrentSize()
{
	return iCurrentSize;
}