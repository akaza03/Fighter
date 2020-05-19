#include "Number.h"

// 数字の画像ファイル名の設定
void Number::setPrefix(std::string prefix)
{
	auto str = cocos2d::__String::createWithFormat("image/UI/counter/%s.plist", prefix.c_str());
	cache->addSpriteFramesWithFile(str->getCString());
}

void Number::setSpan(int span)
{
	_span = span;
}

void Number::setAlignCenter()
{
	_alignCenter = true;
}

void Number::setNumber(int num)
{
	RemoveNumber();
	CreateNumber(num);
}

void Number::remove(void)
{
	RemoveNumber();
	removeFromParentAndCleanup(true);
}

bool Number::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	_alignCenter = false;
	// 透明度の設定
	setCascadeOpacityEnabled(true);

	_num = 0;
	auto figure = cocos2d::Sprite::create();
	figure->setTag(1);
	addChild(figure);

	cache = cocos2d::SpriteFrameCache::getInstance();

	scheduleUpdate();
	return true;
}

void Number::CreateNumber(int num)
{
	_num = num;
	auto number = cocos2d::StringUtils::format("%d", _num);
	long length = number.length();

	int baseX = 0;
	if (_alignCenter)
	{
		if (0 < length)
		{
			baseX = static_cast<int>(length - 1) * _span / 2;
		}
	}
	for (int i = 0; i < length; i++)
	{
		auto charFigure = number.substr(length - 1 - i, 1);
		std::string imageFile = cocos2d::StringUtils::format("%s.png", charFigure.c_str());
		auto figure = Sprite::createWithSpriteFrame(cache->getSpriteFrameByName(imageFile));
		figure->setPosition(cocos2d::Point(baseX - i * _span, 0));
		figure->setTag(i + 1);
		addChild(figure);
	}
}


void Number::RemoveNumber(void)
{
	auto number = std::to_string(_num);
	long length = number.length();

	if (getChildrenCount() == 0)
	{
		return;
	}

	for (int i = 0; i < length; i++)
	{
		auto pNumber = getChildByTag(1 + i);
		removeChild(pNumber,true);
	}
}
