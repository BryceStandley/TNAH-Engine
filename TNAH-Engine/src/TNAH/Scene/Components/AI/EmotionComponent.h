#pragma once
#include "AIBehaviour.h"
#include "AITrait.h"
#include "Emotions.h"

namespace tnah {
	class EmotionComponent
	{
	public:

		void AddBehavior(const AIBehaviour& behavior) { m_Behaviors.push_back(behavior); }
		void AddTrait(const AITrait& trait) { m_Traits.push_back(trait); }

		
		/**
		 * @fn ApplyEvent();
		 * 
		 * @brief Used to apply an event to the AI. Actual values should be processed before applying the event.
		 *
		 * @author Bryce Standley
		 * @date Thursday, 30 September 2021
		 * 
		 *
		 *
		 */
		void ApplyEvent();

	private:

		/**
		 * @fn bool Initiate();
		 * 
		 * @brief Called once the conponent is set up and initiates the personality and other factors.
		 *
		 * @author Bryce Standley
		 * @date Thursday, 30 September 2021
		 * 
		 *
		 * @returns  bool if successfully initiated or not
		 *
		 */
		bool Initiate();
	
		/**
		* @fn glm::vec3 OnUpdate();
		* 
		* @brief Updates the current emotional state of the AI and returns a target position to move towards.
		*
		* @author Bryce Standley
		* @date Thursday, 30 September 2021
		* 
		*
		* @returns A target position of the AI to move towards
		*
		*/
		glm::vec3 OnUpdate();

	private:
		std::pair<float, float> m_Personality;
		//Based off the Vector Emotional Model
		float m_Arousal = 0.0f; // Used in a range of -1 to 1
		float m_Valence = 0.0f; // Used in a range of -1 to 1

		//Current emotional state
		Emotions::State m_State = Emotions::State::Neutral;

		//Current Overall mood
		Emotions::Mood m_Mood = Emotions::Mood::Happy;
	
		//Vector of all traits of the AI
		std::vector<AITrait> m_Traits;

		//vector of Behaviors used by the AI
		std::vector<AIBehaviour> m_Behaviors;
	
	};
}
