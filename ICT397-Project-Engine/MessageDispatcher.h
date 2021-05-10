#pragma once
#include <set>
#include <string>
#include "EntityManager.h"

#define SEND_MESSAGE_IMMEDIATELY = 0.0;
#define SENDER_ID_IRRELEVANT = -1;

class MessageDispatcher
{
private:
	std::set<Telegram> Priority;
	void Discharge(GameObject* receiver, const Telegram msg)
	{
		if (!receiver->handleMessage(msg))
			std::cout << "Message not handled" << std::endl;
	}

public:
	void DisbatchMsg(double delay, int sender, int receiver, int msg, bool all)
	{
		//Use singleton to get entity manager
		GameObject* pReceiver = entityMan.GetEntityFromID(receiver);
		if (pReceiver == NULL) {
			std::cout << "\nWarning! No Receiver with ID of " << receiver << " found" << std::endl;
			return;
		}
		Telegram message(0.0f, sender, receiver, all, msg);
		if (delay <= 0.0) {
			Discharge(pReceiver, message);
		}
		else {
			//Need to make a timer
			double currentTime = timer.getTime();
			message.dispatchTime = currentTime + delay;
			Priority.insert(message);
		}
	}

	void DispatchDelayedMessages()
	{
		//Need to make a timer
		double currentTime = timer.getTime();
		while (!Priority.empty() && (Priority.begin()->dispatchTime < currentTime) && (Priority.begin()->dispatchTime > 0))
		{
			const Telegram message = *Priority.begin();
			GameObject* pReceiver = entityMan.GetEntityFromID(message.receiver);
			Discharge(pReceiver, message);
			Priority.erase(Priority.begin());
		}
	}
};

