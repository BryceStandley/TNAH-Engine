#include "tnahpch.h"
#include "Animation.h"

namespace tnah {


	Animation::Animation()
	{
	}

	Animation::Animation(const std::string& name, std::map<std::string, AnimationFrame> animations,
		const float& duration, const float& ticksPerSecond)
			:m_AnimationFrames(std::move(animations)), m_Duration(duration), m_TicksPerSecond(ticksPerSecond), m_AnimationName(name)
	{
	}

	uint32_t Animation::FindRotation(const float& currentTime, const AnimationFrame* frame)
	{
		for(uint32_t i = 0; i < frame->TotalRotations; i++)
		{
			if(currentTime < frame->Rotations[i + 1].first)
			{
				return i;
			}
		}
		return 0;
	}

	uint32_t Animation::FindPosition(const float& currentTime, const AnimationFrame* frame)
	{
		for(uint32_t i = 0; i < frame->TotalPositions; i++)
		{
			if(currentTime < frame->Positions[i + 1].first)
			{
				return i;
			}
		}
		return 0;
	}

	AnimationFrame* Animation::FindFrame(const std::string& frameName)
	{
		if(m_AnimationFrames.count(frameName))
		{
			return &m_AnimationFrames.at(frameName);
		}
		return nullptr;
	}
}
