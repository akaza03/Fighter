#pragma once
#include <cocos2d.h>

struct AnimUpdate
{
	bool operator() (cocos2d::Sprite & sp, ActData &act);
};

