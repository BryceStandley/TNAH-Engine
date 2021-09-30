#include "tnahpch.h"
#include "Math.h"

namespace tnah
{

	namespace Math
	{
		bool DecomposeTransform(const glm::mat4& transform, glm::vec3& translation, glm::vec3& rotation, glm::vec3& scale)
		{
			using namespace glm;
			using T = float;

			mat4 LocalMatrix(transform);

			// Normalize the matrix.
			if (epsilonEqual(LocalMatrix[3][3], static_cast<float>(0), epsilon<T>()))
				return false;

			// First, isolate perspective.  This is the messiest.
			if (
				epsilonNotEqual(LocalMatrix[0][3], static_cast<T>(0), epsilon<T>()) ||
				epsilonNotEqual(LocalMatrix[1][3], static_cast<T>(0), epsilon<T>()) ||
				epsilonNotEqual(LocalMatrix[2][3], static_cast<T>(0), epsilon<T>()))
			{
				// Clear the perspective partition
				LocalMatrix[0][3] = LocalMatrix[1][3] = LocalMatrix[2][3] = static_cast<T>(0);
				LocalMatrix[3][3] = static_cast<T>(1);
			}

			// Next take care of translation (easy).
			translation = vec3(LocalMatrix[3]);
			LocalMatrix[3] = vec4(0, 0, 0, LocalMatrix[3].w);

			vec3 Row[3];//, Pdum3;

			// Now get scale and shear.
			for (length_t i = 0; i < 3; ++i)
				for (length_t j = 0; j < 3; ++j)
					Row[i][j] = LocalMatrix[i][j];

			// Compute X scale factor and normalize first row.
			scale.x = length(Row[0]);
			Row[0] = detail::scale(Row[0], static_cast<T>(1));
			scale.y = length(Row[1]);
			Row[1] = detail::scale(Row[1], static_cast<T>(1));
			scale.z = length(Row[2]);
			Row[2] = detail::scale(Row[2], static_cast<T>(1));

			// At this point, the matrix (in rows[]) is orthonormal.
			// Check for a coordinate system flip.  If the determinant
			// is -1, then negate the matrix and the scaling factors.
#if 0
			Pdum3 = cross(Row[1], Row[2]); // v3Cross(row[1], row[2], Pdum3);
			if (dot(Row[0], Pdum3) < 0)
			{
				for (length_t i = 0; i < 3; i++)
				{
					scale[i] *= static_cast<T>(-1);
					Row[i] *= static_cast<T>(-1);
				}
			}
#endif

			rotation.y = asin(-Row[0][2]);
			if (cos(rotation.y) != 0.f) {
				rotation.x = atan2(Row[1][2], Row[2][2]);
				rotation.z = atan2(Row[0][1], Row[0][0]);
			}
			else {
				rotation.x = atan2(-Row[2][0], Row[1][1]);
				rotation.z = 0;
			}


			return true;
		}

		//rp3d::ToRp3dTransform() {}

		irrklang::vec3df ConvertVec3ToVec3df(const glm::vec3& other)
		{
			irrklang::vec3df value;
			value.X = other.x;
			value.Y = other.y;
			value.Z = other.z;
			return value;
		}

		glm::vec2 ToGLM(const rp3d::Vector2& vector)
		{
			return glm::vec2(vector.x, vector.y);
		}

		glm::vec2 ToGLM(const aiVector2D& vector)
		{
			return glm::vec2(vector.x, vector.y);
		}

		glm::vec3 ToGLM(const rp3d::Vector3& vector)
		{
			return glm::vec3(vector.x, vector.y, vector.z);
		}

		glm::vec3 ToGLM(const aiVector3D& vector)
		{
			return glm::vec3(vector.x, vector.y, vector.z);
		}

		glm::vec3 ToGLM(const irrklang::vec3df& vector)
		{
			return glm::vec3(vector.X, vector.Y, vector.Z);
		}

		glm::ivec3 ToGLM(const irrklang::vec3di& vector)
		{
			return glm::ivec3(vector.X, vector.Y, vector.Z);
		}

		glm::mat4 ToGLM(const aiMatrix4x4& matrix)
		{
			glm::mat4 result;
			//the a,b,c,d in assimp is the row ; the 1,2,3,4 is the column
			result[0][0] = matrix.a1; result[1][0] = matrix.a2; result[2][0] = matrix.a3; result[3][0] = matrix.a4;
			result[0][1] = matrix.b1; result[1][1] = matrix.b2; result[2][1] = matrix.b3; result[3][1] = matrix.b4;
			result[0][2] = matrix.c1; result[1][2] = matrix.c2; result[2][2] = matrix.c3; result[3][2] = matrix.c4;
			result[0][3] = matrix.d1; result[1][3] = matrix.d2; result[2][3] = matrix.d3; result[3][3] = matrix.d4;
			return result;
		}

		glm::mat3 ToGLM(const aiMatrix3x3& matrix)
		{
			glm::mat3 result;
			//the a,b,c,d in assimp is the row ; the 1,2,3,4 is the column
			result[0][0] = matrix.a1; result[1][0] = matrix.a2; result[2][0] = matrix.a3;
			result[0][1] = matrix.b1; result[1][1] = matrix.b2; result[2][1] = matrix.b3;
			result[0][2] = matrix.c1; result[1][2] = matrix.c2; result[2][2] = matrix.c3;
			return result;
		}

		glm::quat ToGLM(const aiQuaternion& quaternion)
		{
			return glm::quat(quaternion.w, quaternion.x, quaternion.y, quaternion.z);
		}

		rp3d::Vector2 ReactFromGLM(const glm::vec2& vector)
		{
			return rp3d::Vector2(vector.x, vector.y);
		}

		rp3d::Vector3 ReactFromGLM(const glm::vec3& vector)
		{
			return rp3d::Vector3(vector.x, vector.y, vector.z);
		}

		rp3d::Quaternion ReactFromGLM(const glm::quat& quaternion)
		{
			return rp3d::Quaternion(quaternion.x, quaternion.y, quaternion.z, quaternion.w); 
		}

		aiVector2D AssimpFromGLM(const glm::vec2& vector)
		{
			return aiVector2D(vector.x, vector.y);
		}

		aiVector3D AssimpFromGLM(const glm::vec3& vector)
		{
			return aiVector3D(vector.x, vector.y, vector.z);
		}

		aiMatrix4x4 AssimpFromGLM(const glm::mat4& matrix)
		{
			aiMatrix4x4 mat;
			mat.a1 = matrix[0][0]; mat.a2 =  matrix[1][0]; mat.a3 = matrix[2][0]; mat.a4 = matrix[3][0];
			mat.b1 = matrix[0][1]; mat.b2 = matrix[1][1]; mat.b3 = matrix[2][1]; mat.b4 = matrix[3][1];
			mat.c1 = matrix[0][2]; mat.c2 = matrix[1][2]; mat.c3 = matrix[2][2]; mat.c4 = matrix[3][2];
			mat.d1 = matrix[0][3]; mat.d2 = matrix[1][3]; mat.d3 = matrix[2][3]; mat.d4 = matrix[3][3];
			return mat;
		}

		aiMatrix3x3 AssimpFromGLM(const glm::mat3& matrix)
		{
			aiMatrix3x3 mat;
			mat.a1 = matrix[0][0]; mat.a2 =  matrix[1][0]; mat.a3 = matrix[2][0];
			mat.b1 = matrix[0][1]; mat.b2 = matrix[1][1]; mat.b3 = matrix[2][1];
			mat.c1 = matrix[0][2]; mat.c2 = matrix[1][2]; mat.c3 = matrix[2][2];
			return mat;
		}

		aiQuaternion AssimpFromGLM(const glm::quat& quaternion)
		{
			return aiQuaternion(quaternion.w, quaternion.x, quaternion.y, quaternion.z);
		}

		irrklang::vec3df IrrKlangFromGLM(const glm::vec3& vector)
		{
			return irrklang::vec3df(vector.x, vector.y,)
		}

		irrklang::vec3di IrrKlangFromGLM(const glm::ivec3& vector)
		{
		}
	}
}