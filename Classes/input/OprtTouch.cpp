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

	//	マルチタッチ
	//auto listener = cocos2d::EventListenerTouchAllAtOnce::create();

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

		auto moveSP = cocos2d::Sprite::create("CloseNormal.png");
		moveSP->setPosition(_startTouchPos);
		nowScene->addChild(moveSP, 0, "moveIcon");

		//lpEffectManager.SetEffect((RES_ID("changeEff").c_str()), "UILayer", false, _startTouchPos, 20, true);

		return true;
	};

	//	スワイプ移動時
	listener->onTouchMoved = [this](cocos2d::Touch* touch, cocos2d::Event* event)->bool
	{
		firstTouchFlag = false;
		checkKey(touch->getLocation());
		auto nowScene = cocos2d::Director::getInstance()->getRunningScene();
		nowScene->getChildByName("moveIcon")->setPosition(touch->getLocation());

		return true;
	};

	listener->onTouchEnded = [this](cocos2d::Touch* touch, cocos2d::Event* event)->bool
	{
		firstTouchFlag = false;
		auto nowScene = cocos2d::Director::getInstance()->getRunningScene();
		nowScene->removeChildByName("touchIcon");
		nowScene->removeChildByName("moveIcon");
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

void OprtTouch::checkKey(cocos2d::Vec2 touchPos)
{
	auto offset = 50;
	if (touchPos.x < _startTouchPos.x - offset)
	{
		_oprtKeyList[UseKey::K_LEFT] = true;
	}
	else
	{
		_oprtKeyList[UseKey::K_LEFT] = false;
	}

	if (touchPos.x > _startTouchPos.x + offset)
	{
		_oprtKeyList[UseKey::K_RIGHT] = true;
	}
	else
	{
		_oprtKeyList[UseKey::K_RIGHT] = false;
	}

	if (touchPos.y > _startTouchPos.y + offset)
	{
		_oprtKeyList[UseKey::K_UP] = true;
	}
	else
	{
		_oprtKeyList[UseKey::K_UP] = false;
	}

	if (touchPos.y < _startTouchPos.y - offset)
	{
		_oprtKeyList[UseKey::K_DOWN] = true;
	}
	else
	{
		_oprtKeyList[UseKey::K_DOWN] = false;
	}
}

