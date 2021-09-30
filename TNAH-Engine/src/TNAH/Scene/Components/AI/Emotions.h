#pragma once

namespace tnah::Emotions {

	enum class State
	{
		Neutral = 0,
		Excited, Delighted, Happy, // High Arousal - Positive Valence
		Content, Relaxed, Calm, // Low Arousal - Positive Valence
		Tired, Board, Depressed, // Low Arousal - Negative Valence
		Frustrated, Angry, Tense // High Arousal - Negative Valence
	};

	enum class Mood
	{
		Happy, // High Arousal - Positive Valence
		Angry, // High Arousal - Negative Valence
		Sad,  // Low Arousal - Negative Valence
		Relaxed // Low Arousal - Positive Valence
	};
}