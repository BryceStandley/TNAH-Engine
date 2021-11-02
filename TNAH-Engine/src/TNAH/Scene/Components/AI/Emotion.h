#pragma once

namespace tnah
{
	/**
	 * @brief each emotional state is represented in this enum class
	 */
    enum class Emotion 
	{
	Neutral = 0,
	Excited, Delighted, Happy, // High Arousal - Positive Valence
	Content, Relaxed, Calm, // Low Arousal - Positive Valence
	Tense, Angry, Frustrated, // High Arousal - Negative Valence
	Depressed, Bored, Tired,  // Low Arousal - Negative Valence
	};

	/**
	 * @fn  operator<<
	 * 
	 * @brief  Used to allow for the printing of Emotion states
	 * 
	 * @author Dylan Blereau
	 * @date   2/11/2021
	 * 
	 * @param os - output stream object 
	 * @param e - refers to the Emotion states
	 * @return - output stream 
	 */
	inline std::ostream& operator<<(std::ostream& os, Emotion e) 
	{
		switch (e) 
		{
		case Emotion::Happy: 
			return os << "Happy";
			break;
		case Emotion::Delighted:
			return os << "Delighted";
			break;

		case Emotion::Excited:
			return os << "Excited";
			break;
		case Emotion::Calm:
			return os << "Calm";
			break;
		case Emotion::Relaxed:
			return os << "Relaxed";
			break;
		case Emotion::Content:
			return os << "Content";
			break;
		case Emotion::Frustrated:
			return os << "Frustrated";
			break;
		case Emotion::Angry:
			return os << "Angry";
			break;
		case Emotion::Tense:
			return os << "Tense";
			break;
		case Emotion::Tired:
			return os << "Tired";
			break;
		case Emotion::Bored:
			return os << "Bored";
			break;
		case Emotion::Depressed:
			return os << "Depressed";
			break;

		default:
			return os << "Neutral";
		}
	}

	/**
	 * @brief each mood state is represented in this enum class
	 */
	enum class Mood 
	{
		Neutral = 0,
		Happy, // High Arousal - Positive Valence
		Angry, // High Arousal - Negative Valence
		Sad, // Low Arousal - Negative Valence 
		Relaxed // Low Arousal - Positive Valence
	};

	/**
	 * @fn  operator<<
	 *
	 * @brief  Used to allow for the printing of Mood states
	 *
	 * @author Dylan Blereau
	 * @date   2/11/2021
	 *
	 * @param os - output stream object
	 * @param m - refers to the Mood states
	 * @return - output stream
	 */
	inline std::ostream& operator<<(std::ostream& os, Mood m)
	{
		switch (m)
		{
		case Mood::Happy:
			return os << "Happy";
			break;
		case Mood::Angry:
			return os << "Delighted";
			break;
		case Mood::Sad:
			return os << "Excited";
			break;
		case Mood::Relaxed:
			return os << "Calm";
			break;
	
		default:
			return os << "Neutral";
		}
	}

	/**
	 * @brief each character trait is represented in this enum class
	 */
	enum class Trait
	{
		Neutral,

		Cheerful, Delighted, Happy, // High Arousal - Positive Valence
		Depressed, Bland, Sad, // Low Arousal - Negative Valence


		Carefree, Peaceful, Patient, // Low Arousal - Positive Valence
		Paranoid, Aggressive, Impatient // High Arousal - Negative Valence
	};

	/**
	 * @fn  operator<<
	 *
	 * @brief  Used to allow for the printing of character traits
	 *
	 * @author Dylan Blereau
	 * @date   2/11/2021
	 *
	 * @param os - output stream object
	 * @param e - refers to the character Traits
	 * @return - output stream
	 */
	inline std::ostream& operator<<(std::ostream& os, Trait t)
	{
		switch (t)
		{
		case Trait::Happy:
			return os << "Happy";
			break;
		case Trait::Delighted:
			return os << "Delighted";
			break;
		case Trait::Cheerful:
			return os << "Cheerful";
			break;
		case Trait::Sad:
			return os << "Sad";
			break;
		case Trait::Bland:
			return os << "Bland";
			break;
		case Trait::Depressed:
			return os << "Depressed";
			break;
		case Trait::Patient:
			return os << "Patient";
			break;
		case Trait::Peaceful:
			return os << "Peaceful";
			break;
		case Trait::Carefree:
			return os << "Carefree";
			break;
		case Trait::Impatient:
			return os << "Impatient";
			break;
		case Trait::Aggressive:
			return os << "Aggressive";
			break;
		case Trait::Paranoid:
			return os << "Paranoid";
			break;

		default:
			return os << "Neutral";
		}
	}
}
