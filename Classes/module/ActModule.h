#pragma once
#include <cocos2d.h>

struct ActModule
{
	void operator() (cocos2d::Sprite & sp, ActData &act);
};

