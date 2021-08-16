#pragma once
#include "Texture.h"

namespace tnah {
    class Image : public Texture2D
    {
    public:
        ~Image() override;
        void SetData(void* data, uint32_t size) override;
        void Bind(uint32_t slot) const override {}
        void Bind() const override {}
    };
}
