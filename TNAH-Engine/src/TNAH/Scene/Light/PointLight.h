#pragma once
#include "TNAH/Renderer/Light.h"

namespace tnah {
    class PointLight : public Light
    {
    public:
        PointLight();
        PointLight(const float& constant, const float& linear, const float& quadratic);
        virtual ~PointLight() {}

        void SetUpLight(const float& constant, const float& linear, const float& quadratic);
    };
}
