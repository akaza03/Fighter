#include "unit/Character.h"
#include "Attack.h"

bool Attack::operator()(cocos2d::Sprite & sp, ActData & act)
{
	//	‰æ–Ê‰¡ƒTƒCƒY
	auto scSizeX = cocos2d::Director::getInstance()->getOpenGLView()->getDesignResolutionSize().width;

	act.atkFlag = true;
	//	Android”Å
	if ((CC_TARGET_PLATFORM != CC_PLATFORM_WIN32) && (CC_TARGET_PLATFORM != CC_PLATFORM_MAC) && (CC_TARGET_PLATFORM != CC_PLATFORM_LINUX))
	{
		if (sp.getActionByTag(10))
		{
		}
		else if (act.touchPos.x >= 0 && act.touchPos.x < scSizeX / 2)
		{
			if (act.dir == DIR::RIGHT)
			{
				act.dirInver = true;
			}
		}
		else if (act.touchPos.x >= scSizeX / 2 && act.touchPos.x <= scSizeX)
		{
			if (act.dir == DIR::LEFT)
			{
				act.dirInver = true;
			}
		}
		else
		{
			act.atkFlag = false;
		}
	}
	//	PC”Å
	else
	{
		if (sp.getActionByTag(10))
		{
		}
		else if (std::get<0>(act.key[UseKey::K_LEFT]) && !std::get<1>(act.key[UseKey::K_LEFT]))
		{
			if (act.dir == DIR::RIGHT)
			{
				act.dirInver = true;
			}
		}
		else if (std::get<0>(act.key[UseKey::K_RIGHT]) && !std::get<1>(act.key[UseKey::K_RIGHT]))
		{
			if (act.dir == DIR::LEFT)
			{
				act.dirInver = true;
			}
		}
		else
		{
			act.atkFlag = false;
		}
	}
	return false;
}
