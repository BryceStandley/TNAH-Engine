#pragma once

template<class entity>
class State 
{
public:

	virtual ~State() {}

	virtual void Enter(entity*) = 0;
	virtual void Execute(entity*) = 0;
	virtual void Exit(entity*) = 0;
};