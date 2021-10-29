#pragma once
#include "Emotion.h"

namespace tnah
{
class EmotionComponent
{
public:

	EmotionComponent();
	EmotionComponent(float valence, float arousal, Mood m);

	EmotionComponent(Emotion e, Mood m, std::vector<Trait> personality) :
	m_State(e), m_Mood(m), m_Traits(personality){}

	Emotion GetEmotion() { return m_State; }
	void SetEmotion(Emotion e) { m_State = e; }

	Mood GetMood() { return m_Mood; }

	//gets the arousal of the emotion
	float GetArousal();

	//sets the arousal of the emotion to the given value
	void SetArousal(float arousal);

	//gets the valence value of the emotion
	float GetValence();

	//sets the valence of the emotion to the given value
	void SetValence(float valence);

	//increases arousal by the value given
	void IncreaseArousal(float arousal);

	//decreases arousal by the value given
	void DecreaseArousal(float arousal);

	//increases valence by the value given
	void IncreaseValence(float valence);

	//decreases arousal by the value given
	void DecreaseValence(float valence);

	

	//Returns the Arousal and Valence of a given Emotion
	Emotion ReturnEmotion(float arousal, float valence);

	//checks if emotion is present in map, otherwise adds the emotion to the map 
	void AddEmotion(float arousal, float valence, Emotion e);

	void RemoveEmotion(float arousal, float valence);

	void AddTrait(Trait t);

	void Update(float dt);

	float GetScaledArousal(float value);

	float GetScaledValence(float value);

	float GetPositiveValenceMultiplier() { return m_MultiplierPositiveValence; }
	float GetNegativeValenceMultiplier() { return m_MultiplierNegativeValence; }

	float GetPositiveArosualMultiplier() { return m_MultiplierPositiveArousal; }
	float GetNegativeArousalMultiplier() { return m_MultiplierNegativeArousal; }
	
	void SetMood(Mood m);

	std::string GetCurrentEmotionAsString();
	std::string GetCurrentMoodAsString();
	std::string GetTraitAsString(int pos);
	std::string GetTraitsAsString();
	
	void UpdateTimer() {internalTimer = 15.0f;}
private:

	//initalises the map with all the emotions used
	void InitialiseMap();

	void UpdateMood(float dt);
	//std::pair<float, float> m_EmotionValues;
	std::map <std::pair<float,float>, Emotion> EmotionMap;
	std::map <std::pair<float, float>, Emotion>::iterator it = EmotionMap.begin();


	float m_Arousal = 0.0f; // Range of -1 to 1
	float m_Valence = 0.0f; // Range of -1 to 1
	float m_MultiplierPositiveValence = 1.0f;
	float m_MultiplierNegativeValence = 1.0f;	
	float m_MultiplierPositiveArousal = 1.0f;
	float m_MultiplierNegativeArousal = 1.0f;
	
	// Current Emotional State
	Emotion m_State = Emotion::Neutral;

	// Current Mood
	Mood m_Mood = Mood::Neutral;

	// Vector of all traits of the AI - AKA its Personality
	std::vector<Trait> m_Traits;
	std::vector<Trait>::iterator itr;
	float internalTimer;
};
}
