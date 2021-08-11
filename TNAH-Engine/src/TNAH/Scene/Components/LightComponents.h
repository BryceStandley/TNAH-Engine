#pragma once
#include "TNAH/Core/Core.h"
#include "TNAH/Renderer/Light.h"
#include "TNAH/Scene/Light/DirectionalLight.h"
#include "TNAH/Scene/Light/PointLight.h"
#include "TNAH/Scene/Light/SpotLight.h"

namespace tnah {

	
	
	struct LightComponent
	{
		Ref<tnah::Light> Light;

		LightComponent() = default;
		LightComponent(const LightComponent& other) = default;
		LightComponent(const tnah::Light::LightType& type)
		{
			Light.reset(Light::Create(type));
		}

		void SetDirectional(const glm::vec3& direction, const glm::vec3& ambient,const glm::vec3& diffuse,
			const glm::vec3& specular)
		{
			Light.reset(Light::CreateDirectional(direction, ambient, diffuse, specular));
		}
		void SetPoint()
		{
			Light.reset(Light::CreatePoint());
		}
		void SetSpot()
		{
			Light.reset(Light::CreateSpot());
		}

		operator const Ref<tnah::Light> () const { return Light; }
	};

}
