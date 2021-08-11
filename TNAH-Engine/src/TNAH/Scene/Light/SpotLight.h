#pragma once
#include "TNAH/Renderer/Light.h"

namespace tnah {
    class SpotLight : public Light
    {
    public:
        SpotLight();
        SpotLight(const float& cutoff);

        virtual ~SpotLight() {}

        void SetUpLight(const float& cutoff);
    };
}