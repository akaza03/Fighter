#pragma once
#include <cocos2d.h>

struct Blow
{
	bool operator()(cocos2d::Sprite & sp, struct ActData &act);
};

