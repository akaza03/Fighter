#pragma once
#include <cocos2d.h>

struct DamageCheck
{
	bool operator()(cocos2d::Sprite & sp, struct ActData &act);
};

