#pragma once
#include <set>
#include <string>
#include "SingletonHeaders.h"
#include "Debugger.h"

#define SEND_MESSAGE_IMMEDIATELY = 0.0;
#define SENDER_ID_IRRELEVANT = -1;

class MessageDispatcher
{
private:
	std::set<Telegram> Priority;
	void Discharge(GameObject* receiver, const Telegram msg)
	{
		if (!receiver->handleMessage(msg))
            if(Debugger::GetInstance()->debugFSMToConsole) std::cout << "Message not handled" << std::endl;
	}

public:
	void DisbatchMsgSingle(double delay, int sender, int receiver, int msg, bool all)
	{
		//Use singleton to get entity manager
		GameObject* pReceiver = entityMan::getInstance().GetEntity(receiver);
		glm::vec3 pos = entityMan::getInstance().GetEntity(sender)->GetPos();
		if (pReceiver == NULL) {
            if(Debugger::GetInstance()->debugFSMToConsole) std::cout << "Warning! No Receiver with ID of " << receiver << " found" << std::endl;
			return;
		}
		Telegram message(0.0f, sender, receiver, all, msg, pos);
		if (delay <= 0.0) {
			Discharge(pReceiver, message);
		}
		else {
			//Need to make a timer
			double currentTime = GameTimer::getInstance().curTime;
			message.dispatchTime = currentTime + delay;
			Priority.insert(message);
		}
	}

	void DisbatchMsgAllOfType(int sender, int msg, std::string type)
	{
		int max = entityMan::getInstance().Size();
		if (max > 1)
		{
			glm::vec3 pos = entityMan::getInstance().GetEntity(sender)->GetPos();
			for (int i = 0; i < max; i++)
			{
				GameObject* pReceiver = entityMan::getInstance().GetEntity(entityMan::getInstance().NumberedPos(i));
				if (pReceiver->GetType() == type && i != sender )
				{
					Telegram message(0.0f, sender, i, true, msg, pos);
					Discharge(pReceiver, message);
				}
			}
		}
	}

	void DispatchDelayedMessages()
	{
		//Need to make a timer
		double currentTime = GameTimer::getInstance().curTime;
		while (!Priority.empty() && (Priority.begin()->dispatchTime < currentTime) && (Priority.begin()->dispatchTime > 0))
		{
			const Telegram message = *Priority.begin();
			GameObject* pReceiver = entityMan::getInstance().GetEntity(message.receiver);
			Discharge(pReceiver, message);
			Priority.erase(Priority.begin());
		}
	}
};

