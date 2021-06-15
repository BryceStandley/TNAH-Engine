#pragma once
#include "singleton.h"
#include "EntityManager.h"
#include "DynamicEnum.h"
#include "Timer.h"

typedef singleton<DynamicEnum> message;
typedef singleton<EntityManager> entityMan;
typedef singleton<Timer> GameTimer;