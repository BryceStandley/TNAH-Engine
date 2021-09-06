#pragma once
#define USE_MATH_DEFINES

#include <TNAH/Core/Core.h>
#pragma warning(push, 0)
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>

#include <glm/gtx/norm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <corecrt_math_defines.h>
#include <IrrKlang/irrKlang.h>

#include "imgui.h"
#include "glm/glm.hpp"
#include "reactphysics3d/reactphysics3d.h"
#include "TNAH/Scene/Components/Components.h"
#pragma warning(pop)

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

		static rp3d::Vector3 ToRp3dVec3(const glm::vec3& values)
		{
			return rp3d::Vector3(values.x, values.y, values.z);
		}

		static rp3d::Quaternion ToRp3dQuat(const glm::quat& values)
		{
			return rp3d::Quaternion(values.x, values.y, values.z, values.w);
		}

		static rp3d::Transform ToRp3dTransform(const TransformComponent& transform)
		{
			return rp3d::Transform(ToRp3dVec3(transform.Position), ToRp3dQuat(glm::quat(transform.Rotation)));
		}

		static float Random()
		{
			float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			return r;
		}

		static float Random(const float& max)
		{
			float r2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/max));
			return r2;
		}

		static float Random(const float& min, const float& max)
		{
			float r3 = min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max-min)));
			return r3;
		}
	}

}