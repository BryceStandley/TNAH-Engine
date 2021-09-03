#pragma once

#include "TNAH/Renderer/Animation.h"

namespace tnah 
{
	class AnimatorComponent 
	{
	public:
		AnimatorComponent(Ref<Animation> animation);
		void UpdateAnimation(float dt);
		void PlayAnimation(Ref<Animation> animation);
		void CalculateBoneTransform(const AssimpNodeData* node, glm::mat4 parentTransform);
		std::vector<glm::mat4> GetFinalBonesMatrices() const { return m_FinalBoneMatrices; };

	private:
		std::vector<glm::mat4> m_FinalBoneMatrices;
		Ref<Animation> m_CurrentAnimation;
		float m_CurrentTime = 0;
		float m_DeltaTime = 0;
	};



}