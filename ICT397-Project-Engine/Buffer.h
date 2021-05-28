#pragma once
#include <glad/glad.h>
#include <vector>
/**
 * @class Buff
 * @breif The buffer class holds, makes and utilises the buffers in the game, mainly uses for animations
 * @author Christopher Logan
 * @date MAY 2021
 */
class Buffer
{
public:

	Buffer();
	/**
	 * @brief Creates a new buffer for use
	 */
	void CreateBuffer(int s = 0);

		/**
	 * @brief Removes buffers from memory
	 */
	void DeleteBuffer();

		/**
	 * @brief Sets a usage hint into a buffer
	 */
	void* SetBuffer(int iUsageHint);

	/**
	 * @brief Sets a substitute buffer
	 */
	void* SetSubBuffer(int iUsageHint, unsigned int uiOffset, unsigned int uiLength);

	/**
	 * @brief Removes a set buffer
	 */
	void UnsetBuffer();

	/**
	 * @brief Binds the VBO to the buffer
	 */
	void BindVBO(int a_iBufferType = GL_ARRAY_BUFFER);

	/**
	 * @brief Puts the data onto the GPU
	 */
	void UploadData(int iUsageHint);

	/**
	 * @brief Adds data to the data stream
	 */
	void AddData(void* ptrData, unsigned int uiDataSize);

	/**
	 * @brief returns the data pointers
	 */
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