#pragma once
#include "singleton.h"
#include "state.h"

class Enemy;

class wander :public State<Enemy>
{
public:

	virtual void Enter(Enemy* dude);
	virtual void Execute(Enemy* dude);
	virtual void Exit(Enemy* dude);
};

class chase : public State<Enemy>
{
public:
	virtual void Enter(Enemy* dude);
	virtual void Execute(Enemy* dude);
	virtual void Exit(Enemy* dude);
};

class flee :public State<Enemy>
{
public:
	virtual void Enter(Enemy* dude);
	virtual void Execute(Enemy* dude);
	virtual void Exit(Enemy* dude);
};

class attack :public State<Enemy>
{
public:

	virtual void Enter(Enemy* dude);
	virtual void Execute(Enemy* dude);
	virtual void Exit(Enemy* dude);
};

class die :public State<Enemy>
{
public:

	virtual void Enter(Enemy* dude);
	virtual void Execute(Enemy* dude);
	virtual void Exit(Enemy* dude);
};

class global :public State<Enemy>
{
public:
	virtual void Enter(Enemy* dude);
	virtual void Execute(Enemy* dude);
	virtual void Exit(Enemy* dude);
};

typedef  singleton<wander> wander_state;
typedef  singleton<chase> chase_state;
typedef  singleton<flee> flee_state;
typedef  singleton<attack> attack_state;
typedef  singleton<die> die_state;

typedef  singleton<global> global_state;

