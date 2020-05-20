#include "OprtKey.h"

OprtKey::OprtKey()
{
}


OprtKey::~OprtKey()
{
}


cocos2d::EventListener * OprtKey::oprtInit()
{
	auto listener = cocos2d::EventListenerKeyboard::create();

	//	�L�[���������u��
	listener->onKeyPressed = [&](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* keyEvent)
	{
		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		{
			_oprtKeyList[UseKey::K_LEFT] = true;
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			_oprtKeyList[UseKey::K_RIGHT] = true;
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW)
		{
			_oprtKeyList[UseKey::K_DOWN] = true;
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_SPACE)
		{
			_oprtKeyList[UseKey::K_SPACE] = true;
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_ENTER)
		{
			_oprtKeyList[UseKey::K_ENTER] = true;
		}
	};

	//	�L�[�𗣂����u��
	listener->onKeyReleased = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* keyEvent)
	{
		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		{
			_oprtKeyList[UseKey::K_LEFT] = false;
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			_oprtKeyList[UseKey::K_RIGHT] = false;
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW)
		{
			_oprtKeyList[UseKey::K_UP] = false;
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW)
		{
			_oprtKeyList[UseKey::K_DOWN] = false;
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_SPACE)
		{
			_oprtKeyList[UseKey::K_SPACE] = false;
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_ENTER)
		{
			_oprtKeyList[UseKey::K_ENTER] = false;
		}
	};

	return listener;
}

void OprtKey::update()
{
}
