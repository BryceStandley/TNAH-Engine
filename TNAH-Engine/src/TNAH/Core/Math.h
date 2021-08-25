#pragma once
#define USE_MATH_DEFINES

#include <TNAH/Core/Core.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>

#include <glm/gtx/norm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <corecrt_math_defines.h>
#include <IrrKlang/irrKlang.h>

#include "imgui.h"
#include "glm/glm.hpp"

namespace tnah {
	namespace Math {
		
		inline float BiLinearInterpolate(float a, float b, float blend)
		{
			double theta = blend * M_PI;
			float f = static_cast<float>(1.0f - cos(theta)) * 0.5f;
			return a * (1.0f - f) + b * f;
		}

		bool DecomposeTransform(const glm::mat4& transform, glm::vec3& translation, glm::vec3& rotation, glm::vec3& scale);

		inline bool CompareImGuiToGLM(const ImVec2& imgui, const glm::vec2& glm)
		{
			if(static_cast<int>(imgui.x) == static_cast<int>(glm.x) && static_cast<int>(imgui.y) == static_cast<int>(glm.y))
				return true;
			
			return false;
		}

		inline bool CompareImVec2(const ImVec2& a, const ImVec2 b)
		{
			if(static_cast<int>(a.x) == static_cast<int>(b.x) && static_cast<int>(a.y) == static_cast<int>(b.y))
				return true;
			
			return false;
		}

		static float Remap(float value, float oldMin, float oldMax, float newMin, float newMax)
		{
			return newMin + (newMax - newMin) * ((value - oldMin) / (oldMax - oldMin));
		}

		irrklang::vec3df ConvertVec3ToVec3df(const glm::vec3& other);
	}

}