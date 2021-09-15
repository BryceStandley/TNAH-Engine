#pragma once

//TODO: Doxy Animation File!

namespace tnah {
	struct AnimationFrame
	{
		uint32_t TotalPositions = 0;

		uint32_t TotalRotations = 0;

		std::vector<std::pair<double, glm::vec3>> Positions = {};

		std::vector<std::pair<double, glm::quat>> Rotations = {};
	};
	
	class Animation
	{
	public:

		Animation();

		Animation(const std::string& name, std::map<std::string, AnimationFrame> animations, const float& duration, const float& ticksPerSecond);

		uint32_t FindRotation(const float& currentTime, const AnimationFrame* frame);
		
		uint32_t FindPosition(const float& currentTime, const AnimationFrame* frame);

		AnimationFrame* FindFrame(const std::string& frameName);

		float GetTicksPerSecond() { return m_TicksPerSecond; }

		float GetDuration() { return m_Duration; }

		std::string GetName() { return m_AnimationName; }

	private:

		std::map<std::string, AnimationFrame> m_AnimationFrames;

		float m_Duration = 0;

		float m_TicksPerSecond = 0;

		std::string m_AnimationName = "";
	
	};
}
