#include "OprtTouch.h"


OprtTouch::OprtTouch()
{
}


OprtTouch::~OprtTouch()
{
}

cocos2d::EventListener * OprtTouch::oprtInit()
{
	//	シングルタッチ
	auto listener = cocos2d::EventListenerTouchOneByOne::create();

	listener->onTouchBegan = [this](cocos2d::Touch* touch, cocos2d::Event* event)->bool
	{
		_startTouchPos = touch->getLocation();
		touchPoint = _startTouchPos;

		auto nowScene = cocos2d::Director::getInstance()->getRunningScene();

		firstTouchFlag = true;

		//	開始位置に目印を作成
		auto StartSP = cocos2d::Sprite::create("CloseNormal.png");
		StartSP->setPosition(_startTouchPos);
		StartSP->setScale(2);
		nowScene->addChild(StartSP,0,"touchIcon");

		return true;
	};

	//	スワイプ移動時
	listener->onTouchMoved = [this](cocos2d::Touch* touch, cocos2d::Event* event)->bool
	{
		firstTouchFlag = false;
		return true;
	};

	listener->onTouchEnded = [this](cocos2d::Touch* touch, cocos2d::Event* event)->bool
	{
		firstTouchFlag = false;

		//	タッチ開始位置の目印を削除
		auto nowScene = cocos2d::Director::getInstance()->getRunningScene();
		nowScene->removeChildByName("touchIcon");

		for (auto itrKey : UseKey())
		{
			_oprtKeyList[itrKey] = false;
		}
		return true;
	};

	return listener; 
}

void OprtTouch::update()
{
}
