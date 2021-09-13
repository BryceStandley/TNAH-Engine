#pragma once
#include "TNAH/Core/Core.h"
#include "TNAH/Renderer/Light.h"
#include "TNAH/Scene/Light/DirectionalLight.h"
#include "TNAH/Scene/Light/PointLight.h"
#include "TNAH/Scene/Light/SpotLight.h"
#include "ComponentBase.h"

namespace tnah {

	/**********************************************************************************************//**
	 * @class	LightComponent
	 *
	 * @brief	A light component.
	 *
	 * @author	Chris
	 * @date	10/09/2021
	 **************************************************************************************************/

	class LightComponent : public Component
	{
	public:

		/** @brief	The light */
		Ref<Light> Light;

		/**********************************************************************************************//**
		 * @fn	LightComponent::LightComponent() = default;
		 *
		 * @brief	Defaulted constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 **************************************************************************************************/

		LightComponent() = default;

		/**********************************************************************************************//**
		 * @fn	LightComponent::LightComponent(const LightComponent& other) = default;
		 *
		 * @brief	Defaulted copy constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	other	The other.
		 **************************************************************************************************/

		LightComponent(const LightComponent& other) = default;

		/**********************************************************************************************//**
		 * @fn	LightComponent::LightComponent(const tnah::Light::LightType& type)
		 *
		 * @brief	Constructor
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	type	The type.
		 **************************************************************************************************/

		LightComponent(const tnah::Light::LightType& type)
		{
			Light = Light::Create(type);
		}

		/**********************************************************************************************//**
		 * @fn	void LightComponent::SetDirectional(const glm::vec3& direction, const glm::vec3& ambient,const glm::vec3& diffuse, const glm::vec3& specular)
		 *
		 * @brief	Sets a directional
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	direction	The direction.
		 * @param 	ambient  	The ambient.
		 * @param 	diffuse  	The diffuse.
		 * @param 	specular 	The specular.
		 **************************************************************************************************/

		void SetDirectional(const glm::vec3& direction, const glm::vec3& ambient,const glm::vec3& diffuse,
			const glm::vec3& specular)
		{
			Light = Light::CreateDirectional(direction, ambient, diffuse, specular);
		}

		/**********************************************************************************************//**
		 * @fn	void LightComponent::SetPoint(const float& constant, const float& linear, const float& quadratic)
		 *
		 * @brief	Sets a point
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	constant 	The constant.
		 * @param 	linear   	The linear.
		 * @param 	quadratic	The quadratic.
		 **************************************************************************************************/

		void SetPoint(const float& constant, const float& linear, const float& quadratic)
		{
			Light = Light::CreatePoint(constant, linear, quadratic);
		}

		/**********************************************************************************************//**
		 * @fn	void LightComponent::SetSpot(const float& cutoff)
		 *
		 * @brief	Sets a spot
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @param 	cutoff	The cutoff.
		 **************************************************************************************************/

		void SetSpot(const float& cutoff)
		{
			Light = Light::CreateSpot(cutoff);
		}

		/**********************************************************************************************//**
		 * @fn	operator const Ref<tnah::Light> () const
		 *
		 * @brief	Gets the light>
		 *
		 * @author	Chris
		 * @date	10/09/2021
		 *
		 * @tparam	tnah::Light	Type of the tnah light.
		 *
		 * @returns	A const.
		 **************************************************************************************************/

		operator const Ref<tnah::Light> () const { return Light; }

	private:
		friend class EditorUI;
		inline static std::string s_SearchString = "light component";
	};

}
