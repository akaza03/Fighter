#pragma once
#include "OprtState.h"

class OprtTouch
	:public OprtState
{
public:
	OprtTouch();
	~OprtTouch();
	cocos2d::EventListener* oprtInit();
	void update();

private:
	cocos2d::Vec2 _startTouchPos;					//	タッチ開始時の座標
};

