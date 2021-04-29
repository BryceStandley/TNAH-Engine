#pragma once

#include "state.h"

template<class entity>
class stateMachine
{
private:
	entity* owner;
	State<entity>* previousState;
	State<entity>* currentState;
	State<entity>* globalState;

public:
	stateMachine(entity* FSMowner)
	{
		owner = FSMowner;
		previousState = nullptr;
		currentState = nullptr;
		globalState = nullptr;
	}

	void setPreviousState(State<entity>* st) { previousState = st; }
	void setCurrentState(State<entity>* st) { currentState = st; }
	void setGlobalState(State<entity>* st) { globalState = st; }

	void update() const
	{
		if (globalState)
			globalState->Execute(owner);
		if (currentState)
			currentState->Execute(owner);
	}

	void changeState(State<entity>* newState)
	{
		//the current state becomes the previous state
		previousState = currentState;
		//exit state
		currentState->Exit(owner);
		//change current state to new state
		currentState = newState;
		//enter the new current state
		currentState->Enter(owner);
	}

	void revertToPreviousState() 
	{
		currentState = previousState;
	}

	State<entity>* getPreviousState() { return previousState; }
	State<entity>* getCurrentState() { return currentState; }
	State<entity>* getGlobalState() { return globalState; }

	bool isInState(const State<entity>& st) const 
	{
		return typeid(*currentState) == typeid(st);
	}

	virtual ~stateMachine() {}

};