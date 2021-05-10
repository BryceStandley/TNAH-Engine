#include <iostream>

struct Telegram
{
	int sender;
	int receiver;
	bool universal;

	int msg;
	float dispatchTime;
	const float smallestDelay = 0.25;

	Telegram()
	{
		sender = -1;
		receiver = -1;
		dispatchTime = -1;
		universal = false;
		msg = -1;
	}

	Telegram(float time, int send, int rec, bool all, int message)
	{
		sender = send;
		receiver = rec;
		universal = all;
		msg = message;
		dispatchTime = time;
	}
};

inline bool operator==(const Telegram& t1, const Telegram& t2)
{
	return (fabs(t1.dispatchTime - t2.dispatchTime) < t1.smallestDelay)
		&& (t1.sender == t2.sender)
		&& (t1.receiver == t2.receiver)
		&& (t1.msg == t2.msg);
}

inline bool operator<(const Telegram& t1, const Telegram& t2)
{
	if (t1 == t2) { return false; }
	else {
		return (t1.dispatchTime < t2.dispatchTime);
	}
}