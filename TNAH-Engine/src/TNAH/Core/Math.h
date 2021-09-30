#pragma once
#define USE_MATH_DEFINES

#include <TNAH/Core/Core.h>
#include "TNAH/Scene/Components/Components.h"

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

#include <assimp/vector3.h>
#include <assimp/matrix4x4.h>
#include <assimp/matrix3x3.h>
#include <assimp/quaternion.h>

#include "AABB.h"
#include "AABB.h"

#pragma warning(pop)

namespace tnah {
	namespace Math {

		/**
		 * @fn	inline float BiLinearInterpolate(float a, float b, float blend)
		 *
		 * @brief	Bi linear interpolate
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @param 	a	 	A float to process.
		 * @param 	b	 	A float to process.
		 * @param 	blend	The blend.
		 *
		 * @returns	A float.
		 */

		inline float BiLinearInterpolate(float a, float b, float blend)
		{
			double theta = blend * M_PI;
			float f = static_cast<float>(1.0f - cos(theta)) * 0.5f;
			return a * (1.0f - f) + b * f;
		}

		/**
		 * @fn	bool DecomposeTransform(const glm::mat4& transform, glm::vec3& translation, glm::vec3& rotation, glm::vec3& scale);
		 *
		 * @brief	Decompose transform
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @param 		  	transform  	The transform.
		 * @param [in,out]	translation	The translation.
		 * @param [in,out]	rotation   	The rotation.
		 * @param [in,out]	scale	   	The scale.
		 *
		 * @returns	True if it succeeds, false if it fails.
		 */

		bool DecomposeTransform(const glm::mat4& transform, glm::vec3& translation, glm::vec3& rotation, glm::vec3& scale);

		/**
		 * @fn	inline bool CompareImGuiToGLM(const ImVec2& imgui, const glm::vec2& glm)
		 *
		 * @brief	Compare imgui vec2 to glm vec2
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @param 	imgui	The imgui.
		 * @param 	glm  	The glm.
		 *
		 * @returns	True if it succeeds, false if it fails.
		 */

		inline bool CompareImGuiToGLM(const ImVec2& imgui, const glm::vec2& glm)
		{
			if(static_cast<int>(imgui.x) == static_cast<int>(glm.x) && static_cast<int>(imgui.y) == static_cast<int>(glm.y))
				return true;
			
			return false;
		}

		/**
		 * @fn	inline bool CompareImVec2(const ImVec2& a, const ImVec2 b)
		 *
		 * @brief	Compare imgui vec2
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @param 	a	An ImVec2 to process.
		 * @param 	b	An ImVec2 to process.
		 *
		 * @returns	True if it succeeds, false if it fails.
		 */

		inline bool CompareImVec2(const ImVec2& a, const ImVec2 b)
		{
			if(static_cast<int>(a.x) == static_cast<int>(b.x) && static_cast<int>(a.y) == static_cast<int>(b.y))
				return true;
			
			return false;
		}

		/**
		 * @fn	static float Remap(float value, float oldMin, float oldMax, float newMin, float newMax)
		 *
		 * @brief	Remaps the range
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @param 	value 	The value.
		 * @param 	oldMin	The old minimum.
		 * @param 	oldMax	The old maximum.
		 * @param 	newMin	The new minimum.
		 * @param 	newMax	The new maximum.
		 *
		 * @returns	A float.
		 */

		static float Remap(float value, float oldMin, float oldMax, float newMin, float newMax)
		{
			return newMin + (newMax - newMin) * ((value - oldMin) / (oldMax - oldMin));
		}

        //TODO ::DOXy Here
		static float Clamp(float value, float lowClamp, float highClamp)
		{
			if(value < lowClamp) value = lowClamp;
			if(value > highClamp) value = highClamp;
			return value;
		}
		//TODO ::DOXy Here
		static int Clamp(float value, int lowClamp, int highClamp)
		{
			if(value < lowClamp) value = (float)lowClamp;
			if(value > highClamp) value = (float)highClamp;
			return (int)value;
		}


		
		/**
		 * @fn	static rp3d::Vector3 ToRp3dVec3(const glm::vec3& values)
		 *
		 * @brief	Converts the glm vec3 values to a rp3D vector 3 values
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @param 	values	The values.
		 *
		 * @returns	Values as a rp3d::Vector3.
		 */

		static rp3d::Vector3 ToRp3dVec3(const glm::vec3& values)
		{
			return rp3d::Vector3(values.x, values.y, values.z);
		}

		/**
		* @fn	static glm::vec3 FromRp3dVec3(const rp3d::Vector3& values)
		*
		* @brief	Converts the reactphysics3d vector3 values to a glm vec3 values
		*
		* @author	Dylan Blereau
		* @date	7/09/2021
		*
		* @param 	values	The values.
		*
		* @returns	Values as a glm::vec3.
		*/

		static glm::vec3 FromRp3dVec3(const rp3d::Vector3& values)
		{
			return glm::vec3(values.x, values.y, values.z);
		}
		
		/**
		 * @fn	static rp3d::Quaternion ToRp3dQuat(const glm::quat& values)
		 *
		 * @brief	Converts the glm quaternion values to a rp3D quaternion
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @param 	values	The values.
		 *
		 * @returns	Values as a rp3d::Quaternion.
		 */

		static rp3d::Quaternion ToRp3dQuat(const glm::quat& values)
		{
			return rp3d::Quaternion(values.x, values.y, values.z, values.w);
		}

		/**
		 * @fn	static rp3d::Transform ToRp3dTransform(const TransformComponent& transform)
		 *
		 * @brief	Converts a TranformComponent transform to a rp3d transform
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @param 	transform	The transform.
		 *
		 * @returns	Transform as a rp3d::Transform.
		 */

		static rp3d::Transform ToRp3dTransform(const TransformComponent& transform)
		{
			return rp3d::Transform(ToRp3dVec3(transform.Position), ToRp3dQuat(glm::quat(transform.Rotation)));
		}

		/**
		 * @fn	static float Random()
		 *
		 * @brief	Gets the random
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @returns	A float.
		 */

		static float Random()
		{
			float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			return r;
		}

		/**
		 * @fn	static float Random(const float& max)
		 *
		 * @brief	Randoms the given maximum
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @param 	max	The maximum.
		 *
		 * @returns	A float.
		 */

		static float Random(const float& max)
		{
			float r2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/max));
			return r2;
		}

		/**
		 * @fn	static float Random(const float& min, const float& max)
		 *
		 * @brief	Randoms the min and max values
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @param 	min	The minimum.
		 * @param 	max	The maximum.
		 *
		 * @returns	A float.
		 */

		static float Random(const float& min, const float& max)
		{
			float r3 = min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max-min)));
			return r3;
		}

#pragma region ConversionHelpers


	/**
	 * \fn tnah::Math::ToGLM
	 * 
	 * \brief 
	 *
	 * \author Bryce Standley
	 * \date Friday, 17 September 2021
	 * 
	 * \param vector The ReactPhysics3D Vector2 to convert
	 *
	 * \return a glm vec2 of the provided ReactPhysics3D Vector2
	 *
	 */
	static glm::vec2 ToGLM(const rp3d::Vector2& vector);

		

	/**
	 * \fn glm::vec2 tnah::Math::ToGLM(const aiVector2D& vector)
	 * 
	 * \brief Converts a 2 component vector type to another
	 *
	 * \author Bryce Standley
	 * \date Friday, 17 September 2021
	 * 
	 * \param vector Assimp vector to convert from
	 *
	 * \return a glm vec2 of the provided Assimp aiVector2D
	 *
	 */
	static glm::vec2 ToGLM(const aiVector2D& vector);


	/**
	 * \fn glm::vec3 tnah::Math::ToGLM(const rp3d::Vector3& vector)
	 * 
	 * \brief Converts a 3 component vector type to another
	 *
	 * \author Bryce Standley
	 * \date Friday, 17 September 2021
	 * 
	 * \param vector ReactPhysics3D Vector3 to convert from
	 *
	 * \return  RDESCRIPTION
	 *
	 */
	static glm::vec3 ToGLM(const rp3d::Vector3& vector);

		
	/**
	 * \fn glm::vec3 tnah::Math::ToGLM(const aiVector3D& vector)
	 * 
	 * \brief  Converts a 3 component vector type to another
	 *
	 * \author Bryce Standley
	 * \date Friday, 17 September 2021
	 * 
	 * \param vector a Assimp aiVector3D to convert
	 *
	 * \return  a glm vec3 from Assimp values
	 *
	 */
	static glm::vec3 ToGLM(const aiVector3D& vector);

		
	/**
	 * \fn glm::vec3 tnah::Math::ToGLM(const irrklang::vec3df& vector)
	 * 
	 * \brief Converts a 3 component vector type to another
	 *
	 * \author Bryce Standley
	 * \date Friday, 17 September 2021
	 * 
	 * \param vector A Irrklang vec3df to convert
	 *
	 * \return  a glm vec3 from Irrklang values
	 *
	 */
	static glm::vec3 ToGLM(const irrklang::vec3df& vector);

		
	static glm::ivec3 ToGLM(const irrklang::vec3di& vector);

	/**
	 * \fn glm::mat4 tnah::Math::ToGLM(const aiMatrix4x4& matrix)
	 * 
	 * \brief Converts a 4x4 matrix of one type to another
	 *
	 * \author Bryce Standley
	 * \date Friday, 17 September 2021
	 * 
	 * \param matrix A Assimp matrix to convert
	 *
	 * \return  RDESCRIPTION
	 *
	 */
	static glm::mat4 ToGLM(const aiMatrix4x4& matrix);

		/**
		* \fn glm::mat3 tnah::Math::ToGLM(const aiMatrix3x3& matrix)
		* 
		* \brief Converts a 3x3 matrix of one type to another
		*
		* \author Bryce Standley
		* \date Friday, 17 September 2021
		* 
		* \param matrix A Assimp matrix to convert
		*
		* \return  a glm mat3 from Assimp values
		*
		*/
	static glm::mat3 ToGLM(const aiMatrix3x3& matrix);
		
	/**
	 * \fn glm::quat tnah::Math::ToGLM(const aiQuaternion& quaternion)
	 * 
	 * \brief Converts a quaternion from one type to another
	 *
	 * \author Bryce Standley
	 * \date Friday, 17 September 2021
	 * 
	 * \param quaternion Assimp quaternion to convert
	 *
	 * \return  RDESCRIPTION
	 *
	 */
	static glm::quat ToGLM(const aiQuaternion& quaternion);

		/**
		* @fn	static rp3d::Vector2 Math::ReactFromGLM(const glm::vec2& vector);
		*
		* @brief	Convert glm vec2 to ReactPhysics3D Vector2
		*
		* @author	Bryce Standley
		* @date		17/09/2021
		*
		* @param 	vector the GLM equivalent to convert from.
		*
		* @returns	A ReactPhysics3D Vector2 from provided glm vec2.
		*/
	static rp3d::Vector2 ReactFromGLM(const glm::vec2& vector);

		/**
		* @fn	static rp3d::Vector3 Math::ReactFromGLM(const glm::vec3& vector);
		*
		* @brief	Convert glm vec3 to ReactPhysics3D Vector3
		*
		* @author	Bryce Standley
		* @date		17/09/2021
		*
		* @param 	vector the GLM equivalent to convert from.
		*
		* @returns	A ReactPhysics3D Vector3 from provided glm vec3.
		*/
	static rp3d::Vector3 ReactFromGLM(const glm::vec3& vector);

		
	/**
	 * \fn rp3d::Quaternion tnah::Math::ReactFromGLM(const glm::quat& quaternion)
	 * 
	 * \brief Converts a quaternion from glm to ReactPhysics3D
	 *
	 * \author Bryce Standley
	 * \date Friday, 17 September 2021
	 * 
	 * \param quaternion The glm quaternion to convert
	 *
	 * \return A ReactPhysics3D Quaternion from glm values.
	 *
	 */
	static rp3d::Quaternion ReactFromGLM(const glm::quat& quaternion);

		/**
		* @fn	static aiVector2D Math::AssimpFromGLM(const glm::vec2& vector);
		*
		* @brief	Convert glm vec2 to Assimp aiVector2D
		*
		* @author	Bryce Standley
		* @date		17/09/2021
		*
		* @param 	vector the GLM equivalent to convert from.
		*
		* @returns	A Assimp aiVector2D from provided glm vec2.
		*/
	static aiVector2D AssimpFromGLM(const glm::vec2& vector);

		/**
		* @fn	static aiVector3D Math::AssimpFromGLM(const glm::vec3& vector);
		*
		* @brief	Convert glm vec3 to Assimp aiVector3D
		*
		* @author	Bryce Standley
		* @date		17/09/2021
		*
		* @param 	vector the GLM equivalent to convert from.
		*
		* @returns	A Assimp aiVector2D from provided glm vec2.
		*/
	static aiVector3D AssimpFromGLM(const glm::vec3& vector);

		/**
		* @fn	static aiMatrix4x4 Math::AssimpFromGLM(const glm::mat4& matrix);
		*
		* @brief	Convert glm mat4 to Assimp aiMatrix4x4
		*
		* @author	Bryce Standley
		* @date		17/09/2021
		*
		* @param 	matrix the GLM equivalent to convert from.
		*
		* @returns	A Assimp aiMatrix4x4 from provided glm mat4.
		*/
	static aiMatrix4x4 AssimpFromGLM(const glm::mat4& matrix);

		/**
		* @fn	static aiMatrix3x3 Math::AssimpFromGLM(const glm::mat3& matrix);
		*
		* @brief	Convert glm mat3 to Assimp aiMatrix3x3
		*
		* @author	Bryce Standley
		* @date		17/09/2021
		*
		* @param 	matrix the GLM equivalent to convert from.
		*
		* @returns	A Assimp aiMatrix3x3 from provided glm mat3.
		*/
	static aiMatrix3x3 AssimpFromGLM(const glm::mat3& matrix);

		/**
		* @fn	static aiQuaternion Math::AssimpFromGLM(const glm::quat& quaternion);
		*
		* @brief	Convert glm quat to Assimp aiQuaternion
		*
		* @author	Bryce Standley
		* @date		17/09/2021
		*
		* @param 	quaternion the GLM equivalent to convert from.
		*
		* @returns	A Assimp aiQuaternion from provided glm quat.
		*/
	static aiQuaternion AssimpFromGLM(const glm::quat& quaternion);

		/**
		* @fn	static irrklang::vec3df Math::IrrKlangFromGLM(const glm::vec3& vector);
		*
		* @brief	Convert glm vec3 to irrklang vec3df
		*
		* @author	Bryce Standley
		* @date		17/09/2021
		*
		* @param 	vector the GLM equivalent to convert from.
		*
		* @returns	A IrrKlang vec3df using values from the provided glm vec3.
		*/
	static irrklang::vec3df IrrKlangFromGLM(const glm::vec3& vector);

		/**
		* @fn	static irrklang::vec3df Math::IrrKlangFromGLM(const glm::1vec3& vector);
		*
		* @brief	Convert glm 1vec3 to irrklang vec3di
		*
		* @author	Bryce Standley
		* @date		17/09/2021
		*
		* @param 	vector the GLM equivalent to convert from.
		*
		* @returns	A IrrKlang vec3di using values from the provided glm ivec3.
		*/
	static irrklang::vec3di IrrKlangFromGLM(const glm::ivec3& vector);

		
#pragma endregion
		
	}

}