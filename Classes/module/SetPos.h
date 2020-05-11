#pragma once
#include <cocos2d.h>

struct SetPos
{
	bool operator()(cocos2d::Sprite & sp, struct ActData &act);
};

