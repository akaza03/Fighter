#pragma once
#include "OprtState.h"

class OprtKey
	:public OprtState
{
public:
	OprtKey();
	~OprtKey();
	cocos2d::EventListener* oprtInit();
	void update();
};

