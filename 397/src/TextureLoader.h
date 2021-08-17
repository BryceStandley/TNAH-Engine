#pragma once
#include <vector>
#include <string>
#include <glad/glad.h>
#include "stb_image.h"
#include <iostream>
#include <vector>


    /**
    * @class TextureLoader
    * @brief A simple class that is used to load in textures from a given file path;
    *
    * @author Dylan Blereau
    * @version 01
    * @date 20/03/2021 Dylan Blereau, Started
    *
    **/
class TNAH_API TextureLoader
{
public:
        /**
        * @brief loads the texture file from the given file path
        * @param path - represents the file path of the texture file
        * @return unsigned int
        */
	unsigned int loadTexture(std::string path);
};

