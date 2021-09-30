#pragma once

namespace tnah {

	
	/**
	 * @class AIBehaviour
	 * 
	 * @brief Base class for defining a AI Behaviour
	 *
	 * @author Bryce Standley
	 * @date Thursday, 30 September 2021
	 * 
	 *
	 *
	 */
	class AIBehaviour
	{
	public:

		virtual glm::vec3 OnUpdate() = 0;

		virtual ~AIBehaviour();

		
		/**
		 * @fn void ::tnah::AIBehaviour::SetArousalRange(float min)
		 * @fn void ::tnah::AIBehaviour::SetArousalRange(float max)
		 * 
		 * @brief Sets the Arousal range for triggering this behaviour
		 *
		 * @author Bryce Standley
		 * @date Thursday, 30 September 2021
		 * 
		 * @param min Arousal minimum
		 * @param max Arousal maximum
		 *
		 *
		 */
		void SetArousalRange(float min, float max)
		{
			if(min < -1)
				m_ArousalRangeTrigger.first = -1;
			else if(max > 1)
				m_ArousalRangeTrigger.second = 1;
			else
				m_ArousalRangeTrigger = {min, max};	
		}

		
		/**
		 * @fn void ::tnah::AIBehaviour::SetArousalRange(std::pair<float, float> arousal)
		 * 
		 * @brief Sets the Arousal range for triggering this behaviour
		 *
		 * @author Bryce Standley
		 * @date Thursday, 30 September 2021
		 * 
		 * @param arousal Arousal minimum and maximum
		 *
		 *
		 */
		void SetArousalRange(std::pair<float, float> arousal)
		{
			if(arousal.first < -1)
				m_ArousalRangeTrigger.first = -1;
			else if(arousal.second > 1)
				m_ArousalRangeTrigger.second = 1;
			else
				m_ArousalRangeTrigger = arousal;
		}

		void SetValenceRange(float min, float max)
		{
			if(min < -1)
				m_ValenceRangeTrigger.first = -1;
			else if(max > 1)
				m_ValenceRangeTrigger.second = 1;
			else
				m_ValenceRangeTrigger = {min, max};	
		}
		
		void SetValenceRange(std::pair<float, float> valence)
		{
			if(valence.first < -1)
				m_ValenceRangeTrigger.first = -1;
			else if(valence.second > 1)
				m_ValenceRangeTrigger.second = 1;
			else
				m_ValenceRangeTrigger = valence;
		}
		
	
	private:
		std::pair<float, float> m_ArousalRangeTrigger;
		std::pair<float, float> m_ValenceRangeTrigger;
		
	};
}