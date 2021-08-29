#include "tnahpch.h"
#include "Image.h"

namespace tnah {

    Image::~Image()
    {
        //stbi_image_free(this->m_ImageData);
    }

    void Image::SetData(void* data, uint32_t size)
    {
        TNAH_CORE_ASSERT(size == m_Width * m_Height * m_Channels, "Data must be entire image!");
        this->m_ImageData = static_cast<unsigned char*>(data);
    }
}
