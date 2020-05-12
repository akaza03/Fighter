#include "unit/Character.h"
#include "Attack.h"

bool Attack::operator()(cocos2d::Sprite & sp, ActData & act)
{
	act.atkFlag = true;

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
	return false;
}
