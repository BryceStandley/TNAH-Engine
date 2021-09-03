#pragma once

#include "TNAH/Renderer/Animation.h"

namespace tnah 
{
	class AnimatorComponent 
	{
	public:
		AnimatorComponent();
		AnimatorComponent(const Animation& animation);
		void UpdateAnimation(float dt);
		void PlayAnimation(const Animation& animation);
		
		std::vector<glm::mat4> GetFinalBonesMatrices() const { return m_FinalBoneMatrices; };

	private:
		void CalculateBoneTransform(const AssimpNodeData* node, glm::mat4 parentTransform);
	
	private:
		std::vector<glm::mat4> m_FinalBoneMatrices;
		Animation m_CurrentAnimation;
		float m_CurrentTime = 0;
		float m_DeltaTime = 0;
	};



}