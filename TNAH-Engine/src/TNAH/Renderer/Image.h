#pragma once
#include "Texture.h"

namespace tnah {
    class Image : public Texture2D
    {
    public:
        virtual ~Image();
        void SetData(void* data, uint32_t size) override;
        void Bind(uint32_t slot) const override {}
        void Bind() const override {}
        void Free() override;
        void Free(void* data) override;
        ktxTexture* GetKtxData() const override;
        char8_t* GetImageData() const override;
    };
}
