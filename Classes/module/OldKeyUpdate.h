#pragma once
#include <cocos2d.h>

struct OldKeyUpdate
{
	bool operator()(cocos2d::Sprite & sp, struct ActData &act);
};