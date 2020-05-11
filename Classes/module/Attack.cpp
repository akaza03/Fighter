#include "unit/Character.h"
#include "Attack.h"

bool Attack::operator()(cocos2d::Sprite & sp, ActData & act)
{
	if (std::get<0>(act.key[UseKey::K_SPACE]) && !std::get<1>(act.key[UseKey::K_SPACE]))
	{
		
	}
	return false;
}
