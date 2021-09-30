#include "tnahpch.h"
#include "EmotionComponent.h"

namespace tnah {

	void EmotionComponent::ApplyEvent()
	{
		//update this to take in values and apply an event to the current emotional state
	}

	bool EmotionComponent::Initiate()
	{
		//Loop over all traits and set the arousal and valence for the personality.
	}

	glm::vec3 EmotionComponent::OnUpdate()
	{
	 // update the current emotion by using the personality and mood values.
		// then check and trigger any behaviours set
	}
}
