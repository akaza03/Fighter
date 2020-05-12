#pragma once
#include <cocos2d.h>

struct DirCheck
{
	bool operator()(cocos2d::Sprite & sp, struct ActData &act);
};

