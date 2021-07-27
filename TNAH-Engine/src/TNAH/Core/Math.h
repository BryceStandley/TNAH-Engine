#pragma once
#define _USE_MATH_DEFINES

#include <TNAH/Core/Core.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>

#include <glm/gtx/norm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <corecrt_math_defines.h>

namespace tnah::math {

	inline float BiLinearInterpolate(float a, float b, float blend)
	{
		double theta = blend * M_PI;
		float f = (float)(1.0f - cos(theta)) * 0.5f;
		return a * (1.0f - f) + b * f;
	}

	bool DecomposeTransform(const glm::mat4& transform, glm::vec3& translation, glm::vec3& rotation, glm::vec3& scale);

}