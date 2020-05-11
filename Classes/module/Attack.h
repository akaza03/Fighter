#pragma once
#include <cocos2d.h>

struct Attack
{
	bool operator()(cocos2d::Sprite & sp, struct ActData &act);
};
