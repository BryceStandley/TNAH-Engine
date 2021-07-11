#pragma once


	/**
	* @class state
	* @brief An abstract class that provides a common interface to all state classes. It is templated so that class can be reused in any state machine.
	*
	* @author Dylan Blereau
	* @version 01
	* @date 25/04/2021 Dylan Blereau, Started
	*
	*
	**/
template<class entity>
class TNAH_API State
{
public:

		/**
		* @brief virtual destructor
		*
		*/
	virtual ~State() {}

		/**
		* @brief pure virtual function that represents the enter point of the state
		* @param entity* - a pointer to the entity class
		*/
	virtual void Enter(entity*) = 0;

		/**
		* @brief pure virtual function that represents the execute stage of the state
		* @param entity* - a pointer to the entity class
		*/
	virtual void Execute(entity*) = 0;

		/**
		* @brief pure virtual function that represents the exit stage of the state
		* @param entity* - a pointer to the entity class
		*/
	virtual void Exit(entity*) = 0;
};