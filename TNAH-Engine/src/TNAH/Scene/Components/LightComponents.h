#pragma once
#include "TNAH/Core/Core.h"
#include "TNAH/Renderer/Light.h"
#include "TNAH/Scene/Light/DirectionalLight.h"
#include "TNAH/Scene/Light/PointLight.h"
#include "TNAH/Scene/Light/SpotLight.h"
#include "ComponentBase.h"

namespace tnah {

	
	
	class LightComponent : public Component
	{
	public:
		Ref<Light> Light;

		
		LightComponent() = default;
		LightComponent(const LightComponent& other) = default;
		LightComponent(const tnah::Light::LightType& type)
		{
			Light = Light::Create(type);
		}

		void SetDirectional(const glm::vec3& direction, const glm::vec3& ambient,const glm::vec3& diffuse,
			const glm::vec3& specular)
		{
			Light = Light::CreateDirectional(direction, ambient, diffuse, specular);
		}
		void SetPoint(const float& constant, const float& linear, const float& quadratic)
		{
			Light = Light::CreatePoint(constant, linear, quadratic);
		}
		void SetSpot(const float& cutoff)
		{
			Light = Light::CreateSpot(cutoff);
		}

		operator const Ref<tnah::Light> () const { return Light; }

	private:
		friend class EditorUI;
		inline static std::string s_SearchString = "light component";
	};

}
