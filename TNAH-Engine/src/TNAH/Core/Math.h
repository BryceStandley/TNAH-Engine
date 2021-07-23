#pragma once
#define _USE_MATH_DEFINES

#include <TNAH/Core/Core.h>
#include <glm/glm.hpp>
#include <corecrt_math_defines.h>

namespace tnah {

	inline float BiLinearInterpolate(float a, float b, float blend)
	{
		double theta = blend * M_PI;
		float f = (float)(1.0f - cos(theta)) * 0.5f;
		return a * (1.0f - f) + b * f;
	}

}