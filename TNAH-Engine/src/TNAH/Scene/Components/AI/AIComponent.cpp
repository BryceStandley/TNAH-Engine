#include "tnahpch.h"
#include "AIComponent.h"

namespace tnah {


	void AIComponent::OnUpdate(Timestep deltaTime)
	{
		//Get the current position of the agent
		// find the direction = glm::normalize(targetPosition - currentPosition)
		// new position = current position + (direction * movementSpeed * deltaTime.GetSeconds())
	}

}