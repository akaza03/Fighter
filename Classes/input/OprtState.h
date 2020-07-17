#pragma once
#include <cocos2d.h>
#include "manager/AnimManager.h"

//	押されたかどうかの判定用List
using OprtKeyList = std::map<UseKey, bool>;

class Character;

class OprtState
{
public:
	OprtState();
	virtual ~OprtState();
	virtual cocos2d::EventListener* oprtInit() = 0;
	virtual void update() = 0;
	OprtKeyList GetKeyList();
	cocos2d::Vec2 GetTouchPoint();
	bool GetFirstTouch();				//	初回タッチか調べる
	void SetFirstTouch(bool flag);		//	初回タッチのセット
protected:
	OprtKeyList _oprtKeyList;
	cocos2d::Vec2 touchPoint;

	bool firstTouchFlag;				//	初回タッチフラグ
};