#pragma once
#include <TNAH/Core/Core.h>

#include <glm/glm.hpp>
#include <glm/gtx/matrix_decompose.hpp>

namespace tnah {

	struct Transform
	{
		glm::mat4 TransformMatrix;

		glm::vec3 Position;
		glm::quat Rotation;
		glm::vec3 Scale;

		Transform()
		{
			TransformMatrix = glm::mat4(1.0f);
			Position = TransformMatrix[3];
			Rotation = glm::quat_cast(TransformMatrix);
			for (int i = 0; i < 3; i++)
			{
				Scale[i] = glm::length(glm::vec3(TransformMatrix[i]));
			}
		}

		Transform(const Transform&) = default;

		Transform(const glm::mat4& trans)
			:TransformMatrix(trans) {}

		operator const glm::mat4& () const { return TransformMatrix; }
		operator const glm::mat4& () { return TransformMatrix; }



		

	};


}
