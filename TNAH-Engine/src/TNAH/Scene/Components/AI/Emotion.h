#pragma once

namespace tnah
{
    enum class Emotion 
{
	Neutral = 0,
	Excited, Delighted, Happy, // High Arousal - Positive Valence
	Content, Relaxed, Calm, // Low Arousal - Positive Valence
	Tense, Angry, Frustrated, // High Arousal - Negative Valence
	Depressed, Bored, Tired, Fuckboy // Low Arousal - Negative Valence
};

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

enum class Mood 
{
	Neutral = 0,
	Happy, // High Arousal - Positive Valence
	Angry, // High Arousal - Negative Valence
	Sad, // Low Arousal - Negative Valence 
	Relaxed // Low Arousal - Positive Valence
};

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

enum class Trait
{
	Neutral,

	Cheerful, Delighted, Happy, // High Arousal - Positive Valence
	Depressed, Bland, Sad, // Low Arousal - Negative Valence


	Carefree, Peaceful, Patient, // Low Arousal - Positive Valence
	Paranoid, Aggressive, Impatient // High Arousal - Negative Valence
	
	//chair 
	//bin Patient, Happy, Anxious 
	//bushes Depressed, Happy, Easygoing
};

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
