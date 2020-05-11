#pragma once
#include <cocos2d.h>

struct Move
{
	bool operator()(cocos2d::Sprite & sp, struct ActData &act);
};

