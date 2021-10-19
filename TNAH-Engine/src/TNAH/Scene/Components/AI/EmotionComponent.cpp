#include "tnahpch.h"
#include "EmotionComponent.h"

namespace tnah
{
	float EmotionComponent::GetArousal() { return m_Arousal; }
	float EmotionComponent::GetValence() { return m_Valence; }

	EmotionComponent::EmotionComponent()
	{
		InitialiseMap();
	}

	EmotionComponent::EmotionComponent(float valence, float arousal, Mood m)
	{
		InitialiseMap();	
		SetMood(m);
		SetValence(valence);
		SetArousal(arousal);
	}

	void EmotionComponent::SetArousal(float arousal) 
	{ 
		if (arousal > 1)
			m_Arousal = 1;
		else if (arousal < -1)
			m_Arousal = -1;
		else
			m_Arousal = arousal;
	}
	void EmotionComponent::SetValence(float valence) 
	{
		if (valence > 1)
			m_Valence = 1;
		else if (valence < -1)
			m_Valence = -1;
		else
			m_Valence = valence; 
	}

	void EmotionComponent::IncreaseArousal(float arousal)
	{
		// if emotion matches current mood
		m_Arousal = m_Arousal + (arousal * m_MultiplierPositiveArousal);

		//else m_Arusal = m_Arousal + (arousal * multiplier)

		//adjusts arousal if value overflows to ensure accuracy
		if (m_Arousal > 1)
			m_Arousal = 1;
	}

	void EmotionComponent::DecreaseArousal(float arousal)
	{
		// if emotion matches current mood
		m_Arousal = m_Arousal - (arousal * m_MultiplierNegativeArousal);

		//else m_Arusal = m_Arousal - (arousal * multiplier)

		//adjusts arousal if value overflows to ensure accuracy
		if (m_Arousal < -1)
			m_Arousal = -1;
	}

	void EmotionComponent::IncreaseValence(float valence)
	{
		// if emotion matches current mood
		m_Valence = m_Valence + (valence * m_MultiplierPositiveValence);

		//else m_Valence = m_Valence + (valence * multiplier)

		//adjusts arousal if value overflows to ensure accuracy
		if (m_Valence > 1)
			m_Valence = 1;
	}

	void EmotionComponent::DecreaseValence(float valence)
	{
		// if emotion matches current mood
		m_Valence = m_Valence - (valence * m_MultiplierNegativeValence);

		//else m_Valence = m_Valence - (valence * multiplier)

		//adjusts arousal if value overflows to ensure accuracy
		if (m_Valence < -1)
			m_Valence = -1;
	}


	void EmotionComponent::InitialiseMap()
	{
		// High Arousal - Positive Valence
		EmotionMap.insert({ (std::make_pair(1.0f, 0.5f)), Emotion::Excited });
		EmotionMap.insert({ (std::make_pair(0.66f, 0.5f)), Emotion::Delighted });
		EmotionMap.insert({ (std::make_pair(0.33f, 0.5f)), Emotion::Happy });

		// Low Arousal - Positive Valence
		EmotionMap.insert({ (std::make_pair(-0.33f, 0.5f)), Emotion::Content });
		EmotionMap.insert({ (std::make_pair(-0.66f, 0.5f)), Emotion::Relaxed });
		EmotionMap.insert({ (std::make_pair(-1.0f, 0.5f)), Emotion::Calm });

		// High Arousal - Negative Valence
		EmotionMap.insert({ (std::make_pair(1.0f, -0.5f)), Emotion::Tense });
		EmotionMap.insert({ (std::make_pair(0.66f, -0.5f)), Emotion::Angry });
		EmotionMap.insert({ (std::make_pair(0.33f, -0.5f)), Emotion::Relaxed });

		// Low Arousal - Negative Valence
		EmotionMap.insert({ (std::make_pair(-0.33f, -0.5f)), Emotion::Depressed });
		EmotionMap.insert({ (std::make_pair(-0.66f, -0.5)), Emotion::Bored });
		EmotionMap.insert({ (std::make_pair(-1.0f, -0.5)), Emotion::Tired });
	}

	Emotion EmotionComponent::ReturnEmotion(float arousal, float valence)
	{
		std::pair<float, float> emotionVals{ arousal, valence };
		it = EmotionMap.find(emotionVals);

		if (!EmotionMap.count(emotionVals))
			TNAH_CORE_ERROR("Emotion not within map: {0} {1} ", emotionVals.first, emotionVals.second);
		else 
			return it->second;
			
	}

	void EmotionComponent::AddEmotion(float arousal, float valence, Emotion e)
	{
		std::pair<float, float> emotionVals{ arousal,valence };
		if (EmotionMap.count(emotionVals))
			TNAH_CORE_ERROR("Values aready in map: {0} {1} ", emotionVals.first, emotionVals.second);
		/*else
			std::cout << "Added to map" << std::endl;*/
		EmotionMap.insert({ emotionVals, e });
	}

	void EmotionComponent::RemoveEmotion(float arousal, float valence)
	{
		std::pair<float, float> emotionVals{ arousal, valence };
		/*if (EmotionMap.count(emotionVals))
			std::cout << "Emotion removed from map" << std::endl;
		else
			std::cout << "Emotion not in map" << std::endl;*/
		EmotionMap.erase(emotionVals);

	}

	float EmotionComponent::GetScaledArousal(float value)
	{
		float scaledValue = 0;
		if (value >= 0)
		{
			if (value <= 1.0f && value > 0.66f)
				scaledValue = 1.0f;
			else if (value <= 0.66f && value > 0.33f)
				scaledValue = 0.66f;
			else
				scaledValue = 0.33f;
		}
		else
		{
			if (value >= -1.0f && value < -0.66f)
				scaledValue = -1.0f;
			else if (value >= -0.66f && value < -0.33f)
				scaledValue = -0.66f;
			else
				scaledValue = -0.33f;
		}
		return scaledValue;
	}

	float EmotionComponent::GetScaledValence(float value)
	{
		float scaledValue = 0;
		if (value >= 0)
		{
			scaledValue = 0.5f;
		}
		else
		{
			scaledValue = -0.5f;
		}
		return scaledValue;
	}

	void EmotionComponent::AddTrait(Trait t)
	{
		if (m_Traits.size() > 3)
			TNAH_CORE_WARN("Object already has 3 traits");
		else if (std::find(m_Traits.begin(), m_Traits.end(), t) != m_Traits.end())
			TNAH_CORE_WARN("Trait exits");
		else
		{
			m_Traits.push_back(t);
			switch (t)
			{
			case Trait::Happy:
				m_MultiplierPositiveArousal += 0.1f; //more likely to feel positive
				m_MultiplierPositiveValence += 0.1f;
				
				m_MultiplierNegativeArousal -= 0.1f; //less likely to feel negative
				m_MultiplierNegativeValence -= 0.1f;
				break;

			case Trait::Delighted:

				m_MultiplierPositiveArousal += 0.2f; //more likely to feel positive
				m_MultiplierPositiveValence += 0.2f;

				m_MultiplierNegativeArousal -= 0.2f; //less likely to feel negative
				m_MultiplierNegativeValence -= 0.2f;
				break;


			case Trait::Cheerful:
				m_MultiplierPositiveArousal += 0.3f; //more likely to feel positive
				m_MultiplierPositiveValence += 0.3f;

				m_MultiplierNegativeArousal -= 0.3f; //less likely to feel negative
				m_MultiplierNegativeValence -= 0.3f;
				break;

			case Trait::Sad:
				m_MultiplierPositiveArousal -= 0.3f; //arousal more likely to decrease
				m_MultiplierPositiveValence -= 0.3f; //less likely to feel positive

				m_MultiplierNegativeArousal += 0.3f; // negative arousal more likely to increase
				m_MultiplierNegativeValence += 0.3f; //more likely to feel negative
				break;

			case Trait::Bland:
				m_MultiplierPositiveArousal -= 0.2f; //arousal more likely to decrease
				m_MultiplierPositiveValence -= 0.2f; //less likely to feel positive

				m_MultiplierNegativeArousal += 0.2f; // negative arousal more likely to increase
				m_MultiplierNegativeValence += 0.2f; //more likely to feel negative
				break;

			case Trait::Depressed:
				m_MultiplierPositiveArousal -= 0.1f; //arousal more likely to decrease
				m_MultiplierPositiveValence -= 0.1f; //less likely to feel positive

				m_MultiplierNegativeArousal += 0.1f; // negative arousal more likely to increase
				m_MultiplierNegativeValence += 0.1f; //more likely to feel negative
				break;

			case Trait::Patient:
				m_MultiplierNegativeArousal -= 0.1f; //arousal more likely to decrease
				break;

			case Trait::Peaceful:
				m_MultiplierNegativeArousal -= 0.2f; //arousal more likely to decrease
				m_MultiplierPositiveValence -= 0.2f; // more likely to feel positive
				break;

			case Trait::Carefree:
				m_MultiplierNegativeArousal -= 0.3f; //arousal more likely to decrease
				m_MultiplierPositiveValence -= 0.3f; // more likely to feel positive
				break;

			case Trait::Impatient:
				m_MultiplierPositiveArousal += 0.1f; //arousal more likely to increase
				break;

			case Trait::Aggressive:
				m_MultiplierPositiveArousal += 0.2f; //arousal more likely to increase
				m_MultiplierNegativeValence += 0.2f; //more likely to feel negative
				break;

			case Trait::Paranoid:
				m_MultiplierPositiveArousal += 0.3f; //arousal more likely to decrease
				m_MultiplierNegativeValence += 0.3f; //more likely to feel negative
				break;
			}
			//std::cout << "Trait added!" << std::endl;
			//std::cout << "Positive Arousal: " << m_MultiplierPositiveArousal << " Negative Arousal: " << m_MultiplierNegativeArousal << std::endl;
			//std::cout << "Positive Valence: " << m_MultiplierPositiveValence << " Negative Valence: " << m_MultiplierNegativeValence << std::endl;
		}
	}

	void EmotionComponent::Update()
	{
		//std::cout << "Positive Arousal: " << m_MultiplierPositiveArousal << " Negative Arousal: " << m_MultiplierNegativeArousal << std::endl;
		//std::cout << "Positive Valence: " << m_MultiplierPositiveValence << " Negative Valence: " << m_MultiplierNegativeValence << std::endl;

		Emotion em = ReturnEmotion(GetScaledArousal(GetArousal()), GetScaledValence(GetValence()));
		m_State = em;
    		
		//std::cout << "Arousal: " << GetArousal() << " Valence: " << GetValence() << std::endl;
		//std::cout << em << std::endl;
	}

	void EmotionComponent::SetMood(Mood m)
	{
		switch (m)
		{
		case Mood::Happy:
			m_MultiplierPositiveArousal += 0.25f; //more likely to feel positive
			m_MultiplierPositiveValence += 0.5f;

			m_MultiplierNegativeArousal -= 0.25f; //less likely to feel negative
			m_MultiplierNegativeValence -= 0.25f;
			break;
		case Mood::Angry:
			m_MultiplierPositiveArousal += 0.25f; //less likely to feel positive
			m_MultiplierPositiveValence -= 0.25f;

			m_MultiplierNegativeArousal -= 0.25f; //more likely to feel negative
			m_MultiplierNegativeValence += 0.25f;
			break;
		case Mood::Sad:
			m_MultiplierPositiveArousal -= 0.25f; //more likely to feel positive
			m_MultiplierPositiveValence -= 0.25f;

			m_MultiplierNegativeArousal += 0.25f; //less likely to feel negative
			m_MultiplierNegativeValence += 0.25f;
			break;
		case Mood::Relaxed:
			m_MultiplierPositiveArousal -= 0.25f; //more likely to feel positive
			m_MultiplierPositiveValence += 0.25f;

			m_MultiplierNegativeArousal += 0.25f; //less likely to feel negative
			m_MultiplierNegativeValence -= 0.25f;
			break;

		default:
			break;
		}
		//std::cout << "Positive Arousal: " << m_MultiplierPositiveArousal << " Negative Arousal: " << m_MultiplierNegativeArousal << std::endl;
		//std::cout << "Positive Valence: " << m_MultiplierPositiveValence << " Negative Valence: " << m_MultiplierNegativeValence << std::endl;
	}
}